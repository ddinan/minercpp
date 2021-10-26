#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "casecmp.h"
#include "config.h"

#define CFG_COMMENT '#'

static int cfg_getkey(char *dst, size_t n, char *key);
static int cfg_getline(char *dst, size_t n, char *key, FILE *f);
static int str_to_int(int *dst, char *key);
static int str_to_bool(int *dst, char *str);

int cfg_getstr(char *dst, size_t n, char *key)
{
   return cfg_getkey(dst, n, key);
}

int cfg_getint(int *dst, char *key)
{
   char tmp[10 + 1];

   if(cfg_getkey(tmp, sizeof tmp, key)) {
      return 1;
   }

   return str_to_int(dst, tmp);
}

int cfg_getbool(int *dst, char *key)
{
   char tmp[5 + 1];

   if(cfg_getkey(tmp, sizeof tmp, key)) {
      return 1;
   }

   return str_to_bool(dst, tmp);
}

void cfg_template(void)
{
   FILE *f;

   f = fopen("server.cfg", "w");

   fputs("#comment\n", f);
   fputs("name = minerCPP - SMP Edition\n", f);
   fputs("motd = Welcome!\n", f);
   fputs("max-players = 16", f);

   fclose(f);
}

int cfg_getkey(char *dst, size_t n, char *key)
{
   size_t len;
   char fbuf[256], *ptr;
   FILE *f;

   f = fopen("server.cfg", "r");

   if(! f) {
      return 1;
   }

   if(cfg_getline(fbuf, sizeof fbuf, key, f)) {
      fclose(f);
      return 1;
   }

   fclose(f);

   for(ptr = fbuf; ! isalpha(*ptr) && ! isalnum(*ptr); ptr++) {
      if(*ptr == '\0') {
         return 1;
      }
   }

   n--; /* need space for null-termination. */
   len = strlen(ptr);

   if(len > n) {
      len = n;
   }

   strncpy(dst, ptr, len);
   dst[len] = '\0';

   return 0;
}

int cfg_getline(char *dst, size_t n, char *key, FILE *f)
{
   size_t len;

   len = strlen(key);

   do {
      if(fgets(dst, n, f) == NULL) {
         return 1;
      }
      if(dst[0] == CFG_COMMENT) {
         continue;
      }
   } while(strncmp(dst, key, len) != 0);

   len = strlen(dst);

   if(dst[len - 1] == '\n') {
      dst[len - 1] = '\0';
   }

   return 0;
}

int str_to_int(int *dst, char *str)
{
   int i;
   char *endptr;

   errno = 0;
   i = strtol(str, &endptr, 10);

   if(errno || *endptr || endptr == str) {
      return 1;
   }

   *dst = i;

   return 0;
}

int str_to_bool(int *dst, char *str)
{
   if(casecmp(str, "false") == 0) {
      *dst = 0;
   } else if(casecmp(str, "true") == 0) {
      *dst = 1;
   } else {
      return 1;
   }

   return 0;
}
