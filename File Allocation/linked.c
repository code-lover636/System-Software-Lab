#include <stdio.h>
#include <stdlib.h>

struct File{
    int val;
    struct File* next;
};

struct File *head = NULL;
struct File *tail = NULL;

void insert(int val){
    struct File *n = malloc(sizeof(struct File));
    n->val = val;
    n->next = NULL;
    if (!head){
        head = n;
    } else {
        tail->next = n;
    }
    tail = n;
}

void print_list(){
    for (struct File *current = head;current;current = current->next){
        printf("%d ",current->val);
    }
    printf("\n");
}

int main(){
    int command;
    while (1){
        printf("1.Allocate block\n");
        printf("2.Show allocated blocks\n");
        printf("3.Exit\n");
        scanf("%d",&command);
        if (command==1){
            int next;
            printf("Enter next block to be allocated: ");
            scanf("%d",&next);
            insert(next);
        } else if (command==2){
            print_list();
        } else if (command==3){
            return 0;
        } else {
            printf("Enter valid input: ");
        }
    }
}
