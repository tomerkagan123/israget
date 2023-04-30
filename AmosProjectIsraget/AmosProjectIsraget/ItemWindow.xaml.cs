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
using System.Xml.Schema;

namespace AmosProjectIsraget
{
    /// <summary>
    /// Interaction logic for ItemWindow.xaml
    /// </summary>
    public partial class ItemWindow : Window
    {
        DispatcherTimer LiveTime = new DispatcherTimer();
        public ItemWindow(Item item)
        {
            InitializeComponent();
            LiveTimeLabel.Content = DateTime.Now.ToString("HH:mm");
            LiveTime.Interval = TimeSpan.FromSeconds(1);
            LiveTime.Tick += timer_Tick;
            LiveTime.Start();
            price.Text = item.price;
            email.Text = item.email;
            description.Text = item.description;
            username.Text = item.user_name;
            itemname.Text = item.item_name;
            if(username.Text == Client.username)
            {
                delete.Content = "Delete Item";
                delete.Click += Delete;
            }

        }
        private void Delete(object sender, RoutedEventArgs e)
        {
            string message = "{\"user_name\":\"" + Client.username + "\",\"item_name\":\"" + itemname.Text +"\",\"description\":\"" + description.Text;
            message += "\"}";
            string messageToSend = Client.BuildMessage(message, "X");
            Client.SendMsgToServer(messageToSend);
            string recv = Client.ReceiveMsgFromServer();
            MessageBox.Show("Successfully Deleted " + itemname.Text);
            Browse(this, null)
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
            LiveTime = null;
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
        private void Upload(object sender, RoutedEventArgs e)
        {
            LiveTime.Stop();
            LiveTime.Tick -= timer_Tick;
            LiveTime = null;
            Upload win = new Upload();
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
    }
}
