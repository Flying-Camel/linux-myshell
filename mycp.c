#include<stdio.h>
#include<unistd.h>
#include<string.h>
int mycp(char *command){

    char *option1;
    char *option2;

    FILE *original, *copy;
    char c;

    command[strlen(command) -1] = '\0';
    option1 = strtok_r(command," ",&option2);

    //option1 has original file , option2 has targetfile
    if(strstr(option2," ") || option1==NULL || !strcmp(option2,"")){
        printf("Wrong Option\n");
        return -1;
    }
    
    //if targetfile already exist
    if(access(option2,F_OK)==0){
        printf("ERROR : %s is  existing file\n",option2);
    }

    if((original= fopen(option1,"r")) == NULL){
        printf("ERROR : No Exit File\n");
        return -1;
    }
    
    if((copy= fopen(option2,"w")) == NULL){
        printf("ERROR : No Exit File\n");
        return -1;
    }

     //copy file
    while(!feof(original)){
        c=(char)fgetc(original);

        if(c!=EOF){
            fputc((int)c,copy);
        }
    }

    fclose(original);
    fclose(copy);

    return 0;
}
