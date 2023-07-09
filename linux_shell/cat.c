#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc,char *args[]){
char path[100];
strcpy(path,*(args));
int opr=0;
if(strcmp(*(args+1),"-n")==0){
opr=1;
}
if(strcmp(*(args+1),"-b")==0){
opr=2;
}
if(opr==0){
printf("Invalid option\n");
exit(0);
}
FILE *ptr;
struct stat file;
int f=0;
if(stat(*(args),&file)==0){
f=1;
if(S_ISREG(file.st_mode)!=0){
f=2;
}
}
if(f!=2){
printf("Path didn't point to a regular file\n");
exit(0);
}
ptr=fopen(path,"r");
char c=fgetc(ptr);
int flag=0,num=1,numcheck=0;
char cprev='\0';
while(c!=EOF){
if(flag==0){
numcheck=1;
}
if(cprev=='\n'){
numcheck=1;
}
if(c=='\n' && opr==2){
numcheck=0;
}
if(numcheck==1){
printf("%d ",num);
num++;
numcheck=0;
}
if(flag==0){
if(c=='\n'){
printf("%c",c);
flag=1;
cprev=c;
c=fgetc(ptr);
}
else{
printf("%c",c);
cprev=c;
c=fgetc(ptr);
flag=1;
}
}
else if(cprev=='\n'&& c=='\n'){
printf("%c",c);
cprev=c;
c=fgetc(ptr);
}
else{
printf("%c",c);
cprev=c;
c=fgetc(ptr);
}
}
}
