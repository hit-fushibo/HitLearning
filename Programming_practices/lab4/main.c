#include"information_management.h"
#include"fileop.h"
#include"sort.h"
#include"analysis-inf.c"
#include"control.c"
#include"fileop.c"
#include"infprint.c"
#include"search.c"
#include"sort.c"

int main (void)
{   
    //ctr:用来控制程序运行哪一个子程序
    int ctr=-1;
    //flag:控制程序是否结束
    int flag=1;

    //存储数据
    STU * record;
    //数据大小
    int size=0;
    //用来指示数组是否初始化
    int initialize=0;

    //存储search后的结果
    int SearchResult=-1;

    ControlInfPrint();
    while(flag)
    {
        ctr=ControNumGet();
        //ctr = 11;
        switch(ctr)
        {
            //Exit
            case 0 :
            flag=0;
            break;

            //Append record
            case 1 :
            {
                printf("Plese enter the number of student:(now %d data)",size);
                int insize;
                scanf("%d",&insize);getchar();
                if(initialize==0)
                {
                    record=(STU * )malloc(sizeof(STU)*size);
                    initialize=1;
                    for(int i=0;i<insize;i++)
                    {
                        printf("Please enter the %d student's information(NOTICE:input format must be \"ID NAME SCORE1 SCORE2 SCORE3 SCORE4\")\n",i+1);
                        scanf("%s %s %f %f %f %f",record[i].id,record[i].name,&record[i].score[0],&record[i].score[1],&record[i].score[2],&record[i].score[3]);
                        getchar();
                    }
                }
                else
                {
                    STU * buff;
                    buff=(STU * )malloc(sizeof(STU)*(size+insize));
                    memcpy(buff,record,sizeof(STU)*(size));
                    for(int i=size;i<(size+insize);i++)
                    {
                        printf("Please enter the %d student's information(NOTICE:input format must be \"ID NAME SCORE1 SCORE2 SCORE3 SCORE4\")\n",i+1);
                        scanf("%s %s %f %f %f %f",buff[i].id,buff[i].name,&buff[i].score[0],&buff[i].score[1],&buff[i].score[2],&buff[i].score[3]);
                        getchar();
                    }
                    free(record);
                    record=(STU * )malloc(sizeof(STU)*(size+insize));
                    memcpy(record,buff,sizeof(STU)*(size+insize));
                    size +=insize;
                }
            }
            break;

            //Search by name
            case 2 :
            {
                if(initialize==0)
                {
                    printf("ERROE:Data is not populated!Please use 1 or 11 to fill in the data.\n");
                }
                else
                {
                    int inflag=1;
                    while(inflag)
                    {
                        char name[20];
                        printf("Please enter the name you want to search:");
                        gets(name);
                        SearchResult=NameSearch(record,name,size);
                        if(SearchResult==-1)
                        {
                            printf("%s is not in this data.Please check your input.\n",name);
                            printf("0:Quit\n1:Re-enter\n");
                            printf(":");
                            scanf("%d",&inflag);getchar();
                        }
                        else
                        {
                            printf("%s is in %d postion.",name,SearchResult+1);
                            PrintStudentInf(*(record+SearchResult));
                            inflag=0;
                        }
                    }

                }
            }
            break;

            //Search by Id
            case 3 :
            {
                if(initialize==0)
                {
                    printf("ERROE:Data is not populated!Please use 1 or 11 to fill in the data.\n");
                }
                else
                {
                    int inflag=1;
                    while(inflag)
                    {
                        char id[20];
                        printf("Please enter the ID you want to search:");
                        gets(id);
                        SearchResult=IdSearch(record,id,size);
                        if(SearchResult==-1)
                        {
                            printf("%s is not in this data.Please check your input.\n",id);
                            printf("0:Quit\n1:Re-enter\n");
                            printf(":");
                            scanf("%d",&inflag);getchar();
                        }
                        else
                        {
                            printf("%s is in %d postion.",id,SearchResult+1);
                            PrintStudentInf(*(record+SearchResult));
                            inflag=0;
                        }
                    }
                }
            }
            break;

            //Modify by Id
            case 4 :
            {
                if(initialize==0)
                {
                    printf("ERROE:Data is not populated!Please use 1 or 11 to fill in the data.\n");
                }
                else
                {
                    int inflag=1;
                    while(inflag)
                    {
                        char id[20];
                        printf("Please enter the ID you want to modify:");
                        gets(id);
                        SearchResult=IdSearch(record,id,size);
                        if(SearchResult==-1)
                        {
                            printf("%s is not in this data.Please check your input.\n",id);
                            printf("0:Quit\n1:Re-enter\n");
                            printf(":");
                            scanf("%d",&inflag);getchar();
                        }
                        else
                        {
                            printf("%s current data: ",id);
                            PrintStudentInf(*(record+SearchResult));
                            printf("Please enter new data(NOTICE:input format must be \"ID NAME SCORE1 SCORE2 SCORE3 SCORE4\")\n");
                            scanf("%s %s %f %f %f %f",record[SearchResult].id,record[SearchResult].name,&record[SearchResult].score[0],&record[SearchResult].score[1],&record[SearchResult].score[2],&record[SearchResult].score[3]);
                            getchar();
                            printf("now %s data is: ",record[SearchResult].id);
                            PrintStudentInf(*(record+SearchResult));
                            inflag=0;
                        }
                    }
                }
            }
            break;

            //Delete by Id
            case 5 :
            {
                if(initialize==0)
                {
                    printf("ERROE:Data is not populated!Please use 1 or 11 to fill in the data.\n");
                }
                else
                {
                    int inflag=1;
                    while(inflag)
                    {
                        char id[20];
                        printf("Please enter the ID you want to delete:");
                        gets(id);
                        SearchResult=IdSearch(record,id,size);
                        if(SearchResult==-1)
                        {
                            printf("%s is not in this data.Please check your input.\n",id);
                            printf("0:Quit\n1:Re-enter\n");
                            printf(":");
                            scanf("%d",&inflag);getchar();
                        }
                        else
                        {
                            for(int i=SearchResult;i<size-1;i++)
                            {
                                record[i]=record[i+1];
                            }
                            size --;
                            inflag=0;
                        }
                    }
                }
            }
            break;

            //Caculate total and average score of every student
            case 6 :
            {
                if(initialize==0)
                {
                    printf("ERROE:Data is not populated!Please use 1 or 11 to fill in the data.\n");
                }
                else
                {
                    StudentData(record,size);
                }
            }
            break;

            //Caculate average score of every course
            case 7 :
            {
                if(initialize==0)
                {
                    printf("ERROE:Data is not populated!Please use 1 or 11 to fill in the data.\n");
                }
                else
                {
                    SubjectData(record,size);
                }
            }
            break;

            //Sort in descending order by course score
            case 8 :
            {
                if(initialize==0)
                {
                    printf("ERROE:Data is not populated!Please use 1 or 11 to fill in the data.\n");
                }
                else
                {
                    printf("Which subject to use for sorting\n0:ics\n1:PDP\n2:DS\n3:DL\n:");
                    int subject=-1;
                    scanf("%d",&subject);
                    getchar();
                    MergeSort(record,0,size-1,subject);
                    PrintClassInf(record,size);
                }
            }
            break;

            //Statistic analysis for every course
            case 9 :
            {
                if(initialize==0)
                {
                    printf("ERROE:Data is not populated!Please use 1 or 11 to fill in the data.\n");
                }
                else
                {
                    DataRank(record,size);
                }
            }
            break;

            //Save record
            case 10 :
            {
                if(initialize==0)
                {
                    printf("ERROE:Data is not populated!Please use 1 or 11 to fill in the data.\n");
                }
                else
                {
                    FILE * fp=NULL;
                    int inflag =1;
                    while(inflag)
                    {
                        printf("Select the output file(If th efile does not exist it will be creat)\n:");
                        char filename[50]={0};
                        gets(filename);
                        fp = fopen(filename,"w+");
                        if(fp==NULL)
                        {
                            printf("ERROR:Invalid file.\n");
                            printf("0:Quit\n1:Re-enter\n");
                            printf(":");
                            scanf("%d",&inflag);getchar();
                        }
                        else
                        {
                            txtprint(fp,record,size);
                            inflag=0;
                            fclose(fp);
                        }
                    }
                }
            }
            break;

            //Load record
            case 11 :
            {
                FILE * fp=NULL;
                int inflag =1;
                while(inflag)
                {
                    printf("Select the improted file\n:");
                    char filename[50]={0};
                    gets(filename);
                    fp = fopen(filename,"r");
                    size=txtsize(fp);
                    record=(STU *)malloc(sizeof(STU)*size);
                    rewind(fp);
                    size=txtread(fp,record,size);
                    if(size == -1)
                    {
                        printf("ERROR:Invalid file.\n");
                        printf("0:Quit\n1:Re-enter\n");
                        printf(":");
                        scanf("%d",&inflag);getchar();
                    }
                    else if(size == 0)
                    {
                        printf("ERROR:Empty file.\n");
                        printf("0:Quit\n1:Re-enter\n");
                        printf(":");
                        scanf("%d",&inflag);getchar();
                    }
                    else
                    {
                        printf("Success.A total of %d pieces of data were imported\n",size);
                        //PrintClassInf(record,size);
                        inflag=0;
                        initialize=1;
                        fclose(fp);
                    }
                }
            }
            break;

            case 12 :
            {

                ControlInfPrint();

            }
            break;
            //other number entered
            default :
            printf("ERROR:Invalid number!Please enter number in 0-11.\n");
        }
    }
    printf("Thanks for using\n(Press Enter to exit)");
    getchar();
    return 0;

}
