/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#include "Common/Precompile.hpp"
#include "Networking/Networking.hpp"

#include "Memory/MemoryInterface.hpp"
#include "Networking/GameSpyApi.hpp"
#include "Networking/MessageDeltas.hpp"

namespace Yelo
{
	namespace Networking
	{
#define __EL_INCLUDE_ID			__EL_INCLUDE_NETWORKING
#define __EL_INCLUDE_FILE_ID	__EL_NETWORKING_NETWORKING
#include "Memory/_EngineLayout.inl"

#ifdef API_DEBUG
		cstring message_packet_to_string_table[] = {
			"client-broadcast_game_search",
			"client-ping",
			"server-game_advertise",
			"server-pong",
			"server-new_client_challenge",
			"server-machine_accepted",
			"server-machine_rejected",
			"server-game_is_ending_holdup",
			"server-game_settings_update",
			"server-pregame_countdown",
			"server-begin_game",
			"server-graceful_game_exit_pregame",
			"server-pregame_keep_alive",
			"server-postgame_keep_alive",
			"client-join_game_request",
			"client-add_player_request_pregame",
			"client-remove_player_request_pregame",
			"client-settings_request",
			"client-player_settings_request",
			"client-game_start_request",
			"client-graceful_game_exit_pregame",
			"client-map_is_precached_pregame",
			"server-game_update",
			"server-add_player_ingame",
			"server-remove_player_ingame",
			"server-game_over",
			"client-loaded",
			"client-game_update",
			"client-add_player_request_ingame",
			"client-remove_player_request_ingame",
			"client-graceful_game_exit_ingame",
			"client-host_crashed_cry_for_help",
			"client-join_new_host",
			"server-reconnect",
			"server-graceful_game_exit",
			"client-remove_player_request_postgame",
			"client-switch_to_pregame",
			"client-graceful_game_exit_postgame",
		};
#endif

		struct s_network_yelo_settings {
			bool gs_no_update_check;
			PAD24;
		}g_network_yelo_settings;

		s_update_client_globals* UpdateClientGlobals()						PTR_IMP_GET2(update_client_globals);
		s_update_server_globals* UpdateServerGlobals()						PTR_IMP_GET2(update_server_globals);

		network_update_globals* UpdateSettings()							PTR_IMP_GET2(network_update_globals);

		Enums::game_connection GameConnection()								PTR_IMP_GET(global_game_connection);
		bool IsLocal()	{ return GET_PTR(global_game_connection) == Enums::_game_connection_local; }
		bool IsServer() { return GET_PTR(global_game_connection) == Enums::_game_connection_network_server; }
		bool IsClient() { return GET_PTR(global_game_connection) == Enums::_game_connection_network_client; }

		// Points to a static structure, 'network_game_server_memory_do_not_use_directly'
		s_network_game_server* NetworkGameServer()							DPTR_IMP_GET(global_network_game_server);
		// Points to a static structure, 'network_game_client_memory_do_not_use_directly'
		s_network_game_client* NetworkGameClient()							DPTR_IMP_GET(global_network_game_client);

		//////////////////////////////////////////////////////////////////////////
		// Player Hooks (join/leave)
		static void OnPlayerJoin(s_network_game_player* player)
		{
		}

		static void OnPlayerExit(s_network_game_player* player)
		{
		}

		#pragma region OnPlayerJoinDelegate
		API_FUNC_NAKED static void PLATFORM_API OnPlayerJoinDelegate(s_network_game* network_game_data)
		{
			static uint32 TEMP_CALL_ADDR = GET_FUNC_PTR(NETWORK_GAME_ADD_PLAYER);

			__asm {
				// eax = struct s_network_player

				push	ebp
				mov		ebp, esp
				push	esi
				mov		esi, eax

				push	eax		// s_network_player.player_list_index
				call	OnPlayerJoin

				mov		eax, esi
				mov		esi, network_game_data
				push	esi
				call	TEMP_CALL_ADDR
				add		esp, 4

				pop		esi
				mov		esp, ebp
				pop		ebp
				retn
			}
		}
		#pragma endregion

		#pragma region OnPlayerExitDelegate
		API_FUNC_NAKED static void PLATFORM_API OnPlayerExitDelegate()
		{
			static uint32 TEMP_CALL_ADDR = GET_FUNC_PTR(NETWORK_GAME_REMOVE_PLAYER);

			__asm {
				// esi = s_network_game

				push	esi
				push	edi		// save edi just in case the compiler does some nasty stuff
				push	edi		// s_network_player
				call	OnPlayerExit
				pop		edi
				pop		esi

				call	TEMP_CALL_ADDR

				retn
			}
		}
		#pragma endregion
		//////////////////////////////////////////////////////////////////////////

		void Initialize()
		{
			MessageDeltas::Initialize();
			GameSpy::Initialize();

			// NOTE: Uncomment these if you wish to detect
			// when players enter and leave
#if !PLATFORM_DISABLE_UNUSED_CODE
			Memory::WriteRelativeCall(OnPlayerJoinDelegate, 
				GET_FUNC_VPTR(NETWORK_GAME_SERVER_ADD_PLAYER_TO_GAME__HOOK_ADD_PLAYER));
			Memory::WriteRelativeCall(OnPlayerExitDelegate, 
				GET_FUNC_VPTR(CLIENT_MACHINE_CLEANUP__HOOK_REMOVE_PLAYER));
#endif
		}

		void Dispose()
		{
			MessageDeltas::Dispose();
			GameSpy::Dispose();
		}

		void LoadSettings(TiXmlElement* xml_element)
		{
			if(xml_element == NULL) return;

			GameSpy::LoadSettings(xml_element);
		}
		void SaveSettings(TiXmlElement* xml_element)
		{
			GameSpy::SaveSettings(xml_element);
		}

