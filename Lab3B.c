#include <stdio.h>
#include <stdlib.h>

// Node structure for doubly linked list
struct Node {
    int value;
    struct Node* prev;
    struct Node* next;
};

// Function to search for a given element in the linked list
int search(struct Node* head, int element) {
    struct Node* current = head;
    int position = 1;
    
    while (current != NULL) {
        if (current->value == element) {
            return position;
        }
        current = current->next;
        position++;
    }
    
    return -1; // Element not found
}

// Function to insert an element at a specific position in the linked list
void insert(struct Node** head, int element, int position) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = element;
    newNode->prev = NULL;
    newNode->next = NULL;
    
    if (*head == NULL) {
        // Empty list, make the new node as the head
        *head = newNode;
        return;
    }
    
    struct Node* current = *head;
    
    if (position == 1) {
        // Insert at the head
        newNode->next = current;
        current->prev = newNode;
        *head = newNode;
        return;
    }
    
    int count = 1;
    while (count < position - 1 && current->next != NULL) {
        current = current->next;
        count++;
    }
    
    // Insert at the middle or end
    newNode->next = current->next;
    if (current->next != NULL) {
        current->next->prev = newNode;
    }
    newNode->prev = current;
    current->next = newNode;
}

// Function to delete an element from the linked list
void delete(struct Node** head, int element) {
    if (*head == NULL) {
        return;
    }
    
    struct Node* current = *head;
    
    // Check if the element is at the head
    if (current->value == element) {
        *head = current->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
        free(current);
        return;
    }
    
    while (current != NULL && current->value != element) {
        current = current->next;
    }
    
    if (current == NULL) {
        return; // Element not found
    }
    
    // Element found, adjust the pointers
    if (current->prev != NULL) {
        current->prev->next = current->next;
    }
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }
    
    free(current);
}
void printReverse(struct Node* head) {
    if (head == NULL) {
        return;
    }
    
    struct Node* current = head;
    
    // Traverse to the end of the list
    while (current->next != NULL) {
        current = current->next;
    }
    
    // Print elements in reverse order
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->prev;
    }
    
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    int choice;
    
    // Initialize the linked list with user-input values
    int value;
    printf("Enter the initial values for the linked list (enter -1 to stop):\n");
    while (1) {
        scanf("%d", &value);
        if (value == -1) {
            break;
        }
        insert(&head, value, 0);
    }
    
    do {
        printf("\nDoubly Linked List Operations:\n");
        printf("1. Search for an element\n");
        printf("2. Insert an element\n");
        printf("3. Delete an element\n");
        printf("4. Print the elements in reverse order\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter the element to search: ");
                scanf("%d", &value);
                int position = search(head, value);
                if (position != -1) {
                    printf("Element found at position %d\n", position);
                } else {
                    printf("Element not found\n");
                }
                break;
                
            case 2:
                printf("Enter the element to insert: ");
                scanf("%d", &value);
                int insertPosition;
                printf("Enter the position to insert: ");
                scanf("%d", &insertPosition);
                insert(&head, value, insertPosition);
                printf("Element inserted successfully\n");
                break;
                
            case 3:
                printf("Enter the element to delete: ");
                scanf("%d", &value);
                delete(&head, value);
                printf("Element deleted successfully\n");
                break;
                
            case 4:
                printf("Elements in reverse order: ");
                printReverse(head);
                break;
                
            case 5:
                printf("Exiting...\n");
                break;
                
            default:
                printf("Invalid choice\n");
                break;
        }
    } while (choice != 5);
    
    // Clean up memory
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
    
    return 0;
}
