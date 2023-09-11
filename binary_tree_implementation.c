#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insertNode(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    } else {
        if (data <= root->data) {
            root->left = insertNode(root->left, data);
        } else {
            root->right = insertNode(root->right, data);
        }
        return root;
    }
}

struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) {
        return root;
    }
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}
void preorderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        inorderTraversal(root->left);
        inorderTraversal(root->right);
    }
}
void postorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        inorderTraversal(root->right);
        printf("%d ", root->data);

    }
}


void push(struct Node** stack, int* top, struct Node* node) {
    (*top)++;
    stack[*top] = node;
}

struct Node* pop(struct Node** stack, int* top) {
    if (*top == -1) return NULL;
    struct Node* node = stack[*top];
    (*top)--;
    return node;
}

void inorderTraversalwr(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack[100];
    int top = -1;
    struct Node* current = root;

    while (current != NULL || top != -1) {
        while (current != NULL) {
            push(stack, &top, current);
            current = current->left;
        }

        current = pop(stack, &top);
        printf("%d ", current->data);
        current = current->right;
    }
}

void preorderTraversalwr(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack[100]; 
    int top = -1;
    push(stack, &top, root);

    while (top != -1) {
        struct Node* current = pop(stack, &top);
        printf("%d ", current->data);

        if (current->right != NULL) {
            push(stack, &top, current->right);
        }
        if (current->left != NULL) {
            push(stack, &top, current->left);
        }
    }
}

void postorderTraversalwr(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack1[100];
    struct Node* stack2[100];
    int top1 = -1;
    int top2 = -1;

    push(stack1, &top1, root);

    while (top1 != -1) {
        struct Node* current = pop(stack1, &top1);
        push(stack2, &top2, current);

        if (current->left != NULL) {
            push(stack1, &top1, current->left);
        }
        if (current->right != NULL) {
            push(stack1, &top1, current->right);
        }
    }

    while (top2 != -1) {
        struct Node* current = pop(stack2, &top2);
        printf("%d ", current->data);
    }
}


void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void displayMenu() {
    printf("\nBinary Tree Menu\n");
    printf("1. Insert a node\n");
    printf("2. Inorder Traversal\n");
    printf("3. Preorder Traversal\n");
    printf("4. Postorder Traversal\n");
    printf("5. Inorder Traversal without recursion\n");
    printf("6. Preorder Traversal without recursion \n");
    printf("7. Postorder Traversal without recursion\n");
    printf("8. Delete a node \n");
    printf("9. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct Node* root = NULL;
    int choice, data;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the data to insert: ");
                scanf("%d", &data);
                root = insertNode(root, data);
                break;

            case 2:
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;

            case 3:
                printf("Preorder Traversal: ");
                preorderTraversal(root);
                printf("\n");
                break;

            case 4:
                printf("Postorder Traversal: ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 5:
                printf("Inorder Traversal without recursion: ");
                inorderTraversalwr(root);
                printf("\n");
                break;
            case 6:
                printf("Preorder Traversal without recursion: ");
                preorderTraversalwr(root);
                printf("\n");
                break;
            case 7:
                printf("Postorder Traversal without recursion: ");
                postorderTraversalwr(root);
                printf("\n");
                break;
            case 8:
                printf("Enter the data to delete: ");
                scanf("%d", &data);
                root = deleteNode(root, data);
                break;

            case 9:
                freeTree(root);
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 9);

    return 0;
}