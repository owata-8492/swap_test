#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <errno.h>

#define SWAP_IO 309

int main(){

  FILE *fp_A, *fp_B;
  pid_t tmpid, pid_A, pid_B;
  int status = 0;
  int exec_result;

  tmpid = fork();
  
  if(tmpid < 0){
    fprintf(stderr,"error! fork failed\n");
  }
  
  if(tmpid == 0){// child process : printA
    pid_A = tmpid;
    exec_result = execlp("/home/sato-h/funcs_test/printA","/home/sato-h/funcs_test/printA",NULL);
    if(exec_result == -1){printf("exec error: %d\n",errno); exit(1);}
  }else{
    pid_B = tmpid;
    tmpid = fork();

    if(tmpid < 0){
      fprintf(stderr,"error! fork failed\n");
    }

    if(tmpid == 0){// child process : printB
      exec_result = execlp("/home/sato-h/funcs_test/printB","/home/sato-h/funcs_test/printB",NULL);
      if(exec_result == -1){printf("exec error: %d\n",errno); exit(1);}
    }else{
      sleep(1);
      fp_A = fopen("out/out1.txt","w");
      if(fp_A == NULL){fprintf(stderr,"error! fopen failed\n"); exit(1);}
      
      fp_B = fopen("out/out2.txt","w");
      if(fp_B == NULL){fprintf(stderr,"error! fopen failed\n"); exit(1);}
      
      sleep(1);

      exec_result = syscall(SWAP_IO, pid_A, -1, pid_B, -1);
      printf("swap result: %d\n",exec_result);
      
      wait(&status);
      
      fclose(fp_A);
      fclose(fp_B);
    }
  }
  return 0;
}
