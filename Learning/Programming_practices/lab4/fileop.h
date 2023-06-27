#ifndef _FILEOP_H_
#define _FILEOP_H_
#include"information_management.h"

void input_data(int location, struct STU data[], char *input);              //将字符串c输入到结构体数组的第a个元素
int txtread(FILE * fp,STU *data,int size);
void txtprint(FILE * fp,STU *data,int size);
int read_data(char *a, char *data);
int skip_space(char *a);
int txtsize(FILE * fp);

#endif
