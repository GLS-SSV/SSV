#include "CRT_Interface.h"
#include "../SimpleGPCSystem.h"
#include "GeneralDisplays.h"
#include "SimpleFCOS_IO.h"


namespace dps
{
	constexpr double EXEC_RATE_DT = 0.48;// 2.083Hz

	constexpr unsigned short DEU_MSGBUF_BASE_ADDR = 6588;
	constexpr unsigned short DEU_DISPBUF_BASE_ADDR = 6638;

	constexpr unsigned short FCW_EOR = 0b00;
	constexpr unsigned short FCW_DATA1 = 0b01;
	constexpr unsigned short FCW_DATA2 = 0b10;
	constexpr unsigned short FCW_BASIC = 0b11;

	constexpr unsigned short DEU_MODE_SYMBOL = 0x0004;
	constexpr unsigned short DEU_MODE_ROTATE = 0x0008;
	constexpr unsigned short DEU_MODE_CIRCLE = 0x000C;
	constexpr unsigned short DEU_MODE_HIRES = 0x0010;
	constexpr unsigned short DEU_MODE_VECTOR = 0x0014;

	constexpr unsigned short DEU_FLASH_ON = 0x0040;
	constexpr unsigned short DEU_INTENSITY_ON = 0x0100;
	constexpr unsigned short DEU_DASHED = 0x0080;
	constexpr unsigned short DEU_LARGE = 0x0020;
	constexpr unsigned short DEU_MEDSCOLOR_ORANGE = 0x0200;


	constexpr short DCIBXC1 = 2;// OPS_Page_X_Coordinate [AU]
	constexpr short DCIBYC1 = 1;// OPS_Page_Y_Coordinate [AU]


	CRT_Interface::CRT_Interface( SimpleGPCSystem* pGPC, GeneralDisplays* pSystemDisplays, GeneralDisplays* pUserDisplays ):
		step(EXEC_RATE_DT), pGPC(pGPC), pSystemDisplays(pSystemDisplays), pUserDisplays(pUserDisplays),
		fcw_addr{DEU_DISPBUF_BASE_ADDR,DEU_DISPBUF_BASE_ADDR,DEU_DISPBUF_BASE_ADDR,DEU_DISPBUF_BASE_ADDR},
		mode(0), size(0), flash(0), dash(0), intensity(0), medsorange(0), rot(0.0)
	{
		return;
	}

	CRT_Interface::~CRT_Interface( void )
	{
		return;
	}

	void CRT_Interface::DMC_New_DISPLAY( const unsigned char deu, const unsigned short page )
	{
		unsigned short DK_CMDR_MASK = pGPC->ReadCOMPOOL_IS( SCP_DK_CMDR_MASK );
		if ((DK_CMDR_MASK & (1 << (deu - 1))) == 0) return;

		mode = 0;
		size = 0;
		flash = 0;
		dash = 0;
		intensity = 0;
		medsorange = 0;
		rot = 0.0;

		fcw_buf_cnt = 0;

		// set address to beginning of display buffer
		fcw_addr[deu - 1] = DEU_DISPBUF_BASE_ADDR;

		pSystemDisplays->PaintBackground( this, page );
		pUserDisplays->PaintBackground( this, page );

		// push EOR FCW
		fcw_buf[fcw_buf_cnt++] = FCW_EOR;

		SimpleFCOS_IO* IO = dynamic_cast<SimpleFCOS_IO*>(pGPC->pFCOS_IO);

		BUS_ID bus = BUS_DK1;
		if (deu == 2) bus = BUS_DK2;
		else if (deu == 3) bus = BUS_DK3;
		else if (deu == 4) bus = BUS_DK4;

		if (fcw_buf_cnt > 508)
		{
			// set up word count
			pGPC->WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, 1, 508, 511 );
			// set up addr
			pGPC->WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, 2, fcw_addr[deu - 1], 511 );

