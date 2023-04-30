using System;
using System.Collections.Generic;
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
using System.Windows.Shapes;
using System.Windows.Threading;

namespace AmosProjectIsraget
{
    /// <summary>
    /// Interaction logic for Upload.xaml
    /// </summary>
    public partial class Upload : Window
    {
        DispatcherTimer LiveTime = new DispatcherTimer();
        public Upload()
        {
            InitializeComponent();
            LiveTimeLabel.Content = DateTime.Now.ToString("HH:mm");
            LiveTime.Interval = TimeSpan.FromSeconds(1);
            LiveTime.Tick += timer_Tick;
            LiveTime.Start();
        }
        void timer_Tick(object sender, EventArgs e)
        {
            LiveTimeLabel.Content = DateTime.Now.ToString("HH:mm");
        }
        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);

            // Begin dragging the window
            this.DragMove();
        }
        private void CloseProgram(object sender, RoutedEventArgs e)
        {
            LiveTime.Stop();
            LiveTime.Tick -= timer_Tick;
            Client.SendMsgToServer("D");
            Client.socket.Close();
            System.Environment.Exit(0);
        }
        private void Browse(object sender, RoutedEventArgs e)
        {
            LiveTime.Stop();
            LiveTime.Tick -= timer_Tick;
            LiveTime = null;
            Browse win = new Browse();
            win.Top = this.Top;
            win.Left = this.Left;
            Visibility = Visibility.Hidden;
            win.Show();
            this.Close();
        }
        private void Menu(object sender, RoutedEventArgs e)
        {
            LiveTime.Stop();
            LiveTime.Tick -= timer_Tick;
            LiveTime = null;
            Menu win = new Menu();
            win.Top = this.Top;
            win.Left = this.Left;
            Visibility = Visibility.Hidden;
            win.Show();
            this.Close();
        }
        private void CreateItem(object sender, RoutedEventArgs e)
        {
            Item item = new Item();
            item.email = contact.Text;
            item.price = price.Text;
            item.description = description.Text;
            item.item_name = itemname.Text;
            item.user_name = Client.username;
            if (item.description == string.Empty || item.description.Contains(';') || item.description.Contains(','))
            {
                MessageBox.Show("Don't even try...");
                return;
            }
            if (item.email == string.Empty || item.email.Contains(';') || item.email.Contains(','))
            {
                MessageBox.Show("Don't even try...");
                return;
            }
            if (item.item_name == string.Empty || item.item_name.Contains(';') || item.item_name.Contains(','))
            {
                MessageBox.Show("Don't even try...");
                return;
            }
            if (item.user_name == string.Empty || item.user_name.Contains(';') || item.user_name.Contains(','))
            {
                MessageBox.Show("Don't even try...");
                return;
            }
            if (!(int.TryParse(item.price, out int n)))
            {
                item.price = "1";
            }
            string messageToSend = Client.BuildMessage("{\"userName\":\"" + item.user_name + "\",\"itemName\":\"" + item.item_name + "\",\"description\":\"" + item.description + "\",\"price\":\"" + item.price + "\",\"email\":\"" + item.email + "\"}", "C");
            Client.SendMsgToServer(messageToSend);
            string recv = Client.ReceiveMsgFromServer();
            if (recv.Contains("Success"))
            {
                /*LiveTime.Stop();
                string id = String.Join("", recv.Where(char.IsDigit));
                room.name = roomName;
                room.id = id;
                room.maxPlayers = players;
                room.currPlayers = "1";
                RoomWindow window = new RoomWindow(room);
                window.Top = this.Top;
                window.Left = this.Left;
                Visibility = Visibility.Hidden;
                window.Show();*/
                MessageBox.Show("Success!");
            }
            if (recv.Contains("Failure"))
            {
                MessageBox.Show("Try again");
            }
        }

    }
}

