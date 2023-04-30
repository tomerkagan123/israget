using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
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

namespace AmosProjectIsraget
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            try
            {
                if (!Client.flagIfAlreadyOn)
                {
                    Client.socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                    Client.Connect();
                    Client.flagIfAlreadyOn = true;
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                System.Environment.Exit(0);
            }
            InitializeComponent();
        }
        private void CloseProgram(object sender, RoutedEventArgs e)
        {
            Client.SendMsgToServer("D");
            Client.socket.Close();
            System.Environment.Exit(0);
        }
        private void LoginUser(object sender, RoutedEventArgs e)
        {
            string user = username.Text;
            Client.username = user;
            string pass = password.Password;
            string message = "{\"username\":\"" + user + "\",\"password\":\"" + pass + "\"}";
            string messageToSend = Client.BuildMessage(message, "L"); //"L": login request
            Client.SendMsgToServer(messageToSend);
            string recv = Client.ReceiveMsgFromServer();
            if (recv.Contains("Successful"))
            {
                Menu newWindow = new Menu();
                this.Visibility = Visibility.Hidden;
                newWindow.Show(); //moves to next screen
                this.Close();
            }
        }
        private void SignupPage(object sender, RoutedEventArgs e)
        {
            SignupWindow window = new SignupWindow();
            Visibility = Visibility.Hidden;
            window.Show();
            this.Close();
        }
    }
}
