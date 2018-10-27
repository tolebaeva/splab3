/*
does same thing as 'sum01'
shell logic is performed by the parent process
*/

/* sum01
#! /bin/bash
#                  A               B                               
list=$(cat log.txt | cut -f4 -d' ' | sed -E 's/\[0*([0-9]*).*/\1/')
# C is the pipe that is used to store the result of the above pipeline to $list
sum=0
for i in $list
do
  sum=$(( sum + i ))
done
# the above loop uses C pipe

echo $sum
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
	int A[2]; // pipe A
	pipe(A);
	pid_t pid1 = fork(); // cat
	if (!pid1) {
		dup2(A[1], 1);
		close(A[0]);
		close(A[1]);      
		execlp("cat","cat", "log.txt", NULL);
		exit(EXIT_FAILURE);
	}  

  int B[2]; // pipe B
	pipe(B);

	pid_t pid2 = fork();                                       
	if (!pid2) { // cut
		dup2(A[0], 0);
		close(A[0]);
		close(A[1]); 

		dup2(B[1], 1);
		close(B[0]);
		close(B[1]);      

		execlp("cut","cut", "-f4", "-d ", NULL);
		exit(EXIT_FAILURE);                            
	}
	
  int C[2]; // pipe C
	pipe(C);

	pid_t pid3 = fork();                                       
	if (!pid3) { // grep
		dup2(B[0], 0);
		close(B[0]);
		close(B[1]);
		close(A[0]);
		close(A[1]);

		dup2(C[1], 1);
		close(C[0]);
		close(C[1]);

		execlp("sed","sed", "-E", "s/\\[0*([0-9]*).*/\\1/", NULL); // sed -E 's/\[0*([0-9]*).*/\1/'
		exit(EXIT_FAILURE);                            
	}
  close(A[0]); close(A[1]);
  close(B[0]); close(B[1]);
	close(C[1]);

	FILE* Cin = fdopen(C[0],"r"); // Cin is FILE* object made from C[0]
	int x,sum=0;
	while(fscanf(Cin,"%d",&x)>0){ // this loop is like the loop of shell 
		sum+=x;
	}
	printf("sum = %d\n",sum); // echo $sum
}
