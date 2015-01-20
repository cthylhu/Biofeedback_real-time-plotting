#include "stdafx.h"
#include "DataBuffer.h"

//是一个数组型的buffer，不是环型数组，因为环形数组不利于
//对buffer中数据的直接操作，一般需要将数据取出，然后操作，
//会增加一个数据复制的问题

BOOL EnterBufferString( DATA_BUFFER_STRUCT *p_buffer, int *p_data, int len )
{
  if( p_buffer->tail + len == BUFFER_SIZE + 1 )
    return FALSE;

  for( int i = 0; i != len; i++ )
  {
    p_buffer->data[p_buffer->tail] = p_data[i];
    p_buffer->tail++;
  }
  return TRUE;
}

BOOL EnterBufferChar( DATA_BUFFER_STRUCT *p_buffer, int data )
{
  if( p_buffer->tail  == BUFFER_SIZE - 1 )
    return FALSE;

  p_buffer->data[p_buffer->tail] = data;
  p_buffer->tail++;

  return TRUE;
}


