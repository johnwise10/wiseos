/* queue.c -- Juan Sabio */ 
#include <queue.h>
#include <types.h>

/*
 * Inicializamos una estructura de tipo cola haciendo
 * que el primero y el ultimo apunten a la misma structura
 */
void init_queue(struct queue * queue){
	queue->last = queue->first = (struct item *)queue;

}

/*
 * Procedimiento que inserta al final de la cola el
 * elemento especificado (Item)
 */
void enqueue(struct queue * queue, struct item * item){
   struct item *j;
   if((j = queue->last) != NULL){
	item->next = j->next;
        item->back = j;
	j->next->back = item;
	j->next = item;
   }  
}

/*
 * Rutina que inserta un elemento en una cola ordenada por 
 * pesos
 */
void insert(struct queue *queue,struct item *item, unsigned long weight){
    
   struct item *j, *k;
   
   if ((j=queue->last) == NULL) return;
   
   item->weight = weight;
   k = (struct item *) queue;
   while((j!=(struct item *)queue) && (j->weight < weight))
   {
      k = j;
      j = j->back;
   }
   item->next = k;
   item->back = j;
   k->back = item;
   j->next = item;	
}

/*
 * Función que devuelve el puntero al primer elemento de la cola
 * y lo saca de la cola. Si la cola está vacía o no está inicializada 
 * devuelve NULL
 */
struct item * first(struct queue *queue){
   struct item * j;
   if ((j=queue->first) == NULL) return (NULL);
  
   queue->first = j->next;
   j->next->back = (struct item *)queue;

   return (j==(struct item *)queue ? NULL:j);
}

/*
 * Función que extrae de una cola ordenada, un elemento de un peso 
 * determinado. Si la cola está vacía o no está inicializada
 * devuelve NULL
 */
struct item * extract(struct queue *queue, unsigned long weight){
  struct item *j,*k;

  if((j=queue->first)==NULL) return (NULL);

  k = (struct item *) queue;

  while((j!=(struct item *)queue) && (j->weight > weight)){
      k = j;
      j = j->next;
  }
  
  if ((j==(struct item *)queue) || (j->weight != weight)) return(NULL);
  k->next = j->next;
  j->next->back = k;
  return(j);

}

/*
 * Función que extrae de una cola ordenada, un elemento. 
 * Si la cola está vacía o no está inicializada devuelve NULL
 */
struct item * extirpate(struct queue *queue, struct item *item){
  struct item *j,*k;

  if((j=queue->first)==NULL) return (NULL);

  k = (struct item *) queue;

  while((j!=(struct item *)queue) && (j!=item)){
      k = j;
      j = j->next;
  }
  if ((j==(struct item *)queue)) return(NULL);
  k->next = j->next;
  j->next->back = k;
  return(j);
}


/*
 * Función que devuelve el primer elemento de la cola 
 * pero no lo extrae
 */
struct item * head(struct queue *queue){
	return (queue->first);
}

/*
 * Función que mira si la cola está vacía, y si lo esta 
 * devuelve cierto. si la cola no está inicializada tambien 
 * devuelve cierto
 */
int empty(struct queue *queue){
	return ((queue->first == NULL) || queue->first == (struct item *)queue);
}

/*
 * Busca el primer elemento de la cola con un peso igual al del
 * parámetro pes. si no lo encuentra devuelve NULL
 */
struct item * search_item(struct queue *queue, unsigned long weight){
   struct item * j;

   if((j=queue->first)==NULL) return (NULL);
   while ((j!=(struct item *)queue) && (j->weight > weight))
	j=j->next;
   if((j==(struct item *)queue) || (j->weight != weight)) return(NULL);
   return(j);
}

/*
 * Obtiene el siguiente elemento de la cola
 */
struct item * next(struct queue *queue, struct item *item){
    if (item->next == (struct item *)queue) return (NULL);
    return (item->next);
}	

/*
 * Obtiene el siguiente elemento de la cola
 */
struct item * back(struct queue *queue, struct item *item){
    if (item->back == (struct item *)queue) return (NULL);
    return (item->back);
}

