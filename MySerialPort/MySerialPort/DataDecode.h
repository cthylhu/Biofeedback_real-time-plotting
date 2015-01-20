#ifndef _DATA_DECODE_H
#define _DATA_DECODE_H


double DataDecode( unsigned int *p_data, int len, const char *type );

int Hr_Cal( double ECGsignal);

int Hr_Cal1( double ECGsignal);

float Get_GSR (int GSR_value);

#endif