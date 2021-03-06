/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#if !PLATFORM_IS_DEDI
#include <blamlib/Halo1/game/game_allegiance.hpp> // for game teams
#include <blamlib/Halo1/game/players.hpp>
#include <blamlib/Halo1/interface/first_person_weapons.hpp>
#include <blamlib/Halo1/interface/hud.hpp>
#include <blamlib/Halo1/interface/hud_messaging.hpp>
#include <blamlib/Halo1/interface/hud_nav_points.hpp>
#include <blamlib/Halo1/interface/hud_weapon.hpp>
#include <blamlib/Halo1/interface/interface.hpp>
#include <blamlib/Halo1/interface/motion_sensor.hpp>

#include "Interface/YeloSettingsInterface.hpp"

namespace Yelo
{
	namespace Enums
	{
		enum {
			k_maximum_number_of_hud_sounds = 12, // MAXIMUM_NUMBER_OF_HUD_SOUNDS

			k_max_custom_blips = 16, // MAX_CUSTOM_BLIPS
		};

		enum text_style : _enum
		{
			_text_style_plain = CAST(_enum,NONE),

			_text_style_bold = 0,
			_text_style_italic,
			_text_style_condense,
			_text_style_underline,
		};

		enum text_justification : _enum
		{
			_text_justification_left,
			_text_justification_right,
			_text_justification_center,
		};

		enum rasterize_score : long_enum
		{
			_rasterize_score_welcome,
			_rasterize_score_s_died,
			_rasterize_score_s_was_killed_by_guardians,
			_rasterize_score_s_was_killed_by_vehicle,
			_rasterize_score_s_was_killed_by_s,
			_rasterize_score_s_was_betrayed_bs_s,
			_rasterize_score_s_commited_suicide,
			_rasterize_score_double_kill,
			_rasterize_score_you_killed_s,
			_rasterize_score_triple_kill,
			_rasterize_score_killtacular,
			_rasterize_score_killing_spree,
			_rasterize_score_running_riot,
			_rasterize_score_you_betrayed_s,
			_rasterize_score_killtacular_d,
			_rasterize_score_triple_kill_d,
			_rasterize_score_double_kill_d,
			_rasterize_score_running_riot_d,
			_rasterize_score_started_killing_spree,
			_rasterize_score_you_killed_s_d,
			_rasterize_score_you_are_odd_man_out,
			_rasterize_score_you_are_out_of_lives,
			_rasterize_score_rejoin_in_d,
			_rasterize_score_waiting_for_space,
			_rasterize_score_you_quit,
			_rasterize_score_s_quit,
			_rasterize_score_hold_s_for_score,
			_rasterize_score_d_remaining,
			_rasterize_score_telefragged,
			_rasterize_score,
		};

		enum blip_type : byte_enum
		{
			_blip_type_local_player,			// 1, .5, 0
			_blip_type_friendly_team,			// 1, 1, 0
			_blip_type_enemy_team,				// 1, 0, 0
			_blip_type_friendly_team_vehicle,	// 1, 1, 0
			_blip_type_enemy_team_vehicle,		// 1, 0, 0
			_blip_type_objective,				// .5, .5, 1
			_blip_type_none,					// 0, 0, 0
		};
	};

	namespace Flags
	{
		enum unit_interface_flags : long_flags
		{
			_unit_interface_show_health_bit,
			_unit_interface_blink_health_bit,
			_unit_interface_show_shield_bit,
			_unit_interface_blink_shield_bit,
			_unit_interface_show_motion_sensor_bit,
			_unit_interface_blink_motion_sensor_bit,
		};

		enum weapon_interface_show : byte_flags // TODO: verify this flags field size
		{
			_weapon_interface_show_crosshair_bit,
		};

		enum text_flag : long_flags
		{
			_text_bit1,
			_text_bit2,
			_text_bit4,
			_text_bit8,
		};
	};

	namespace GameUI
	{
		struct s_hud_scripted_globals
		{
			bool show_hud;
			bool show_hud_help_text;
			PAD16;
		};
		s_hud_scripted_globals*		HudScriptedGlobals();

		struct s_hud_messaging : TStructImpl(1160)
		{
		};
		s_hud_messaging*			HudMessaging();


