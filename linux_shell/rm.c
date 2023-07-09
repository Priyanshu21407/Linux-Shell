#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include <sys/types.h>
int main(int argc,char *args[]){
char *ptr;
struct stat file;
int flag=0;
if(stat(*(args),&file)==0){
flag=1;
if(S_ISREG(file.st_mode)!=0){
flag=2;
}
}
if(flag!=2){
printf("Path didn't point to a regular file\n");
exit(0);
}
if(strcmp(*(args+1),"-i")==0){
char c;
printf("Confirm to delete the file: y/n");
scanf("%c",&c);
if(c=='y'){
remove(*(args));
}
else if(c!='n'){
printf("invalid input for confirmation");
}
}
if(strcmp(*(args+1),"-v")==0){
remove(*(args));
printf("removed %s\n",*(args));
}
}
