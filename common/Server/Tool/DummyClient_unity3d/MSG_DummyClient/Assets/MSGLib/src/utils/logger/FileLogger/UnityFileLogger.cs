#if UNITY_3_0 || UNITY_3_0_0 || UNITY_3_1 || UNITY_3_2 || UNITY_3_3 || UNITY_3_4 || UNITY_3_5 || UNITY_4_0 || UNITY_4_1 || UNITY_4_2
using UnityEngine;
using System.Collections;
using System.IO;
namespace MSG
{
    public class UnityFileLogger : Logger
    {
        public string initTime;
        public string path;

        public UnityFileLogger(LoggerOption option)
        {
            this.initTime = option.initTime;
            switch (option.type)
            {
                case LogDirectoryType.Cache:
                    this.path = UnityEngine.Application.temporaryCachePath;
                    break;
                case LogDirectoryType.Persistent:
                    this.path = UnityEngine.Application.persistentDataPath;
                    break;
                case LogDirectoryType.Custom:
                    this.path = option.customDirectoryPath;
                    break;
            }
        }

        public override void HandleLog(string log)
        {
            writeFile(log);
        }

        private void writeFile(string log)
        {
            string fileName = initTime;
            string dirPath = path;

            if (dirPath != null && dirPath.Length > 0)
            {
                string filePath = dirPath + "/" + fileName;
                if (File.Exists(filePath))
                {
                    FileStream file = new FileStream(filePath, FileMode.Append, FileAccess.Write, FileShare.None);
                    StreamWriter writer = new StreamWriter(file);
                    writer.WriteLine(log);
                    writer.Close();
                    file.Close();
                }
                else
                {
                    FileStream file = new FileStream(filePath, FileMode.Create, FileAccess.Write, FileShare.None);
                    StreamWriter writer = new StreamWriter(file);
                    writer.WriteLine(log);
                    writer.Close();
                }
            }
        }
    }
}
#endif