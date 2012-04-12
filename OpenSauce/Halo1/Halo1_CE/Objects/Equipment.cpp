/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#include "Common/Precompile.hpp"
#include "Objects/Equipment.hpp"

#include <TagGroups/Halo1/item_definitions.hpp>
#include "Objects/Objects.hpp"

namespace Yelo
{
	namespace Objects { namespace Equipment {
		
		void InitializeType(s_object_type_definition* equipment_type)
		{
			equipment_type->new_ = &New;
			equipment_type->delete_ = &Delete;
			equipment_type->update = &Update;
			equipment_type->export_function_values = &ExportFunctionValues;
		}

		bool PLATFORM_API New(datum_index equipment_index)
		{
			return true;
		}

		void PLATFORM_API Delete(datum_index equipment_index)
		{
		}

		bool PLATFORM_API Update(datum_index equipment_index)
		{
			return true;
		}

		void PLATFORM_API ExportFunctionValues(datum_index equipment_index)
		{
			s_equipment_datum* equipment = (*Objects::ObjectHeader())[equipment_index]->Type._equipment;

			TagGroups::s_equipment_definition const* definition = GetObjectDefinition<TagGroups::s_equipment_definition>(equipment_index);
		}

	}; };
};