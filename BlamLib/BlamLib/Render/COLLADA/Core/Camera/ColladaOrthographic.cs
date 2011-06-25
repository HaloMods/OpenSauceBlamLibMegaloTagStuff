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
using System.Collections.Generic;
using BlamLib.Render.COLLADA.Validation;

namespace BlamLib.Render.COLLADA.Core
{
	[SerializableAttribute()]
	[XmlTypeAttribute(AnonymousType = true)]
	public partial class ColladaOrthographic : ColladaElement
	{
		#region Fields
		ColladaObjectElement<ColladaSIDValue<float>> _xMag;
		ColladaObjectElement<ColladaSIDValue<float>> _yMag;
		ColladaObjectElement<ColladaSIDValue<float>> _aspectRatio;
		ColladaObjectElement<ColladaSIDValue<float>> _zNear;
		ColladaObjectElement<ColladaSIDValue<float>> _zFar;
		#endregion

		#region Children
		[XmlElement("xmag")]
		public ColladaSIDValue<float> XMag
		{ get { return _xMag.Value; } set { _xMag.Value = value; } }

		[XmlElement("ymag")]
		public ColladaSIDValue<float> YMag
		{ get { return _yMag.Value; } set { _yMag.Value = value; } }

		[XmlElement("aspect_ratio")]
		public ColladaSIDValue<float> AspectRatio
		{ get { return _aspectRatio.Value; } set { _aspectRatio.Value = value; } }

		[XmlElement("znear")]
		public ColladaSIDValue<float> ZNear
		{ get { return _zNear.Value; } set { _zNear.Value = value; } }

		[XmlElement("zfar")]
		public ColladaSIDValue<float> ZFar
		{ get { return _zFar.Value; } set { _zFar.Value = value; } }
		#endregion

		public ColladaOrthographic() : base(Enums.ColladaElementType.Core_Orthographic)
		{
			Fields.Add(_xMag = new ColladaObjectElement<ColladaSIDValue<float>>());
			Fields.Add(_yMag = new ColladaObjectElement<ColladaSIDValue<float>>());
			Fields.Add(_aspectRatio = new ColladaObjectElement<ColladaSIDValue<float>>());
			Fields.Add(_zNear = new ColladaObjectElement<ColladaSIDValue<float>>());
			Fields.Add(_zFar = new ColladaObjectElement<ColladaSIDValue<float>>());

			List<ColladaObject> required_fields = new List<ColladaObject>();
			required_fields.Add(_xMag);
			required_fields.Add(_yMag);

			ValidationTests.Add(new ColladaOneRequired(Enums.ColladaElementType.All, required_fields));
			ValidationTests.Add(new ColladaIsNull(Enums.ColladaElementType.All, _aspectRatio));
			ValidationTests.Add(new ColladaIsNull(Enums.ColladaElementType.All, _zNear));
			ValidationTests.Add(new ColladaIsNull(Enums.ColladaElementType.All, _zFar));
		}
	}
}