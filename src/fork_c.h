#include <unistd.h>
#include <wait.h>
#include <stdint.h>
#include <sys/mman.h>
#include "shared_memory/mmap_c.h"

const char* fork_loop(int numForks, int arrayLength, char fileName[]);
