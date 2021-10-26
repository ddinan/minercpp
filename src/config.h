#ifndef _CONFIG_H
#define _CONFIG_H

extern int cfg_getstr(char *dst, size_t n, char *key);
extern int cfg_getint(int *dst, char *key);
extern int cfg_getbool(int *dst, char *key);
extern void cfg_template(void);

#endif