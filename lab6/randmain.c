#include "randcpuid.h"
#include <errno.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool
writebytes (unsigned long long x, int nbytes)
{
  int ndigits = nbytes * 2;
  do
    {
      if (putchar ("0123456789abcdef"[x & 0xf]) < 0)
	return false;
      x >>= 4;
      ndigits--;
    }
  while (0 < ndigits);

  return 0 <= putchar ('\n');
}

int
main (int argc, char **argv)
{
  /* Check arguments.  */
  bool valid = false;
  long long nbytes;
  if (argc == 2)
    {
      char *endptr;
      errno = 0;
      nbytes = strtoll (argv[1], &endptr, 10);
      if (errno)
	perror (argv[1]);
      else
	valid = !*endptr && 0 <= nbytes;
    }
  if (!valid)
    {
      fprintf (stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
      return 1;
    }

  /* If there's no work to do, don't worry about which library to use.  */
  if (nbytes == 0)
    return 0;

  /* Now that we know we have work to do, arrange to use the
     appropriate library.  */

  // void (*initialize) (void);
  unsigned long long (*rand64) (void);
  // void (*finalize) (void);
  void *libHandle;
  // char *error;

  if (rdrand_supported ())
    {
      // printf("Using hardware 2\n");
      //hardware implementation exists so we load hw library
      libHandle = dlopen("./randlibhw.so", RTLD_LAZY);
      if(!libHandle){
        fprintf(stderr, "Error when opening library: %s\n", dlerror());
        exit(1);
      }
      rand64 = dlsym(libHandle, "rand64");
      if(dlerror() != NULL){
        fprintf(stderr, "Error finding symbol\n");
        exit(1);
      }
    }
  else
    {
      // printf("Using software 2\n");
      libHandle = dlopen("./randlibsw.so", RTLD_LAZY);
      if(!libHandle){
        fprintf(stderr, "Error when opening library: %s\n", dlerror());
        exit(1);
      }
      rand64 = dlsym(libHandle, "rand64");
      if(dlerror() != NULL){
        fprintf(stderr, "Error finding symbol\n");
        exit(1);
      }
    }

    //no need to initialize cause that gets done when the library is loaded
  int wordsize = sizeof rand64 ();
  int output_errno = 0;

  do
    {
      unsigned long long x = rand64 ();
      int outbytes = nbytes < wordsize ? nbytes : wordsize;
      if (!writebytes (x, outbytes))
	{
	  output_errno = errno;
	  break;
	}
      nbytes -= outbytes;
    }
  while (0 < nbytes);

  if (fclose (stdout) != 0)
    output_errno = errno;

  if (output_errno)
    {
      errno = output_errno;
      perror ("output");
      return 1;
    }

  //no need to finalize b/c library does that when closing
  if(dlclose(libHandle)){
    fprintf(stderr, "Error when closing dynamic library\n");
    exit(1);
  }
  return 0;
}
