#ifndef _DATA_BUFFER_H
#define _DATA_BUFFER_H

#define BUFFER_SIZE 128

typedef struct _DATA_BUFFER_STRUCT
{
  int data[BUFFER_SIZE];
  int head;//head�����ݿ�ʼ��λ��
  int tail;//tail���������ݵ�λ��
}DATA_BUFFER_STRUCT;

#endif