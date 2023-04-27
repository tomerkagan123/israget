using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace AmosProjectIsraget
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        protected override void OnExit(ExitEventArgs e)
        {
            try
            {
                Client.SendMsgToServer("D");
                Client.socket.Close();
                System.Environment.Exit(0);
            }
            finally
            {
                base.OnExit(e);
            }
        }
    }
}
