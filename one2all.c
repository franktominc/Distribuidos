#include <stdio.h>
#include "smpl.h"

#define testar 1

int main(void) {
  int evento, x;
  int i, N = 5;
  int nodo[N];
  char fa_name[5];
  smpl(0, "one2all");
  reset();
  stream(1); 
  for(i=0; i<N; i++) {
    memset(fa_name, '\0',5);
    sprintf(fa_name, "%d",i);
    nodo[i] = facility(fa_name, 1);
  }
  
  for (i=1; i<N; i++) {	
    schedule(testar, 30.0, i);
  }
  
  while (time() < 300) {
    cause(&evento, &x);
    switch(evento) {
    case testar:	
      printf("O nodo 0 testou nodo %d no tempo %5.1f - ", x, time());
      int st =  status(nodo[x]);
      if (st != 0) //nodo testado esta falho?
	printf("falho!\n");		
      else
	printf("não-falho\n");
      schedule(testar, 30.0, x);
      break;
    }
  } 
  return 0;
}