		static API_FUNC_NAKED bool NetworkConnectionWrite(const s_network_connection& connection,
			const void* data, size_t data_size_in_bits,
			const void* header, size_t header_size_in_bits,
			BOOL unbuffered, BOOL flush_queue, int32 buffer_priority)
		{
			static const uintptr_t CALL_ADDR = GET_FUNC_PTR(NETWORK_CONNECTION_WRITE);

			API_FUNC_NAKED_START()
				push	edi
				push	ebx

				push	buffer_priority
				push	flush_queue
				push	unbuffered
				push	header_size_in_bits
				push	header
				mov		ebx, data_size_in_bits
				push	data
				mov		edi, connection
				call	CALL_ADDR
				add		esp, 4 * 6

				pop		ebx
				pop		edi
			API_FUNC_NAKED_END(8)
		}
		bool ConnectionWrite(const s_network_connection& connection, 
			const void* data, size_t data_size_in_bits,
			const void* header, size_t header_size_in_bits,
			bool unbuffered, bool flush_queue, int32 buffer_priority)
		{
			return NetworkConnectionWrite(connection, 
				data, data_size_in_bits, 
				header, header_size_in_bits, 
				unbuffered, flush_queue, buffer_priority);
		}

		bool ClientSendMessageToServer(
			const void* data, size_t data_size_in_bits, 
			Enums::network_messsage_type message_type, 
			bool unbuffered, bool flush_queue, int32 buffer_priority)
		{
			using namespace Networking;

			s_network_game_client* client = NetworkGameClient();
			const s_network_connection& client_connection = *client->connection;
			long_flags flags = client_connection.flags;

			if(!TEST_FLAG(flags, Flags::_connection_create_server_bit))
			{
				Enums::network_messsage_type header = Enums::_network_messsage_type_message_delta;
				return ConnectionWrite(client_connection, 
					data, data_size_in_bits,
					&message_type, 1,
					unbuffered, flush_queue, buffer_priority);
			}

			return false;
		}

		API_FUNC_NAKED bool ServerSendRejectionMessage(s_network_game_player& rejected_player, Enums::transport_rejection_code code)
		{
			static const uintptr_t CALL_ADDR = GET_FUNC_PTR(NETWORK_GAME_SERVER_SEND_REJECTION_MESSAGE);

			API_FUNC_NAKED_START()
				push	esi

				call	IsServer
				test	al, al
				jz		not_a_server // al will be our return value, which would be 0 if this jmp is hit

				call	NetworkGameServer
				mov		esi, eax

				mov		ecx, code
				mov		eax, rejected_player
#if PLATFORM_IS_USER
				push	esi
#endif
				call	CALL_ADDR
#if PLATFORM_IS_USER
				add		esp, 4 * 1
#endif

not_a_server:
				pop		esi
			API_FUNC_NAKED_END(2)
		}

		API_FUNC_NAKED bool ServerHoldupNewClient(s_network_client_machine& client_machine)
		{
			static const uintptr_t CALL_ADDR = GET_FUNC_PTR(NETWORK_GAME_SERVER_SEND_REJECTION_MESSAGE);

			API_FUNC_NAKED_START()
				call	IsServer
				test	al, al
				jz		not_a_server

				push	client_machine
				// function takes the server as a parameter in debug builds, but param is unreferenced in release builds
				call	CALL_ADDR
				add		esp, 4 * 1
not_a_server:
			API_FUNC_NAKED_END(1)
		}

		API_FUNC_NAKED bool SvSendMessageToMachine(int32 machine_index, 
			const void* data, size_t data_size_in_bits, 
			Enums::network_messsage_type message_type, 
			BOOL unbuffered, BOOL flush_queue, BOOL write_to_local_connection, 
			int32 buffer_priority)
		{
			static const uintptr_t CALL_ADDR = GET_FUNC_PTR(NETWORK_GAME_SERVER_SEND_MESSAGE_TO_MACHINE);

			API_FUNC_NAKED_START()
				push	esi

				push	buffer_priority
				push	write_to_local_connection
				push	flush_queue
				push	unbuffered
				push	data_size_in_bits
				push	data
				push	message_type
				call	NetworkGameServer
				mov		esi, eax
				mov		eax, machine_index
				call	CALL_ADDR
				add		esp, 4 * 7

				pop		esi
			API_FUNC_NAKED_END(8)
		}

		API_FUNC_NAKED bool SvSendMessageToAll(
			const void* data, size_t data_size_in_bits, 
			Enums::network_messsage_type message_type, 
			BOOL unbuffered, BOOL flush_queue, BOOL write_to_local_connection, 
			int32 buffer_priority, 
			BOOL ingame_only)
		{
			static const uintptr_t CALL_ALL_MACHINES = GET_FUNC_PTR(NETWORK_GAME_SERVER_SEND_MESSAGE_TO_ALL_MACHINES);
			static const uintptr_t CALL_ALL_MACHINES_INGAME = GET_FUNC_PTR(NETWORK_GAME_SERVER_SEND_MESSAGE_TO_ALL_MACHINES_INGAME);

			API_FUNC_NAKED_START()
				push	ebp

				push	buffer_priority
				push	write_to_local_connection
				push	flush_queue
				push	unbuffered
				push	data
				push	message_type
				call	NetworkGameServer
				mov		ecx, eax
				mov		eax, data_size_in_bits

				mov		ebp, ingame_only
				test	ebp, ebp
				jnz		all_machines_ingame
				call	CALL_ALL_MACHINES
				jmp		cleanup
all_machines_ingame:
				call	CALL_ALL_MACHINES_INGAME
cleanup:
				add		esp, 4 * 6

				pop		ebp
			API_FUNC_NAKED_END(8)
		}
	};
};