#include "mmap_c.h"

int create_fileDescriptor(char *filename) {
    return shm_open(filename, O_CREAT | O_RDWR, 0666);
}

void *shared_mmap_fd(int len, int fileDescriptor) {
    // cout << "Started to generate shared memory with mmap." << endl;
    ftruncate(fileDescriptor, len);

    // char buf[4096] = {NULL};
    // write(fileDescriptor, buf, len);
    void *shared_mem = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fileDescriptor, 0 /* offset */);
    if (shared_mem == MAP_FAILED) {
        printf("Created shared memory with mmap in c. /n");
        perror("Generating mmap failed");
        printf("This might be due to a wrong filename given to the fileDescriptor. Usually the respective file get's created in the /dev/shm directory and no further path needs to be specified. \n");
        return NULL;
    }
    return shared_mem;
}

void *shared_mmap(int len) {
    return shared_mmap_fd(len, -1);
}

bool close_mmap(int fd, char *filename) {
    close(fd);
    shm_unlink(filename);
    return true;
}

bool write_string_si(char *shared_mem, int shared_len, int startIndex, char *str) {    
    // cout << "Start writing to shared memory at position " << startIndex << endl;
    if(shared_len < startIndex + strln(str)) {
        return false;
    }
    int i = 0;
    for (; i < strln(str); i++) {
        shared_mem[i + startIndex] = str[i];
    }

    if (startIndex + strln(str) < shared_len) {
        for (i += startIndex; i < shared_len; i++) {
            shared_mem[i] = NULL;
        }
    }
        
    // cout << "Stop writing to shared memory at position " << i << endl;
    return true;
}

bool write_string(char *shared_mem, int shared_len, char *str) {
    return write_string_si(shared_mem, shared_len, 0, str);
}

bool addAllSoft(char *shared_mem, int shared_len, int seg_len, int startIndex, char *list[]) {
    int listSize = sizeof(list) / sizeof(list[0]);
    for (int i = 0; i < listSize; i++)
    {
        write_string_si(shared_mem, (i + 1) * seg_len, i * seg_len, list[i]);
    }
    
}
char *get(char *shared_mem, int index, int seg_len) {
    int shared_len = strlen(shared_mem);
    if(shared_len < (index + 1) * seg_len) {
        return NULL;
    }
    char *retString;
    strncpy(retString, shared_mem + (index * seg_len), seg_len);
    return retString;
}
