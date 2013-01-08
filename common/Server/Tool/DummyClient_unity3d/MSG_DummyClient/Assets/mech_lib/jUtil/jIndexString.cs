using UnityEngine;
using System.Collections;
using System.Collections.Generic;

using string_id_t = System.Int32;

namespace nNWM
{
    public class jIndexString
    {
        private static Dictionary<string, string_id_t>  m_string_id_map = new Dictionary<string, string_id_t>();
        private static List<string>                     m_string_id_vector = new List<string>();
        public static string_id_t GetIndex(string str)
        {
            if (str.Length == 0) return 0;

            string_id_t string_id;
            if (m_string_id_map.TryGetValue(str,out string_id) != true)
            {
                m_string_id_vector.Add(str);
				string_id = m_string_id_vector.Count;
                m_string_id_map.Add(str, string_id );
            }
            return string_id;
        }
        public static string GetString(string_id_t id)
        {
            if (m_string_id_vector.Count < id || id <= 0)
                return "";
            return m_string_id_vector[id];
        }

    }//public class jIndexString

}//namespace nNWM