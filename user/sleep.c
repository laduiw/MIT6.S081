#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int main(int argc,char *argv[])
{
	if (argc<2) exit(1);
	else 
	{
		int ti=atoi(argv[1]);
		sleep(ti);
		exit(0);
	}
}
