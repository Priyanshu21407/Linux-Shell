#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include <sys/stat.h>
#include <sys/types.h>
int main(int argc,char *args[]){
if(strcmp(*(args+1),"-u")==0 ||strcmp(*(args+1),"--universal")==0|| strcmp(*(args+1),"--utc")==0){
time_t localTime;
time(&localTime);
struct tm* utcTime= gmtime(&localTime);
time_t time=mktime(utcTime);
char timeString[100];
memset(timeString,0,sizeof(strlen(timeString)));
strcpy(timeString,ctime(&time));
timeString[strlen(timeString)-1]=' ';
printf("%sUTC\n",timeString);
}
else if(strcmp(*(args+1),"-r")==0){
char path[100];
strcpy(path,*args);
struct stat attr;
stat(path,&attr);
char mtime[100];
memset(mtime,0,strlen(mtime));
strcpy(mtime,ctime(&attr.st_mtime));
mtime[strlen(mtime)-1]=' ';
printf("last modified: %sIST\n",mtime);
}
else if(strlen(*(args+1))==0){
time_t localTime;
time(&localTime);
char timeString[100];
memset(timeString,0,sizeof(strlen(timeString)));
strcpy(timeString,ctime(&localTime));
timeString[strlen(timeString)-1]=' ';
printf("%sIST\n",timeString);

}
else{
printf("Invalid option\n");
}
}
