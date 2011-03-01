/*
    Yelo: Open Sauce SDK
		Halo 1 (CE) Edition
    Copyright (C) 2005-2010  Kornner Studios (http://kornner.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

ENGINE_PTR(void*, gather_exception_data,	0x6BDEAC, 0x626524);
FUNC_PTR(GATHER_EXCEPTION,					0x582780, 0x52AEB0);

FUNC_PTR(TEXTURE_CACHE_TEXTURE_REQUEST,		0x445080, FUNC_PTR_NULL);
FUNC_PTR(SOUND_CACHE_SOUND_REQUEST,			0x444940, FUNC_PTR_NULL);

//////////////////////////////////////////////////////////////////////////
// Console
FUNC_PTR(CONSOLE_PROCESS_COMMAND,	0x4C9F40, 0x4B3990); // also in Console.cpp
FUNC_PTR(CONSOLE_TERMINAL_PRINTF,	0x4C9D40, 0x48ED70);
FUNC_PTR(CONSOLE_PRINTF,			0x4C9DE0, 0x4B3790);
FUNC_PTR(CONSOLE_WARNING,			0x4C9EA0, 0x4B38F0);

//////////////////////////////////////////////////////////////////////////
// Cheats
FUNC_PTR(CHEAT_ALL_WEAPONS,						0x45B0B0, 0x457B10);
FUNC_PTR(CHEAT_SPAWN_WARTHOG,					0x45B140, 0x457BA0);
FUNC_PTR(CHEAT_TELEPORT_TO_CAMERA,				0x45B1B0, 0x457C10);
FUNC_PTR(CHEAT_ACTIVE_CAMOFLAGE,				0x45B240, 0x457CA0);
FUNC_PTR(CHEAT_ACTIVE_CAMOFLAGE_LOCAL_PLAYER,	0x45B2A0, 0x457D00);
FUNC_PTR(CHEAT_PLAYER_INDEX,					0x45B320, 0x457D80);
FUNC_PTR(DIRECTOR_SAVE_CAMERA,					0x4463B0, FUNC_PTR_NULL);
FUNC_PTR(DIRECTOR_LOAD_CAMERA,					0x446470, FUNC_PTR_NULL);

//////////////////////////////////////////////////////////////////////////
// Game
FUNC_PTR(SCENARIO_SWITCH_STRUCTURE_BSP,		0x542610, 0x4FD320);
FUNC_PTR(BINK_PLAYBACK_START,				0x43ED20, FUNC_PTR_NULL);
FUNC_PTR(GAME_ENGINE_RASTERIZE_MESSAGE,		0x462C90, FUNC_PTR_NULL);
FUNC_PTR(GAME_TEAM_IS_ENEMY,				0x45C8D0, 0x459280);
FUNC_PTR(GAME_ENGINE_PLAY_MULTIPLAYER_SOUND,0x46EC70, FUNC_PTR_NULL);

//////////////////////////////////////////////////////////////////////////
// HS
FUNC_PTR(OBJECT_LIST_ADD,					0x48E000, 0x4858E0);

//////////////////////////////////////////////////////////////////////////
// Input
FUNC_PTR(INPUT_KEY_IS_DOWN, 0x493AD0, FUNC_PTR_NULL);

//////////////////////////////////////////////////////////////////////////
// Interface
FUNC_PTR(KEYSTONE_CHAT_LOG_ADD_STRING,	0x4AEAD0, FUNC_PTR_NULL); // I forget if the dedicated has a chat log equivalent...
FUNC_PTR(HUD_PRINT_MESSAGE,				0x4B1790, 0x4A0240);
FUNC_PTR(HUD_GET_ITEM_MESSAGE,			0x4AD630, 0x49F340);

//////////////////////////////////////////////////////////////////////////
// Math
FUNC_PTR(PERIODIC_FUNCTION_EVALUATE,	0x4CFEF0, 0x4B8F60);
FUNC_PTR(TRANSITION_FUNCTION_EVALUATE,	0x4D0000, 0x4B9070);

//////////////////////////////////////////////////////////////////////////
// Memory
FUNC_PTR(DATUM_NEW_AT_INDEX,0x4D3910, 0x4BC880);
FUNC_PTR(DATUM_NEW,			0x4D39C0, 0x4BC930);
FUNC_PTR(DATUM_DELETE,		0x4D3A50, 0x4BC9C0);
FUNC_PTR(DATA_ITERATOR_NEXT,0x4D3B10, 0x4BCA80);
FUNC_PTR(DATUM_NEXT_INDEX,	0x4D3B70, 0x4BCAE0);
FUNC_PTR(DATUM_GET,			0x4D3BC0, 0x4BCB30);
FUNC_PTR(DATUM_INITIALIZE,	0x4D3C00, 0x4BCB70);

//////////////////////////////////////////////////////////////////////////
// Networking
FUNC_PTR(MDP_ENCODE_OBJECT_DELETION_MESSAGE,			0x4F9730, 0x4E0720);
FUNC_PTR(ENCODE_HUD_CHAT_NETWORK_DATA,					0x4ADF70, 0x49F740);
FUNC_PTR(MDP_TRANSLATED_INDEX_TRANSLATE,				0x4F4270, 0x4DD4D0);
DATA_PTR(MESSAGE_DELTA_FIELD_OBJECT_INDEX_PARAMETERS,	0x6226F0, 0x5980A8);
DATA_PTR(MESSAGE_DELTA_FIELD_PLAYER_INDEX_PARAMETERS,	0x622B18, 0x5984D0);

//////////////////////////////////////////////////////////////////////////
// Objects
FUNC_PTR(OBJECT_PLACEMENT_DATA_NEW,		0x4F9030, 0x4E0020);
FUNC_PTR(OBJECT_NEW_NETWORK,			0x4F90F0, 0x4E00E0);
FUNC_PTR(OBJECT_NEW,					0x4F9140, 0x4E0130);
FUNC_PTR(OBJECT_START_INTERPOLATION,	0x4FA800, 0x4E1750); // Until PY's netcode is finalized, this function don't mean shit (read: doesn't sync)
FUNC_PTR(OBJECT_RESET,					0x4F8DF0, 0x4DFDE0);
FUNC_PTR(OBJECT_RECONNECT_TO_MAP,		0x4F98C0, 0x4E08B0);
FUNC_PTR(OBJECT_DISCONNECT_FROM_MAP,	0x4F9A70, 0x4E0A60);
FUNC_PTR(OBJECT_GET_ORIGIN,				0x4FA590, 0x4E14E0);
FUNC_PTR(OBJECT_GET_ORIENTATION,		0x4FA600, 0x4E1550);
FUNC_PTR(OBJECT_GET_LOCATION,			0x4FA7A0, 0x4E16F0);
FUNC_PTR(OBJECT_SET_POSITION,			0x4F8E50, 0x4DFE40);
FUNC_PTR(OBJECT_SET_POSITION_NETWORK,	0x4F8F50, 0x4DFF40);
FUNC_PTR(OBJECT_RESTORE_BODY,			0x4F1660, 0x4DA8C0);
FUNC_PTR(OBJECT_DEPLETE_BODY,			0x4F16B0, 0x4DA910);
FUNC_PTR(OBJECT_DEPLETE_SHIELD,			0x4F17A0, 0x4DAA00);
FUNC_PTR(OBJECT_DOUBLE_CHARGE_SHIELD,	0x4F1830, 0x4DAA90);
FUNC_PTR(UNIT_GET_CAMERA_POSITION,		0x56CA80, FUNC_PTR_NULL);
FUNC_PTR(OBJECT_DEFINITION_PREDICT,		0x4FB760, 0x4E26B0);
FUNC_PTR(UNIT_ORIENT_TO_FLAG,			0x48ACA0, 0x482580);

//////////////////////////////////////////////////////////////////////////
// Players
FUNC_PTR(PLAYER_INDEX_FROM_UNIT_INDEX,		0x477BF0, 0x46F670);
FUNC_PTR(PLAYER_TELEPORT,					0x478A90, 0x470510);
FUNC_PTR(PLAYER_OVER_SHIELD_SCREEN_EFFECT,	0x47C4B0, FUNC_PTR_NULL);
FUNC_PTR(PLAYER_CAMO_SCREEN_EFFECT,			0x47C570, FUNC_PTR_NULL);
FUNC_PTR(PLAYER_HEALTH_PACK_SCREEN_EFFECT,	0x47C630, FUNC_PTR_NULL);
FUNC_PTR(FIND_CLOSEST_PLAYER_INDEX,			0x45EEE0, FUNC_PTR_NULL);

//////////////////////////////////////////////////////////////////////////
// Scenario
FUNC_PTR(SCENARIO_TRIGGER_VOLUME_TEST_POINT,0x542780, 0x4FD490);

//////////////////////////////////////////////////////////////////////////
// TagGroups
FUNC_PTR(PHYSICAL_MEMORY_MAP_PREDICT_RESOURCES,	0x445520, FUNC_PTR_NULL);
FUNC_PTR(TAG_LOADED,							0x4429A0, 0x443530);
FUNC_PTR(UNICODE_STRING_LIST_GET_STRING,		0x55B390, 0x509DE0);