#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void) {
	int fd,n;
	char buf[1024];

	fd = open("fifo2",0_RDONLY);
	n = read(fd, buf,sizeof(buf));
	printf("Numero de bytes rx: %d \n",n);
	printf("RX Mensaje: %s\n", buf);
	close(fd);
	return 0;
}
