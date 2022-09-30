#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fileop.h"
#include "fileop.c"
int main(int argc, char *argv[])
{
    char space = ' ';
    char n = '\n';
    int test;
    for (test = 0; test < argc; test++)
    {
        printf("%s", argv[test]);
    }
    char par = *argv[1];
    if (par - '0' == 1)
    {
        myrecord record[4];        //记录数据
        int i = 0;                 //结构体数组下标
        char Buffer[101] = {0};    //缓冲区，读取每一行的数据
        FILE *fp = NULL;           //文件指针
        fp = fopen(argv[2], "r+"); //以读写的方式打开testfile文件
        FILE *dp = NULL;
        dp = fopen(argv[3], "wb");
        if (fp == NULL || dp == NULL) //未能成功打开文件
        {
            printf("error can't open the file");
            perror;
            exit(0);
        }
        else
        {

            while (fgets(Buffer, 100, fp) != NULL)
            {

                input_data(i, record, Buffer); //将Buffer里的数据填入record的第i位
                printf("%ld:%s;%.1f;%.1f;%.1f;%.1f\n", record[i].id, record[i].name, record[i].score[0], record[i].score[1], record[i].score[2], record[i].score[3]);
                //输出数据
                i++;
            }
            fwrite(record, sizeof(record), 4, dp);
        }
        fclose(fp); //关闭文件
        fclose(dp);
    }
    if (par - '0' == 2)
    {
        char space = ' ';
        char n = '\n';
        myrecord record[4]; //记录数据
        int i = 0;          //结构体数组下标
        // char Buffer[101] = {0};          //缓冲区，读取每一行的数据
        FILE *fp = NULL;           //文件指针
        fp = fopen(argv[2], "rb"); //以读写的方式打开testfile文件
        FILE *dp = NULL;
        dp = fopen(argv[3], "w+");
        if (fp == NULL || dp == NULL) //未能成功打开文件
        {
            printf("error can't open the file");
            perror;
            exit(0);
        }
        else
        {
            fread(record, sizeof(record), 4, fp);
            while (i < 4)
            {
                printf("%ld:%s;%.1f;%.1f;%.1f;%.1f\n", record[i].id, record[i].name, record[i].score[0], record[i].score[1], record[i].score[2], record[i].score[3]);
                ++i;
            }
            for (i = 0; i < 4; i++)
            {

                fprintf(dp, "%ld %s %f %f %f %f\n", record[i].id, record[i].name, record[i].score[0], record[i].score[1], record[i].score[2], record[i].score[3]);
            }
        }
        fclose(fp); //关闭文件
        fclose(dp);
    }

    return 0;
}
