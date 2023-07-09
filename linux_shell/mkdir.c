#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
int checkifexist(char path[]){
struct stat dir;
int check=0;
if(stat(path,&dir)==0 && S_ISDIR(dir.st_mode)){
check=1;
}
return check;
}
int main(int argc,char *args[]){
char path[100];
strcpy(path,*(args));
strcat(path,"/");
struct stat dir;
int check=0;
if(stat(*(args),&dir)==0 && S_ISDIR(dir.st_mode)){
check=1;
}
if(check==1){
printf("Directory already exists\n");
}
else if(check==0){
if(strcmp(*(args+1),"-v")==0){
int f=0;
int flag=mkdir(*(args),0777);
if(flag==0){
printf("directory created successfully\n");
}
else{
printf("couldn't create directory\n");
}
}
else if(strcmp(*(args+1),"-p")==0|| strcmp(*(args+1),"--parent")==0){
char subpath[100];
int ind=0;
for(int i=0;i<=strlen(path);i++){
if(i!=0){
if(path[i]!='/'){
subpath[ind]=path[i];
ind++;
}
else{
int exist=checkifexist(subpath);
if(exist==0){
mkdir(subpath,0777);
}
subpath[ind]='/';
ind++;
}
}
else{
if(path[0]!='/'){
subpath[ind]=path[0];
ind++;
//printf("not valid format for the directory\n");
//exit(0);
}
else{
subpath[ind]='/';
ind++;
}
}
}
}
else{
printf("invalid option\n");
}
}
}
