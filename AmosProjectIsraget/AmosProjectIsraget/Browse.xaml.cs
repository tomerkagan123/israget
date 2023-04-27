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
    /// Interaction logic for Browse.xaml
    /// </summary>
    public partial class Browse : Window
    {
        private Dictionary<int, string> allItems = new Dictionary<int, string>();
        public Browse()
        {
            InitializeComponent();
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
        private void Menu(object sender, RoutedEventArgs e)
        {
            Menu win = new Menu();
            win.Top = this.Top;
            win.Left = this.Left;
            Visibility = Visibility.Hidden;
            win.Show();
        }
        /*private void Refresh()
        {
            roombox.Items.Clear();
            string messageToSend = Client.BuildMessage(" ", "R");
            Client.SendMsgToServer(messageToSend);
            string recv = Client.ReceiveMsgFromServer();
            char ch = ';';
            int freq = recv.Count(x => (x == ch));
            recv = recv.Replace("Items;", String.Empty).Replace(";", String.Empty);
            String[] arrItems = recv.Split(',');
            String[][] arrItemsarr = new string[freq][];
            Client.arrayOfItemsArray = new Item[freq];
            for (int i = 0; i < freq; i++)
            {
                Item item = new Item();
                arrItemsarr[i] = arrItems[i].Split(":");
                item.user_name = arrItemsarr[i][0];
                item.item_name = arrItemsarr[i][1];
                item.date = arrItemsarr[i][2];
                item.description = arrItemsarr[i][3];
                item.price = Int32.Parse(arrItemsarr[i][5]);
                item.email = arrItemsarr[i][6];
                Client.arrayOfItemsArray[i] = item;
            }
            for (int i = 0; i < freq; i++)
            {
                Button button = new Button();
                button.Content = Client.arrayOfItemsArray[i].item_name;
                button.Click += ButtonClick;
                button.Height = 100;
                button.Width = 469;
                button.BorderThickness = new Thickness(0, 0, 0, 0); ;
                button.Background = new SolidColorBrush(Color.FromRgb(15, 15, 45));
                button.FontSize = 50;
                button.FontFamily = new FontFamily("Fonts/#Dosis");
                button.Foreground = new SolidColorBrush(Colors.White);
                Style style = this.FindResource("MyButton") as Style;
                button.Style = style;
                itembox.Items.Add(button);
            }
        }

        private void ButtonClick(object sender, RoutedEventArgs e)
        {
            var keyword = (e.Source as Button).Content.ToString();
            Item currItem = null;
            foreach (var item in Client.arrayOfItemsArray)
            {
                if (item.item_name == keyword)
                {
                    currItem = item;
                }
            }
            ItemWindow window = new ItemWindow(item);
            window.Top = this.Top;
            window.Left = this.Left;
            Visibility = Visibility.Hidden;
            window.Show();
        }*/


    }
}
