#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node* next;
};

typedef struct Node Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

int search(Node* head, int value) {
    if (head == NULL) {
        return -1;
    }

    Node* current = head;
    int position = 1;

    while (current != NULL) {
        if (current->value == value) {
            return position;
        }
        current = current->next;
        position++;
    }

    return -1;
}

void insertAtMiddle(Node** head, int value, int position) {
    if (position <= 0) {
        printf("Invalid position.\n");
        return;
    }

    Node* newNode = createNode(value);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    if (position == 1) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node* current = *head;
    int count = 1;

    while (current->next != NULL && count < position - 1) {
        current = current->next;
        count++;
    }

    if (count == position - 1) {
        newNode->next = current->next;
        current->next = newNode;
    } else {
        printf("Invalid position.\n");
    }
}

void insertAtHead(Node** head, int value) {
    Node* newNode = createNode(value);
    newNode->next = *head;
    *head = newNode;
}

void insertAtEnd(Node** head, int value) {
    Node* newNode = createNode(value);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
}

void deleteFromMiddle(Node** head, int value) {
    if (*head == NULL) {
        printf("Linked list is empty.\n");
        return;
    }

    Node* current = *head;
    Node* prev = NULL;

    while (current != NULL) {
        if (current->value == value) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Element not found in the linked list.\n");
}

void deleteFromHead(Node** head) {
    if (*head == NULL) {
        printf("Linked list is empty.\n");
        return;
    }

    Node* temp = *head;
    *head = (*head)->next;
    free(temp);
}

void deleteFromEnd(Node** head) {
    if (*head == NULL) {
        printf("Linked list is empty.\n");
        return;
    }

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    Node* current = *head;
    Node* prev = NULL;

    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    prev->next = NULL;
    free(current);
}

void printLinkedList(Node* head) {
    if (head == NULL) {
        printf("Linked list is empty.\n");
        return;
    }

    Node* current = head;

    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }

    printf("\n");
}

int main() {
    Node* head = NULL;

    int choice;
    int value, position;
    int val;
    int numNodes;

    printf("Enter the number of nodes to initialize the linked list: ");
    scanf("%d", &numNodes);

    for (int i = 0; i < numNodes; i++) {
        printf("Enter the value for node %d: ", i + 1);
        scanf("%d", &val);
        insertAtEnd(&head, val);
    }

    printf("Linked list initialized with %d nodes.\n", numNodes);
    printLinkedList(head);

    while (1) {
        printf("\nLinked List Operations:\n");
        printf("1. Search for an element\n");
        printf("2. Insert an element at the middle\n");
        printf("3. Insert an element at the head\n");
        printf("4. Insert an element at the end\n");
        printf("5. Delete an element from the middle\n");
        printf("6. Delete an element from the head\n");
        printf("7. Delete an element from the end\n");
        printf("8. Print the linked list\n");
        printf("9. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to search: ");
                scanf("%d", &value);
                position = search(head, value);
                if (position != -1) {
                    printf("Element %d found at position %d in the linked list.\n", value, position);
                } else {
                    printf("Element %d not found in the linked list.\n", value);
                }
                break;
            case 2:
                printf("Enter the element to insert: ");
                scanf("%d", &value);
                printf("Enter the position to insert at: ");
                scanf("%d", &position);
                insertAtMiddle(&head, value, position);
                printf("Element %d inserted at position %d in the linked list.\n", value, position);
                break;
            case 3:
                printf("Enter the element to insert at the head: ");
                scanf("%d", &value);
                insertAtHead(&head, value);
                printf("Element %d inserted at the head of the linked list.\n", value);
                break;
            case 4:
                printf("Enter the element to insert at the end: ");
                scanf("%d", &value);
                insertAtEnd(&head, value);
                printf("Element %d inserted at the end of the linked list.\n", value);
                break;
            case 5:
                printf("Enter the element to delete from the middle: ");
                scanf("%d", &value);
                deleteFromMiddle(&head, value);
                printf("Element %d deleted from the middle of the linked list.\n", value);
                break;
            case 6:
                deleteFromHead(&head);
                printf("Element deleted from the head of the linked list.\n");
                break;
            case 7:
                deleteFromEnd(&head);
                printf("Element deleted from the end of the linked list.\n");
                break;
            case 8:
                printLinkedList(head);
                break;
            case 9:
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}