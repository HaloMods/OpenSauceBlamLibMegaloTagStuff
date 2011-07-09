/*
    BlamLib: .NET SDK for the Blam Engine

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
using System;
using System.ComponentModel;
using System.Xml;
using System.Xml.Serialization;

namespace BlamLib.Render.COLLADA.Core
{
	[SerializableAttribute()]
	[XmlTypeAttribute(AnonymousType = true)]
	public partial class ColladaFloatArray : ColladaValueArray<float>
	{
		#region Fields
		ColladaObjectAttribute<string> _id;
		ColladaObjectAttribute<string> _name;
		ColladaObjectAttribute<short> _digits;
		ColladaObjectAttribute<short> _magnitude;
		#endregion

		#region Attributes
		[XmlAttribute("count")]
		public uint Count
		{
			get
			{
				if (Values == null)
					return 0;
				else
					return (uint)Values.Count;
			}
			set { }
		}

		[XmlAttribute("id"), DefaultValue(""), ColladaID("floatarray-{0}")]
		public string ID
		{ get { return _id.Value; } set { _id.Value = value; } }

		[XmlAttribute("name"), DefaultValue("")]
		public string Name
		{ get { return _name.Value; } set { _name.Value = value; } }

		[XmlAttribute("digits"), DefaultValue(6)]
		public short Digits
		{ get { return _digits.Value; } set { _digits.Value = value; } }

		[XmlAttribute("magnitude"), DefaultValue(38)]
		public short Magnitude
		{ get { return _magnitude.Value; } set { _magnitude.Value = value; } }
		#endregion

		public ColladaFloatArray() : base(Enums.ColladaElementType.Core_FloatArray)
		{
			Fields.Add(_id = new ColladaObjectAttribute<string>(""));
			Fields.Add(_name = new ColladaObjectAttribute<string>(""));
			Fields.Add(_digits = new ColladaObjectAttribute<short>(6));
			Fields.Add(_magnitude = new ColladaObjectAttribute<short>(38));
		}
	}
}