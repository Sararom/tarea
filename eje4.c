
// C program for passing value from 
// child process to parent process 
#include <pthread.h> 
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>  
#include <stdlib.h>  
#include <sys/wait.h> 

struct Node { 
    int data; 
    struct Node* next; // Pointer to next node in DLL 
    struct Node* prev; // Pointer to previous node in DLL 
};

struct Node* head;

struct Node* GetNewNode(int x) {
	struct Node* newNode
		= (struct Node*)malloc(sizeof(struct Node));
	newNode->data = x;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

void InsertAtHead(int x) {
	struct Node* newNode = GetNewNode(x);
	if(head == NULL) {
		head = newNode;
		return;
	}
	head->prev = newNode;
	newNode->next = head; 
	head = newNode;
}

void ReversePrint() {
	struct Node* temp = head;
	
	while(temp != NULL) {
	sleep(1);
	printf("Soy el Nodo con pid: ");
		printf("%d \n",temp->data);
		temp = temp->next;
	}
	printf("\n");
}

void Print() {
	struct Node* temp = head;
	if(temp == NULL) return; // empty list, exit
	while(temp->next != NULL) {
		temp = temp->next;
	}
	// Traversing backward using prev pointer
	
	while(temp != NULL) {
		sleep(1);
		printf("Soy el Nodo con pid: ");
		printf("%d \n",temp->data);
		temp = temp->prev;
	}
	printf("\n");
}

int main(int argc, char *argv[]) 
{ 
  
  int fd[2], i = 0; 
  pipe(fd); 
   
  int pidc; 
  int n = atoi(argv[1]);
	int hijos[n];

  for(int i=0; i<n;i++){
	pid_t pid = fork();
   if(pid > 0) { 
      //wait(NULL); 
      // padre  
      close(0); 
      close(fd[1]);  
      dup(fd[0]);  
      read(fd[0], &pidc, sizeof(pidc)); 
	sleep(1);
      printf("Soy el padre con pid %d y el pid de mi hijo es: %d \n",getpid(), pidc);
	//hijos[i] =pidc;
	InsertAtHead(pidc);
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
 }
	Print();
}  

