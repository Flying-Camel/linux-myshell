#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>

#define CPU_CLOCK 100

int myps(char *command){

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
            
    printf("   UID   PID   PPID   PGID   SID   STIME    TIME  CMD\n");
    printf(" ----------------------------------------------------\n");

    while(dirent = readdir(dir)){
        int pid;
        int ppid;
        int pgid;
        int sid;
        int uid;
        long stime;
        long tty;
        int ctime;

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

        for(i=0;i<7;i++)
            fgets(status,1024,fp);

        tmp=strtok(status,":");
        tmp=strtok(NULL,"\t");

        //get uid
        uid = atoi(tmp);

        memset(path,0,256);
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

        //get pgid
        tmp=strtok(NULL," ");
        pgid = atoi(tmp);

        //get sid
        tmp=strtok(NULL," ");
        sid = atoi(tmp);

        //get tty
        tmp = strtok(NULL," ");
        tty = atol(tmp);

        if(tty != thistty)
            continue;

        //get 14th stat element for time
        int e14;
        for(i=0;i<7;i++)
            tmp=strtok(NULL," ");
        e14 = atoi(tmp);

        //get 15th stat element for time
        int e15;
        tmp=strtok(NULL," ");
        e15 = atoi(tmp);

        //get stime, get 22th stat element for time
        int e22;
        for(i=0;i<7;i++)
            tmp=strtok(NULL," ");
        e22=atoi(tmp);

        //get time
        ctime = getcputime(e14,e15,e22,cpuSecond);

        //current time
        time_t timer = time(NULL);
        timeInfo = localtime(&timer);

        //get stime  = current time - cput booting time + process running time
        e22 = e22/CPU_CLOCK;
        stime = timer - cpuSecond + e22;

        //printf("stime : %ld timer :  %ld second : %ld e22 : %ld",stime,timer,cpuSecond,e22);

        //current month and day
        int mon = timeInfo->tm_mon;
        int day = timeInfo->tm_mday;

        //time_t sstimer = stime;
        struct tm *stimeInfo = localtime(&stime);

        //compare mon and stime's mon for print differ
        if((stimeInfo->tm_mon == mon) && (stimeInfo->tm_mday == day))
            printf("%5d %5d  %5d  %5d  %5d   %02d:%02d   %2d.%d   %s",uid,pid,ppid,pgid,sid,stimeInfo->tm_hour,stimeInfo->tm_min,ctime/10,ctime%10,cmdline);

        else
            printf("%5d %5d  %5d  %5d  %5d   %2d/%2d   %2d.%d   %s",uid,pid,ppid,pgid,sid,stimeInfo->tm_mon+1,stimeInfo->tm_mday,ctime/10,ctime%10,cmdline);

        printf("\n");

    }

    closedir(dir);

    return 0;
}

int getcputime(ulong utime, ulong stime, ulong starttime, int seconds)
{   
    unsigned long long total;
    int pcpu=0;

    total = utime + stime;

    seconds = seconds - (int)(starttime/CPU_CLOCK);

    if(seconds)
    {
        pcpu = (int)(total * 1000ULL/100.)/seconds;
    }

    return pcpu;
}


int uptime()
{
    FILE *fp;
    char buf[36];
    double stime;
    double idletime;

    if ((fp = fopen("/proc/uptime", "r")) == NULL)
    {
        printf("ERROR : fopen error");
        return -1;
    }
    fgets(buf, 36, fp);
    sscanf(buf, "%lf %lf", &stime, &idletime);
    fclose(fp);

    return (int)stime;
}
