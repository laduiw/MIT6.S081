#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char*
fmtname(char *path)
{
  //static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  //memmove(buf, p, strlen(p));
 // memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return p;
}

void
find(char *path,char *name)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;
  
  //printf("path=%s\n",path);
  if((fd = open(path, 0)) < 0){
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "find: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_DEVICE:
  case T_FILE:
  	if (strcmp(fmtname(path),name)==0) printf("%s\n", path);
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("find: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;

      //printf("de=%s\n",de.name);
      memmove(p, de.name,DIRSIZ);
      p[DIRSIZ] = 0;
      //printf("now buf=%s\n",buf);
      if(stat(buf, &st) < 0){
        printf("find: cannot stat %s\n", buf);
        continue;
      }
      //if (strcmp(de.name,name)==0) printf("%s\n", buf);
      //printf("p=%s\n",p);
      if (strcmp(de.name,".")!=0 && strcmp(de.name,"..")!=0) find(buf,name);
      //printf("%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  find(argv[1],argv[2]);
  exit(0);
}
