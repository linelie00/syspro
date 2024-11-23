#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node **top, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        perror("malloc");
        exit(1);
    }
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

int pop(struct node **top) {
    if (*top == NULL) {
        fprintf(stderr, "The stack is empty.\n");
        exit(1);
    }
    struct node *temp = *top;
    int data = temp->data;
    *top = temp->next;
    free(temp);
    return data;
}

void printStack(struct node *top) {
    struct node *current = top;
    printf("Stack contents: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct node *top = NULL;
    int data;

    printf("Enter numbers (input a non-natural number to print the stack contents): \n");
    while (scanf("%d", &data) == 1) {
        push(&top, data);
    }

    printStack(top);

    while (top != NULL) {
        printf("Popped: %d\n", pop(&top));
    }

    return 0;
}

