#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define size 17


struct symbol{
    char name[10];
    int addr;
};

void display(struct symbol *table[]){
    printf("Symbol Table:\n");
    for(int i=0 ;i<size; i++){
        printf("%d: ",i);
        if(table[i] != NULL) printf("%s   %d", table[i]->name, table[i]->addr);
        printf("\n");
    }
    printf("--------------------------------");
}

int hash(char *a){
    int sum=0;
    while(*a != '\0'){
        sum+=*a;
        a++;
    }

    return sum%size;
}

void insert(struct symbol *table[], struct symbol entry){
    int hashVal = hash(entry.name), i=0;

    while(table[hashVal] != NULL && i<size){
        if(strcmp(table[hashVal]->name, entry.name) == 0){
            printf("----Symbol already exists----");
            return;
        }
        hashVal=(++hashVal)%size;
        i++;
    }
    if(i >= size){
        printf("----Table Full----");
        return;
    }
    printf("----Symbol inserted at %d----",hashVal);
    table[hashVal] = malloc(sizeof(struct symbol));
    strcpy(table[hashVal]->name, entry.name);
    table[hashVal]->addr = entry.addr;

}

int search(struct symbol *table[], char *a){

    int hashVal = hash(a),i=0;
    if(table[hashVal] == NULL) return -1;
    while(strcmp(a,table[hashVal]->name) != 0){

        hashVal = (++hashVal)%size;
        i++;
        if(i >= size || table[hashVal] == NULL){
            
            return -1;
        }  
    }

    return hashVal;
    


}

int main()
{
    struct symbol *table[size] = {NULL}, x;
    int choice, hashVal;

    while(1){
        printf("\n\nMENU: 1)Insert   2)Search   3)Display   4)Exit\nEnter choice: ");
        scanf("%d",&choice);
        if(choice == 1){
            scanf("%s %d",x.name,&x.addr);
            insert(table, x);
        }
        else if(choice == 2){
            scanf("%s", x.name);
            hashVal = search(table, x.name);
            if(hashVal != -1){
                printf("----Symbol found at index %d----\n", hashVal);
                printf("----%s   %d----", table[hashVal]->name, table[hashVal]->addr);
            }
            else printf("----Symbol not found----");
        }
        else if(choice == 3){
            display(table);
        }
        else break;
    }

}