#ifndef FILEOP_H
#define FILEOP_H

#include"Define.h"

void OutputData(char *data);//将译码结果写入文件
void OutputCode(char *code);//将编码结果写入文件
void GetData(char **data);//从文件读入输入
void OutputHufcode(char **hufcode,int kind);//将哈夫曼码对照表输出到文件
void GetHufcode(char **hufcode);//从文件读入哈夫曼码对照表


#endif