#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 5

int main() {
    int buffer[BUFFER_SIZE];
    int in = 0, out = 0;
    int count = 0;

    int pipe_producer_consumer[2];
    pipe(pipe_producer_consumer);

    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(-1);
    } else if (pid == 0) {  // Child process (consumer)
        close(pipe_producer_consumer[1]); // Close write end of the pipe

        while (1) {
            if (count > 0) {
                int item;
                read(pipe_producer_consumer[0], &item, sizeof(int));
                printf("Consumed: %d\n", item);
                out = (out + 1) % BUFFER_SIZE;
                count--;
            }
        }

        close(pipe_producer_consumer[0]); // Close read end of the pipe
    } else {  // Parent process (producer)
        close(pipe_producer_consumer[0]); // Close read end of the pipe

        while (1) {
            if (count < BUFFER_SIZE) {
                int item = rand() % 100; // Generate a random item
                buffer[in] = item;
                printf("Produced: %d\n", item);
                in = (in + 1) % BUFFER_SIZE;
                count++;
                write(pipe_producer_consumer[1], &item, sizeof(int));
                usleep(1000000); // Sleep for 1 second
            }
        }

        close(pipe_producer_consumer[1]); // Close write end of the pipe
    }

    return 0;
}

