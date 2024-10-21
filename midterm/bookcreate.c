#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define START_ID 1

struct book {
	int id;
	char bookname[24];
	char author[24];
	int year;
	int numofborrow;
	int borrow;
};

int main(int argc, char *argv[]){
	int fd;
	struct book record;
	if (argc < 2) {
		fprintf(stderr, "How to use %s file\n", argv[0]);
		exit(1);
	}
	if ((fd = open(argv[1], O_WRONLY|O_CREAT|O_EXCL, 0640)) == -1) {
		perror(argv[1]);
		exit(2);
	}
	while (scanf("%d %s %s %d %d %d", &record.id, record.bookname, record.author, &record.year, &record.numofborrow, &record.borrow) == 6) {
		lseek(fd, (record.id - START_ID) * sizeof(record), SEEK_SET);
		write(fd, (char *) &record, sizeof(record));
	}
	close(fd);
	exit(0);
}
