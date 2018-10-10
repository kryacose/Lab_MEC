#include<stdio.h>

void inp(int arr[][3], int n)
{
    printf("\n   A B C\n");
    for(int i=0;i<n;i++)
    {
        printf("p%d ",i);
        scanf("%d %d %d", &arr[i][0], &arr[i][1], &arr[i][2]);
    }
    printf("----------");
}

void outp(int arr[][3], int n)
{
    printf("\n  A B C");
    for(int i=0;i<n;i++)
    {
        printf("\np%d ",i);
        for(int j=0;j<3;j++)
            printf("%d ",arr[i][j]);
    }
    printf("\n----------");
}

int satisfied(int need[], int available[])
{
    for(int i=0;i<3;i++)
        if(need[i]>available[i])
            return 0;
    return 1;
}   

int done(int x, int completed[], int ncomp)
{
    for(int i=0;i<ncomp;i++)
        if(x == completed[i])
            return 0;
        

    return 1;
}

int main()
{   
    int max[20][3], allocation[20][3], available[3], need[20][3], n;
    printf("Enter no of processes: ");
    scanf("%d",&n);

    printf("\nMAX");
    inp(max, n);

    printf("\nALLOCATION");
    inp(allocation, n);

    for(int i=0;i<n;i++)
        for(int j=0;j<3;j++)
            need[i][j] = max[i][j] - allocation[i][j];

    printf("\nNEED");
    outp(need, n);

    printf("\nAVAILABLE");
    printf("\n   A B C\n   ");
    scanf("%d %d %d", &available[0], &available[1], &available[2]);
    printf("----------\n");

    

    int x=0, completed[20] ,ncomp=0, progress = 0;
    while(1)
    {
        if(done(x ,completed, ncomp))
        {
            printf("P%d: ", x);
            if(satisfied(need[x] , available))
            {   
                printf("need < available, executed\n");
                for(int i=0;i<3;i++)
                    available[i]+=allocation[x][i];
                printf("   new Available\n    A  B  C\n   %d  %d  %d\n", available[0], available[1], available[2]);

                completed[ncomp] = x;
                ncomp++;
                progress++;
            }

            else
            {   
                printf("need > available, NOT executed\n");

            }
        }

        if(ncomp >= n) break;
        x = (x+1)%n;

        if(x == 0 && progress == 0) break;
        else progress = 0;
    }

    if(ncomp == n)
    {
        printf("All procceses completed,\n  order of completion: ");
        for(int i=0;i<n;i++)
            printf("p%d, ",completed[i]);
    }

    else printf("\nDEADLOCK occured");
    
}

