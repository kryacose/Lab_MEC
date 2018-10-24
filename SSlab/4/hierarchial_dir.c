#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct dir{
    char name[10];
    int n_dir, n_file;
    struct dir *subdir[5];
    char files[5][10];
};

void initialize_dir(struct dir *x){
    x->n_dir=0;
    x->n_file=0;
    for(int i=0; i<5; i++)
        x->subdir[i] = NULL;
}

void add_file(struct dir *x){

    char z[10];
    scanf("%s", z);

    if(x->n_file>=5){
        printf("    Directory Full\n");
        
        return;
    }

    for(int i=0; i<x->n_file; i++){
        if(strcmp(z,x->files[i]) == 0){
            printf("        Already Exists\n");
            return;
        }
    }
    // printf("    Enter File Name: ");
    // scanf("%s", x->files[x->n_file]);
    strcpy(x->files[x->n_file], z);
    x->n_file++;
    printf("        File inserted\n");

    // test
    // printf("%s %d", x->files[x->n_file-1], x->n_file);
}

void del_file(struct dir *x){
    if(x->n_file <= 0){
        printf("    No files to delete\n");
        char z[10];
        scanf("%s", z);
        return;
    }
    
    char str[10];
    int i=0;
    // printf("    Enter name of file: ");
    scanf("%s", str);
    while(i<x->n_file && strcmp(str, x->files[i])){
        i++;
    }
    if(i >= x->n_file){
        printf("    File not found\n");
    }
    else{
        for(int j=i; j<x->n_file;++j)
            strcpy(x->files[j], x->files[j+1]);
        x->n_file--;
        printf("        File Deleted\n");
    }
}

void add_subdir(struct dir *x){
    char z[10];
    scanf("%s", z);
    if(x->n_dir>=5){
        printf("    Directory Full\n");
        
        return;
    }

    for(int i=0; i<x->n_dir; i++){
        if(strcmp(z, x->subdir[i]->name) == 0){
            printf("        Already Exists\n");
            return;
        }
    }

    // struct dir subDirectory;
    
    x->subdir[x->n_dir] = (struct dir*) malloc(sizeof(struct dir));

    initialize_dir(x->subdir[x->n_dir]);
    // name_dir(x->subdir[x->n_dir]);
    strcpy(x->subdir[x->n_dir]->name, z);

    x->n_dir++;
    printf("        SubDirectory added\n");

    //Test
    // printf("    TEST %s %p", x->subdir[x->n_dir-1]->name, x->subdir[x->n_dir - 1]);
}

void del_subdir(struct dir *x){
    if(x->n_dir <= 0){
        printf("    No SubDirectories to delete\n");
        char z[10];
        scanf("%s", z);
        return;
    }

    char str[10];
    int i=0;
    // printf("    Enter name of SubDirectory: ");
    scanf("%s", str);
    while(i<x->n_dir && strcmp(str, x->subdir[i]->name)){
        i++;
    }
    if(i >= x->n_dir){
        printf("    SubDirectory not found\n");
    }
    else{
        free(x->subdir[i]);
        for(int j=i; j<x->n_dir;++j)
            x->subdir[j] = x->subdir[j+1];
        x->n_dir--;

        for(int i = x->n_dir; i<5; i++) x->subdir[i]= NULL;

        printf("    SubDirectory Deleted\n");
    }
}

void print_currdir(struct dir *x[]){

    printf("\n.");
    int i = 1;
    while(x[i] != NULL){
        printf("/%s", x[i]->name);
        i++;
    }
    printf("> ");

}

void display_dir(struct dir *x){
    printf("    Name: %s\n", x->name);
    printf("    SubDirectories:\n");
    for(int i=0; i<x->n_dir; i++) printf("          %s\n", x->subdir[i]->name);
    printf("    Files:\n");
    for(int i=0; i<x->n_file; i++) printf("          %s\n", x->files[i]);

    //TEST
    // printf("    %d %d", x->n_dir,x->n_file);
}

struct dir *getSubD(struct dir *x, char str[]){
    // char str[10];
    // // printf("    Enter name of SubDirectory: ");
    // scanf("%s", str);
    int i=0;
    while(i<x->n_dir && strcmp(str, x->subdir[i]->name)){
        i++;
    }
    if(i >= x->n_dir){
        printf("    SubDirectory not found\n");
        return NULL;
    }
    else{
        return x->subdir[i];
    }

}


int main(){

    struct dir *curr_dir_list[20];
    struct dir *curr_dir;
    int depth = 1;
    for(int i=0; i<20; i++) curr_dir_list[i] = NULL;


    //create root directory
    struct dir root;
    initialize_dir(&root);
    strcpy(root.name, "root");
    curr_dir_list[0] = &root;

    char cmd[10];

    printf("Controls:\n  cd   : Change Directory\n");
    printf("  mkdir  : Insert SubDirectory\n  rmdir  : Remove SubDirectory\n");
    printf("  mkfile : Insert File\n  rmfile : Remove File\n  ls     : List contents of directory\n\n");

    while(1){

        curr_dir = curr_dir_list[depth-1];

        print_currdir(curr_dir_list);
        scanf("%s", cmd);

        if(strcmp(cmd,"cd") == 0){
            char tdir[10];
            scanf("%s", tdir);

            if(strcmp("..", tdir) == 0){
                if(depth == 1){
                    printf("    Can't go any higher");
                }
                else{
                curr_dir_list[depth-1] = NULL;
                depth--;
                }
            }
        
            else{
                curr_dir_list[depth] = getSubD(curr_dir, tdir);
                if(&curr_dir != NULL){
                    depth++;
                }
            }
            
        }
        else if(strcmp(cmd,"mkdir") == 0){
            add_subdir(curr_dir);
        }
        else if(strcmp(cmd,"rmdir") == 0){
            del_subdir(curr_dir);
        }
        else if(strcmp(cmd,"mkfile") == 0){
            add_file(curr_dir);
        }
        else if(strcmp(cmd,"rmfile") == 0){
            del_file(curr_dir);
        }
        else if(strcmp(cmd,"ls") == 0){
            display_dir(curr_dir);
        }
        else{
            printf("    Command not found");
        }

        // if(depth == curr_depth)
        //     curr_dir_list[depth-1] = &curr_dir;

    }

}
