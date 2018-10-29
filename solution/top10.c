#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
 int A[2]; 
 pipe(A);
 int pid1 = fork(); 
 
 if (!pid1) {
  dup2(A[1], 1);
  close(A[0]);
  close(A[1]);
  execlp("cat","cat", "log.txt", NULL);
  exit(EXIT_FAILURE);
 }
 
 int B[2]; 
 pipe(B);
 int pid2 = fork();                                       
 if (!pid2) { 
  dup2(A[0], 0);
  close(A[0]);
  close(A[1]); 

  dup2(B[1], 1);
  close(B[0]);
  close(B[1]);      

  execlp("cut","cut", "-f1", "-f11","-d ", NULL);
  exit(EXIT_FAILURE);                            
 }

 
 close(A[0]);
 close(A[1]);
 
 int C[2]; 
 pipe(C);
 
 int pid3 = fork();                                       
 if (!pid3) { 
  dup2(B[0], 0);
  close(B[0]);
  close(B[1]);
  
  dup2(C[1], 1);
  close(C[0]);
  close(C[1]);

  execlp("grep","grep", "\"-\"", NULL);
  exit(EXIT_FAILURE);    

 }


 close(B[0]);
 close(B[1]);

 int D[2]; 
 pipe(D);
 int pid4 = fork(); 

 if (!pid4) { 
  dup2(C[0], 0);
  close(C[0]);
  close(C[1]);
  
  dup2(D[1], 1);
  close(D[0]);
  close(D[1]);
  execlp("sort","sort",NULL);
  exit(EXIT_FAILURE);                            
 }
 
 close(C[0]);
 close(C[1]);

 int E[2]; 
 pipe(E);
 int pid5 = fork(); 

 if (!pid5) { 
  dup2(D[0], 0);
  close(D[0]);
  close(D[1]);
  
  dup2(E[1], 1);
  close(E[0]);
  close(E[1]);
    execlp("uniq","uniq", "-c", NULL);
    exit(EXIT_FAILURE);                            
 }

 close(D[0]);
 close(D[1]);


 int F[2]; 
 pipe(F);

 int pid6 = fork(); 

 if (!pid6) { 
  dup2(E[0], 0);
  close(E[0]);
  close(E[1]);
  
  dup2(F[1], 1);
  close(F[0]);
  close(F[1]);
  execlp("sort","sort","-rn", NULL);
  exit(EXIT_FAILURE);                            
 }

 close(E[0]);
 close(E[1]);
 
 int G[2]; 
 pipe(G);

 int pid7 = fork(); 

 if (!pid7) { 
  dup2(F[0], 0);
  close(F[0]);
  close(F[1]);
  
  dup2(G[1], 1);
  close(G[0]);
  close(G[1]);
  execlp("awk","awk","{ NUMBERS[$2]=$1;LINK[$2]=$2; } END { for(i in LINK) print i,\"-\",NUMBERS[i],\"-\",int(NUMBERS[i]/NR*100) }", NULL);
  exit(EXIT_FAILURE);                            
 }

 close(F[0]);
 close(F[1]);
 
 int H[2]; 
 pipe(H);

 int pid8 = fork(); 

 if (!pid8) { 
  dup2(G[0], 0);
  close(G[0]);
  close(G[1]);
  
  dup2(H[1], 1);
  close(H[0]);
  close(H[1]);
  execlp("sort","sort","-k3","-rn", NULL);
  exit(EXIT_FAILURE);                            
 }

 close(G[0]);
 close(G[1]); 

 int I[2]; 
 pipe(I);

 int pid9 = fork(); 

 if (!pid9) { 
  dup2(H[0], 0);
  close(H[0]);
  close(H[1]);
  
  dup2(I[1], 1);
  close(I[0]);
  close(I[1]);
  execlp("head","head","-n","10", NULL);
  exit(EXIT_FAILURE);                            
 }

 close(H[0]);
 close(H[1]); 

  FILE* Cin = fdopen(I[0],"r"); 
  int sum=0;
  char line[1000];
  while (fgets(line, sizeof(line), Cin)) {
   printf("%s", line); 
   }                                       
 return 0;
}
