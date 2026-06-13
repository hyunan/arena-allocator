#include <stdio.h>

#include "arena.h"


typedef struct Node {
    int data;
    struct Node *next;
} Node;


int main(void) {
    printf("Simple linked list program to demo arena usage.\n");

    Arena arena;
    arena_init(&arena, sizeof(Node) * 20);

    Node *head = arena_alloc(&arena, sizeof(Node));
    head->data = 0;
    head->next = NULL;
    Node *temp = head;

    for (int i = 1; i <= 10; i++) {
        Node *node = arena_alloc(&arena, sizeof(Node));
        node->data = i;
        node->next = NULL;
        temp->next = node;
        temp = temp->next;
    }

    // Loop through and print the linked list
    for (Node *p = head; p != NULL; p = p->next)
        printf("Node %d\n", p->data);

    // Reset the arena to rewrite
    printf("Before reset:\n\tArena used: %.2f%%\n\n", (float) arena_used(&arena) / arena.capacity * 100);
    arena_reset(&arena);
    printf("After reset:\n\tArena used: %.2f%%\n\n", (float) arena_used(&arena) / arena.capacity * 100);

    printf("Resetting and overwritting.\n");
    head = arena_alloc(&arena, sizeof(Node));
    head->data = 10;
    head->next = NULL;
    temp = head;

    for (int i = 9; i >= 0; i--) {
        Node *node = arena_alloc(&arena, sizeof(Node));
        node->data = i;
        node->next = NULL;
        temp->next = node;
        temp = temp->next;
        // Print arena stats
        printf("Arena usage:\nUsed: %zu, Remaining: %zu\n", arena_used(&arena), arena_remaining(&arena));
    }
    
    arena_free(&arena);
    return 0;
}
