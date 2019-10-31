#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
  int fd;
  int i;
  
  fd = open("out/out1.txt",O_WRONLY);
  
  if(fd == -1){
    fprintf(stderr,"error! open failed\n");
  }

  for(i=0;i<100;i++){
    write(fd,"A",1);
  }

  write(fd,"\n",1);

  printf("first printA finished\n");
  
  sleep(3);

  for(i=0;i<100;i++){
    write(fd,"A",1);
  }

  printf("second printA finished\n");

  close(fd);

  return 0;
}
