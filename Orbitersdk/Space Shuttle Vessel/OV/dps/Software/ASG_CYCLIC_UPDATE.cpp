#include "ASG_CYCLIC_UPDATE.h"
#include "../../Atlantis.h"


namespace dps
{
	ASG_CYCLIC_UPDATE::ASG_CYCLIC_UPDATE( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "ASG_CYCLIC_UPDATE" ),
		timer1ena(false),timer2ena(false),timer1before(false),timer2before(false)
	{
		return;
	}

	ASG_CYCLIC_UPDATE::~ASG_CYCLIC_UPDATE( void )
	{
		return;
	}

	bool ASG_CYCLIC_UPDATE::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void ASG_CYCLIC_UPDATE::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	void ASG_CYCLIC_UPDATE::OnPreStep( double simt, double simdt, double mjd )
	{
		if (timer1ena)
		{
			// check time (24h clock)
			int alarmt = (((ReadCOMPOOL_AIS( SCP_CAAV_TM_ITEM_I, 3, 23 ) * 60) + ReadCOMPOOL_AIS( SCP_CAAV_TM_ITEM_I, 4, 23 )) * 60) + ReadCOMPOOL_AIS( SCP_CAAV_TM_ITEM_I, 5, 23 );// time from midnight [sec]
			int mt = static_cast<int>(STS()->GetMET()) % 86400;// time from midnight [sec]

			if ((mt >= alarmt) && (timer1before == true))
			{
				const char* CRTMSG_TIMETONE = "    TIME       TONE";
				unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
				if (j < 5)
				{
					WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_TIMETONE, 5, 19 );
					WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 3, 5 );
					WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
				}

				timer1ena = false;
				timer1before = false;
			}
			else if (mt <= alarmt) timer1before = true;
		}
		if (timer2ena)
		{
			// check time (24h clock)
			int alarmt = (((ReadCOMPOOL_AIS( SCP_CAAV_TM_ITEM_I, 6, 23 ) * 60) + ReadCOMPOOL_AIS( SCP_CAAV_TM_ITEM_I, 7, 23 )) * 60) + ReadCOMPOOL_AIS( SCP_CAAV_TM_ITEM_I, 8, 23 );// time from midnight [sec]
			int mt = static_cast<int>(STS()->GetMET()) % 86400;// time from midnight [sec]

			if ((mt >= alarmt) && (timer2before == true))
			{
				const char* CRTMSG_TIMETONE = "    TIME       TONE";
				unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
				if (j < 5)
				{
					WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_TIMETONE, 5, 19 );
					WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 3, 5 );
					WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
				}

				timer2ena = false;
				timer2before = false;
			}
			else if (mt <= alarmt) timer2before = true;
		}
		return;
	}
}
