using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace AmosProjectIsraget
{
    static class Client
    {
        public static bool flagIfAlreadyOn = false;
        public static Socket socket = new Socket(AddressFamily.InterNetwork,
            SocketType.Stream,
            ProtocolType.Tcp);
        public static IPEndPoint newPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 5555);
        public static int msgRec = 0;
        public static String msgConverted = "";
        public static byte[] data = new byte[1024];
        public static string username;

        public static string BuildMessage(string msg, string type)
        {
            int[] arr = { 0, 0, 0, 0 };
            int size = msg.Length;
            for (int i = 3; i > -1; i--)
            {
                if (size <= 127)
                {
                    for (int j = i; j > 0; j--)
                    {
                        arr[j] = 0;
                    }
                    arr[i] = size;
                    break;
                }
                else if (size > 127)
                {
                    arr[i] = 127;
                    size -= 127;
                }
            }
            string message_send = type + (char)arr[0] + (char)arr[1] + (char)arr[2] + (char)arr[3] + msg;
            return message_send;
        }
        public static void Connect()
        {
            socket.Connect(newPoint);
        }

        public static string ReceiveMsgFromServer()
        {
            msgRec = socket.Receive(data);
            string msg = System.Text.Encoding.UTF8.GetString(data); // Rooms:...
            data = new byte[1048];
            //MessageBox.Show(msg);
            return msg;
        }
        public static void SendMsgToServer(string message)
        {
            byte[] forwardMessage = Encoding.Default.GetBytes(message);
            Client.socket.Send(forwardMessage);

        }
    }

}
