/* stack.c -- Juan Sabio */

#include <stack.h>
#include <types.h>

// Funcion que inicializa la pila
void init_stack(struct stack * stack){
     stack->cim = NULL;
}

// Función que inserta un elemento en la pila
int push(struct stack * stack, struct item * item){
 
 item->back = stack->cim;
 item->pes  = 0;
 stack->cim = item;
 return 0;
}

// Función que devuelve la cima de la pila
struct item * pop(struct stack * stack){
 struct item * it;
 if (stack->cim == NULL){
    return NULL;
 }else{
 it = stack->cim;
 stack->cim = it->back;
 return it;
 }
}
