#ifndef _DATA_BUFFER_H
#define _DATA_BUFFER_H

#define BUFFER_SIZE 128

typedef struct _DATA_BUFFER_STRUCT
{
  int data[BUFFER_SIZE];
  int head;//head是数据开始的位置
  int tail;//tail是增加数据的位置
}DATA_BUFFER_STRUCT;

#endif