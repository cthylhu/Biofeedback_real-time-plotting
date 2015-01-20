#include "stdafx.h"
#include "string.h"
#include "DataDecode.h"
//#include <iostream>
#include <Windows.h>
/*GSR*/
float GSR_voltage = 0;
float GSR_conductance = 0;
float GSR_resistance = 0; 

/*Hr Calcuation*/

//peak Detection HR
  double peakAG = 0;
  double sample = 0;
  double _attack = 0.9875;
  double _decay = 0.992;
  double gain;
  double sampleAG;
  double lower_bound = 0.9975;
  double upper_bound = 0.99;
  unsigned long currentMillis,previousMillis;
  int near_peak = 0;
  long Interval = 0;
//peak Detection Breathing
  double peakAG1 = 0;
  double sample1 = 0;
  double _attack1 = 0.9875;
  double _decay1 = 0.992;
  double gain1;
  double sampleAG1;
  double lower_bound1 = 0.9975;
  double upper_bound1 = 0.99;
  unsigned long currentMillis1,previousMillis1;
  int near_peak1 = 0;
  long Interval1 = 0;
// HR 
  int HRBeatCounter = 0;
  int HrBeatCN;
  double timeSum, HrBeat, HrBeatBuffer, HrBeatBufferSum;
  double timeBuffer [20];// = new double[11];
// Breatthing
  int HRBeatCounter1 = 0;
  int HrBeatCN1;
  double timeSum1, HrBeat1, HrBeatBuffer1, HrBeatBufferSum1;
  double timeBuffer1 [6];// = new double[11];

double DataDecode( unsigned int *p_data, int len, const char *type )
{
	double ftmp = 0;
	int int32tmp = 0;

	ASSERT(len >= 0 && len <= 4);

	//低位先接收
	for( int i = 0; i != len; i++ )
		int32tmp = int32tmp | (p_data[i]  << (i*8));

	if( int32tmp & (0X00000080 << (len - 1)*8) )
		int32tmp |= 0XFFFFFF80 << (len - 1)*8;

	if( strcmp( type, "AD8232" ) == 0 )
	    ftmp =  (((double)int32tmp * 5.0 ) / 1023)*2/1000*30;
	else if( strcmp( type, "ADXL345" ) == 0 )
		ftmp =  Get_GSR(int32tmp)*2/1000;
	else if( strcmp( type, "ADXL345_1" ) == 0 )
		ftmp = (((double)int32tmp * 5.0 ) / 1023)*2/1000*40;
	
	return ftmp;
}

int Hr_Cal( double ECGsignal)

{
	float ECG = ECGsignal;
	if (ECG > peakAG) 
      peakAG = _attack * ECG;
    else
      peakAG = _decay * peakAG;

    gain = _attack / peakAG;
    sampleAG = gain * ECG;  

    if (sampleAG >= lower_bound)
		near_peak = 1;   

    if ((near_peak == 1) && (sampleAG < upper_bound))
    {
       near_peak = 0;
       currentMillis = GetTickCount();
       //sw.Stop(); //stop the stopwatch
       Interval = currentMillis - previousMillis;
       //interval = sw.ElapsedMilliseconds;		//get the time interval
       HRBeatCounter++;							// if a peak is detected, the counter increases
       if (HRBeatCounter == 20)
       {
           HRBeatCounter = 1;
       } 
       if (Interval > 500)	// if the detected peak is very closed to the last peak (less than 500 milliseconds), we will ingore it.
       {		
           switch (HRBeatCounter)	// get the time interval in timeBuffer
             {						
                 case 1:
                 timeBuffer[1] = (double)(Interval) / 1000;
                 break;
                 case 2:
                 timeBuffer[2] = (double)(Interval) / 1000;
                 break;
                 case 3:
                 timeBuffer[3] = (double)(Interval) / 1000;
                 break;
                 case 4:
                 timeBuffer[4] = (double)(Interval) / 1000;
                 break;
                 case 5:
                 timeBuffer[5] = (double)(Interval) / 1000;
                 break;
                 case 6:
                 timeBuffer[6] = (double)(Interval) / 1000;
                 break;
                 case 7:
                 timeBuffer[7] = (double)(Interval) / 1000;
                 break;
                 case 8:
                 timeBuffer[8] = (double)(Interval) / 1000;
                 break;
                 case 9:
                 timeBuffer[9] = (double)(Interval) / 1000;
                 break;
                 case 10:
                 timeBuffer[10] = (double)(Interval) / 1000;
                 break;
                 case 11:
                 timeBuffer[11] = (double)(Interval) / 1000;
                 break;
                 case 12:
                 timeBuffer[12] = (double)(Interval) / 1000;
                 break;
                 case 13:
                 timeBuffer[13] = (double)(Interval) / 1000;
                 break;
                 case 14:
                 timeBuffer[14] = (double)(Interval) / 1000;
                 break;
                 case 15:
                 timeBuffer[15] = (double)(Interval) / 1000;
                 break;
                 case 16:
                 timeBuffer[16] = (double)(Interval) / 1000;
                 break;
                 case 17:
                 timeBuffer[17] = (double)(Interval) / 1000;
                 break;
                 case 18:
                 timeBuffer[18] = (double)(Interval) / 1000;
                 break;
                 case 19:
                 timeBuffer[19] = (double)(Interval) / 1000;
                 break;

                 default:
                 break;
         }

         if (((timeBuffer[10] != 0) && (timeBuffer[9] != 0) && (timeBuffer[8] != 0) && (timeBuffer[7] != 0) && (timeBuffer[6] != 0) && (timeBuffer[5] != 0) && (timeBuffer[4] != 0) && (timeBuffer[3] != 0) && (timeBuffer[2] != 0) && (timeBuffer[1] != 0))&&((timeBuffer[19] != 0) && (timeBuffer[18] != 0) && (timeBuffer[17] != 0) && (timeBuffer[16] != 0) && (timeBuffer[15] != 0) && (timeBuffer[14] != 0) && (timeBuffer[13] != 0) && (timeBuffer[12] != 0) && (timeBuffer[11] != 0)))
         {
               for (int i = 1; i < 20; i++)
                  {
                     timeSum = timeSum + timeBuffer[i];
                  }
               //get the heart rate beat
               if (timeSum != 0)
                 {
                     HrBeatBuffer = 20 / timeSum * 60;
					 HrBeatCN ++;// = HrBeat
                 }
			   HrBeatBufferSum = HrBeatBufferSum + HrBeatBuffer;
               timeSum = 0;
			}
		 if (HrBeatCN == 3)
		 {
			HrBeat = HrBeatBufferSum/3;
			HrBeatBufferSum = 0;
			HrBeatCN = 0;
		 }
        previousMillis = currentMillis;
//        Serial.println(HrBeat);
//        Hr_low = lowByte((int)HrBeat);
//        Hr_high = highByte((int)HrBeat);
//        message[4] = Hr_low;
//        message[5] = Hr_high;
//        Serial.write(message, sizeof(message));
//        return (int)HrBeat;
     }   
   } 

	return HrBeat;
}


