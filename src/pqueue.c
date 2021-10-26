#include <stdlib.h>
#include <string.h>
#include "pqueue.h"

int pcklen(int type)
{
   return 1;
}

pqueue_t *pq(int type, player_t *player, char *packet)
{
   size_t len;
   pqueue_t *p;

   p = malloc(sizeof(pqueue_t));

   if(p) {
      p->type = type;
      p->player = player;

      len = pcklen(type);

      if(! len) {
         free(p);
         return NULL;
      }

      p->packet = malloc(sizeof(char) * len);

      if(! p->packet) {
         free(p);
         return NULL;
      }

      p->len = len;
      memcpy(p->packet, packet, p->len);

      pq->prev = NULL;
      pq->next = NULL;
   }

   return p;
}

void pfree(pqueue_t *p)
{
   free(p->packet);
   free(p);
}

void pqfree(pqueue_t *pq)
{
   pqueue_t *p, *tmp;

   for(p = pq; p;) {
      tmp = p;
      p = p->next;
      pfree(tmp);
   }
}

void pdel(pqueue_t *p)
{
   pqueue_t *pp;

   pp = p->prev;

   if(pp) {
      pp->next = p->next;
   }

   pfree(p);
}
