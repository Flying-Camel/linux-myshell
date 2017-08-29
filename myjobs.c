#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>


int myjobs(char *command,int parentId){

    command[strlen(command) -1] = '\0';

    //check command 
    if(strstr(command," ")){
        printf("ERROR : Wrong Command\n");
        return -1;
    }
    else if(strcmp(command,"")){
        printf("ERROR : Wrong Command\n");
        return -1;
    }

    DIR *dir;
    struct dirent *dirent;
    struct stat fileInfo;
    struct tm *timeInfo;
    FILE *fp;

    //get cpu time
    int cpuSecond = uptime();

    if(!(dir = opendir("/proc"))){
        printf("ERROR : Can't open /proc\n");
        return -1;
    }


    int thisid = getpid();
    char ptty,ttypath[256];
    char *tmp,stat[1024];

    sprintf(ttypath,"/proc/%d/stat",thisid);

    fp=fopen(ttypath,"r");
    fgets(stat,256,fp);
    fclose(fp);

    int k;
    tmp = strtok(stat," ");
    for(k=0;k<6;k++)
            tmp=strtok(NULL," ");
    //get this tty
    long thistty = atol(tmp);

    //get this pid and coutn num
    int thisId = getpid();
    int num=1;
            
    while(dirent = readdir(dir)){
        int pid;
        int ppid;
        int pgid;
        long tty;
        int ctime;
        char pst[128];

        char cmdline[128];    
        char path[256];        //for file path
        char status[1024];     //for stat
        struct tm *timeInfo;

        char *tmp;
        int i;

        //if hidden
        if(!strcmp(dirent->d_name,".") || !strcmp(dirent->d_name,".."))
            continue;

        //check isDigit if pid=1, continue
        //get pid
        if((pid = atoi(dirent->d_name)) <= 0 )
            continue;

        //open cmdline 
        //get cmd
        sprintf(path,"/proc/%d/cmdline",pid);
        fp = fopen(path,"r");
        if(!fgets(cmdline,128,fp))
            strcpy(cmdline,"?");
        memset(path,0,256);
        fclose(fp);

        //open status file
        //for get uid
        sprintf(path,"/proc/%d/status",pid);
        fp = fopen(path,"r");

        for(i=0;i<2;i++)
            fgets(status,1024,fp);

        tmp=strtok(status,":");
        tmp=strtok(NULL,"(");
        tmp=strtok(NULL,")");
        strcpy(pst,tmp);

        //get status 
        memset(path,0,256);
        memset(status,0,256);
        fclose(fp);

        //get ppid
        sprintf(path,"/proc/%d/stat",pid);

        fp = fopen(path,"r");
        if(!fgets(status,1024,fp)){
            printf("ERROR : Read Stat fail\n");
            return -1;
        }
        fclose(fp);
        memset(path,0,256);

        //tokernize stat
        //get ppid
        tmp = strtok(status," ");
        for(i=0;i<3;i++)
            tmp=strtok(NULL," ");
        ppid = atoi(tmp);

        //getpgid
        tmp=strtok(NULL," ");
        pgid=atoi(tmp);

        //get tty
        tmp = strtok(NULL," ");
        tmp = strtok(NULL," ");
        tty = atol(tmp);

        if(tty != thistty)
            continue;

        if(pgid == parentId && pid != thisId && parentId != pid && ppid !=1)
            printf("[%d]  %s\t%s\n",num++,pst,cmdline);


    }

    closedir(dir);

    return 0;
}  
