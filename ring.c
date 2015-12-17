#include <stdio.h>
#include "smpl.h"

#define FALHAR 0
#define TESTAR 1

int main(){
  int evento, x;
  int i, n = 10;
  int node[n];
  short node_status[n];
  int who_to_test[n];
  char facility_name[6];
  int k = 0;

  smpl(0, "ring");
  reset();
  stream(1);
  
  memset(node_status, 0, n);
  
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
  
  while(time() <= 300){
    cause(&evento, &x);
    switch(evento){
    case TESTAR:
      printf("O nodo %d testou o nodo %d no tempo %5.1f - ", (k++)%n, who_to_test[k%n], time());
      int st = status(node[k%n]);
      if(st != 0)
	printf("falho!\n");
      else
	printf("nao falho\n");
      schedule(TESTAR, 30.0, x);
      break;
    }
    //printf("No while\n");
  }
  return 0;
}
