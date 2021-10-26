#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <zlib.h>

#ifdef _WIN32
#include <windows.h>
typedef HANDLE FILEOBJ;
#else
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
typedef int FILEOBJ;
#endif

#include "world.h"

typedef struct {
   FILEOBJ wf;
   char wfnam[32];
} WFILE;

static WFILE *wfopen(void);
static void wfclose(WFILE *wf);
static int wfwrite(const void *ptr, size_t n, WFILE *wf);
static int wfseek(WFILE *wf, int offset, int whence);
static void *wfmmap(WFILE *wf, size_t n);
static void wfmunmap(void *addr, size_t n);

static long fsize(FILE *f);
static long gzsize(FILE *gz);

world_t *wload(char *wname)
{
   return NULL;
}

int wsave(world_t *w, char *wname)
{
   return 0;
}

WFILE *wfopen(void)
{
   WFILE *wf;

   wf = malloc(sizeof(WFILE));

   if(wf) {
#ifdef _WIN32
      GetTempFileName(".", "tmp_", 0, wf->wfnam);

      wf->wf = CreateFile(
      wf->wfnam, GENERIC_READ | GENERIC_WRITE,
      FILE_SHARE_READ, NULL, CREATE_ALWAYS,
      FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_DELETE_ON_CLOSE, NULL);
#else
      strcpy(wf->wfnam, "./tmp_XXXXXX");
      wf->wf = mkstemp(wf->wfnam);
#endif
   }

   return wf;
}

void wfclose(WFILE *wf)
{
#ifdef _WIN32
   CloseHandle(wf->wf);
#else
   close(wf->wf);
   remove(wf->wfnam);
#endif
   free(wf);
}

int wfwrite(const void *ptr, size_t n, WFILE *wf)
{
   int i;
   int written = 0;
   char *byteptr = (char*) ptr;

#ifdef _WIN32
   DWORD nBytesWritten;

   while(n) {
      i = WriteFile(wf->wf, byteptr, n, &nBytesWritten, NULL);

      if(! i) {
         return 0;
      }

      n -= nBytesWritten;
      written += nBytesWritten;
      byteptr += nBytesWritten;
   }
#else
   ssize_t sn;

   while(n) {
      sn = write(wf->wf, byteptr, len);

      if(sn == -1) {
         return 0;
      }

      n -= sn;
      written += sn;
      byteptr += sn;
   }
#endif

   return written;
}

int wfseek(WFILE *wf, int offset, int whence)
{
   int ret;

#ifdef _WIN32
   ret = SetFilePointer(wf->wf, offset, 0, whence);
#else
   ret = lseek(wf->wf, offset, whence);
#endif

   return (ret != -1 ? 0 : 1);
}

void *wfmmap(WFILE *wf, size_t n)
{
   void *addr;

#ifdef _WIN32
   HANDLE hMap;

   hMap = CreateFileMapping(
   wf->wf, NULL, PAGE_READWRITE, 0, 0, NULL);

   if(hMap == NULL) {
      return NULL;
   }

   addr = MapViewOfFile(
   hMap, FILE_MAP_READ | FILE_MAP_WRITE,
   0, 0, n);

   CloseHandle(hMap);
#else
   addr = mmap(0, n, PROT_READ | PROT_WRITE, MAP_SHARED, wf->wf, 0);

   if(addr == MAP_FAILED) {
      mapped = NULL;
   }
#endif

   return addr;
}

void wfmunmap(void *addr, size_t n)
{
#ifdef _WIN32
   UnmapViewOfFile(addr);
#else
   munmap(addr, n);
#endif
}

long fsize(FILE *f)
{
   long filesize;
   fpos_t oldpos;

   fgetpos(f, &oldpos);
   fseek(f, 0, SEEK_END);
   filesize = ftell(f);
   fsetpos(f, &oldpos);

   return filesize;
}

/* returns the .gz file's original, uncompressed size */
long gzsize(FILE *gz)
{
   long ucsize;
   fpos_t oldpos;

   fgetpos(gz, &oldpos);
   fseek(gz, -4, SEEK_END);
   fread(&ucsize, sizeof(char), sizeof(long), gz);
   fsetpos(gz, &oldpos);

   return ucsize;
}
