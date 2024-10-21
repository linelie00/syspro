#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void Enlarge(char* strSrc, char* strDest, long size);
void Ensmall(char* srtSrc, char* strDest, long size);

int main(int argc, char *argv[])
{
	/*
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
	} */
	FILE* fp = fopen(argv[2],"rt");
	long size;
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char* strSrc = malloc(sizeof(char) * size);
	char* strDest = malloc(sizeof(char) * size);

	fread(strSrc, sizeof(char), size, fp);
	fclose(fp);

	if(strcmp(argv[1],"0") == 0) {
		printf("0\n");
	}
	else if(strcmp(argv[1],"1") == 0) {
		Ensmall(strSrc, strDest, size);
	}
	else if(strcmp(argv[1],"2") == 0) {
		Enlarge(strSrc, strDest, size);
		
	}
	/*while ((n = read(fd1, buf, BUFSIZ)) > 0) {
		write(fd2, buf, n);
	}*/
	fp = fopen(argv[3],"wt");
	fwrite(strDest, sizeof(char), size, fp);
	fclose(fp);
	free(strSrc);
	free(strDest);
	exit(0);
}

void Enlarge(char* strSrc, char* strDest, long size)
{
	for (long i = 0; i < size; i++)
	{
		if (strSrc[i] >= 'a' && strSrc[i] <= 'z'){
			strDest[i] = strSrc[i] - 32;
		}
		else{
			strDest[i] = strSrc[i];
		}
	}
}

void Ensmall(char* strSrc, char* strDest, long size)
{
	for (long i = 0; i < size; i++)
	{
		if (strSrc[i] >= 'A' && strSrc[i] <= 'Z'){
			strDest[i] = strSrc[i] + 32;
		}
		else{
			strDest[i] = strSrc[i];
		}
	}
}
