#ifndef _QUEUE_H
#define _QUEUE_H

// Definición de las estructuras de la cola
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
 * Función que devuelve el puntero al primer elemento de la cola
 * y lo saca de la cola. Si la cola está vacía o no está inicializada 
 * devuelve NULL
 */
struct item * first(struct queue *);

/*
 * Función que extrae de una cola ordenada, un elemento de un peso 
 * determinado. Si la cola está vacía o no está inicializada
 * devuelve NULL
 */
struct item * extract(struct queue *, unsigned long);


/*
 * Función que extrae de una cola ordenada, un elemento. 
 * Si la cola está vacía o no está inicializada devuelve NULL
 */
struct item * extirpate(struct queue *,struct item *);


/*
 * Función que devuelve el primer elemento de la cola 
 * pero no lo extrae
 */
struct item * head(struct queue *);

/*
 * Función que mira si la cola está vacía, y si lo esta 
 * devuelve cierto. si la cola no está inicializada tambien 
 * devuelve cierto
 */
int empty(struct queue *);

/*
 * Busca el primer elemento de la cola con un peso igual al del
 * parámetro pes. si no lo encuentra devuelve NULL
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
