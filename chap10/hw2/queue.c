#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node **head, struct node **tail, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        perror("malloc");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;

    if (*tail == NULL) {
        *head = *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

int delete(struct node **head, struct node **tail) {
    if (*head == NULL) {
        fprintf(stderr, "The queue is empty.\n");
        exit(1);
    }
    struct node *temp = *head;
    int data = temp->data;
    *head = temp->next;

    if (*head == NULL) {
        *tail = NULL;
    }
    free(temp);
    return data;
}

void printQueue(struct node *head) {
    struct node *current = head;
    printf("Queue contents: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct node *head = NULL, *tail = NULL;
    int data;

    printf("Enter numbers to add to the queue:\n");
    while (scanf("%d", &data) == 1) {
        addq(&head, &tail, data);
    }

    printQueue(head);

    while (head != NULL) {
        printf("Deleted: %d\n", delete(&head, &tail));
    }

    return 0;
}

