using System;
using System.Runtime.InteropServices;
using System.Reflection;
using System.Windows.Forms;
using System.Diagnostics;
using System.Runtime.CompilerServices;

// 어셈블리의 일반 정보는 다음 특성 집합을 통해 제어됩니다.
// 어셈블리와 관련된 정보를 수정하려면
// 이 특성 값을 변경하십시오.

//[assembly: AssemblyKeyFile("CShopUtil.snk")]
[assembly: AssemblyDelaySign(false)]
[assembly: AssemblyVersion("1.1.1.1")]
[assembly: ComVisible(true)]

    public enum WeatherIndications
    {
        Sunny = 0,
        Cloudy,
        Rainy,
        Snowy
    }


    public interface ITestCom
    {

        float Temperature { get; set; }
        void DisplayCurrentTemperature();
        WeatherIndications GetWeatherIndications();
    }


    [ClassInterface(ClassInterfaceType.None)]
    public class TestCom : ITestCom
    {

        private float m_fTemperature = 0;

        public TestCom()
        {
            m_fTemperature = 30.0f;
        }


        public float Temperature
        {
            get
            {
                return m_fTemperature;

            }/* end get */

            set
            {
                if ((value < -30) || (value > 150))
                {
                    TemperatureException excep =
              new TemperatureException("Marlinspike has never experienced such extreme temperatures. " +
                                   "Please recalibrate your thermometer");

                    throw excep;
                }

                m_fTemperature = value;

            }/* end set */

        }/* end get/set TestCom */


        public void DisplayCurrentTemperature()
        {
            String strTemp = "";
            strTemp = String.Format("The current temperature at Marlinspike is : " +
               "{0:####} degrees farenheit", m_fTemperature);
            MessageBox.Show(strTemp, "Today's TestCom");

        }/* end DisplayCurrentTemperature */


        public WeatherIndications GetWeatherIndications()
        {
            if (m_fTemperature > 70)
            {
                return WeatherIndications.Sunny;
            }
            else
            {
                // Let's keep this simple and just return Cloudy
                return WeatherIndications.Cloudy;
            }

        }/* end GetWeatherIndications */



        private void RegAsmAX()
        {
            Process prcss = new Process();
            try
            {
#if USE_CODE_ASDF98
                ProcessStartInfo prcssStartInfo = new ProcessStartInfo(getNetDir(), ViewerPath + AXfileNCom + " /codebase");
                prcssStartInfo.UseShellExecute = false;
                prcssStartInfo.RedirectStandardOutput = true;
                prcss.StartInfo = prcssStartInfo;
                prcss.Start();
                prcss.WaitForExit();
                //textBox1.AppendText("Exit CODE : " + prcss.ExitCode.ToString() + "\r\n");
#endif
            }
            catch (Exception ex)
            {
                //textBox1.AppendText("Error : " + ex.Message + "\r\n");
            }
            finally
            {
                prcss.Close();
                prcss.Dispose();
            }


        }

    }/* end class TestCom */


    class TemperatureException : ApplicationException
    {
        public TemperatureException(String message)
            : base(message)
        {
        }

    }/* end class TemperatureException */

