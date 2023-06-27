#include"information_management.h"

void ControlInfPrint(void)
{
    printf("1. Append record\n2. Search by name\n3. Search by ID\n4. Modify by ID\n5. Delete by ID\n6. Caculate total and average score of every student\n7. Caculate average score of every course\n8. Sort in descending order by course score\n9. Statistic analysis for every course\n10.Save record\n11.Load record\n12.Redisplay the prompt message\n0. Exit\n");
}

int ControNumGet(void)
{
    printf("Please enter your choice (you can enter 12 to chack massage):");
    int i;
    scanf("%d",&i);
    getchar();
    return i;
}