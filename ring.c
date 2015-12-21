#include <stdio.h>
#include "smpl.h"

#define FALHAR 0
#define TESTAR 1

int main(){
  int evento, x;
  int i, n = 10;
  int node[n];
  short node_status[n+2];
  int who_to_test[n];
  char facility_name[6];
  int k = 0;
  int node_tester;
  int r=0;

  smpl(0, "ring");
  reset();
  stream(1);
  
  memset(node_status, 0, n*sizeof(int));
  
  for(i=0; i < n; i++){
    memset(facility_name, '\0', 5);
    sprintf(facility_name, "%d", i);
    node[i] = facility(facility_name,1);
    who_to_test[i] = i+1;
    if(i == n-1)
      who_to_test[i] = 0;
  }

  for(i = 0; i < n; i++){
    schedule(TESTAR, 30.0, i);
  }
  schedule(FALHAR, 270.0, 2);
  schedule(FALHAR, 240, 1);

  do{
    cause(&evento, &x);
    
    switch(evento){
    case TESTAR:
      
      if(!node_status[k]){
      
	printf("O nodo %d testou o nodo %d no tempo %5.1f - ",k, who_to_test[k], time());
	int st = status(node[who_to_test[k]]);
	if(st != 0){
	  printf("falho!\n");
	
	  node_status[who_to_test[k]] = 1;

	  who_to_test[k]++;
	}else
	  printf("nao falho\n");
      }
      break;
    case FALHAR:
      r = request(node[x-1],x, 0);
      node_status[x] = 1;
      printf("O nodo %d falhou\n", x-1);
      break;
    }
   
    if(!node_status[k])
      schedule(TESTAR, 20.0, k);
    k=(++k)%n;
    //printf("%d\n", k);
  }while(time()<300);
  return 0;
}
