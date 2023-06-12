#include <unistd.h>
#include <wait.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int create_fileDescriptor(char *filename);
void *shared_mmap_fd(int len, int fileDescriptor);
void *shared_mmap(int len);
bool close_mmap(int fd, char *filename);
bool write_string_si(char *shared_mem, int shared_len, int startIndex, char *str);
bool write_string(char *shared_mem, int shared_len, char *str);
bool addAllSoft(char *shared_mem, int shared_len, int segLength, int startIndex, char *list[]);
char *get(char *shared_mem, int index, int segLength);
