#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int strcnt(char *,char);
int mymkdir(char *command){

    char *option1,*option2;
    char *pwd = (char *)malloc(100);

    command[strlen(command) -1] = '\0';

    //Create Directory if user didn't using -p option
    //If using -p option, tokernizing command
    if(strstr(command," ")){
        option1 = strtok_r(command," ",&option2);
    }
    else{  
        if(mkdir(command, 0755)){
            printf("ERROR : Make Directory Faile\n");
            return -1;
        }


        getcwd(pwd,100);
        printf("PATH : %s/%s\n",pwd,command);

        free(pwd);

        return 0;
    }

    if(!strcmp(option1,"-p")){

        int i,count=0;
        count = strcnt(option2,'/');

        for(i=0;i<count+1;i++){
            char *tmp;

            //tokernize path
            if(i==0)
                tmp = strtok(option2,"/\n");
            else
                tmp = strtok(NULL,"/\n");

            //file check
            if(!access(tmp,F_OK)){

                chdir(tmp);

            }
            else{
                mkdir(tmp, 0755);
                chdir(tmp);
            }
        }


        //print path
        getcwd(pwd,100);
        printf("PATH : %s\n",pwd);

        free(pwd);

        //back to original directory
        for(i=0;i<count;i++)
            chdir("..");

    }
    else{
        printf("Wrong Option\n");
        return -1;
    }

    return 0;
}

//counting '/'
int strcnt(char str[], char c){

    int i,count=0;

    for(i=0;str[i] != '\0' ;i++){
        if(str[i]==c)
            count++;
    }
    return count;
}
