#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pwd.h>
#include<dirent.h>
#include<grp.h>
#include<sys/stat.h>
#include<time.h>
void printRWX();

int myls(char *command){

    DIR *dir;
    struct passwd *pw;
    struct dirent *dirent;
    struct group *group;
    struct stat fileInfo;
    struct tm *timeInfo;
    mode_t fileMode;

   char *option1 = (char *)malloc(256);
    //filename
   char *fileName = (char *)malloc(256);

    command[strlen(command) -1] = '\0';

    if(strstr(command," ")){
        option1 = strtok_r(command," ",&fileName);

        if(strcmp(option1,"-a")){
            printf("Wrong Option\n");
            return -1;
        }
    }
    else{
        //option
        if(!strcmp(command,"-a")){
            strcpy(option1,"-a");
            strcpy(fileName,"");
        }
        else{
            strcpy(option1,"");
            strcpy(fileName,command);
        }
    }

    //check path
    char path[256]; 
    strcpy(path,getcwd(NULL,0));

    if(strcmp(fileName,"")){
        strcat(path,"/");
        strcat(path,fileName);
    }
    if(fileName[0]=='/'){
        strcpy(path,fileName);
    }

  
    //confirm fileName is file or directory
    int isFile=0;
    if((dir=opendir(path))==NULL){
        //1 is fileName is File...
        isFile=1;
        //path=getcwd(NULL,0);
        strcpy(path,getcwd(NULL,0));
        //open directory
        if((dir=opendir(path))==NULL){
            printf("Fail Open Directory\n");
            return -1;
        }
    }

    //check exit file or directory
    int check=0;
    //read directory information
    while(dirent = readdir(dir)){

        char str[128];
        sprintf(str,"%s/%s",path,dirent->d_name);
        stat(str, &fileInfo);

        //skip if file is hidden mode
        if(strcmp(option1,"-a") && dirent->d_name[0] == '.') continue;
        else{
            if(isFile){
                if(strcmp(fileName,dirent->d_name)){
                    continue;
                }
            }

            fileMode = fileInfo.st_mode;
            //print file mode
            printRWX(fileMode);
            printf(" %3d ",fileInfo.st_nlink);

            pw=getpwuid(fileInfo.st_uid);
            group=getgrgid(fileInfo.st_gid);
            printf("%s",pw->pw_name);
            printf(" %s ",group->gr_name);

            //print file size
            printf(" %7d  ", fileInfo.st_size);

            char buf[100];
            //file create time  and typqe
            timeInfo=localtime(&(fileInfo.st_mtime));
            strftime(buf,sizeof(buf), " %m/%d %H:%M ",timeInfo);
            printf(" %s ",buf);

            //print name
            if(dirent->d_ino !=0)
                printf(" %s\n",dirent->d_name);

            check=1;
        }
    }
    closedir(dir);

    if(check==0){
        printf("There is no exit File or Directory\n");
        return -1;
    }

//    free(option1);
//    free(fileName);

    return 0;
}


void printRWX(file_mode){

    //directory
    if(S_ISDIR(file_mode))
        printf("d");
    else printf("-");

    //user
    if(file_mode & S_IRUSR)
        printf("r");
    else printf("-");

    if(file_mode & S_IWUSR)
        printf("w");
    else printf("-");

    if(file_mode & S_IXUSR)
        printf("x");
    else printf("-");

    //group
    if(file_mode & S_IRGRP)
        printf("r");
    else printf("-");

    if(file_mode & S_IWGRP)
        printf("w");
    else printf("-");

    if(file_mode & S_IXGRP)
        printf("x");
    else printf("-");

    //ect
    if(file_mode & S_IROTH)
        printf("r");
    else printf("-");

    if(file_mode & S_IWOTH)
        printf("w");
    else printf("-");

    if(file_mode & S_IXOTH)
        printf("x");
    else printf("-");

    printf(" ");

}
