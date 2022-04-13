using ExtendedSerialPort;
using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace RobotInterface
{
    /// <summary>
    /// Logique d'interaction pour MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        ReliableSerialPort serialPort1;
        DispatcherTimer timerAffichage;

        Robot robot = new Robot();

        public MainWindow()
        {
            InitializeComponent();
            // textBoxEmission.Text = "Bonjour";
            serialPort1 = new ReliableSerialPort("COM6", 115200, Parity.None, 8, StopBits.One);
            serialPort1.DataReceived += SerialPort1_DataReceived;
            serialPort1.Open();
            /// timer 
            timerAffichage = new DispatcherTimer();
            timerAffichage.Interval = new TimeSpan(0, 0, 0, 0, 100);
            timerAffichage.Tick += TimerAffichage_Tick;
            timerAffichage.Start();




        }

        private void TimerAffichage_Tick(object sender, EventArgs e)
        {
            while(robot.byteListReceived.Count>0)            
            {
                //textBoxReception.Text += receivedText;
                //receivedText = "";
                textBoxReception.Text += " 0x" + robot.byteListReceived.Dequeue().ToString("X2");
               
            }
        }
                

        private void SerialPort1_DataReceived(object sender, DataReceivedArgs e)
        {
            //throw new NotImplementedException();
            //receivedText += Encoding.UTF8.GetString(e.Data, 0, e.Data.Length);
            //robot.receivedText += Encoding.UTF8.GetString(e.Data, 0, e.Data.Length);
            

            foreach (byte c in e.Data)
            {
                robot.byteListReceived.Enqueue(c);
            }
        }



        void envoyer()
        {
            serialPort1.Write(textBoxEmission.Text);
            textBoxEmission.Clear();
        }

        private void buttonEnvoyer_Click(object sender, RoutedEventArgs e)
        {
            buttonEnvoyer.Background = Brushes.RoyalBlue;
            if (buttonEnvoyer.Background == Brushes.RoyalBlue)
            {
                buttonEnvoyer.Background = Brushes.Beige;
            }

            else
            {
                buttonEnvoyer.Background = Brushes.RoyalBlue;
            }

            envoyer();

        }

        private void textBoxEmission_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                envoyer();
            }
        }

        private void buttonClear_Click(object sender, RoutedEventArgs e)
        {
            textBoxReception.Clear();
        }

        private void buttonTest_Click(object sender, RoutedEventArgs e)
        {
            byte[] byteList = new byte[20];
            for (int i = 0; i < 20; i++)
            {
                byteList[i] = (byte)(2 * i);
            }
            serialPort1.Write(byteList, 0, byteList.Length);
            textBoxEmission.Clear();

        }
    }
   
}
