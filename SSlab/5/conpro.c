#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>
#include<unistd.h>

int wait(int *mutex)
{   
    while(*mutex == 0);
    *mutex = 0;
    return 1;
}

void release(int *mutex)
{
    (*mutex)++;
}

int main()
{   
    int mutex = 1, buffer = 0, n = 5 , tnum;
    omp_set_num_threads(2);
    srand(time(0));
    #pragma omp parallel private(tnum)
    {
        tnum = omp_get_thread_num();

        procon:
        

        if((tnum*n != buffer) && wait(&mutex))
        {   
            
            // printf("%d\n",tnum);
            int amt = rand();
            // printf("    %d\n",amt);
            if(tnum == 0) amt = amt%buffer +1;
            else amt= amt%(n-buffer) +1;
            // printf("    %d\n",amt);
            buffer += (2*tnum - 1)*amt;
            // printf("        %d  %d  %d\n",tnum,buffer,amt);
            
            // printf("%d",tnum);
            // #pragma omp crtical
            {

            for(int i=0;i<buffer;i++) printf("#");
            for(int i=0;i<n-buffer;i++) printf("_");
            (tnum == 1)? printf("   Produce +%d\n",amt) : printf("   Consume -%d\n",amt);

            }
            
            // printf("");
            
            release(&mutex);
            sleep(1);
        }
       

        goto procon;
    }
}
