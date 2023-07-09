#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<errno.h>
char pmt[100][100];
char tem[100];
char cd[100];
char mkddir[100],lsdir[100],rmddir[100],catdir[100],datedir[100];
int idx;
char execdir[100];
int check=0,numpmt=0,flag=0,checkdot=0;
void setupcd(){
strcpy(cd,getenv("PWD"));
idx=strlen(cd);
}
void getexecdir(){
strcpy(execdir,getenv("PWD"));
}
void setalldir(){
strcpy(lsdir,execdir);
strcat(lsdir,"/ls");

strcpy(mkddir,execdir);
strcat(mkddir,"/mkdir");

strcpy(rmddir,execdir);
strcat(rmddir,"/rm");

strcpy(datedir,execdir);
strcat(datedir,"/date");

strcpy(catdir,execdir);
strcat(catdir,"/cat");
}
void add(){
if(pmt[1][0]=='.'&&pmt[1][1]=='/'){
for(int i=1;i<strlen(pmt[1]);i++){
idx++;
cd[idx]=pmt[1][i];
}
}
else if(pmt[1][0]=='.'&&pmt[1][1]=='.'){
int i=(int)strlen(cd);
while(1){
if(cd[idx]=='/'){
cd[idx]='\0';
idx--;
break;
}
else{
cd[idx]='\0';
idx--;
}
}
}
else{
idx=0;
memset(cd,0,sizeof(cd));
for(int i=0;i<strlen(pmt[1]);i++){
cd[idx]=pmt[1][i];
idx++;
}
}
}
void display(){
if(check==0){
system("clear");
check=1;
}
printf("shell#");
}
void input(char pmt[][100]){
char inp[100];
scanf("%c",&inp[0]);
int i=0,j=0;
flag=0;
int count=0;
while(inp[i]!='\n'){
if(inp[i]!=' ' && flag==0){
pmt[0][i]=inp[i];
count++;
}
else{
if(inp[i]==' '){
flag++;
count++;
j=0;
}
else{
pmt[flag][j]=inp[i];
j++;
}
}
i++;
scanf("%c",&inp[i]);
}
numpmt=flag;
}
void *command(void *arg){
if(strcmp(pmt[0],"ls&t")==0){                                                       //opt: -a,-r
char arg1[100],arg2[100];
if(flag==0){
printf("option not provided in input\n");
}
else{
char predir[100];
getcwd(predir,100);
strcpy(arg1,"ls");
strcat(arg1," ");
strcpy(arg2,pmt[1]);
strcat(arg1,arg2);
chdir(execdir);
system(arg1);
chdir(predir);
}
}
if(strcmp(pmt[0],"cat&t")==0){                                                      //opt: -n,-b
char path[100],cmd[500],opt[100];
if(flag==1){
if(pmt[1][0]!='-'){
printf("option not provided\n");
}
else{
printf("path not provided\n");
}
}
else{
char predir[100];
getcwd(predir,100);
strcpy(cmd,"cat");
strcat(cmd," ");
strcpy(path,pmt[2]);
strcpy(opt,pmt[1]);
strcat(opt," ");
strcat(opt,path);
strcat(cmd,opt);
chdir(execdir);
system(cmd);
chdir(predir);
}
}
if(strcmp(pmt[0],"date&t")==0){                                                     //opt: -u,-r
char path[100],cmd[500],opt[100];
if (flag>2){
printf("invalid format\n");
}
else{
strcpy(cmd,datedir);
strcat(cmd," ");
strcpy(path,pmt[2]);
strcpy(opt,pmt[1]);
strcat(opt," ");
strcat(opt,path);
strcat(cmd,opt);
system(cmd);                 
}
}
if(strcmp(pmt[0],"rm&t")==0 ){                                                        //opt: -i,-v
char path[100],cmd[500],opt[100];
if(flag==1){
if(pmt[1][0]!='-'){
printf("option not provided\n");
}
else{
printf("path not provided\n");
}
}
else{
strcpy(cmd,"rm");
strcat(cmd," ");
strcpy(path,pmt[2]);
strcpy(opt,pmt[1]);
strcat(opt," ");
strcat(opt,path);
strcat(cmd,opt);
chdir(execdir);
system(cmd);
}
}
if(strcmp(pmt[0],"mkdir&t")==0){ 
char path[100],cmd[500],opt[100];                                                   //opt: -v,-p
if(flag==1){
if(pmt[1][0]!='-'){
printf("option not provided\n");
}
else{
printf("path not provided\n");
}
}                                        
else{
strcpy(cmd,mkddir);
strcat(cmd," ");
strcpy(path,pmt[2]);
strcpy(opt,pmt[1]);
strcat(opt," ");
strcat(opt,path);
strcat(cmd,opt);
system(cmd);
}
}
}
int main(){
getexecdir();
setupcd();
setalldir();
while(1){
for(int i=0;i<=flag;i++){
memset(pmt[i],0,strlen(pmt[i]));
}
display();
input(pmt);
int internal=0;
if(pmt[0][strlen(pmt[0])-2]!='&'){
if(strcmp(pmt[0],"exit")==0||strcmp(pmt[0],"echo")==0||strcmp(pmt[0],"pwd")==0||strcmp(pmt[0],"cd")==0){
internal=1;
}

if(internal==0){
if(fork()!=0){
wait(NULL);
if(strcmp(pmt[0],"cat")!=0 && strcmp(pmt[0],"date")!=0&&strcmp(pmt[0],"ls")!=0&&strcmp(pmt[0],"mkdir")!=0&&strcmp(pmt[0],"rm")!=0){
exit(0);
}
}
else{

if(strcmp(pmt[0],"ls")==0){                                                       //opt: -a,-r
char *arg1="ls",*arg2=pmt[1];
if(flag==0){
printf("option not provided in input\n");
}
else{
execl(lsdir,arg1,arg2,(char *)0);
}
}
if(strcmp(pmt[0],"cat")==0){                                                      //opt: -n,-b
char *path=pmt[2];
char *opt=pmt[1];
if(flag==1){
if(pmt[1][0]!='-'){
printf("option not provided\n");
}
else{
printf("path not provided\n");
}
}
else{
execl(catdir,path,opt,(char *)0);
}
}
if(strcmp(pmt[0],"date")==0){                                                     //opt: -u,-r
char *path=pmt[2];
char *opt=pmt[1];
if (flag>2){
printf("invalid format\n");
}
else{
execl(datedir,path,opt,(char *)0); 
}                 
}
if(strcmp(pmt[0],"rm")==0 ){                                                        //opt: -i,-v
char *path=pmt[2];
char *opt=pmt[1];
if(flag==1){
if(pmt[1][0]!='-'){
printf("option not provided\n");
}
else{
printf("path not provided\n");
}
}
else{
execl(rmddir,path,opt,(char *)0);
}
}

if(strcmp(pmt[0],"mkdir")==0){                                                     //opt: -v,-p
char *path=pmt[2];
char *opt=pmt[1];
if(flag==1){
if(pmt[1][0]!='-'){
printf("option not provided\n");
}
else{
printf("path not provided\n");
}
}                                        
else{                                             
execl(mkddir,path,opt,(char *)0);
}
}
}
}
else{
if(strcmp(pmt[0],"cd")==0){
char cdp[100];
int cdcheck=0;
checkdot=0;
if(flag==0){
printf("no option/path provided\n");
}
else{
if(strcmp(pmt[1],"~")==0){
strcpy(pmt[1],getenv("HOME"));
}
if(flag==2){
if(strcmp(pmt[1],"-L")==0){
strcpy(pmt[1],pmt[2]);
}
else{
printf("invalid option\n");
cdcheck=1;
}
}
if(cdcheck==0){
if(strcmp(pmt[1],"..")==0){
checkdot=1;
}
else{
checkdot=0;
}
if(chdir(pmt[1])==-1){
printf("No such file or directory\n");
}
else{
add();
}
}
}
}
if(strcmp(pmt[0],"echo")==0){
if(flag>=1){
if(strcmp(pmt[1],"-n")==0){
for(int i=2;i<=flag;i++){
printf("%s",pmt[i]);
if(i!=flag){
printf(" ");
}
}
}
else if(strcmp(pmt[1],"-E")==0|| flag==0){
for(int i=2;i<=flag;i++){
for(int j=0;j<strlen(pmt[i]);j++){
printf("%c",pmt[i][j]);
}
printf(" ");
}
printf("\n");
}
else{
printf("invalid option\n");
}
}
else{
printf("invalid format\n");
}
}
if(strcmp(pmt[0],"pwd")==0){
char a[100],path[100];
if(flag==0|| flag==1){
if(strcmp(pmt[1],"-P")==0){
if(checkdot==1){
chdir(cd);
checkdot=0;
}
printf("%s\n",getcwd(a,100));
}
else if(strcmp(pmt[1],"-L")==0 ||strlen(pmt[1])==0){
printf("%s\n",cd);
}
else{
printf("invalid option\n");
}
}
else{
printf("invalid format\n");
}
}
if(strcmp(pmt[0],"exit")==0){
exit(0);
}
}
}

else if(pmt[0][strlen(pmt[0])-2]=='&'&&pmt[0][strlen(pmt[0])-1]=='t'){
pthread_t thread;
pthread_create(&thread,NULL,&command,NULL);
pthread_join(thread,NULL);
}
}
}
