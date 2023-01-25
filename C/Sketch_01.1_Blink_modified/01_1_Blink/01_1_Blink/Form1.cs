using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.ProgressBar;

namespace _01_1_Blink
{
    public partial class Form1 : Form
    {
        // Global variables
        bool rasp_Connected = false;
        bool led_Blinking = false;
        SerialPort serialPort_Rasp;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // Set port names in comboBox
            comboBox_Ports.DataSource = SerialPort.GetPortNames();
            this.Closing += new CancelEventHandler(this.Form1_Closing);
        }

        private void Form1_Closing(object sender, CancelEventArgs e)
        {
            // Stop serial communication if window closes
            if(rasp_Connected)
            {
                serialPort_Rasp.Write("0");
                serialPort_Rasp.Close();
                serialPort_Rasp.Dispose();
            }
        }

        private void button_Connect_Disconnect_Click(object sender, EventArgs e)
        {
            try
            {
                // Start serial communication
                serialPort_Rasp = new SerialPort(comboBox_Ports.SelectedItem.ToString(), 9600);
                serialPort_Rasp.DtrEnable = true;
                serialPort_Rasp.RtsEnable = true;
                if (!rasp_Connected)
                {
                    serialPort_Rasp.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);    // Handle serial data received
                    serialPort_Rasp.Open(); // Open serial port
                    rasp_Connected = true;
                    MessageBox.Show("Serial port connected!");
                    button_Connect_Disconnect.Text = "Disconnect";
                }
                else
                {
                    serialPort_Rasp.Close();    // Close serial port
                    serialPort_Rasp.Dispose();  // Free resources
                    rasp_Connected = false;
                    MessageBox.Show("Serial port disconnected!");
                    button_Connect_Disconnect.Text = "Connect";
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void button_Start_Stop_Blinking_Click(object sender, EventArgs e)
        {
            try
            {
                if (rasp_Connected)
                {
                    if (!led_Blinking)
                    {
                        serialPort_Rasp.Write("1"); // Start blinking
                        led_Blinking = true;
                        button_Start_Stop_Blinking.Text = "Stop blinking";
                    }
                    else
                    {
                        serialPort_Rasp.Write("0"); // Stop blinking
                        led_Blinking = false;
                        button_Start_Stop_Blinking.Text = "Start blinking";
                    }
                }
                else
                {
                    MessageBox.Show("Connect to a port before sending!");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        // Function to handle serial data received
        private void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            string indata = sp.ReadExisting();
            if(indata == "1")
            {
                button_LED.BackColor = Color.Red;
            }
            else
            {
                button_LED.BackColor = Color.White;
            }
        }
    }
}
