사용법.

	using UnityEngine;
	using System.Collections.Generic;
	using jxD = nNWM.nXML.jxDocument; // xml doc;
	using jxE = nNWM.nXML.jxElement; // xml element
	using jxA = nNWM.nXML.jxVar; // element attribute
	using jxV = nNWM.nXML.jxVar; // attribute or element data
	using string_id_t = System.Int32;


	nXML.jxDocument doc = nXML.jxDocument.Load(m_XmlAsset.name, m_XmlAsset.text);


버그
	다음은 로딩이 안됨.
		<r_Win_ToggleListbox>260 ;30;420;250</r_Win_ToggleListbox> 

