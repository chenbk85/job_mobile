using UnityEngine;
using System.Collections;


namespace nNWM
{
    namespace nXML
    {
        public class jxUtil
        {
            public static EDataType GetTypeByTagName(string sTagName, ref string modifyed_TagName)
            {
                modifyed_TagName = sTagName;

                if (sTagName == null || sTagName.Length == 0)
                {
                    return EDataType.e_error;
                }

                if (sTagName.Length <= 2)
                {
                    return EDataType.e_element;
                }
                string tag = sTagName.Substring(0, 2);
                modifyed_TagName = sTagName.Substring(2);

                if (tag == "i_")
                {
                    return EDataType.e_int;
                }
                if (tag == "f_")
                {
                    return EDataType.e_float;
                }
                if (tag == "b_")
                {
                    return EDataType.e_bool;
                }
                if (tag == "r_")
                {
                    return EDataType.e_Rect;
                }
                if (tag == "p_")
                {
                    return EDataType.e_Point;
                }

                if (sTagName.Length <= 3)
                {
                    modifyed_TagName = sTagName;
										return EDataType.e_element;
                }
                tag = sTagName.Substring(0, 3);
                modifyed_TagName = sTagName.Substring(3);

                if (tag == "ii_")
                {
                    return EDataType.e_int_array;
                }
                if (tag == "ff_")
                {
                    return EDataType.e_float_array;
                }

                if (sTagName.Length <= 4)
                {
                    modifyed_TagName = sTagName;
										return EDataType.e_element;
                }
                tag = sTagName.Substring(0, 4);
                modifyed_TagName = sTagName.Substring(4);

                if (tag == "i64_")
                {
                    return EDataType.e_Int64;
                }
                if (tag == "f64_")
                {
                    return EDataType.e_double;
                }

                modifyed_TagName = sTagName;
                return EDataType.e_element;
            }

            public static string GetTagNameByType(string name, EDataType eType)
            {
                switch (eType)
                {
                    case EDataType.e_Int64:// i64_
                        {
                            return "i64_" + name;
                        }
                    case EDataType.e_int: // i_
                        {
                            return "i_" + name;
                        }
                    case EDataType.e_double: // f64_
                        {
                            return "f64_" + name;
                        }
                    case EDataType.e_float: // f_
                        {
                            return "f_" + name;
                        }

                    case EDataType.e_bool: // b_
                        {
                            return "b_" + name;
                        }
                    case EDataType.e_int_array: // ia_
                        {
                            return "ii_" + name;
                        }
                    case EDataType.e_Rect: // r_
                        {
                            return "r_" + name;
                        }
                    case EDataType.e_Point: // ia_
                        {
                            return "p_" + name;
                        }
                    case EDataType.e_float_array: // fa_
                        {
                            return "ff_" + name;
                        }
                }
                return name;

            }//public static string GetTagNameByType(String name , EDataType eType)
        }

    }//namespace nXML

}//namespace nNWM
