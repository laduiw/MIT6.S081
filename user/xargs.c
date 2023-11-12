#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc,char *argv[])
{
	char *xar[20];
	for (int i=0;i<15;i++)
		xar[i]=(char *)malloc(30*sizeof(char));

	//printf("argc=%d\n",argc);
	//for (int i=0;i<argc;i++)
	//	printf("%s ",argv[i]);
	//printf("\n");
	for (int i=1;i<argc;i++)
	{
		strcpy(xar[i-1],argv[i]);
		//int len=strlen(argv[i]);
		//for (int j=0;j<=len;j++)
		//{
		//	xar[i-1][j]=argv[i][j];
		//	printf("char =%c\n",xar[i-1][j]);
		//}
	}	
	//printf("xar=\n");
	//for (int i=0;i<argc-1;i++)
	//	printf("%s ",xar[i]);
	//printf("\n");
	char ch;
	int tot=0;
	char s[20]="";
	while (read(0,&ch,sizeof(char))>0)
	{
		if (ch=='\n')
		{
			s[tot]='\0';
                        //printf("s=%s\n",s);
                        strcpy(xar[argc-1],"");
                        strcpy(xar[argc-1],s);
                        strcpy(s,"");
                        tot=0;
			int pid=fork();
			if (pid==0)
			{
				exec(argv[1],xar);
			}
			else 
			{
				wait(0);
			}
		}
		else s[tot++]=ch;
	}
	//exec(argv[1],xar);
	//printf("error exec");	
	exit(0);
}
