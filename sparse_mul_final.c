#include <stdio.h>
#include <stdlib.h>
#include<string.h>


struct Mat
{    int **M;
    int r;
    int c;
};

typedef struct Mat Mat;
int COL;
int ROW;
int COM;

void make_mat( Mat *Mat)
{    printf("Enter the no of row and column");
    scanf("%d%d",&Mat->r,&Mat->c);
    Mat->M = malloc(sizeof(int *)*(Mat->r));
    int i;
    for(i=0;i<Mat->r;i++)
    {      Mat->M[i]=malloc(sizeof(int)*Mat->c);    }}

void Get( Mat *Mat)
{    int i,j;
    for(i=0;i<Mat->r;i++)
    {        for(j=0;j<Mat->c;j++)
            scanf("%d",&Mat->M[i][j]);
    }}

void stringcat(char str1[],char str2[])
{    int i,j;
    i=strlen(str1);
    for(j=0;j<=strlen(str2);j++)
        str1[i++]=str2[j];
}
FILE *D;

void combine(Mat A,Mat B)
{    ROW=A.r;
    COL=B.c;
    if(A.c!=B.r)
    {
        exit(0);
    }
    COM=A.c;
    int i,j;
     FILE *fp;
   fp= fopen("file1.txt","w");

   for(i=0;i<A.r;i++)
    {        char str1[200];
        char str2[200];
        str1[0]='\0';
        str2[0]='\0';
        char line[200];
        line[0]='\0';
        stringcat(str1,"A,");
        char num[10];
        itoa(i,num,10);
        stringcat(str1,num);
        stringcat(str1,",");
        for(j=0;j<A.c;j++)
        {        if(A.M[i][j]==0)
                continue;
            else
            {    char nt[10],np[10];
                itoa(j,nt,10);
                stringcat(str1,nt);
                itoa(A.M[i][j],np,10);
                stringcat(str2,np);
                if(j!=A.c-1)
                {
                    stringcat(str2,",");
                    stringcat(str1,",");
                }
            }        }
       stringcat(line,str1);
       stringcat(line,"\t");
       stringcat(line,str2);
       fprintf(fp,"%s\n",line);
   }
    fclose(fp);
//  for matrix b
fp= fopen("file2.txt","w");
    for(i=0;i<B.r;i++)
    {        char str1[200];
        char str2[200];
        str1[0]='\0';
        str2[0]='\0';
        char line[200];
        line[0]='\0';

        stringcat(str1,"B,");
        char num[10];
        itoa(i,num,10);
        stringcat(str1,num);
       stringcat(str1,",");
      for(j=0;j<B.c;j++)
        {      if(B.M[i][j]==0)
                continue;
            else
            {
                char nt[10],np[10];
                itoa(j,nt,10);
                stringcat(str1,nt);
                itoa(B.M[i][j],np,10);
                stringcat(str2,np);
                if(j!=B.c-1)
                {
                   stringcat(str2,",");
                   stringcat(str1,",") ;
                }
           }
        }
       stringcat(line,str1);
       stringcat(line,"\t");
       stringcat(line,str2);
       fprintf(fp,"%s\n",line);
   }
    fclose(fp);
//    joining the files
    D=fopen("D.txt","w");
    char ch;
    fp=fopen("file1.txt","r+");
    while((ch=getc(fp))!=EOF)
    {        fprintf(D,"%c",ch);
    }
    FILE *ff;
   ff=fopen("file2.txt","r+");
    while((ch=getc(ff))!=EOF)
    {        fprintf(D,"%c",ch);
    }
    fclose(D);
    fclose(fp);
    fclose(ff);
}
char** split_string(char* text, char delim) {
    char** result = malloc(1*sizeof(char*));
    int size = 1;
    char* temp = strtok(text, &delim);
    *result = temp;
    while(temp != NULL) {
        size++;
        result = realloc(result,size*sizeof(char*));
        temp = strtok(NULL, &delim);
        result[size-1] = temp;
    }
    return result;
}
void map()
{    int n=0;
    char ch;
    FILE *fp;
    fp=fopen("D.txt","r");
    FILE *ff;
    ff=fopen("Dpart.txt","w");
    while((ch=getc(fp))!=EOF)
    {      if(ch=='\n')
            n++;
    }
    fclose(fp);
    fp=fopen("D.txt","r");
    int i;
    for(i=0;i<n;i++)
    {    char line[200];
        int j=0;
        while(((ch=getc(fp))!='\n'))
            line[j++]=ch;
        line[j]='\0';
        char **str;
        str=split_string(line,'\t');
        char **str1;
        char **str2;
        str1=split_string(str[0],',');
        str2=split_string(str[1],',');
       if(strcmp(str1[0],"A")==0)
        {   int m,n;
           for(m=0;m<COL;m++)
           {   for(n=0;str2[n]!=NULL;n++)
               {
                    char key[200];
                    char value[200];
                    key[0]='\0';
                    value[0]='\0';
                   stringcat(key,str1[1]);
                   stringcat(key,",");
                   char conv[10];
                   itoa(m,conv,10);
                   stringcat(key,conv);
                   stringcat(value,"A");
                   stringcat(value,",");
                   stringcat(value,str1[n+2]);
                   stringcat(value,",");
                   stringcat(value,str2[n]);

                   fprintf(ff,"%s\t%s\n",key,value);
               }
           }
        }

        if(strcmp(str1[0],"B")==0)
        {     int o,p;
           for(o=0;o<ROW;o++)
           {   for(p=0;str2[p]!=NULL;p++)
               {    char key[200];
                    char value[200];
                    key[0]='\0';
                    value[0]='\0';
                    char conv[10];
                   itoa(o,conv,10);
                   stringcat(key,conv);
                   stringcat(key,",");
                   stringcat(key,str1[p+2]);
                   stringcat(value,"B");
                   stringcat(value,",");
                   stringcat(value,str1[1]);
                   stringcat(value,",");
                   stringcat(value,str2[p]);

                   fprintf(ff,"%s\t%s\n",key,value);
               }
           }
        }
    }
    fprintf(ff,"exit");
    fclose(ff);
}
void reduce()
{    FILE *fp,*ff;

    fp=fopen("Dpart.txt","r");
    char list[100];


    char item[10000][100];
    int i=0;
    fgets(list,100,fp);
    while(strcmp(list,"exit"))
    {


        strcpy(item[i],list);
        fgets(list,100,fp);
        i++;

    }



    int lenght=i;

    int j;
    for(i=0;i<lenght-1;i++)
    {     for(j=1+i;j<lenght;j++)
        {    if(strcmp(item[i],item[j])>0)
            {
                char temp[100];
                strcpy(temp,item[i]);
                strcpy(item[i],item[j]);
                strcpy(item[j],temp);
            }
        }
    }
    printf("sorted");

    fclose(fp);

    fp=fopen("Dpart.txt","w");

    i=0;

    while(i<lenght)
    {   fprintf(fp,"%s",item[i]);
        i++;
    }
    fprintf(fp,"exit");
    fclose(fp);
    char line[200];

    fp=fopen("Dpart.txt","r");
    ff=fopen("result.txt","w");
    int flag=0;
    char check[10];
    char **pair;
    char **value;
    fgets(line,30,fp);
    while(strcmp(line,"exit"))
    {   int arr1[20]={0};
        int arr2[20]={0};
        pair=split_string(line,'\t');
        strcpy(check,pair[0]);
        do
        {    char line1[200];
            char **value1;
            flag=0;
            value=split_string(pair[1],',');
            if(strcmp(value[0],"A")==0)
                arr1[atoi(value[1])]=atoi(value[2]);
            else if(strcmp(value[0],"B")==0)
                arr2[atoi(value[1])]=atoi(value[2]);
            fgets(line,30,fp);
            strcpy(line1,line);
            value1=split_string(line1,'\t');

            if(strcmp(check,value1[0])==0)
                flag=1;
        }while(flag&&(strcmp(line,"exit")));
    if(!flag)
        {   int xx,result=0,aij,bjk;
            for(xx=0;xx<COM;xx++)
            {   aij=(arr1[xx]!=0)?arr1[xx]:0;
                bjk=(arr2[xx]!=0)?arr2[xx]:0;
                result=result+aij*bjk;
           }
            if(result)
            fprintf(ff,"%s,%d\n",check,result);
        }
    }
    fprintf(ff,"exit");
    fclose(ff);
    fclose(fp);
}

void print_mat()
{
    int sparse[200][3];
    sparse[0][0]=ROW;
    sparse[0][1]=COL;
    FILE *fp;
    int i=1;
    char line[200];
    char **pair;
    fp=fopen("result.txt","r");
    fgets(line,50,fp);
    while(strcasecmp(line,"exit"))
    {
        pair=split_string(line,',');
        sparse[i][0]=atoi(pair[0]);
        sparse[i][1]=atoi(pair[1]);
        sparse[i][2]=atoi(pair[2]);
        i++;
        fgets(line,50,fp);
    }
    sparse[0][2]=i-1;
    printf("Your result is \n row col value:\n");
   for(i=0;i<=sparse[0][2];i++)
    {
        printf("%3d  %3d  %3d \n",sparse[i][0],sparse[i][1],sparse[i][2]);
        if(i==0)
            printf("----------------\n");
    }
    fclose(fp);
}

int main()
{   Mat Mat1,Mat2;
    make_mat(&Mat1);
    Get(&Mat1);
    make_mat(&Mat2);
    Get(&Mat2);
    combine(Mat1,Mat2);
    map();
    reduce();
    print_mat();
}

