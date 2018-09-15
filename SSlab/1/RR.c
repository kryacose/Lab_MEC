#include<stdio.h>
 
void main()
{
    int bt[20],btc[20],wt[20],tat[20],i,j,n,total=0,ts,completed,bursttime,turnaroundtime;
    float avwt,avtat;
   
    
    printf("Enter number of process:");
    scanf("%d",&n);

    printf("Enter time slice:");
    scanf("%d",&ts);

    printf("\nEnter Burst Time:\n");
    for(i=0;i<n;i++)
    {
        printf("p%d:",i+1);
        scanf("%d",&bt[i]);
        btc[i] = bt[i];
     
    }
 
    for(i=0;i<n;i++)
        wt[i]=0;            //waiting time for first process will be zero
    j=0;
    completed = 0;
    avwt = 0;
    printf("\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    avtat = 0;
    while(1){
        
        j%=n;
        //printf("\n%d",j+1);
    
        //ALL COMPLETE CASE
        if(completed == n)
            break;
        
        turnaroundtime = 0;
        
        if(bt[j] == 0){
            j++;
            continue;
            }
        else if(bt[j] <= ts){
            completed++;
            avwt+=wt[j];
            bursttime = bt[j];
            bt[j] = 0;
            turnaroundtime = btc[j] + wt[j];
        }
        else{
            bursttime = ts;
            bt[j] -= ts;
        }
        
        
        //Adding waiting time
        for(i=0;i<n;i++){
            if(i!=j)
                wt[i]+=bursttime;
        }
        
        printf("\np%d\t\t  %d\t\t    %d\t\t\t%d",j+1,bursttime,wt[j],turnaroundtime);
        avtat += turnaroundtime;
        
        
            
            
            
        j++;
    }
    

    
    //printf("\n%f   %f",avwt,avtat);
    printf("\n\nAverage Waiting Time=%f",(float)avwt/n);
    printf("\nAverage Turnaround Time=%f\n",(float)avtat/n);
}
