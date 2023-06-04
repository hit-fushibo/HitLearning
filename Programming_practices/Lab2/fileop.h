#ifndef _FILEOP_H_
#define _FILEOP_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct myrecord
{
    unsigned long id;
    char name[32];
    float score[4];
}myrecord;
int input_data(int location, struct myrecord data[], char *input); //将字符串c输入到结构体数组的第a个元素
int char_to_int(char *a);                                          //将字符串a转换为整数
float char_to_float(char *a);                                      //将字符串a转换为浮点数 可以用strtod函数
int read_data(char *a, char *data);                                //将a当前位置到最近的空格之间的所有字符复制到data上
int skip_space(char *a);                                           //跳过空格

#endif