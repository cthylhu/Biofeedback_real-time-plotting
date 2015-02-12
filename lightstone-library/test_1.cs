using UnityEngine;
using System;
using System.Collections;
using System.Runtime.InteropServices;

public class test : MonoBehaviour {
	public GUIText HRText;
	public int heartRate;
	public float scldata;

	[DllImport("C:/Users/azhang/Desktop/WildDivine/lightstone_scl.dll")]//
	extern static int lightstone_Initial();
	
	[DllImport("C:/Users/azhang/Desktop/WildDivine/lightstone_scl.dll")]
	extern static int lightstone_ReadBPM();

	[DllImport("C:/Users/azhang/Desktop/WildDivine/lightstone_scl.dll")]
	extern static float lightstone_Readscl();

	[DllImport("C:/Users/azhang/Desktop/WildDivine/lightstone_scl.dll")]
	extern static int lightstone_Exit();
	
	// Use this for initialization
	void Start () {
		Debug.Log("Log Start =======");
		int p = lightstone_Initial();
	}
	
	// Update is called once per frame
	void Update () {
		heartRate = lightstone_ReadBPM();
		scldata = lightstone_Readscl();
		UpdateHeartRateText();
	}
	
	void UpdateHeartRateText() {
		Debug.Log("HR: " + heartRate);
		guiText.text = "Heart Rate: " + heartRate +", Skin Conduct: "+ scldata;
	}

	void OnApplicationQuit()
	{
		Debug.Log("Test Exit");
		lightstone_Exit();
	}
}