#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <errno.h>

#define SWAP_IO 309

int main(){
  pid_t tmpid, pid_A, pid_B;
  int status = 0;
  int exec_result;

  tmpid = fork();
  
  if(tmpid < 0){
    fprintf(stderr,"error! fork failed\n");
  }
  
  if(tmpid == 0){// child process : printA
    exec_result = execl("/home/sato-h/funcs_test/printA","/home/sato-h/funcs_test/printA",NULL);
    if(exec_result == -1){printf("exec error: %d\n",errno); exit(1);}
  }else{
    pid_A = tmpid;
    tmpid = fork();

    if(tmpid < 0){
      fprintf(stderr,"error! fork failed\n");
    }

    if(tmpid == 0){// child process : printB
      exec_result = execl("/home/sato-h/funcs_test/printB","/home/sato-h/funcs_test/printB",NULL);
      if(exec_result == -1){printf("exec error: %d\n",errno); exit(1);}
    }else{
      pid_B = tmpid;

      sleep(1);

      printf("pid_A:%d\n",pid_A);
      printf("pid_B:%d\n",pid_B);

      exec_result = syscall(SWAP_IO, pid_A, -1, pid_B, -1);

      sleep(1);

      waitpid(pid_A, &status, 0);
      waitpid(pid_B, &status, 0);

      printf("swap result: %d\n",exec_result);
    }
  }
  return 0;
}
