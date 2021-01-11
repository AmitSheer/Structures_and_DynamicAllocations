#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM_LETTERS ((int)26)
typedef enum {FALSE=0, TRUE=1} boolean;
typedef struct node {
    char letter;
    int isRoot;
    int wordEnd;
    long unsigned int count;

    struct node* children[NUM_LETTERS];
} node;

//check if letter in the right place
int main() {
    struct node *head = (struct node*)malloc(sizeof(node));
    head -> isRoot = 1;
    struct node *ptr = head;
    int letter = fgetc(stdin);
    while (letter!=EOF){
        if(letter != ' ' && letter != '\n' && letter != '\t') {
            if(isalpha(letter)){
                if (ptr->children[letter - 97] == NULL) {
                    ptr->children[letter - 97] = (struct node *) malloc(sizeof(node));
                    ptr = ptr->children[letter - 97];
                    ptr -> letter = (char)letter;
                    ptr -> count += 1;
                }else{
                    ptr = ptr->children[letter - 97];
                    ptr -> count += 1;
                }
            }
        }else{
            if(!(ptr -> isRoot)){
                ptr -> wordEnd = 1;
            }
            ptr = head;
        }
        letter = fgetc(stdin);
    }
}