			// move buffer to DMC_DEU_BUF
			for (int i = 0; i < 508; i++) pGPC->WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, i + 3, fcw_buf[i], 511 );

			// output
			IO->OutputDK( DEU_MSGFIELDS_DISPLAY_FILL, SCP_DMC_DEU_BUF, 508 + 2/*count+addr*/, bus );



			// set up word count
			pGPC->WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, 1, fcw_buf_cnt - 508, 511 );
			// set up addr
			pGPC->WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, 2, fcw_addr[deu - 1] + 508, 511 );

			// move buffer to DMC_DEU_BUF
			for (int i = 0; i < fcw_buf_cnt - 508; i++) pGPC->WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, i + 3, fcw_buf[i], 511 );

			// output
			IO->OutputDK( DEU_MSGFIELDS_DISPLAY_FILL, SCP_DMC_DEU_BUF, fcw_buf_cnt - 508 + 2/*count+addr*/, bus );
		}
		else
		{
			// set up word count
			pGPC->WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, 1, fcw_buf_cnt, 511 );
			// set up addr
			pGPC->WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, 2, fcw_addr[deu - 1], 511 );

			// move buffer to DMC_DEU_BUF
			for (int i = 0; i < fcw_buf_cnt; i++) pGPC->WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, i + 3, fcw_buf[i], 511 );

			// output
			IO->OutputDK( DEU_MSGFIELDS_DISPLAY_FILL, SCP_DMC_DEU_BUF, fcw_buf_cnt + 2/*count+addr*/, bus );
		}

		fcw_addr[deu - 1] += fcw_buf_cnt - 1/*EOR*/;
		return;
	}

	void CRT_Interface::DCICYC( double simdt )
	{
		step += simdt;
		if (step < EXEC_RATE_DT) return;

		unsigned short DK_CMDR_MASK = pGPC->ReadCOMPOOL_IS( SCP_DK_CMDR_MASK );

		// run DEUs, check if commanding
		for (int deu = 1; deu <= 4; deu++)
		{
			if ((DK_CMDR_MASK & (1 << (deu - 1))) == 0) continue;

			//// (dynamic) display data
			mode = 0;
			size = 0;
			flash = 0;
			dash = 0;
			intensity = 0;
			medsorange = 0;
			rot = 0.0;

			fcw_buf_cnt = 0;

			DCIBHDR( deu );

			unsigned short page = pGPC->ReadCOMPOOL_AIS( SCP_CRT_DISP, deu, 4 );
			if (page == dps::MODE_UNDEFINED)
			{
				page = pGPC->ReadCOMPOOL_AIS( SCP_CRT_SPEC, deu, 4 );
				if (page == dps::MODE_UNDEFINED)
				{
					page = pGPC->ReadCOMPOOL_IS( SCP_MM );// TODO change format to (MM*100)+1
				}
			}

			pSystemDisplays->Paint( this, page );
			pUserDisplays->Paint( this, page );

			// push EOR FCW
			fcw_buf[fcw_buf_cnt++] = FCW_EOR;

			SimpleFCOS_IO* IO = dynamic_cast<SimpleFCOS_IO*>(pGPC->pFCOS_IO);

			BUS_ID bus = BUS_DK1;
			if (deu == 2) bus = BUS_DK2;
			else if (deu == 3) bus = BUS_DK3;
			else if (deu == 4) bus = BUS_DK4;

			if (fcw_buf_cnt > 508)
			{
				// set up word count
				pGPC->WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, 1, 508, 511 );
				// set up addr
				pGPC->WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, 2, fcw_addr[deu - 1], 511 );

				// move buffer to DMC_DEU_BUF
				for (int i = 0; i < 508; i++) pGPC->WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, i + 3, fcw_buf[i], 511 );

				// output
				IO->OutputDK( DEU_MSGFIELDS_DISPLAY_FILL, SCP_DMC_DEU_BUF, 508 + 2/*count+addr*/, bus );



				// set up word count
				pGPC->WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, 1, fcw_buf_cnt - 508, 511 );
				// set up addr
				pGPC->WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, 2, fcw_addr[deu - 1] + 508, 511 );

				// move buffer to DMC_DEU_BUF
				for (int i = 0; i < fcw_buf_cnt - 508; i++) pGPC->WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, i + 3, fcw_buf[i], 511 );

				// output
				IO->OutputDK( DEU_MSGFIELDS_DISPLAY_FILL, SCP_DMC_DEU_BUF, fcw_buf_cnt - 508 + 2/*count+addr*/, bus );
			}
			else
			{
				// set up word count
				pGPC->WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, 1, fcw_buf_cnt, 511 );
				// set up addr
				pGPC->WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, 2, fcw_addr[deu - 1], 511 );

				// move buffer to DMC_DEU_BUF
				for (int i = 0; i < fcw_buf_cnt; i++) pGPC->WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, i + 3, fcw_buf[i], 511 );

				// output
				IO->OutputDK( DEU_MSGFIELDS_DISPLAY_FILL, SCP_DMC_DEU_BUF, fcw_buf_cnt + 2/*count+addr*/, bus );
			}


			//// fault message
			mode = 0;
			size = 0;
			flash = 0;
			dash = 0;
			intensity = 0;
			medsorange = 0;
			rot = 0.0;

			fcw_buf_cnt = 0;

			unsigned int illegalentryfault = pGPC->ReadCOMPOOL_IS( SCP_ILLEGAL_ENTRY_FAULT );
			if (illegalentryfault & (1 << (deu - 1)))
			{
				TextGrid( 1, 25, "ILLEGAL ENTRY", DEUATT_MEDSORANGE | DEUATT_FLASHING );
			}
			else
			{
				unsigned int state = pGPC->ReadCOMPOOL_IS( SCP_FAULT_MSG_LINE_STATE );
				if (state != 0)
				{
					// assemble msg
					char tmp[64];
					char msg[64];
					memset( tmp, 0, 64 );
					pGPC->ReadCOMPOOL_C( SCP_FAULT_MSG_LINE, tmp, 43 );

					unsigned short ind = pGPC->ReadCOMPOOL_IS( SCP_FAULT_MSG_BUF_IND );
					if (ind != 0) sprintf_s( msg, 64, "%.30s      %s(%2hu)", tmp, tmp + 35, ind );
					else sprintf_s( msg, 64, "%.30s      %s", tmp, tmp + 35 );

					TextGrid( 1, 25, msg, DEUATT_MEDSORANGE | ((state == 1) ? DEUATT_FLASHING : DEUATT_NORMAL) );

					
				}
			}

			// push EOR FCW
			fcw_buf[fcw_buf_cnt++] = FCW_EOR;

			// set up word count
			pGPC->WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, 1, fcw_buf_cnt, 511 );
			// set up addr
			pGPC->WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, 2, DEU_MSGBUF_BASE_ADDR, 511 );

			// move buffer to DMC_DEU_BUF
			for (int i = 0; i < fcw_buf_cnt; i++) pGPC->WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, i + 3, fcw_buf[i], 511 );

			// output
			IO->OutputDK( DEU_MSGFIELDS_DISPLAY_FILL, SCP_DMC_DEU_BUF, fcw_buf_cnt + 2/*count+addr*/, bus );
		}

		step = 0.0;
		return;
	}

	void CRT_Interface::DCIBHDR( const unsigned char deu )
	{
		char cbuf[16];

		sprintf_s( cbuf, 16, "%03d1", pGPC->ReadCOMPOOL_IS( SCP_MM ) );

		unsigned short tmp = pGPC->ReadCOMPOOL_AIS( SCP_CRT_SPEC, deu, 4 );
		if (tmp != dps::MODE_UNDEFINED) sprintf_s( cbuf + strlen( cbuf ), 16 - strlen( cbuf ), "/%03d", tmp );
		else strcat_s( cbuf, "/   "  );

		tmp = pGPC->ReadCOMPOOL_AIS( SCP_CRT_DISP, deu, 4 );
		if (tmp != dps::MODE_UNDEFINED) sprintf_s( cbuf + strlen( cbuf ), 16 - strlen( cbuf ), "/%03d", tmp );
		else strcat_s( cbuf, "/"  );

		TextGrid( DCIBXC1, DCIBYC1, cbuf );


		// GPC_ID_X_Coordinate
		return;
	}

	void CRT_Interface::TextGrid( const unsigned short x, const unsigned short y, const char* text, const unsigned char attributes )
	{
		size_t len = strlen( text );
		if (len < 1)
		{
			oapiWriteLogV( "(SSV_OV) [ERROR] TextGrid empty (%d,%d)", x, y );
			return;
		}

		// save state of FCW component, if change -> new mode FCW
		bool update_fcwbasic = false;

		if (mode != DEU_MODE_SYMBOL)
		{
			mode = DEU_MODE_SYMBOL;
			update_fcwbasic = true;
		}

		if (attributes & DEUATT_FLASHING)
		{
			if (flash == 0)
			{
				flash = DEU_FLASH_ON;
				update_fcwbasic = true;
			}
		}
		else
		{
			if (flash == DEU_FLASH_ON)
			{
				flash = 0;
				update_fcwbasic = true;
			}
		}

		if (attributes & DEUATT_OVERBRIGHT)
		{
			if (intensity == 0)
			{
				intensity = DEU_INTENSITY_ON;
				update_fcwbasic = true;
			}
		}
		else
		{
			if (intensity == DEU_INTENSITY_ON)
			{
				intensity = 0;
				update_fcwbasic = true;
			}
		}

		if (attributes & DEUATT_LARGE)
		{
			if (size == 0)
			{
				size = DEU_LARGE;
				update_fcwbasic = true;
			}
		}
		else
		{
			if (size == DEU_LARGE)
			{
				size = 0;
				update_fcwbasic = true;
			}
		}

		if (attributes & DEUATT_MEDSORANGE)
		{
			if (medsorange == 0)
			{
				medsorange = DEU_MEDSCOLOR_ORANGE;
				update_fcwbasic = true;
			}
		}
		else
		{
			if (medsorange == DEU_MEDSCOLOR_ORANGE)
			{
				medsorange = 0;
				update_fcwbasic = true;
			}
		}

		if (update_fcwbasic)
		{
			fcw_buf[fcw_buf_cnt++] = medsorange | size | intensity | flash | mode | FCW_BASIC;
		}

		// position
		unsigned short posx = x << 2;
		unsigned short posy = y << 8;
		fcw_buf[fcw_buf_cnt++] = posy | posx | FCW_DATA1;

		for (size_t i = 0; i < len; i += 2)
		{
			unsigned short chr1 = ((text[i] & 0x7F) << 9);
			unsigned short chr2 = ((i + 1) <= len) ? ((text[i + 1] & 0x7F) << 2) : 0;
			fcw_buf[fcw_buf_cnt++] = chr1 | chr2 | FCW_DATA2;
		}
		return;
	}

	void CRT_Interface::Text( const short x, const short y, const char* text, const unsigned char attributes, const double angle )
	{
		size_t len = strlen( text );
		if (len < 1)
		{
			oapiWriteLogV( "(SSV_OV) [ERROR] Text empty (%d,%d)", x, y );
			return;
		}

		// update angle
		if (angle != rot)
		{
			// mode
			mode = DEU_MODE_ROTATE;

			fcw_buf[fcw_buf_cnt++] = size | intensity | flash | mode | FCW_BASIC;


			// angle
			double cosrot = cos( angle * RAD );
			double sinrot = sin( angle * RAD );

			short icosrot = static_cast<short>(fabs( cosrot ) * 31);
			short isinrot = static_cast<short>(fabs( sinrot ) * 31);

			if (cosrot < 0.0) icosrot |= 0b100000;
			if (sinrot < 0.0) isinrot |= 0b100000;

			fcw_buf[fcw_buf_cnt++] = (icosrot << 2) | (isinrot << 8) | FCW_DATA1;

			rot = angle;
		}

		// save state of FCW component, if change -> new mode FCW
		bool update_fcwbasic = false;

		if (mode != DEU_MODE_HIRES)
		{
			mode = DEU_MODE_HIRES;
			update_fcwbasic = true;
		}

		if (attributes & DEUATT_FLASHING)
		{
			if (flash == 0)
			{
				flash = DEU_FLASH_ON;
				update_fcwbasic = true;
			}
		}
		else
		{
			if (flash == DEU_FLASH_ON)
			{
				flash = 0;
				update_fcwbasic = true;
			}
		}

		if (attributes & DEUATT_OVERBRIGHT)
		{
			if (intensity == 0)
			{
				intensity = DEU_INTENSITY_ON;
				update_fcwbasic = true;
			}
		}
		else
		{
			if (intensity == DEU_INTENSITY_ON)
			{
				intensity = 0;
				update_fcwbasic = true;
			}
		}

		if (attributes & DEUATT_LARGE)
		{
			if (size == 0)
			{
				size = DEU_LARGE;
				update_fcwbasic = true;
			}
		}
		else
		{
			if (size == DEU_LARGE)
			{
				size = 0;
				update_fcwbasic = true;
			}
		}

		if (update_fcwbasic)
		{
			fcw_buf[fcw_buf_cnt++] = size | intensity | flash | mode | FCW_BASIC;
		}

		// position
		unsigned short posx = abs( x ) << 2;
		if (x < 0) posx |= 0x1000;
		fcw_buf[fcw_buf_cnt++] = posx | FCW_DATA1;

		unsigned short posy = abs( y ) << 2;
		if (y < 0) posy |= 0x1000;
		fcw_buf[fcw_buf_cnt++] = posy | FCW_DATA1;

		for (size_t i = 0; i < len; i += 2)
		{
			unsigned short chr1 = ((text[i] & 0x7F) << 9);
			unsigned short chr2 = ((i + 1) <= len) ? ((text[i + 1] & 0x7F) << 2) : 0;
			fcw_buf[fcw_buf_cnt++] = chr1 | chr2 | FCW_DATA2;
		}
		return;
	}

	void CRT_Interface::NumberGrid( const unsigned short x, const unsigned short y, const double num, const unsigned short size_i, const unsigned short size_f, const unsigned char attributes )
	{
		double lnum = min(fabs( num ), pow( 10, size_i ) - (1.0 / pow( 10, size_f )));

		double intg;
		double frac = modf( lnum, &intg );
		frac *= pow( 10, size_f );

		char cbuf[64];
		if (size_i > 0)
		{
			sprintf_s( cbuf, 64, "%*d", size_i, static_cast<int>(intg) );
			TextGrid( x, y, cbuf, attributes );
		}

		if (size_f > 0)
		{
			sprintf_s( cbuf, 64, ".%0*d", size_f, static_cast<int>(frac) );
			TextGrid( x + size_i, y, cbuf, attributes );
		}
		return;
	}

	void CRT_Interface::NumberSignGrid( const unsigned short x, const unsigned short y, const double num, const unsigned short size_i, const unsigned short size_f, const char plus, const char minus, const unsigned char attributes )
	{
		double lnum = min(fabs( num ), pow( 10, size_i ) - (1.0 / pow( 10, size_f )));

		double intg;
		double frac = modf( lnum, &intg );
		frac *= pow( 10, size_f );

		char cbuf[64];
		// sign
		if (num != 0.0)
		{
			char sign;
			if (num > 0.0) sign = plus;
			else /*if (num < 0.0)*/ sign = minus;

			sprintf_s( cbuf, 64, "%c", sign );
			TextGrid( x, y, cbuf, attributes );
		}

		if (size_i > 0)
		{
			sprintf_s( cbuf, 64, "%*d", size_i, static_cast<int>(intg) );
			TextGrid( x + 1/*sign*/, y, cbuf, attributes );
		}

		if (size_f > 0)
		{
			sprintf_s( cbuf, 64, ".%0*d", size_f, static_cast<int>(frac) );
			TextGrid( x + 1/*sign*/ + size_i, y, cbuf, attributes );
		}
		return;
	}

	void CRT_Interface::NumberGrid( const unsigned short x, const unsigned short y, const int num, const unsigned short size, const unsigned char attributes )
	{
		// limit value
		int lnum = min(abs( num ), static_cast<int>(pow( 10, size )) - 1);

		char cbuf[64];
		sprintf_s( cbuf, "%*d", size, lnum );

		TextGrid( x, y, cbuf, attributes );
		return;
	}

	void CRT_Interface::NumberSignGrid( const unsigned short x, const unsigned short y, const int num, const unsigned short size, const char plus, const char minus, const unsigned char attributes )
	{
		// limit value
		int lnum = min(abs( num ), static_cast<int>(pow( 10, size )) - 1);

		// sign char
		char sign = ' ';
		if (num > 0) sign = plus;
		else if (num < 0) sign = minus;

		char cbuf[64];
		sprintf_s( cbuf, "%c%*d", sign, size, lnum );

		TextGrid( x, y, cbuf, attributes );
		return;
	}

	void CRT_Interface::Line( const short x1, const short y1, const short x2, const short y2, const unsigned char attributes )
	{
		// save state of FCW component, if change -> new mode FCW
		bool update_fcwbasic = false;

		if (mode != DEU_MODE_VECTOR)
		{
			mode = DEU_MODE_VECTOR;
			update_fcwbasic = true;
		}

		if (attributes & DEUATT_FLASHING)
		{
			if (flash == 0)
			{
				flash = DEU_FLASH_ON;
				update_fcwbasic = true;
			}
		}
		else
		{
			if (flash == DEU_FLASH_ON)
			{
				flash = 0;
				update_fcwbasic = true;
			}
		}

		if (attributes & DEUATT_OVERBRIGHT)
		{
			if (intensity == 0)
			{
				intensity = DEU_INTENSITY_ON;
				update_fcwbasic = true;
			}
		}
		else
		{
			if (intensity == DEU_INTENSITY_ON)
			{
				intensity = 0;
				update_fcwbasic = true;
			}
		}

		if (attributes & DEUATT_DASHED)
		{
			if (dash == 0)
			{
				dash = DEU_DASHED;
				update_fcwbasic = true;
			}
		}
		else
		{
			if (dash == DEU_DASHED)
			{
				dash = 0;
				update_fcwbasic = true;
			}
		}

		if (update_fcwbasic)
		{
			fcw_buf[fcw_buf_cnt++] = intensity | flash | dash | mode | FCW_BASIC;
		}

		// coords
		unsigned short posx1 = abs( x1 ) << 2;
		if (x1 < 0) posx1 |= 0x1000;
		fcw_buf[fcw_buf_cnt++] = posx1 | FCW_DATA1;

		unsigned short posy1 = abs( y1 ) << 2;
		if (y1 < 0) posy1 |= 0x1000;
		fcw_buf[fcw_buf_cnt++] = posy1 | FCW_DATA1;

		unsigned short posx2 = abs( x2 ) << 2;
		if (x2 < 0) posx2 |= 0x1000;
		fcw_buf[fcw_buf_cnt++] = posx2 | FCW_DATA2;

		unsigned short posy2 = abs( y2 ) << 2;
		if (y2 < 0) posy2 |= 0x1000;
		fcw_buf[fcw_buf_cnt++] = posy2 | FCW_DATA2;
		return;
	}

	void CRT_Interface::Circle( const short x, const short y, const unsigned short radius, const unsigned char attributes )
	{
		// save state of FCW component, if change -> new mode FCW
		bool update_fcwbasic = false;

		if (mode != DEU_MODE_CIRCLE)
		{
			mode = DEU_MODE_CIRCLE;
			update_fcwbasic = true;
		}

		if (attributes & DEUATT_FLASHING)
		{
			if (flash == 0)
			{
				flash = DEU_FLASH_ON;
				update_fcwbasic = true;
			}
		}
		else
		{
			if (flash == DEU_FLASH_ON)
			{
				flash = 0;
				update_fcwbasic = true;
			}
		}

		if (attributes & DEUATT_OVERBRIGHT)
		{
			if (intensity == 0)
			{
				intensity = DEU_INTENSITY_ON;
				update_fcwbasic = true;
			}
		}
		else
		{
			if (intensity == DEU_INTENSITY_ON)
			{
				intensity = 0;
				update_fcwbasic = true;
			}
		}

		if (attributes & DEUATT_DASHED)
		{
			if (dash == 0)
			{
				dash = DEU_DASHED;
				update_fcwbasic = true;
			}
		}
		else
		{
			if (dash == DEU_DASHED)
			{
				dash = 0;
				update_fcwbasic = true;
			}
		}

		if (update_fcwbasic)
		{
			fcw_buf[fcw_buf_cnt++] = intensity | flash | dash | mode | FCW_BASIC;
		}

		// position
		unsigned short posx = abs( x ) << 2;
		if (x < 0) posx |= 0x1000;
		fcw_buf[fcw_buf_cnt++] = posx | FCW_DATA1;

		unsigned short posy = abs( y ) << 2;
		if (y < 0) posy |= 0x1000;
		fcw_buf[fcw_buf_cnt++] = posy | FCW_DATA1;

		// radius
		unsigned short r = radius << 2;
		fcw_buf[fcw_buf_cnt++] = r | FCW_DATA2;
		return;
	}
}
