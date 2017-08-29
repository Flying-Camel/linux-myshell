#include<stdio.h>
#include<string.h>
int mycd(char *command){

    command[strlen(command) -1] = '\0';

    if(strstr(command," "))
        printf("ERROR : Command Error\n");

    //cd if no directory and ~
    if(!strcmp(command,"") || !strcmp(command,"~")){
        if(chdir("/home")<0)
            printf("ERROr : Change Directory Fail!\n");
    }
    else{
	//cd directory
        if(chdir(command)<0)
            printf("ERROr : Change Directory Fail!\n");
    }

    return 0;
}
