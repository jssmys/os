#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>


int main(){
DIR *d;
struct dirent *de;
struct stat buf;
int i,j;
char P[10]="rwxrwxrwx",AP[10]=" ";
struct passwd *p;
struct group *g;
struct tm *t;
char time[26];

d=opendir(".");
readdir(d);

while((de=readdir(d))!=NULL){
stat(de->d_name,&buf);


if(S_ISDIR(buf.st_mode))
printf("d");
else if(S_ISREG(buf.st_mode))
printf("r");
else if(S_ISCHR(buf.st_mode))
printf("c");
else if(S_ISBLK(buf.st_mode))
printf("b");
else if(S_ISFIFO(buf.st_mode))
printf("p");
else if(S_ISSOCK(buf.st_mode))
printf("s");

for(i=0,j=(1<<8);i<9;i++,j>>=1)
AP[i]=(buf.st_mode & j) ? P[i] : '-';
printf("%s\t",AP);


printf("%5ld\t",buf.st_nlink);

p=getpwuid(buf.st_uid);
printf("%.8s\t",p->pw_name);

g=getgrgid(buf.st_gid);
printf("%-8.8s\t",g->gr_name);

printf("%8ld\t",buf.st_size);

t=localtime(&buf.st_mtime);
strftime(time,sizeof(time),"%b%d%H:%M",t);
printf("%s\t",time);
printf("%s\n",de->d_name);
}

}
