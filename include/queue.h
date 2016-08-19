#ifndef _QUEUE_H
#define _QUEUE_H

// Definici�n de las estructuras de la cola
typedef struct item{ 
	struct item *next;
	struct item *back;
	unsigned long weight;
}item;

typedef struct queue{
	struct item *first;
	struct item *last;
}queue;

/*
 * Inicializamos una estructura de tipo cola haciendo
 * que el primero y el ultimo apunten a la misma structura
 */
void init_queue(struct queue *);

/*
 * Procedimiento que inserta al final de la cola el
 * elemento especificado (Item)
 */
void enqueue(struct queue *, struct item * );

/*
 * Rutina que inserta un elemento en una cola ordenada por 
 * pesos
 */
void insert(struct queue *,struct item *, unsigned long);

/*
 * Funci�n que devuelve el puntero al primer elemento de la cola
 * y lo saca de la cola. Si la cola est� vac�a o no est� inicializada 
 * devuelve NULL
 */
struct item * first(struct queue *);

/*
 * Funci�n que extrae de una cola ordenada, un elemento de un peso 
 * determinado. Si la cola est� vac�a o no est� inicializada
 * devuelve NULL
 */
struct item * extract(struct queue *, unsigned long);


/*
 * Funci�n que extrae de una cola ordenada, un elemento. 
 * Si la cola est� vac�a o no est� inicializada devuelve NULL
 */
struct item * extirpate(struct queue *,struct item *);


/*
 * Funci�n que devuelve el primer elemento de la cola 
 * pero no lo extrae
 */
struct item * head(struct queue *);

/*
 * Funci�n que mira si la cola est� vac�a, y si lo esta 
 * devuelve cierto. si la cola no est� inicializada tambien 
 * devuelve cierto
 */
int empty(struct queue *);

/*
 * Busca el primer elemento de la cola con un peso igual al del
 * par�metro pes. si no lo encuentra devuelve NULL
 */
struct item * search_item(struct queue *, unsigned long);

/*
 * Obtiene el siguiente elemento de la cola
 */
struct item * next(struct queue *, struct item *);

/*
 * Obtiene el siguiente elemento de la cola
 */
struct item * back(struct queue *, struct item *);

#endif
