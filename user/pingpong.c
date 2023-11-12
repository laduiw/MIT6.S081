#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char *argv[])
{
	int p[2],e[2];
	char buf[10]="a";
	pipe(p);
	pipe(e);
	int pid = fork();
	if (pid==0)
	{
		close(e[1]);
		close(p[0]);
		int n=read(e[0],buf,1);
		if (n<0) exit(1);
		printf("%d: received ping\n",getpid());
		n=write(p[1],buf,1);
		if (n<0) exit(1);
		exit(0);
	}
	else {
		close(e[0]);
		close(p[1]);
		int n=write(e[1],buf,1);
		if (n<0) exit(1);
		wait(0);
		n=read(p[0],buf,1);
		if (n<0) exit(1);
		printf("%d: received pong\n",getpid());
		exit(0);
	}
}
