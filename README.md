# Inter-Process Communication in C

## Description
This project contains a series of C programs that demonstrate various methods of inter-process communication (IPC) in Unix-like operating systems. These programs illustrate the use of pipes and named pipes (FIFOs) to facilitate communication between processes. Each file showcases different aspects of IPC, providing a comprehensive overview of how to implement these mechanisms in C.

### Key Features
- **Anonymous Pipes**: Examples of using pipes for communication between a parent and child process.
- **Named Pipes (FIFOs)**: Demonstrations of using named pipes to communicate between unrelated processes.
- **Process Synchronization**: Basic examples of synchronizing processes using IPC mechanisms.

### Files
1. **A1P7.c**
    - Demonstrates the use of anonymous pipes for communication between a parent process and a child process.
    - **Key Code Snippet**:
        ```c
        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>

        #define MAX 256

        int main() {
            int tuberia[2];
            int pid;
            char mensaje[MAX];

            if (pipe(tuberia) == -1) {
                perror("pipe");
                exit(-1);
            }
            if ((pid = fork()) == -1) {
                perror("fork");
                exit(-1);
            } else if (pid == 0) {
                while (read(tuberia[0], mensaje, MAX) > 0 && strcmp(mensaje, "FIN") != 0) {
                    printf("PROCESO RECEPTOR. MENSAJE: %s\n", mensaje);
                }
                close(tuberia[0]);
                close(tuberia[1]);
                exit(0);
            } else {
                while (printf("PROCESO EMISOR. MENSAJE:") != 0 && gets(mensaje) != NULL && write(tuberia[1], mensaje, strlen(mensaje) + 1) > 0 && strcmp(mensaje, "FIN") != 0);
                close(tuberia[0]);
                close(tuberia[1]);
                exit(0);
            }
        }
        ```
        This code creates a pipe and uses it to send messages from the parent process to the child process.

2. **A2P7.c**
    - Illustrates the use of two pipes for bidirectional communication between a parent process and a child process.
    - **Key Code Snippet**:
        ```c
        #include <sys/types.h>
        #include <fcntl.h>
        #include <unistd.h>
        #include <stdio.h>
        #include <string.h>
        #include <stdlib.h>
        #include <wait.h>

        #define SIZE 512

        int main(int argc, char **argv) {
            pid_t pid;
            int a[2], b[2], readbytes;
            char buffer[SIZE];

            pipe(a);
            pipe(b);

            if ((pid = fork()) == 0) {
                close(a[1]);
                close(b[0]);
                while ((readbytes = read(a[0], buffer, SIZE)) > 0)
                    write(1, buffer, readbytes);
                close(a[0]);
                strcpy(buffer, "Soy tu hijo hablandote por la otra tuberia\n");
                write(b[1], buffer, strlen(buffer));
                close(b[1]);
            } else {
                close(a[0]);
                close(b[1]);
                strcpy(buffer, "Soy tu padre hablandote por una tuberia\n");
                write(a[1], buffer, strlen(buffer));
                close(a[1]);
                while ((readbytes = read(b[0], buffer, SIZE)) > 0)
                    write(1, buffer, readbytes);
                close(b[0]);
            }
            waitpid(pid, NULL, 0);
            exit(0);
        }
        ```
        This code sets up two pipes for bidirectional communication between the parent and child processes.

3. **A3P7.c**
    - Demonstrates the use of a named pipe (FIFO) to send a message from one process to another.
    - **Key Code Snippet**:
        ```c
        #include <sys/stat.h>
        #include <unistd.h>
        #include <fcntl.h>
        #include <stdio.h>

        int main(void) {
            int fd;
            char buf[] = "Hola, pase por la tuberia";
            mkfifo("fifo2", 0666);
            fd = open("fifo2", O_WRONLY);
            write(fd, buf, sizeof(buf));
            close(fd);
            return 0;
        }
        ```
        This code creates a named pipe and writes a message to it.

4. **receptor.c**
    - Demonstrates reading a message from a named pipe (FIFO).
    - **Key Code Snippet**:
        ```c
        #include <sys/stat.h>
        #include <unistd.h>
        #include <fcntl.h>
        #include <stdio.h>

        int main(void) {
            int fd, n;
            char buf[1024];

            fd = open("fifo2", O_RDONLY);
            n = read(fd, buf, sizeof(buf));
            printf("Numero de bytes rx: %d\n", n);
            printf("RX Mensaje: %s\n", buf);
            close(fd);
            return 0;
        }
        ```
        This code opens a named pipe and reads a message from it.

## How to Use
1. **Compilation**: Each C file can be compiled using a C compiler such as `gcc`.
    ```bash
    gcc A1P7.c -o A1P7
    gcc A2P7.c -o A2P7
    gcc A3P7.c -o A3P7
    gcc receptor.c -o receptor
    ```

2. **Execution**:
    - Run the anonymous pipe example:
      ```bash
      ./A1P7
      ```
    - Run the bidirectional pipe example:
      ```bash
      ./A2P7
      ```
    - Run the named pipe examples:
      - First, run the receptor in one terminal:
        ```bash
        ./receptor
        ```
      - Then, run the sender in another terminal:
        ```bash
        ./A3P7
        ```

