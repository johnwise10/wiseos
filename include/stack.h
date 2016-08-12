#ifndef _STACK_H
#define _STACK_H

typedef struct item
{
    struct item *back;//puntero al elemento anterior
    int pes;
} item;

typedef struct stack{
	struct item  *cim;
} stack;

// Funcion que inicializa la pila
void init_stack(struct stack * stack);

// Función que inserta un elemento en la pila
int push(struct stack *, struct item *);

// Función que devuelve la cima de la pila
struct item * pop(struct stack *);
#endif
