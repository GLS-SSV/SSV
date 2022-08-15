/****************************************************************************
  This file is part of Space Shuttle Vessel

  SSV Sound definition


  Space Shuttle Vessel is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Vessel is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Vessel; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file SSV-LICENSE.txt for more details.

  **************************************************************************/
/******* SSV File Modification Notice *******
Date         Developer
2020/05/01   GLS
2020/05/07   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/24   GLS
2021/12/30   GLS
********************************************/
#ifndef __SSVSOUND_H
#define __SSVSOUND_H


#include <OrbiterSoundSDK40.h>


const static char* SOUND_DIRECTORY = "Sound\\_CustomVesselsSounds\\SSV\\";

// Atlantis
const static char* AIR_CONDITIONING_SOUND_FILE = "Orbiter_AC.wav";

inline constexpr int RCS_SOUND = 1;
const static char* RCS_SOUND_FILE = "RCS_Jet_Fire.wav";

inline constexpr int APU_1_START = 2;
inline constexpr int APU_2_START = 3;
inline constexpr int APU_3_START = 4;
const static char* APU_START_FILE = "APU_start_up.wav";

inline constexpr int APU_1_RUNNING = 5;
inline constexpr int APU_2_RUNNING = 6;
inline constexpr int APU_3_RUNNING = 7;
const static char* APU_RUNNING_FILE = "APU_continues.wav";

inline constexpr int APU_1_SHUTDOWN = 8;
inline constexpr int APU_2_SHUTDOWN = 9;
inline constexpr int APU_3_SHUTDOWN = 10;
const static char* APU_SHUTDOWN_FILE = "APU_shut_down.wav";

inline constexpr int SSME_START = 11;
const static char* SSME_START_FILE = "SSME_ignition.wav";

inline constexpr int SSME_RUNNING = 12;
const static char* SSME_RUNNING_FILE = "SSME_sustain.wav";

inline constexpr int SSME_SHUTDOWN = 13;
const static char* SSME_SHUTDOWN_FILE = "SSME_shutdown.wav";

inline constexpr int SWITCH_GUARD_SOUND = 14;
const static char* SWITCH_GUARD_FILE = "switch_guard.wav";

inline constexpr int SWITCH_THROW_SOUND = 15;
const static char* SWITCH_THROW_FILE = "switch_throw.wav";

inline constexpr int KEY_PRESS_SOUND = 16;
const static char* KEY_PRESS_FILE = "key_press.wav";

inline constexpr int TB_OFF_SOUND = 17;
const static char* TB_OFF_FILE = "talkback_off.wav";

inline constexpr int TB_ON_SOUND = 18;
const static char* TB_ON_FILE = "talkback_on.wav";

inline constexpr int CW_TONE_SOUND = 19;
inline constexpr int CW_TONE_RMS_SOUND = 20;// 2 IDs as there are 2 separate sources
const static char* CW_TONE_FILE = "cw_tone.wav";

inline constexpr int CB_SOUND = 21;
const static char* CB_FILE = "circuit_breaker.wav";

// SSV_LC39 and SSV_SLC6
inline constexpr int RSS_ROTATE_SOUND = 1;
static const char* RSS_ROTATE_SOUND_FILE = "RSS_Rotation.wav";
inline constexpr int CRYO_HISS = 2;
static const char* CRYO_HISS_SOUND_FILE = "Cryo_noise.wav";

// Crawler
inline constexpr int ENGINE_SOUND_ID = 1;
static const char* ENGINE_SOUND_FILE = "CrawlerEngine.wav";
inline constexpr int ENGINE_START_SOUND_ID = 2;
static const char* ENGINE_START_SOUND_FILE = "CrawlerEngine_startup.wav";
inline constexpr int ENGINE_STOP_SOUND_ID = 3;
static const char* ENGINE_STOP_SOUND_FILE = "CrawlerEngine_shutdown.wav";


#endif //__SSVSOUND_H
