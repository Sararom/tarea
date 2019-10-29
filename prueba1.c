
// C program for passing value from 
// child process to parent process 
#include <pthread.h> 
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>  
#include <stdlib.h>  
#include <sys/wait.h> 
  
int main(int argc, char *argv[]) 
{ 
  
  int fd[2], i = 0; 
  pipe(fd); 
   
  int pidc; 
  int n = atoi(argv[1]);
  for(int i=0; i<n;i++){
	pid_t pid = fork();
   if(pid > 0) { 
      wait(NULL); 
  
      // padre  
      close(0); 
  
      // no need to use the write end of pipe here so close it 
      close(fd[1]);  
  
       // duplicating fd[0] with standard input 0 
      dup(fd[0]);  
      
  
      // n stores the total bytes read succesfully 
      read(fd[0], &pidc, sizeof(pidc)); 
      printf("Soy el padre con pid %d y el pid de mi hijo es: %d \n",getpid(), pidc);
	wait(NULL);  
  }  
  else if( pid == 0 ) { 
      pidc= getpid();
  
      // no need to use the read end of pipe here so close it 
      close(fd[0]);  
  
       // closing the standard output 
      close(1);     
  
      // duplicating fd[0] with standard output 1 
      dup(fd[1]);   
      write(1, &pidc, sizeof(pidc)); 
  }  
  
  else { 
      perror("error\n"); //fork() 
  } 
 }
}  

