#ifndef _PQUEUE_H
#define _PQUEUE_H

#include <string.h>
// #include "player.h"
typedef int player_t;

typedef struct pqueue {
   int type;
   player_t *player;
   char *packet;
   size_t len;
   struct pqueue *prev, *next;
} pqueue_t;

/* creates a new entry with the given arguments */
extern pqueue_t *pq(int type, player_t *player, char *packet);
/* free's an entry without consideration to the list */
extern void pfree(pqueue_t *p);
/* free's an entire list. */
extern void pqfree(pqueue_t *pq);
/* deletes the entry p and relinks the list. */
extern void pdel(pqueue_t *p);
/* pops an entry from pq, relinks the list */
extern pqueue_t *pqpop(pqueue_t *pq);

#endif