int Hr_Cal1( double ECGsignal)

{
	float ECG1 = ECGsignal;
	if (ECG1 > peakAG1) 
      peakAG1 = _attack1 * ECG1;
    else
      peakAG1 = _decay1 * peakAG1;
    gain1 = _attack1 / peakAG1;
    sampleAG1 = gain1 * ECG1;  
    if (sampleAG1 >= lower_bound1)
    near_peak1 = 1;   
    if ((near_peak1 == 1) && (sampleAG1 < upper_bound1))
    {
       near_peak1 = 0;
       currentMillis1 = GetTickCount();
       //sw.Stop(); //stop the stopwatch
       Interval1 = currentMillis1 - previousMillis1;
       //interval = sw.ElapsedMilliseconds;		//get the time interval
       HRBeatCounter1++;		//if a peak is detected, the counter increases
       if (HRBeatCounter1 == 6)
       {
           HRBeatCounter1 = 1;
       } 
       if (Interval1 > 500)	//if the detected peak is very closed to the last peak (less than 500 milliseconds), we will ingore it.
       {	
           switch (HRBeatCounter1)	//get the time interval in timeBuffer
             {						
                 case 1:
                 timeBuffer1[1] = (double)(Interval1) / 1000;
                 break;
                 case 2:
                 timeBuffer1[2] = (double)(Interval1) / 1000;
                 break;
                 case 3:
                 timeBuffer1[3] = (double)(Interval1) / 1000;
                 break;
                 case 4:
                 timeBuffer1[4] = (double)(Interval1) / 1000;
                 break;
                 case 5:
                 timeBuffer1[5] = (double)(Interval1) / 1000;
                 break;

                 default:
                 break;
         }
         if ((timeBuffer1[5] != 0) && (timeBuffer1[4] != 0) && (timeBuffer1[3] != 0) && (timeBuffer1[2] != 0) && (timeBuffer1[1] != 0))
           {
               for (int i = 1; i < 5; i++)
                  {
                     timeSum1 = timeSum1 + timeBuffer1[i];
                  }
               //get the heart rate beat
               if (timeSum1 != 0)
                 {
                     HrBeatBuffer1 = 5 / timeSum1 * 60;
					 //HrBeatCN1 ++;// = HrBeat
                 }
			   HrBeat1 = HrBeatBuffer1;
			   //HrBeatBufferSum1 = HrBeatBufferSum + HrBeatBuffer;
               timeSum1 = 0;
			}

        previousMillis1 = currentMillis1;
//        Serial.println(HrBeat);
//        Hr_low = lowByte((int)HrBeat);
//        Hr_high = highByte((int)HrBeat);
//        message[4] = Hr_low;
//        message[5] = Hr_high;
//        Serial.write(message, sizeof(message));
//        return (int)HrBeat;
     }   
   } 

	return HrBeat1;
}

float Get_GSR (int GSR_value)
{
		// Read an analogic value from analogic2 pin and convert
		GSR_voltage = GSR_value*5.0/1023;

		// Use given formula to get the conductance, unit is S.
		// Sensor calibration: Subtract 0.5V for offset (board is powered by 0.5V)
		GSR_conductance = 2*((GSR_voltage - 0.5) / 100000); // R = V/I, C = 1/R
		
		GSR_resistance = 1 / GSR_conductance; 
		GSR_conductance = GSR_conductance*1000000;	// Change the unit from S to mS, 
													// Normally the conductance for a human is 0-100 mS. 
		
		//if (GSR_conductance > 0) 	
			//return GSR_conductance;	//return the conductance only it is valid.
		//else return 0;
		return GSR_conductance;
}