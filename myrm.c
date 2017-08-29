#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<dirent.h>

int myrm(char *command){

    char *option1,*fileName;
    char *pwd;

    command[strlen(command) -1] = '\0';


    //Remove file if user didn't using -p option
    //If using -rf option, tokernizing command
    if(strstr(command," ")){
        option1 = strtok_r(command," ",&fileName);
    }
    else{  
        //remove file
        if(unlink(command)){
            printf("ERROR : No File\n");
            return -1;
        }

        return 0;
    }

    if(!strcmp(option1,"-rf")){

        //check file or dir is real
        if(access(fileName,F_OK)==0){
            if(remove(fileName)==-1){

                //set path
                char *tmp=getcwd(NULL,0);
                strcat(tmp,"/");
                strcat(tmp,fileName);

                //remove directory if it has files
                removeAll(tmp);
            }
        }else{
            printf("ERROR : No such File\n");
            return -1;
        }
    }
    else{
        printf("ERROR : Wrong Option\n");
        return -1;
    }

    return 0;
}

int removeAll(const char *fileName){

    DIR *dir;
    struct dirent *dirent;
    char target[2048];

    //if not directory
    if((dir=opendir(fileName)) == NULL){
        printf("ERROR : Open Error // path : [%s]\n",fileName);
        return -1;
    }

    while(1){
        //no directory
        if(!(dirent = readdir(dir))){
            break;
        }

        if(dirent->d_name[0] == '.')
            continue;

        //add path
        sprintf(target,"%s/%s",fileName,dirent->d_name);

        //if counldn't remove it means it is directory
        //recuresive removing
        if(remove(target)<0){
            if(removeAll(target) == -1)
                return -1;
            continue;
        }
    }

    //close directory and remove directory
    if(remove(fileName) <0){
        closedir(dir);
        return -1;
    }
    else{
        closedir(dir);
        return 1;
    }
}
