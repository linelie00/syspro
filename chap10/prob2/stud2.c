#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int id;
    char name[20];
    struct student *next;
};

int main() {
    int id;
    char name[20];
    struct student *p, *head = NULL;

    printf("학번과 이름을 입력하세요\n");

    while (scanf("%d %s", &id, name) == 2) {
        p = (struct student *)malloc(sizeof(struct student));
        if (p == NULL) {
            perror("malloc");
            exit(1);
        }
        p->id = id;
        strcpy(p->name, name);
        p->next = head;
        head = p;
    }

    for (p = head; p != NULL; p = p->next) {
        printf("%d %s\n", p->id, p->name);
    }

    while (head != NULL) {
        p = head;
        head = head->next;
        free(p);
    }

    return 0;
}

