#ifndef DECODE_H
#define DECODE_H

#include "Define.h"

char *FindCode(char *code, char **Hufcode, int *location); //匹配当前未处理编码，返回匹配之后的编码指针位置和字符
void Decode(char *data, char **Hufcode, char *code);       //根据hufcode解码code并存储在data里

#endif