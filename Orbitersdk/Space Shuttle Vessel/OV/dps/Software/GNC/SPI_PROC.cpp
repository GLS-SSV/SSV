#include "SPI_PROC.h"
#include <MathSSV.h>


namespace dps
{
	// K-Loads
	constexpr float DBFMAX = 22.55f;// MAXIMUM VALUE OF BODY FLAP POS (V97U6751C) [deg]
	constexpr float DBFMIN = -11.71f;// MINIMUM VALUE OF BODY FLAP POS (V97U6752C) [deg]


	SPI_PROC::SPI_PROC( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "SPI_PROC" )
	{
		return;
	}

	SPI_PROC::~SPI_PROC( void )
	{
		return;
	}

	void SPI_PROC::OnPostStep( double simt, double simdt, double mjd )
	{
		// inputs
		unsigned short MM = ReadCOMPOOL_IS( SCP_MM );
		float DELOBOFB = ReadCOMPOOL_SS( SCP_LOB_ELVN_POS_FDBK );// TODO
		float DELIBOFB = ReadCOMPOOL_SS( SCP_LIB_ELVN_POS_FDBK );// TODO
		float DERIBOFB = ReadCOMPOOL_SS( SCP_RIB_ELVN_POS_FDBK );// TODO
		float DEROBOFB = ReadCOMPOOL_SS( SCP_ROB_ELVN_POS_FDBK );// TODO
		float DROFB = ReadCOMPOOL_SS( SCP_DRFB );// TODO
		float DSB_ENT_SCHED = 0.0f;// TODO
		float DSBC_AT = ReadCOMPOOL_SS( SCP_DSBC_AT );
		float DSBC_AL = ReadCOMPOOL_SS( SCP_DSBC_AL );
		unsigned short TG_END = ReadCOMPOOL_IS( SCP_TG_END );
		float DSBOFB = ReadCOMPOOL_SS( SCP_DSBFB_DEG );// TODO
		float DBFOFB = ReadCOMPOOL_SS( SCP_DBFOFB );// TODO

		// outputs
		unsigned short SPIELOB = 0;
		unsigned short SPIELIB = 0;
		unsigned short SPIERIB = 0;
		unsigned short SPIEROB = 0;
		unsigned short SPIRP = 0;
		unsigned short SPISBP = 0;
		unsigned short SPISBC = 0;
		unsigned short HUD_SPBRK_POS = 0;
		unsigned short HUD_SPBRK_CMD = 0;
		unsigned short BFP_CRT = 0;
		unsigned short SPIBFP = 0;
		unsigned short HUD_AIL_POS = 0;
		unsigned short SPIAP = 0;

		// Elevon Position 160 ms
		const float EL_CONV_C = 9.091f;// [cts/deg]
		const float EL_BIAS_C = 318.185f;// [cts]
		SPIELOB = 64 * static_cast<unsigned short>((EL_CONV_C * range( -35.0, DELOBOFB, 20.0 )) + EL_BIAS_C);
		SPIELIB = 64 * static_cast<unsigned short>((EL_CONV_C * range( -35.0, DELIBOFB, 20.0 )) + EL_BIAS_C);
		SPIERIB = 64 * static_cast<unsigned short>((EL_CONV_C * range( -35.0, DERIBOFB, 20.0 )) + EL_BIAS_C);
		SPIEROB = 64 * static_cast<unsigned short>((EL_CONV_C * range( -35.0, DEROBOFB, 20.0 )) + EL_BIAS_C);

		// Rudder Position 160 ms
		const float R_CONV_C = -8.333f;// [cts/deg]
		const float R_BIAS_C = 249.9f;// [cts]
		SPIRP = 64 * static_cast<unsigned short>((-R_CONV_C * range( -30.0, DROFB, 30.0 )) + R_BIAS_C);

		// Speedbrake Position and Command 160 ms
		//const float SB_CONV_C = 5.0f;// [cts/pct]
		float SBC;
		if ((MM == 301) || (MM == 302) || (MM == 303) || (MM == 601))
		{
			SBC = 0.0f;
		}
		else if (MM == 304)
		{
			SBC = DSB_ENT_SCHED;
		}
		else if (((MM == 305) || (MM == 602) || (MM == 603)) && (TG_END == 0))
		{
			SBC = DSBC_AT;
		}
		else// TG_END = 1
		{
			SBC = DSBC_AL;
		}
		SPISBP = 64 * static_cast<unsigned short>(500 * range( 0.0, DSBOFB, 98.6 ) / 98.6);
		SPISBC = 64 * static_cast<unsigned short>(500 * range( 0.0, SBC, 98.6 ) / 98.6);
		HUD_SPBRK_POS = static_cast<unsigned short>(range( 0.0, DSBOFB, 98.6 ));
		HUD_SPBRK_CMD = static_cast<unsigned short>(range( 0.0, SBC, 98.6 ));

		// Body Flap Position 160 ms
		const float BF_CONV_C = 5.0f;// [cts/pct]
		BFP_CRT = static_cast<unsigned short>(100 * (range( DBFMIN, DBFOFB, DBFMAX ) - DBFMIN) / (DBFMAX - DBFMIN));
		SPIBFP = 64 * static_cast<unsigned short>(BF_CONV_C * BFP_CRT);

		// Aileron Position 160 ms
		const float A_CONV_C = 50.0f;// [cts/deg]
		const float A_BIAS_C = 250.0f;// [cts]
		float DAILERON = (DELIBOFB + DELOBOFB - DERIBOFB - DEROBOFB) / 4;
		if (DAILERON < -5.0f)
		{
			DAILERON = -5.0f;
		}
		else if (DAILERON > 5.0)
		{
			DAILERON = 5.0;
		}
		HUD_AIL_POS = static_cast<unsigned short>(100 * DAILERON);
		SPIAP = 64 * static_cast<unsigned short>((A_CONV_C * DAILERON) + A_BIAS_C);


		// output
		// Left Outboard Elevon Position
		WriteCOMPOOL_IS( SCP_FF1_IOM8_CH11_DATA, SPIELOB  );
		// Left Inboard Elevon Position
		WriteCOMPOOL_IS( SCP_FF1_IOM8_CH10_DATA, SPIELIB  );
		// Right Inboard Elevon Position
		WriteCOMPOOL_IS( SCP_FF1_IOM8_CH12_DATA, SPIERIB  );
		// Right Outboard Elevon Position
		WriteCOMPOOL_IS( SCP_FF1_IOM8_CH13_DATA, SPIEROB  );
		// Rudder Position
		WriteCOMPOOL_IS( SCP_FF1_IOM8_CH8_DATA, SPIRP  );
		// Speed Brake Position
		WriteCOMPOOL_IS( SCP_FF1_IOM8_CH9_DATA, SPISBP  );
		// Speed Brake Command
		WriteCOMPOOL_IS( SCP_FF1_IOM8_CH7_DATA, SPISBC  );
		// Body Flap Position
		WriteCOMPOOL_IS( SCP_FF2_IOM8_CH8_DATA, SPIBFP  );
		// Aileron Position
		WriteCOMPOOL_IS( SCP_FF2_IOM8_CH9_DATA, SPIAP );
		// Valid Flag
		WriteCOMPOOL_IS( SCP_FF1_IOM13_CH0_DATA, 1 );

		// HUD
		WriteCOMPOOL_IS( SCP_HUD_SPBRK_POS, HUD_SPBRK_POS );
		WriteCOMPOOL_IS( SCP_HUD_SPBRK_CMD, HUD_SPBRK_CMD );
		WriteCOMPOOL_IS( SCP_HUD_AIL_POS, HUD_AIL_POS );

		// CRT
		// TODO BFP_CRT
		return;
	}

	bool SPI_PROC::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 301:
			case 302:
			case 303:
			case 304:
			case 305:
			case 601:
			case 602:
			case 603:
				return true;
			default:
				return false;
		}
	}
}
