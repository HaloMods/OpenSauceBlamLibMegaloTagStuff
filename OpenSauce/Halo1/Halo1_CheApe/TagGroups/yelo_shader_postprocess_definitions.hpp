/*
    Yelo: Open Sauce SDK
		Halo 1 (Editing Kit) Edition
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
#pragma once

namespace Yelo
{
	namespace PostProcessing
	{
#if PLATFORM_ID == PLATFORM_TOOL
		bool PLATFORM_API shader_postprocess_collection_group_postprocess(datum_index tag_index, bool verify_data);
		bool PLATFORM_API shader_postprocess_generic_group_postprocess(datum_index tag_index, bool verify_data);
#endif
		void Initialize();
		void Dispose();
	};
};