		struct s_hud_unit_interface_unit
		{
			real shields, health;
			UNKNOWN_TYPE(real);
			uint32 last_update_time;
			struct {
				uint32 hud_background_element;
				uint32 health_panel_background_element;
				uint32 motion_sensor_elements;
			}last_render_time;
			datum_index unit_index;
			int16 integrated_light_power; // 0 = off 1 = on
			int16 integrated_light_time;
			word_flags active_sound_elements;
			PAD16;
			datum_index sound_elements[Enums::k_maximum_number_of_hud_sounds]; // sound cache index
		}; BOOST_STATIC_ASSERT( sizeof(s_hud_unit_interface_unit) == 0x58 );
		struct s_hud_unit_interface
		{
			s_hud_unit_interface_unit units[Enums::k_maximum_number_of_local_players]; // 0x0
			long_flags flags; // 0x58, unit_interface_flags
		}; BOOST_STATIC_ASSERT( sizeof(s_hud_unit_interface) == 0x5C );
		s_hud_unit_interface*		HudUnitInterface();


		struct s_hud_weapon_interface_player : TStructImpl(0x50)
		{
			// 0x0, uint32 state_last_render_times[Enums::_weapon_hud_state]; // last render for each weapon hud state type
			// 0x20, datum_index weapon_index
			// 0x24, argb_color flash color

			// 0x4C, long_flags render_crosshair_types_mask
		};
		struct s_hud_weapon_interface : TStructImpl(0x7C)
		{
			TStructGetPtrImpl(s_hud_weapon_interface_player, LocalPlayers, 0x0);
			TStructGetPtrImpl(Flags::weapon_interface_show, ShowHudFlags, 0x78);
		};
		s_hud_weapon_interface*		HudWeaponInterface();

		struct s_hud_nav_points
		{
			struct s_nav_point
			{
				int16 navpoint_index;
				struct {
					// 0 - cutscene flag
					// 1 - object
					// 2 - game goal (objective)
					// 3 - deactivated
					uint16 type : 4;
				};
				// cutscene flag index
				// object = datum_index
				// game goal index
				int32 type_index;
				real vertical_offset;
			};
			struct s_local_player
			{
				s_nav_point nav_points[4];
			};

			s_local_player local_players[Enums::k_maximum_number_of_local_players];
		}; BOOST_STATIC_ASSERT( sizeof(s_hud_nav_points) == 0x30 );
		s_hud_nav_points*			HudNavPoints();

		struct s_motion_sensor
		{
			struct s_custom_blip
			{
				sbyte x;
				sbyte y;
			};
			struct s_blip : s_custom_blip
			{
				Enums::blip_type type; // set to _blip_type_none when not used
				byte_enum size;	// a la object's size (tiny, large, etc)
			}; BOOST_STATIC_ASSERT( sizeof(s_blip) == 0x4 );
			struct s_team_data
			{
				s_blip object_blips[Enums::k_max_custom_blips];			// objects belonging to just this team
				struct {
					s_custom_blip goal_blips[Enums::k_max_custom_blips];
					sbyte goal_indices[Enums::k_max_custom_blips];		// indices to the game engine's global goals
				}game_engine;

				real_point2d world_position;
				UNKNOWN_TYPE(int32); // game time related
				UNKNOWN_TYPE(real); // related to calculations with objects and facing angle of the player
				sbyte active_object_blips_count;
				PAD24;
			}; BOOST_STATIC_ASSERT( sizeof(s_team_data) == 0x84 );
			struct s_local_player
			{
				s_team_data nearby_team_objects[Enums::k_number_of_game_teams];
				datum_index nearby_object_indexes[Enums::k_max_custom_blips];
			}; BOOST_STATIC_ASSERT( sizeof(s_local_player) == 0x568 );


			s_local_player local_players[Enums::k_maximum_number_of_local_players];

			struct {
				UNKNOWN_TYPE(int32); // game time related
				int16 current_object_blip_index;
				PAD8; // actually boolean, but you don't need to worry about this value!
				PAD8;
			}update_data;
		}; BOOST_STATIC_ASSERT( sizeof(s_motion_sensor) == 0x570 );
		s_motion_sensor*			MotionSensor();

		struct s_first_person_weapon : TStructImpl(0x1EA0)
		{
			TStructGetPtrImpl(bool, IsVisible, 0x0);
			TStructGetPtrImpl(datum_index, UnitIndex, 0x4);
			TStructGetPtrImpl(datum_index, WeaponIndex, 0x8);
			// 1 = o-h-enter, 3 = overheated, 4 = charging, 5 = posing, 6 = firing1, 10 = meleeing, 
			// 13 = reload empty, 14 = reload full, 19 = switching/ready, 22 = o-h-exit, 23 = firing2
			TStructGetPtrImpl(int16, AnimationState, 0xC);
			// 0xE = unknown 2 bytes
			TStructGetPtrImpl(int16, IdleTime, 0x10);
			TStructGetPtrImpl(Objects::s_animation_state, CurrentBaseAnimation, 0x12); // frame index of current base animation (idle or moving)
			TStructGetPtrImpl(Objects::s_animation_state, CurrentAnimation, 0x16);
			TStructGetPtrImpl(Objects::s_animation_state, CurrentMovingOverlayAnimation, 0x1A);
			//TStructGetPtrImpl(Objects::s_animation_state, , 0x1E);

