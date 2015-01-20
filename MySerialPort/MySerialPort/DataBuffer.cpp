#include "stdafx.h"
#include "DataBuffer.h"

//��һ�������͵�buffer�����ǻ������飬��Ϊ�������鲻����
//��buffer�����ݵ�ֱ�Ӳ�����һ����Ҫ������ȡ����Ȼ�������
//������һ�����ݸ��Ƶ�����

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


