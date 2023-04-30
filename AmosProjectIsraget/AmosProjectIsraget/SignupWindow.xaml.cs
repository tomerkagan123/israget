using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace AmosProjectIsraget
{
    /// <summary>
    /// Interaction logic for SignupWindow.xaml
    /// </summary>
    public partial class SignupWindow : Window
    {
        public SignupWindow()
        {
            InitializeComponent();
        }
        private void ClearBox(object sender, RoutedEventArgs e)
        {
            username.Clear();
            password.Clear();
            email.Clear();
        }
        private void CloseProgram(object sender, RoutedEventArgs e)
        {
            Client.SendMsgToServer("D");
            Client.socket.Close();
            System.Environment.Exit(0);
        }
        private void SignupUser(object sender, RoutedEventArgs e)
        {
            if(username.Text.Length > 10)
            {
                MessageBox.Show("Name too long...");
                return;
            }
            if (password.Password.Length > 10)
            {
                MessageBox.Show("Password too long!");
                return;
            }
            if (email.Text.Length > 20)
            {
                MessageBox.Show("Email too long.");
                return;
            }
            string user = username.Text;
            string pass = password.Password;
            string mail = email.Text;
            string message = "{\"username\":\"" + user + "\",\"password\":\"" + pass + "\",\"email\":\"" + mail + "\"}";
            string messageToSend = Client.BuildMessage(message, "S");
            Client.SendMsgToServer(messageToSend);
            string recv = Client.ReceiveMsgFromServer();
            if (recv.Contains("Succeeded"))
            {
                LoginPage(sender, e);
            }
        }
        private void LoginPage(object sender, RoutedEventArgs e)
        {
            Visibility = Visibility.Hidden;
            MainWindow newWindow = new MainWindow();
            newWindow.Show(); //moves to next screen
            this.Close();
        }
    }
}
