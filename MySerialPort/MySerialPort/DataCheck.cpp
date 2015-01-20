#include "stdafx.h"
#include "DataCheck.h"

#define POLYNOMIAL_16 0X8408
#define PRESET_VALUE_16 0xFFFF
#define POLYNOMIAL_8 0X31
#define PRESET_VALUE_8 0xFF

static unsigned short CRC_16( unsigned char *pData, int len );
static unsigned char CRC_8( unsigned char *pData, int len );

unsigned short CRC_16( unsigned char *pData, int len )
{
  unsigned short crc_value = PRESET_VALUE_16;

  for( int i = 0; i != len; i++ )  /*len=number of protocol bytes without CRC*/
  {
    crc_value = crc_value ^ ( (unsigned short)pData[i] << 8 );
    for( int j = 0; j != 8; j++ )
	  {
	    if( crc_value & 0x8000 )
	      crc_value = ( crc_value << 1 ) ^ POLYNOMIAL_16;
	    else
        crc_value = crc_value << 1 ;
	  }
    crc_value &= 0XFFFF;
  }
  return crc_value;
}

unsigned char CRC_8( unsigned char *pData, int len )
{
  unsigned char crc_value = PRESET_VALUE_8;

  for( int i = 0; i != len; i++ )  /*len=number of protocol bytes without CRC*/
  {
    crc_value = crc_value ^ ( (unsigned int)pData[i] );
    for( int j = 0; j != 8; j++ )
    {
      if( crc_value & 0x80 )
        crc_value = ( crc_value << 1 ) ^ POLYNOMIAL_8;
      else
        crc_value = crc_value << 1 ;
    }
    crc_value &= 0XFF;
  }
  return crc_value;
}

BOOL CheckData( unsigned int *p_data, unsigned int len )
{
	unsigned char *p_pack_date = NULL;
  p_pack_date = (unsigned char *)malloc(len * sizeof(char));

	if( len < 4 )
		return FALSE;

	for( int i = 0; i != len - 1; i++ )
    p_pack_date[i] = (unsigned char)p_data[i];

  unsigned int crc_value = CRC_8( p_pack_date, len - 1 );

  return crc_value == p_data[len-1];
}

