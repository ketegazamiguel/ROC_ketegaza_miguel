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

namespace RobotInterface
{
    /// <summary>
    /// Logique d'interaction pour MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        ReliableSerialPort serialPort1; 
        

        public MainWindow()
        {
            InitializeComponent();
            textBoxEmission.Text = "Bonjour";
            serialPort1 = new ReliableSerialPort("COM6", 115200, Parity.None, 8, StopBits.One);
            serialPort1.Open();



        }

        void envoyer() {

            textBoxReception.Text = textBoxReception.Text + "reçu: "+textBoxEmission.Text + "\n";
            textBoxEmission.Clear();

                }

        private void buttonEnvoyer_Click(object sender, RoutedEventArgs e)
        {
            buttonEnvoyer.Background = Brushes.RoyalBlue;
            if(buttonEnvoyer.Background == Brushes.RoyalBlue)
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
            if(e.Key == Key.Enter )
{
                envoyer();
            }
        }
    }
}
