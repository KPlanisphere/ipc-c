#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void) {
	int fd;
	char buf[] = "Hola, pase por la tuberia";
	mkfifo("fifo2",0666);
	FD = open("fifo2",0_WRONLY);
	write(fd,buf,sizeof(buf));
	// printf("Numero de bytes rx: %d \n",n);
	// printf("RX Mensaje: %s\n", buf); 
	close(fd);
	return 0;
}
