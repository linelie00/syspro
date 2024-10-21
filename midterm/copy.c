#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	int i,fd1,fd2,n,ch;
	char buf[BUFSIZ];
	FILE *s = NULL, *d = NULL;
	if(argc != 4) {
		fprintf(stderr,"How to use: %s file1 file2\n",argv[0]);
		exit(1);
	}
	if((fd1 = open(argv[2], O_RDONLY)) == -1) {
		perror(argv[2]);
		exit(2);
	}
	if((fd2 = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
		perror(argv[3]);
		exit(3);
	}
	if(strcmp(argv[1],"0") == 0) {
		printf("0\n");
	}
	else if(strcmp(argv[1],"1") == 0) {
		printf("1\n");
	}
	else if(strcmp(argv[1],"2") == 0) {
		printf("2\n");
		
	}

	while ((n = read(fd1, buf, BUFSIZ)) > 0) {
		write(fd2, buf, n);
	}
	exit(0);
}
