#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256

int main(){
        int tuberia[2];
        int pid;
        char mensaje[MAX];

        if (pipe(tuberia) == -1){
                perror("pipe");
                exit(-1);
        }
        if((pid = fork()) == -1){
                perror("fork");
                exit(-1);
        }
        else if(pid == 0){
                while(read(tuberia[0],mensaje,MAX) > 0 && strcmp(mensaje,"FIN") != 0){
                        printf("PROCESO RECEPTOR. MENSAJE: %s\n", mensaje);
                        close(tuberia[0]);
                        close(tuberia[1]);
                        exit(0);
                }
        }
        else{
                while(printf("PROCESO EMISOR. MENSAJE:") != 0 && gets(mensaje) != NULL && write(tuberia[1], mensaje,strlen(mensaje) + 1) > 0 && strc>
                        close(tuberia[0]);
                        close(tuberia[1]);
                        exit(0);
                }
	}
}               
