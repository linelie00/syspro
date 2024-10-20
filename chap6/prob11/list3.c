#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>

char type(mode_t mode);
char *perm(mode_t mode);
void printStat(char* path, char* file, struct stat* st, int show_long, int show_hidden, int show_size);

int main(int argc, char **argv)
{
    DIR *dp = NULL;
    char *dir = NULL;
    struct stat st;
    struct dirent *d = NULL;
    char path[BUFSIZ+1];
    int show_hidden = 0, show_long = 0, show_size = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            show_hidden |= (strchr(argv[i], 'a') != NULL);
            show_long |= (strchr(argv[i], 'l') != NULL);
            show_size |= (strchr(argv[i], 's') != NULL);
        } else {
            dir = argv[i];
        }
    }

    if (!dir) dir = ".";

    dp = opendir(dir);
    if (!dp) {
        perror(dir);
        return 1;
    }

    while ((d = readdir(dp)) != NULL) {
        if (!show_hidden && d->d_name[0] == '.')
            continue;

        snprintf(path, sizeof(path), "%s/%s", dir, d->d_name);

        if (lstat(path, &st) == -1) {
            perror(path);
            continue;
        }
        
        printStat(path, d->d_name, &st, show_long, show_hidden, show_size);
    }

    closedir(dp);
    return 0;
}

void printStat(char *path, char *file, struct stat *st, int show_long, int show_hidden, int show_size) 
{
    if (show_size) {
        printf("%5ld ", (long)st->st_blocks);
    }
    if (show_long) {
        printf("%c%s ", type(st->st_mode), perm(st->st_mode));
        printf("%3ld ", (long)st->st_nlink);
        printf("%s %s ", getpwuid(st->st_uid)->pw_name, getgrgid(st->st_gid)->gr_name);
        printf("%9ld ", (long)st->st_size);
        printf("%.12s ", ctime(&st->st_mtime) + 4);
    }
    printf("%s\n", file);
}

char type(mode_t mode) 
{
    switch (mode & S_IFMT) {
        case S_IFREG: return '-';
        case S_IFDIR: return 'd';
        case S_IFCHR: return 'c';
        case S_IFBLK: return 'b';
        case S_IFLNK: return 'l';
        case S_IFIFO: return 'p';
        case S_IFSOCK: return 's';
        default: return '?';
    }
}

char* perm(mode_t mode) 
{
    static char perms[10];
    memset(perms, '-', sizeof(perms) - 1);
    perms[9] = '\0';

    for (int i = 0; i < 3; i++) {
        if (mode & (S_IRUSR >> (i*3))) perms[i*3] = 'r';
        if (mode & (S_IWUSR >> (i*3))) perms[i*3 + 1] = 'w';
        if (mode & (S_IXUSR >> (i*3))) perms[i*3 + 2] = 'x';
    }

    return perms;
}

