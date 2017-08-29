#include<stdio.h>
#include<stdlib.h>

int mypwd(char *command){

    //get pwd
    if(!strcmp(command,"")){
        char *pwd = (char *)malloc(100);
        getcwd(pwd,100);

        printf("%s\n",pwd);
        free(pwd);
    }
    else
        printf("Wrong Option\n");


    return 0;

}
