#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *fp = NULL;

    int len = 0;
    char *buffer;
    fp = fopen("hello.c", "r"); 
    if (fp == NULL)
    {
        return 0;
    }
    else
    {
        fseek(fp, 0, SEEK_END);
        len = ftell(fp);
        rewind(fp);
        buffer = malloc(len + 1); 
        for (int i = 0; i < len + 1; i++)
            buffer[i] = 0;
        int k; 
        k = fread(buffer, 1, len, fp);
        fclose(fp);
    }
    len = strlen(buffer);


    int flag = 0; 
    int end = 0;
    for (int i = 0; i < len; i++)
    {
        if (i % 16 == 0 && i != 0 && end == 0)
        { 
            printf("\n");
            if (flag == 0)
                i -= 16;
            flag = !flag;
        }
        if (!flag)
        { 
            if (buffer[i] == ' ')
                printf("SP\t");
            else if (buffer[i] == '\n')
                printf("\\n\t");
            else if (buffer[i] == '\t')
                printf("\\t\t");
            else
                printf("%c\t", buffer[i]);
        }
        else
        { 
            if (buffer[i] == ' ')
                printf("%d\t", ' ');
            else if (buffer[i] == '\n')
                printf("%d\t", '\n');
            else if (buffer[i] == '\t')
                printf("%d\t", '\t');
            else
                printf("%d\t", buffer[i]);
        }
        if (i + 1 == len && !end)
        {
            printf("\n");
            i -= (len % 16);
            flag = !flag;
            end = 1;
        }
    }
    free(buffer);
    return 0;
}