#ifndef _WORLD_H
#define _WORLD_H

typedef struct world {
   char *map;
   int x, y, z;
   int sx, sy, sz;
   char srx, sry;
} world_t;

extern world_t *wload(char *wname);
extern int wsave(world_t *w, char *wname);

#endif
