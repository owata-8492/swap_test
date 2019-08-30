#include <stdio.h>
#include <unistd.h>

int main(){
  FILE *fp;
  int i;
  
  fp = fopen("out/out1.txt","w");
  
  if(fp == NULL){
    fprintf(stderr,"error! fopen failed\n");
  }
  for(i=0;i<100;i++){
    fprintf(fp,"a");
  }
  
  sleep(3);

  for(i=0;i<100;i++){
    fprintf(fp,"a");
  }
  return 0;
}
