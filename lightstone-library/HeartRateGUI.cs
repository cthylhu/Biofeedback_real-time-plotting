using UnityEngine;
using System;
using System.Collections;
using System.IO.Ports;


public class HeartRateGUI : MonoBehaviour {
    public GUIText HRText;
    public int heartRate;
    public SerialPort mySerialPort;

	// Use this for initialization
	void Start () {
        Debug.Log("Log Start =======");
        heartRate = 0;
        UpdateHeartRateText();

        mySerialPort = new SerialPort("COM7",115200);  //Please change the Arduino Serial Port # here
        mySerialPort.Open();

        //mySerialPort.BaudRate = 115200;
        //mySerialPort.Parity = Parity.None;
        //mySerialPort.StopBits = StopBits.One;
        //mySerialPort.DataBits = 8;
        //mySerialPort.Handshake = Handshake.None;

        //mySerialPort.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);

        //mySerialPort.Open();

        //Console.WriteLine();
        //Console.ReadKey();
        //mySerialPort.Close();
	}
	
	// Update is called once per frame
	void Update () {
        string value = mySerialPort.ReadLine();
        string firstchar = value.Substring(0, 1);
        if (firstchar.Equals("B"))
        {
            heartRate = Int32.Parse(value.Substring(1));
            UpdateHeartRateText();
        }

        mySerialPort.BaseStream.Flush();
	}

    void UpdateHeartRateText() {
        Debug.Log("HR: " + heartRate);
        guiText.text = "Heart Rate: " + heartRate;
    }
    /*
    private void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
    {
        SerialPort sp = (SerialPort)sender;
        string indata = sp.ReadLine();// sp.ReadExisting();//
        //heartRate = Convert.ToInt32(indata);
        //Console.WriteLine("Data Received:");

        //Testing if heartrate changes
        heartRate = 65;
        
        
        String chfirst = indata.Substring(0, 1);
        if (chfirst.Equals("B"))
        {
            Console.WriteLine(indata);
            //Debug.Log(indata);
        }
    }
    */
}
