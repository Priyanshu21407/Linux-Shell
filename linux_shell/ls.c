#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
void ls(char *dir,int opr){
DIR *d1=opendir(dir);
struct dirent *d2=readdir(d1);
char fname[100][100];
int p=0,check=0;
while(d2!=NULL){
if(opr==1){
printf("%s ",d2->d_name);
}
else if(opr==2){
if(d2->d_name[0]!='.'){
printf("%lX %s ",d2->d_ino,d2->d_name);
}
}
d2=readdir(d1);
}
printf("\n");
}
int main(int numpmt,char *pmt[]){
if(strcmp(*(pmt+1),"-a")==0||strcmp(*(pmt+1),"--all")==0){
ls(".",1);
}
else if(strcmp(*(pmt+1),"-i")==0||strcmp(*(pmt+1),"--inode")==0){
ls(".",2);
}
else{
printf("Option not valid\n");
}
}
