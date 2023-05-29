#include "fork_c.h"

const char* fork_loop(int numForks, int arrayLength, char fileName[]) {
    void *shared_mem_pointer[numForks];
    struct shmget memory = create(numForks, arrayLength, fileName);
    pid_t pid;
    for (int i = 0; i < numForks -1; i++) {
        pid = fork();

        // decide if continue as child or parent process
        if (pid == 0) {
            // beginn child execution
            return get(i, memory);
        } else if(pid > 0) {
            // beginn parent execution
            // shared_mem_pointer[i] = result.first;
        } else {
            printf("Error creating the Process. The resulting PID is %d.\n",pid);
        }
    }
    const char *ret = get(numForks - 1, memory);
    removeMemory(memory);
    return ret;
}