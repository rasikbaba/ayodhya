Server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main() {
    int shm_id;
    key_t key = 5678;
    char *shm_ptr;

    if ((shm_id = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if ((shm_ptr = shmat(shm_id, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    char message[] = "Hello from the server!";
    strncpy(shm_ptr, message, SHM_SIZE);
    printf("Message written to shared memory: %s\n", message);

    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        exit(1);
    }

    return 0;
}

Client 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

#define SHM_SIZE 1024

int main() {
    int shm_id;
    key_t key = 5678;
    char *shm_ptr;

    if ((shm_id = shmget(key, SHM_SIZE, 0666)) < 0) {
        if (errno == ENOENT) {
            printf("Shared memory segment does not exist.\n");
        } else {
            perror("shmget");
            exit(1);
        }
    }

    if ((shm_ptr = shmat(shm_id, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    printf("Message read from shared memory: %s\n", shm_ptr);

    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        exit(1);
    }

    return 0;
}
