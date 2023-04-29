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

namespace AmosProjectIsraget
{
    /// <summary>
    /// Interaction logic for ItemWindow.xaml
    /// </summary>
    public partial class ItemWindow : Window
    {
        public ItemWindow(Item item)
        {
            InitializeComponent();
            price.Text = item.price;
            email.Text = item.email;
            description.Text = item.description;
            username.Text = item.user_name;
            itemname.Text = item.item_name;

        }
        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);

            // Begin dragging the window
            this.DragMove();
        }
        private void CloseProgram(object sender, RoutedEventArgs e)
        {
            Client.SendMsgToServer("D");
            Client.socket.Close();
            System.Environment.Exit(0);
        }
        private void Browse(object sender, RoutedEventArgs e)
        {
            Browse win = new Browse();
            win.Top = this.Top;
            win.Left = this.Left;
            Visibility = Visibility.Hidden;
            win.Show();
        }
        private void Upload(object sender, RoutedEventArgs e)
        {
            Upload win = new Upload();
            win.Top = this.Top;
            win.Left = this.Left;
            Visibility = Visibility.Hidden;
            win.Show();
        }
    }
}
