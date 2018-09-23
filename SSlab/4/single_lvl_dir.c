#include<stdio.h>
#include<string.h>

int main()
{
    char dir[20][20];
    char file_name[20];
    int num_files = 0, choice;

    while(1)
    {
        printf("\n\nMENU:   1)CreateFile   2)DeleteFile   3)SearchFile   4)DisplayFiles   5)Exit\n   Enter choice: ");
        scanf("%d",&choice);
        if(choice == 1)
        {
            if(num_files == 20) 
            {
                printf("      \nDirectory Full");
                continue;
            }

            printf("      Enter FileName: ");
            scanf("%s", file_name);
            strcpy(dir[num_files], file_name);
            ++num_files;
            printf("      File Added");

        }
        else if(choice == 2)
        {
            if(num_files == 0) 
            {
                printf("      \nDirectory Empty");
                continue;
            }

            printf("      Enter name of file to be deleted: ");
            scanf("%s", file_name);
            int deleted = 0;
            for(int i=0;i<num_files;++i)
            {
                if(strcmp(dir[i], file_name) == 0)
                {
                    for(int j=i; j<num_files;++j)
                        strcpy(dir[j], dir[j+1]);
                    ++deleted;
                    --num_files;
                    printf("      File Deleted");
                    break;
                }

            }

            if(deleted == 0)
                printf("      File not found");
                



        }
        else if(choice == 3)
        {
            if(num_files == 0) 
            {
                printf("      \nDirectory Empty");
                continue;
            }

            printf("      Enter name of file to be searched: ");
            scanf("%s", file_name);
            int found = 0;
            for(int i=0;i<num_files;++i)
            {
                if(strcmp(dir[i], file_name) == 0)
                {
                    printf("      File found at index %d",i);
                    ++found;
                    break;
                }

                
            }

            if(found == 0)
                    printf("      File not found");

        }
        else if(choice == 4)
        {
            printf("   Files:\n");
            for(int i=0;i<num_files;i++)
                {
                    printf("      %s\n", dir[i]);
                }
        }
        else break;

    }
}