			//TStructGetPtrImpl(real, , 0x28); // frame index (real) for the above anim state
			//TStructGetPtrImpl(real, , 0x2C);
			// 0x30?
			//TStructGetPtrImpl(real, , 0x34);
			// 0x38?
			// 0x3C?
			//TStructGetPtrImpl(real, , 0x40);
			//TStructGetPtrImpl(real, , 0x44);
			// 0x48?
			// 0x4C?
			// 0x50 bool
			// 0x54 real_vector3d forward?
			// 0x60 real_euler_angles2d
			// 0x68 real_euler_angles2d
			// 0x70 real_point3d
			// 0x7C real_point3d?
			//////////////////////////////////////////////////////////////////////////
			// 0x88 int16 frame index
			// 0x8A int16 frame count
			// 0x8C real_orientation3d node orientations[128]
			// 0x108C real_matrix4x3 node matrices[64]
			//////////////////////////////////////////////////////////////////////////
			// 0x1D8C bool remapped weapon?
			// PAD8;
			// 0x1D8E int16 node_remappings[64]
			//////////////////////////////////////////////////////////////////////////
			// 0x1E0E bool remapped hands
			// PAD8;
			// 0x1E10 int16 node_remappings[64]
			//////////////////////////////////////////////////////////////////////////
			// 0x1E90 ?
			// 0x1E94 _enum shotgun_reload_type;
			//		_shotgun_reload_type_last_round = 1
			//		_shotgun_reload_type_first_and_last_round = 2
			//TStructGetPtrImpl(int32, , 0x1E98);
			//TStructGetPtrImpl(int16, , 0x1E9C);
		};
		struct s_first_person_weapons
		{
			s_first_person_weapon local_players[Enums::k_maximum_number_of_local_players];
		}; BOOST_STATIC_ASSERT( sizeof(s_first_person_weapons) == 0x1EA0 );
		s_first_person_weapons*		FirstPersonWeapons();


		struct s_text_bounds_globals_data
		{
			rectangle2d bounds;
			void* styled_font_tag; // 'font'
		};
		s_text_bounds_globals_data*	TextBoundsGlobals();

		struct s_font_drawing_globals_data
		{
			datum_index internal_string_localization_tag;
			datum_index font_tag;
			Flags::text_flag flags;
			Enums::text_style style;
			Enums::text_justification justification;
			real_argb_color color;
			int16 tab_stop_count;
			wchar_t tab_stops[16];
			int16 highlight_start;
			int16 highlight_end;
			int16 initial_indent;
			int16 paragraph_indent[72];
		};
		s_font_drawing_globals_data*	FontDrawingGlobals();


		void Initialize();
		void Dispose();
		void PLATFORM_API Update();

		void PLATFORM_API FirstPersonWeaponsUpdate();
	};


	namespace Hud
	{
		void Initialize();
		void Dispose();

		void Update();

		bool& ScaleHUD();
		bool& ShowCrosshair();
		void* HudGlobals(); // get the hud_globals tag definition

		Enums::settings_adjustment_result AdjustSettings();
		void LoadSettings(TiXmlElement* hud_element);
		void SaveSettings(TiXmlElement* hud_element);

		void EnableScaling();
		void DisableScaling();

#if defined(DX_WRAPPER) // TODO: Need fallback initialization for when we're not using the DX_WRAPPER
		void Initialize3D(IDirect3DDevice9 *pDevice, D3DPRESENT_PARAMETERS *pPP);
		void OnLostDevice();
		void OnResetDevice(D3DPRESENT_PARAMETERS *pPP);
		void Render();
		void Release();
#endif

	};


	namespace Menu
	{
		void Initialize();
		void Dispose();

#if defined(DX_WRAPPER) // TODO: Need fallback initialization for when we're not using the DX_WRAPPER
		void Initialize3D(IDirect3DDevice9 *pDevice, D3DPRESENT_PARAMETERS *pPP);
		void OnLostDevice();
		void OnResetDevice(D3DPRESENT_PARAMETERS *pPP);
		void Render();
		void Release();
#endif
	};
};
#endif