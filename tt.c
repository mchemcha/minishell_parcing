#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char data[50];
    struct Node* next;
};

struct Node* createNode(char* data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->data, data);
    newNode->next = NULL;
    return newNode;
}

void append(struct Node** head_ref, char* new_data) {
    struct Node* new_node = createNode(new_data);
    struct Node* last = *head_ref;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL) {
        last = last->next;
    }

    last->next = new_node;
}
void display(struct Node* node) {
    while (node != NULL) {
        printf("%s\n", node->data);
        node = node->next;
    }
}

int main() {
    char *str = "\"maryem\"'chemchaq'";

    struct Node* head = NULL;

    char *start = str;
    char *end;
    while (*start != '\0') {
        if (*start == '"' || *start == '\'') {
            char quote = *start;
            start++;
            end = strchr(start, quote);
            if (end != NULL) {
                char word[50];
                int len = end - start + 2;
                strncpy(word, start - 1, len);
                word[len] = '\0';
                append(&head, word);
                start = end + 1;
            } else {
                break;
            }
        } else {
            start++;
        }
    }
    display(head);

    return 0;
}
