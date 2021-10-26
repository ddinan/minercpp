#include <string.h>
#include <ctype.h>

extern int casecmp(char *s1, char *s2)
{
   char c1, c2;

   for(; *s1 && *s2; s1++, s2++) {
      c1 = tolower(*s1);
      c2 = tolower(*s2);

      if(c1 != c2) {
         return 1;
      }
   }

   return 0;
}

extern int casencmp(char *s1, char *s2, size_t n)
{
   size_t i;
   char c1, c2;

   for(i = 0; i < n; i++) {
      c1 = tolower(s1[i]);
      c2 = tolower(s2[i]);

      if(c1 != c2) {
         return 1;
      }
   }

   return 0;
}
