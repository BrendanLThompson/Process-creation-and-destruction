#include <stdio.h>
#include <stdlib.h>

int max_processes = 0;
struct node1 {
    int process;
    struct node1 *link;
};

typedef struct node1 linked_list_type;
struct node2 {
    int parent;
    linked_list_type *children;
}*pcb = NULL;

typedef struct node2 pcb_type;


void option1() {
    int i;
    printf("Enter Maximum Number of Processes\n");
    scanf("%d", &max_processes);
    printf("%d\n", max_processes);
    pcb = (pcb_type *) malloc(max_processes * sizeof(pcb_type) );
    pcb[0].parent = 0;
    pcb[0].children = NULL;
    for (i=1; i < max_processes; i++) {
        pcb[i].parent = -1;
    }
    return;
}

void option2() {
    int p;
    int q = 1;
    linked_list_type *new_child;
    linked_list_type *next_child;
    int num_children = 1;
    printf("Enter Parent Process Index:");
    scanf("%d", &p);
    printf("%d\n", p);
    while (pcb[q].parent != -1) {
        q++;
    }
    new_child = (linked_list_type*)malloc(sizeof(linked_list_type));
    new_child->process = q;
    new_child->link = NULL;
    pcb[q].parent = p;
    pcb[q].children = NULL;
    if (pcb[p].children == NULL){
        pcb[p].children = new_child;
        num_children = 0;
    }
    else{
        next_child = pcb[p].children;
        while (next_child->link != NULL) {
            next_child = next_child->link;
            num_children++;
        }
        next_child->link = new_child;
    }
   
    printf("cr[%d]  /*creates %dth child of PCB[%d] at PCB[%d]*/ \n\n", p,num_children + 1, p, q);
    return;
}

void option3recursive(linked_list_type *new_child) {
    int q;
    if (new_child==NULL) {
        return;
    }
    else {
        option3recursive(new_child->link);
        q = new_child->process;
        option3recursive(pcb[q].children);
        printf("PCB[%d] ", q);
        free(new_child);
        pcb[q].parent = -1;
        new_child = NULL;
    }
    return;
}
void option3() {
    int p;
    printf("Enter destroyer");
    scanf("%d", &p);
    printf("%d\n",p);
    printf("Going to destroy PCB[%d]\n", p);
    option3recursive(pcb[p].children);
    pcb[p].children = NULL;
    return;
}
void option4() {
    if (pcb != NULL) {
        if(pcb[0].children != NULL) {
            option3recursive(pcb[0].children);
        }
    }
    if (pcb[0].children != NULL) {
        option3recursive(pcb[0].children);
        free(pcb);
    }
    return;
}

int main() {
    int menuSelection = 0;
    while(menuSelection != 4) {
        printf("\nProcess creation and destruction\n"
               "--------------------------------\n"
               "1) Enter parameters\n"
               "2) Create a new child process\n"
               "3) Destroy all descendants of a process\n"
               "4) Quit program and free memory\n"
               "\n"
               "Enter selection: ");
        scanf("%d", &menuSelection);
        switch (menuSelection) {
            case 1:
                option1();
                break;
            case 2:
                option2();
                break;
            case 3:
                option3();
                break;
            case 4:
                option4();
                break;
            default:
                break;
        }
    }
    return 0;
}