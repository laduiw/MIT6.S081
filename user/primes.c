#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int p[30][2];
void dfs(int now)
{
	//printf("now=%d signal\n",now);
	int t;
	close(p[now][1]);
	int n=read(p[now][0],&t,sizeof(int));
	//printf("n=%d\n",n);
	if (n==0) { return;}
	printf("prime %d\n",t);
//	printf("now=%d\n",now);
        //close(p[now+1][0]);

	pipe(p[now+1]);
	int pid=fork();
	if (pid==0)
	{
	//	sleep(4);
	//	printf("now=%d this is child\n",now);
	//	printf("dfs now=%d\n",now);
		dfs(now+1);
		exit(0);
	}
	else {	
	//	printf("now=%d this is parent\n",now);
		close(p[now+1][0]);
		int t1;
		//int cnt=0;
		while (read(p[now][0],&t1,sizeof(int))>0)
		{
			if (t1%t!=0 && t1<=35) {/*printf("now=%d t1=%d t=%d\n",now,t1,t)*/;write(p[now+1][1],&t1,sizeof(int));}
			//if (t1>35 && cnt==0) {printf("error t1=%d\n",t1);cnt=1;}
		}
		close(p[now][0]);
		close(p[now+1][1]);
		wait(0);
	//	printf("exit now=%d\n",now);
		exit(0);
	}
	exit(0);
}

int main(int argc,char *argv[])
{
	pipe(p[1]);
	if (fork()==0)
	{
		dfs(1);
	//	printf("end\n");
		exit(0);
	}
	else {
		close(p[1][0]);
		int i;
		for (i=2;i<=35;i++)
		{
			write(p[1][1],&i,sizeof(int));
		}
		close(p[1][1]);
		wait(0);
		exit(0);

	}
	exit(0);
}

