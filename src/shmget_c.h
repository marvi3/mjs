#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


struct shmget {  
    key_t key;
    int shmid;
    char* shared_mem;
    int numElem;
    int size;
    int IPC_RESULT_ERROR;
};

struct shmget create(int numChar, int arrayLen, char filename[]);
void removeMemory(struct shmget element);
bool detach(int i, struct shmget memory);
bool add(int index, char str[], struct shmget memory);
bool addAll(char *list[], struct shmget memory);
bool addAllSoft(char *list[], struct shmget memory);
const char *get(int index, struct shmget memory);
