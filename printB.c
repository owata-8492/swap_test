#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
  int fd;
  int i;
  
  fd = open("out/out2.txt",O_WRONLY);
  
  if(fd == -1){
    fprintf(stderr,"error! open failed\n");
  }

  for(i=0;i<100;i++){
    write(fd,"B",1);
  }

  write(fd,"\n",1);

  printf("first printB finished\n");
  
  sleep(3);

  for(i=0;i<100;i++){
    write(fd,"B",1);
  }

  printf("second printB finished\n");

  close(fd);
  return 0;
}
