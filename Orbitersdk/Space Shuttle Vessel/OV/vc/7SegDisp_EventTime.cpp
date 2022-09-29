/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/08/24   GLS
2021/12/30   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "7SegDisp_EventTime.h"
#include "../Atlantis.h"


namespace vc
{
	_7SegDisp_EventTime::_7SegDisp_EventTime( Atlantis* _sts, const std::string& _ident ):_7SegDisp( _sts, _ident )
	{
		time = 0;
		clk = 0.0;

		start = false;
		up = false;
		forceup = false;
		forceup_set = false;
		old_start = false;
		old_AbortReset = false;
		old_LiftoffStart = false;
	}

	_7SegDisp_EventTime::~_7SegDisp_EventTime()
	{
	}

	bool _7SegDisp_EventTime::OnParseLine( const char* line )
	{
		double fTmp = 0.0;
		short sTmp1 = 0;
		short sTmp2 = 0;
		short sTmp3 = 0;

		sscanf_s( line, "%hd %lf %hd %hd", &sTmp1, &fTmp, &sTmp2, &sTmp3 );

		if ((sTmp1 >= 0) && (sTmp1 < 3600)) time = sTmp1;
		if ((fTmp >= 0.0) && (fTmp < 1.0)) clk = fTmp;
		start = (sTmp2 != 0);
		old_start = start;
		up = (sTmp3 != 0);
		return true;
	}

	bool _7SegDisp_EventTime::GetStateString( unsigned long ulBufferSize, char* pszBuffer )
	{
		sprintf_s( pszBuffer, ulBufferSize, "%d %f %d %d", time, clk, start, up );
		return true;
	}

	void _7SegDisp_EventTime::Controller( void )
	{
		//// implementation of event timer logic ////

		// input
		bool Mode_Down = !(Mode_Up.IsSet() || Mode_Test.IsSet());

		bool abortliftoffup = AbortReset.IsSet() || LiftoffStart.IsSet();
		bool AbortReset_re = !old_AbortReset && AbortReset.IsSet();
		old_AbortReset = AbortReset.IsSet();
		bool LiftoffStart_re = !old_LiftoffStart && (LiftoffStart.IsSet() && !AbortReset.IsSet());
		old_LiftoffStart = LiftoffStart.IsSet() && !AbortReset.IsSet();
		bool abortliftoffreset = AbortReset_re || LiftoffStart_re || (Control_Stop.IsSet() && abortliftoffup);

		start = (!(Control_Stop.IsSet() || Timer_Set.IsSet() || Timer_Reset.IsSet()) && start) || ((Control_Start.IsSet() || abortliftoffup) && !(Control_Stop.IsSet() || Timer_Set.IsSet() || Timer_Reset.IsSet()));
		bool start_re = !old_start && start;
		old_start = start;

		forceup = (!(Timer_Reset.IsSet() || start_re) && forceup) || (forceup_set && !(Timer_Reset.IsSet() || start_re));
		forceup_set = false;

		up = (!(Mode_Down && start_re && !forceup && !abortliftoffup) && up) || ((abortliftoffup || start_re || Mode_Up.IsSet() || forceup) && !(Mode_Down && start_re && !forceup && !abortliftoffup));

		// run timer
		if (Timer_Reset.IsSet() || abortliftoffreset)
		{
			time = 0;
			clk = 0.0;
		}
		else if (Timer_Set.IsSet())
		{
			time = (int)Minutes_1.IsSet() + (2 * (int)Minutes_2.IsSet()) + (4 * (int)Minutes_4.IsSet()) + (8 * (int)Minutes_8.IsSet()) +
				(10 * (int)Minutes_10.IsSet()) + (20 * (int)Minutes_20.IsSet()) + (40 * (int)Minutes_40.IsSet());
			time *= 60;
			time += (int)Seconds_1.IsSet() + (2 * (int)Seconds_2.IsSet()) + (4 * (int)Seconds_4.IsSet()) + (8 * (int)Seconds_8.IsSet()) +
				(10 * (int)Seconds_10.IsSet()) + (20 * (int)Seconds_20.IsSet()) + (40 * (int)Seconds_40.IsSet());
		}
		else if (start)
		{
			clk += oapiGetSimStep();
			int dt = static_cast<int>(clk);
			clk -= dt;

			if (up)
			{
				time += dt;
				if (time >= 3600) time -= 3600;// overflow at 60mins
			}
			else
			{
				time -= dt;
				if (time <= 0)// reached 0, now count up
				{
					time = -time;
					forceup_set = true;
				}
			}
		}
		else clk = 0.0;

		// output
		if (Mode_Test.IsSet())
		{
			next_state[3] = 8;
			next_state[2] = 8;
			next_state[1] = 8;
			next_state[0] = 8;
			return;
		}

		short sTimerMinutes = time / 60;
		short sTimerSeconds = time % 60;

		next_state[3] = sTimerMinutes / 10;
		next_state[2] = sTimerMinutes % 10;
		next_state[1] = sTimerSeconds / 10;
		next_state[0] = sTimerSeconds % 10;
		return;
	}
}
