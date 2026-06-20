#include <iostream>

#include "arena.h"

struct Node {
    int data;
    Node* next;
};

int main() {
    std::cout << "Simple linked list program to demo arena usage.\n";

    Arena arena(sizeof(Node) * 20);

    Node* head = static_cast<Node*>(arena.alloc(sizeof(Node)));
    head->data = 0;
    head->next = nullptr;

    Node* temp = head;

    for (int i = 1; i <= 10; ++i) {
        Node* node = static_cast<Node*>(arena.alloc(sizeof(Node)));

        node->data = i;
        node->next = nullptr;

        temp->next = node;
        temp = node;
    }

    std::cout << "\nForward traversal:\n";

    for (Node* p = head; p != nullptr; p = p->next) {
        std::cout << "Node " << p->data << '\n';
    }

    std::cout << "\nBefore reset:\n";
    std::cout << "Used: " << arena.used() << '\n';
    std::cout << "Remaining: " << arena.remaining() << '\n';

    arena.reset();

    std::cout << "\nAfter reset:\n";
    std::cout << "Used: " << arena.used() << '\n';
    std::cout << "Remaining: " << arena.remaining() << '\n';

    std::cout << "\nReusing arena:\n";

    head = static_cast<Node*>(arena.alloc(sizeof(Node)));
    head->data = 10;
    head->next = nullptr;

    temp = head;

    for (int i = 9; i >= 0; --i) {
        Node* node = static_cast<Node*>(arena.alloc(sizeof(Node)));

        node->data = i;
        node->next = nullptr;

        temp->next = node;
        temp = node;

        std::cout
            << "Used: " << arena.used()
            << " Remaining: " << arena.remaining()
            << '\n';
    }

    std::cout << "\nFinal traversal:\n";

    for (Node* p = head; p != nullptr; p = p->next) {
        std::cout << "Node " << p->data << '\n';
    }

    return 0;
}