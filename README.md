real-time-plotting
==================

For biofeedback devices.

* Arduino IDE needs to be installed for the eHealth sensor
  (specifically the USB driver)

=======
Notes
==========

Reference
- Embedded Sensing and Computing Lab at University of Buffalo (http://www.cse.buffalo.edu/~wenyaoxu/esc.html)

accdata.txt columns:
1. GSR
2. Breathing rate
3. none

500 milliseconds - how long you wait to detect a peak
 - lower value - assume higher heart rate, but more noise
 - higher value - assume lower heart rate, less noise  

 
 -------------
 
 TeeChart5.ocx needs to be a registered activex component:
 
 Run::

   C:\Windows\System32\regsvr32.exe .\TeeChart5.ocx
   
 inside the MySerialPort/MySerialPort/ folder in the project.