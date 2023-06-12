#include "fork_c.h"

const char* fork_loop(int numChar, int arrayLen, char fileName[]) {
    // void *shared_mem_pointer[arrayLength];
    printf("Fork_c.c: filename is %s\n", fileName);
    int fileDescriptor = create_fileDescriptor(fileName);
    char *memory = (char*)shared_mmap_fd(numChar * arrayLen, fileDescriptor);
    // struct shmget memory = create(numChar, arrayLen, fileName);
    pid_t pid;
    for (int i = 0; i < arrayLen -1; i++) {
        pid = fork();

        // decide if continue as child or parent process
        if (pid == 0) {
            // beginn child execution
            return get(memory, i, numChar);
        } else if(pid > 0) {
            // beginn parent execution
            // shared_mem_pointer[i] = result.first;
        } else {
            printf("Error creating the Process. The resulting PID is %d.\n",pid);
        }
    }
    const char *ret = get(memory, arrayLen - 1, numChar);
    close_mmap(fileDescriptor, fileName);
    return ret;
}