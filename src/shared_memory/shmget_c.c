#include "shmget_c.h"

// This constructor creates a shared memory with "arrayLen" strings, each with "numChar" chars
struct shmget create(int numChar, int arrayLen, char filename[]) {
    struct shmget returnMem;
    returnMem.numElem = arrayLen;
    returnMem.size = numChar;
    returnMem.IPC_RESULT_ERROR = -1;
    // ftok to generate unique key
    returnMem.key = ftok(filename, 65);
    if (returnMem.key == returnMem.IPC_RESULT_ERROR)
    {
        printf("Could not get the key to the shared memory.\n");
        perror("IPC error: ftok");
        exit(1);
    }

    // shmget returns an identifier in shmid
    returnMem.shmid = shmget(returnMem.key, returnMem.size * returnMem.numElem, 0666 | IPC_CREAT);
    // shmat to attach to shared memory
    returnMem.shared_mem = (char *)shmat(returnMem.shmid, NULL, 0);
    return returnMem;
}

void removeMemory(struct shmget memory) {
    shmctl(memory.shmid, IPC_RMID, NULL);
}

bool detach(int i, struct shmget memory) {
    // detach from shared memory
    return (shmdt(memory.shared_mem) != memory.IPC_RESULT_ERROR);
}

bool add(int index, char str[], struct shmget memory) {
    // sanity check if the element would write out of memory bounds.
    printf("Size of string in c shmget add: " + sizeof(str));
    if (index >= memory.numElem || sizeof(str) >= memory.size)
    {
        return false;
    }
    for (int i = (index * memory.size); i < (index * memory.size) + sizeof(str); i++)
    {
        memory.shared_mem[i] = str[i];
    }

    for (int i = (index * memory.size) + sizeof(str); i < ((index + 1) * memory.size); i++)
    {
        memory.shared_mem[i] = NULL;
    }
    return true;
}

// adds all elements in the list to the shared memory if the list fits in
// If the list is longer than the shared memory, it will not add anything and return with false.
bool addAll(char *list[], struct shmget memory) {
    int listSize = sizeof(list) / sizeof(list[0]);
    if(memory.numElem < listSize) {
        return false;
    }
    
    for (int i = 0; i < listSize; i++) {
        add(i, list[i], memory);
    }

    for (int i = listSize; i < memory.numElem; i++) {
        add(i, NULL, memory);
    }
    
    return true;
}

// adds all elements in the list to the shared memory even if the list does not fit in completely.
// if not all elements fit in only the first number of elements that do fit in will be added.
bool addAllSoft(char *list[], struct shmget memory) {
    int listSize = sizeof(list) / sizeof(list[0]);
    if(memory.numElem < listSize) {
        for (int i = 0; i < memory.numElem; i++) {
            add(i, list[i], memory);
        }
    } else {
        for (int i = 0; i < listSize; i++) {
            add(i, list[i], memory);
        }

        for (int i = listSize; i < memory.numElem; i++) {
            add(i, NULL, memory);
        }
    }
    
    return true;
}

const char *get(int index, struct shmget memory) {
    if (index >= memory.numElem) {
        return NULL;
    }
    char *returnString = NULL;
    for (int i = (index * memory.size); i < ((index + 1) * memory.size); i++) {
        if (memory.shared_mem[i] == NULL) {
            return returnString;
        }
        returnString += memory.shared_mem[i];
    }
    return returnString;
}

// int shm_init()
// {
//     printf("Data read from memory: %s\n",str);

//     // destroy the shared memory
//     shmctl(shmid,IPC_RMID,NULL);

//     return 0;
// }