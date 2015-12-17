#include <stdio.h>
#include <stdlib.h>
#include "smpl.h"

/* Eventos */
#define test   1
#define fault  2
#define repair 3

/* Descritor de nodo */
typedef struct {
   int id; //identificador de facility
   //variaveis locais seguiriam aqui
}tnodo;

   tnodo *nodo;

void main(int argc, char *argv[]) {

   static N, token, event, r, i;
   static char fa_name[5];

   if (argc != 2) {
       printf("Uso correto: time <N>");
       exit(1);
   } 
     
   N = atoi(argv[1]);
   smpl(0, "um exemplo de simulacao");
   reset();
   stream(1);
   
   /* Inicializacao dos nodos */
   nodo = (tnodo *) malloc (sizeof(tnodo) * N);
   for(i=0; i<N; i++) {
      memset(fa_name, '\0',5);
      sprintf(fa_name, "%d",i);
      nodo[i].id = facility(fa_name, 1);
   }
   
   /* Escalonamento inicial de eventos */
   for (i=0; i<N; i++) 
      schedule(test, 30.0, i);
   schedule(fault, 50.0, 2);
   schedule(repair, 80.0, 2);
   
   /* Disparar tempo de simulacao */
   while (time() < 100) {
      cause(&event, &token);
      switch(event) {
	case test:
	  if (status(nodo[token].id != 0))
	     break;
	  printf("O nodo %d testou no tempo %5.1f\n", token, time());
	  schedule(test, 30.0, token);
	  break;
	case fault:
	  r = request(nodo[token].id, token, 0);
	  if (r != 0) {
	      printf("Não foi possível falhar o nodo %d no tempo %5.1f!\n", token, time());
	      exit(1);
	  }
	  printf("O nodo %d falhou no tempo %5.1f\n", token, time()); 
	  break;
	case repair:
	  release(nodo[token].id, token);
	  /*if (r != 0) { //nodo token falho
	      printf("Não foi possível recuperar o nodo %d no tempo %5.1f!\n", token, time);
	      exit(1);
	  }*/
	  schedule(test, 30.0, token);
	  printf("O nodo %d se recuperou no tempo %5.1f\n", token, time()); 
	  break;	  
      }
   }
   
   printf("Fim da simulacao\n");
   exit(0);

}