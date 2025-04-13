#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include "get_num.h"

static void gnFail(const char *fname, const char *msg, 
                   const char *arg, const char *name){
    fprintf(stderr, "%s error", fname);
    if (name != NULL) fprintf(stderr, " (in %s)", name);
    fprintf(stderr, ": %s\n", msg);
    if (arg != NULL && *arg != '\0') fprintf(stderr,  " offending text: %s\n", arg);
    
    exit(EXIT_FAILURE);
}
