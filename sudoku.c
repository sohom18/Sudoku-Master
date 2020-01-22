#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<time.h>
void display_sudoku(char a[6][6])
{
    int i,j;
    printf("------------------------|-------------------------------|\n");
    for(i=0;i<6;i++)
    {
        if(i==2||i==4)
        {
            printf("------------------------|-------------------------------|");
            printf("\n");
        }
        for(j=0;j<6;j++)
        {
                if(a[i][j]!='.')
                printf("%d\t",a[i][j]);
                else    printf("%c\t",a[i][j]);
            if(j==2||j==5)
               printf("|\t");
        }
            printf("\n");
    }
    printf("------------------------|-------------------------------|\n");
}
int random_it(int upper)
{
    int n;
    n=(int*)malloc(sizeof(int));
    n=n%upper;
    return(n);
}
void first_stage(char a[6][6],char b[6][6])
{
    int i,j,col,res,z,x,ci,cj,k;
    for(i=0;i<6;i++)
    {
        for(j=0;j<6;j++)
        {
            do
            {
                col=rand()%6;
                if(col<0)
                    col=-col;
            }while(a[i][col]!='.');
            do
            {
                res=0;
                do
                {
                    a[i][col]=(char)rand()%7;
                    if(a[i][col]<0)
                        a[i][col]=-a[i][col];
                }while(a[i][col]==0);
                for(z=0;z<6;z++)
                {
                    if(z!=col&&a[i][col]==a[i][z])
                    {
                        res=1;
                        break;
                    }
                }
                for(z=0;z<6;z++)
                {
                    if(z!=i&&a[i][col]==a[z][col])
                    {
                        res=1;
                        break;
                    }
                }
                if(col<3)
                    x=0;
                else
                    x=3;
                if(i==0||i==1)
                {
                    for(ci=0;ci<2;ci++)
                    {
                        for(cj=(x+0);cj<(x+3);cj++)
                        {
                            if(ci!=i&&cj!=col&&a[i][col]==a[ci][cj])
                            {
                                res=1;
                                break;
                            }
                        }
                    }
                }
                if(i==2||i==3)
                {
                    for(ci=2;ci<4;ci++)
                    {
                        for(cj=(x+0);cj<(x+3);cj++)
                        {
                            if(ci!=i&&cj!=col&&a[i][col]==a[ci][cj])
                            {
                                res=1;
                                break;
                            }
                        }
                    }
                }
                if(i==4||i==5)
                {
                    for(ci=4;ci<6;ci++)
                    {
                        for(cj=(x+0);cj<(x+3);cj++)
                        {
                            if(ci!=i&&cj!=col&&a[i][col]==a[ci][cj])
                            {
                                res=1;
                                break;
                            }
                        }
                    }
                }
            }while(res==1);
        }
    }
    for(i=0;i<6;i++)
    {
        for(j=0;j<2;j++)
        {
            if(j==0)
            {
                k=rand()%6;
                b[i][k]=a[i][k];
                a[i][k]='.';
            }
            else
            {
                do
                {
                    k=random_it(6);
                }while(a[i][k]=='.');
                b[i][k]=a[i][k];
                a[i][k]='.';
            }
        }
    }
    display_sudoku(a);
}
int main()
{
    char a[6][6],b[6][6],r[50],c[50],n[50],choice[50];
    int i,j,col,row,f=0,k,ch,num,res=0,x=0;
    clock_t start,end;
    double execution_time;
    float score=1000;
    for(i=0;i<6;i++)
    {
        for(j=0;j<6;j++)
        {
            a[i][j]='.';
            b[i][j]='.';
        }
    }
    printf("\nYou have 70 seconds to complete Sudoku else you will start loosing your score\nYour timer will start as soon as you Press 1");
    do
    {
        f=0;
        printf("\nPress 1 to play Sudoku and 2 to exit");
        gets(choice);
        ch=(int)choice[0];
        ch=ch-48;
        if(choice[1]!='\0'||(ch!=1&&ch!=2))
            f=1;
        else
            f=0;
    }while(f==1);
    if(ch==1){
    system("cls");
    start=clock();
    first_stage(a,b);
    do
    {
        res=0;
        do
        {
            do
            {
                printf("\nenter row no.");
                gets(r);
                if(r[1]=='\0')
                {
                    row=(int)r[0];
                    row=row-48;
                }
                else if(r[1]!='\0'||row>5||row<0)
                    printf("\nentered wrong row no.");
            }while(r[1]!='\0'||row>5||row<0);
            do
            {
                printf("\nenter col no.");
                gets(c);
                if(c[1]=='\0')
                {
                    col=(int)c[0];
                    col=col-48;
                }
                else if(c[1]!='\0'||col>5||col<0)
                    printf("\nentered wrong col no.");
            }while(c[1]!='\0'||col>5||col<0);
            if(b[row][col]=='.')
                printf("\nyou cannot place here");
        }while(b[row][col]=='.');
        do
        {
            printf("\nenter no.");
            gets(n);
            if(n[1]=='\0')
            {
                num=(int)n[0];
                num=num-48;
            }
            else if(n[1]!='\0'||num>6||num<1)
                printf("\nentered wrong no.");
        }while(n[1]!='\0'||num>6||num<1);
        system("cls");
        a[row][col]=num;
        display_sudoku(a);
        for(i=0;i<6;i++)
        {
            for(j=0;j<6;j++)
            {
                if(b[i][j]!='.'&&b[i][j]!=a[i][j])
                {
                    res=1;
                    break;
                }
            }
        }
        if(res==0)
            printf("\nSudoku Completed\n");
    }while(res==1);
    end=clock();
    execution_time=((double)end-start)/CLOCKS_PER_SEC;
    printf("\ntime taken %f",execution_time);
    if(execution_time<70.0)
         score=score-execution_time;
    else
        score=score-1.5*execution_time;
    printf("\nYour score is %.2f",score);
    return(0);}
    else
        return(0);
}
