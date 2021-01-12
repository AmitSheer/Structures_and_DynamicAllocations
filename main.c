#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM_LETTERS ((int)26)
typedef enum {FALSE=0, TRUE=1} boolean;
typedef struct node {
    char letter;
    int is_root;
    int word_end;
    unsigned int dist_from_stem;
    struct node *children[NUM_LETTERS];
} node;

node * init(){
    struct node *n = (node *) malloc(sizeof(struct node));
    if(!n) return NULL;
    n->dist_from_stem=0;
    n->letter = 0;
    n->word_end=0;
    n->is_root=0;
    for (int i = 0; i < NUM_LETTERS; ++i) {
        n->children[i] = NULL;
    }
    return n;
}

void print_lexicographic(node *head, char *s){
    if(head == NULL) return;
    *(s+head -> dist_from_stem-1) = head -> letter;
    if(head->word_end){
        *(head -> dist_from_stem+s) = '\0';
        printf("%s %d\n", s, head->word_end);
    }
    for(int i = 0; i<NUM_LETTERS;i++){
        print_lexicographic(head->children[i], s);
    }
}

void print_reverse_lexicographic(node *head, char *s){
    if(head == NULL) return;
    *(s+head -> dist_from_stem-1) = head -> letter;
    if(head->word_end){
        *(head -> dist_from_stem+s) = '\0';
        printf("%s %d\n", s, head->word_end);
    }
    for(int i = NUM_LETTERS-1; i>=0;i--){
        if(head->children[i]!=NULL) {
            print_reverse_lexicographic(head->children[i], s);
        }
    }
}

void freeAll(node *head){
    for (int i = 0; i < NUM_LETTERS; ++i) {
        if (head->children[i]!=NULL){
            freeAll(head->children[i]);
        }
    }
    free(head);
}
int read(node* head){
    head -> is_root = 1;
    struct node *ptr = head;
    int letter;
    int counter = 0;
    int longest_word = 0;
    do{
        letter = fgetc(stdin);
        if(letter != ' ' && letter != '\n' && letter != '\t' && letter != EOF) {
            if(isalpha(letter)){
                counter+=1;
                if (ptr->children[letter - 97] == NULL) {
                    ptr->children[letter - 97] = init();
                    if(!ptr->children[letter - 97]){
                        return 0;
                    }
                    ptr->children[letter - 97]->dist_from_stem = ptr -> dist_from_stem+1;
                    ptr->children[letter - 97]->letter = (char)letter;
                }
                ptr = ptr->children[letter - 97];
            }
        }else{
            if(!(ptr -> is_root)){
                ptr -> word_end += 1;
            }
            if(counter>longest_word){
                longest_word = counter;
                counter = 0;
            }
            ptr = head;
        }
    }while (letter!=EOF);
    return longest_word;
}
int main(int argc, char *argv[]) {
    node* head = init();
    if(!head) exit(0);
    int longest_word = read(head);
    if(!longest_word){
        freeAll(head);
    }
    char *s = (char *) malloc((longest_word + 1) * sizeof(char));
    if(!s){
        freeAll(head);
        exit(0);
    }
    if(argc==1){
        for(int i = 0; i<NUM_LETTERS;i++){
            if(head->children[i] != NULL) {
                print_lexicographic(head->children[i], s);
            }
        }
    }else if(*argv[1]=='r'){
        for(int i = NUM_LETTERS-1; i>=0;i--){
            if(head->children[i] != NULL) {
                print_reverse_lexicographic(head->children[i], s);
            }
        }
    }
    free(s);
    freeAll(head);
}
