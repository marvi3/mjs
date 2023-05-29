#include <unistd.h>
#include <wait.h>
#include <stdint.h>
#include <sys/mman.h>
#include "shmget_c.h"

const char* fork_loop(int numForks, int arrayLength, char fileName[]);
