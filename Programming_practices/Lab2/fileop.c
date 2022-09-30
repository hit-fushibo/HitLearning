#include"fileop.h"
int char_to_int(char *a) //将字符串a转换为整数
{
    int i = 0; //对应的整数
    int j = 0;
    for (; a[j] != '\0' && a[j] != '\n'; j++)
    {
        i = i * 10 + (a[j] - '0');
    }
    return i;
}
int read_data(char *a, char *data) //将a当前位置到最近的空格之间的所有字符复制到data上
{

    int i = 0; //用来复制
    for (i = 0; *a != '\0' && *a != '\n' && *a != ' ' && i < 30; i++, a++)
    {
        data[i] = *a;
    }
    return i;
}
int skip_space(char *a) //跳过空格
{
    int i = 0;
    for (; *a == ' '; a++, i++)
        ;
    return i;
}
int input_data(int location, struct myrecord data[], char *input) //将字符串c输入到结构体数组的第a个元素
{
    int i = 0;
    char *temp = input;
    char **endstr;
    char tempdata[30] = {0};
    temp += read_data(temp, tempdata);
    data[location].id = char_to_int(tempdata);
    temp += skip_space(temp);
    temp += read_data(temp, tempdata);
    strcpy(data[location].name, tempdata);
    temp += skip_space(temp);
    temp += read_data(temp, tempdata);
    data[location].score[0] = strtod(tempdata, endstr);
    if (*temp == '\0' || *temp == '\n')
    {
        data[location].score[1] = 0;
        data[location].score[2] = 0;
        data[location].score[3] = 0;
        return 0;
    }
    temp += skip_space(temp);
    temp += read_data(temp, tempdata);
    data[location].score[1] = strtod(tempdata, endstr);
    if (*temp == '\0' || *temp == '\n')
    {
        data[location].score[2] = 0;
        data[location].score[3] = 0;
        return 0;
    }
    temp += skip_space(temp);
    temp += read_data(temp, tempdata);
    data[location].score[2] = strtod(tempdata, endstr);
    if (*temp == '\0' || *temp == '\n')
    {
        data[location].score[3] = 0;
        return 0;
    }
    temp += skip_space(temp);
    temp += read_data(temp, tempdata);
    data[location].score[3] = strtod(tempdata, endstr);
}