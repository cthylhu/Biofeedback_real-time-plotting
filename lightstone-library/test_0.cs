using UnityEngine;
using System;
using System.Collections;
using System.Runtime.InteropServices;

public class test : MonoBehaviour {
	public GUIText HRText;
	public int heartRate;

    //My dll path is C:\Users\azhang\Desktop\WildDivine\, please change the path in your own PC
	[DllImport(@"C:\Users\azhang\Desktop\WildDivine\lightstone.dll")]
	extern static int lightstone_Initial();

    //My dll path is C:\Users\azhang\Desktop\WildDivine\, please change the path in your own PC
	[DllImport(@"C:\Users\azhang\Desktop\WildDivine\lightstone.dll")]
	extern static int lightstone_ReadBPM();

    //My dll path is C:\Users\azhang\Desktop\WildDivine\, please change the path in your own PC
	[DllImport(@"C:\Users\azhang\Desktop\WildDivine\lightstone.dll")]
	extern static int lightstone_Exit();
	
	// Use this for initialization
	void Start () {
		Debug.Log("Log Start =======");
		int p = lightstone_Initial();
	}
	
	// Update is called once per frame
	void Update () {
		heartRate = lightstone_ReadBPM();
		UpdateHeartRateText();
	}
	
	void UpdateHeartRateText() {
		Debug.Log("HR: " + heartRate);
		guiText.text = "Heart Rate: " + heartRate;
	}

	void OnApplicationQuit()
	{
		Debug.Log("Test Exit");
		lightstone_Exit();
	}
}