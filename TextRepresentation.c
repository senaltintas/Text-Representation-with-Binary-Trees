
//the aim of this project: create a tree by using frequency and word at given text and compare them.We decide which one is the most efficient to access word in the text and total access time is less than the other.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node{
    int frequency;
    char word[20];
    int order;
    struct node* left;
    struct node* right;
};
struct node *RootNode =NULL;


struct node* create(int frequency,char word[20]){ //to create new node
    struct node* newNode =(struct node*)(malloc(sizeof(struct node)));
    newNode->frequency=frequency;
    strcpy(newNode->word,word); //given word copy to word of created node
    newNode->right=NULL;
    newNode->left=NULL;
    return newNode;
}

//for part a, insertion by word using binary search tree. .
void insert(struct node *root,struct node *key){

    if(stricmp(key->word, root->word)<0){  //when word is  less than word of current node and compare two words by ignore upper char
        if(root->left!=NULL)
            insert(root->left,key);
        else
            root->left=key; //we assign the word to left side of current node
    }

    if(stricmp(key->word, root->word)>0){ //when word is greater than word of current node,we assign the word to right side of current node

        if(root->right!=NULL)
            insert(root->right,key);
        else
            root->right=key;
    }
}

// for part c , insertion by frequency using binary tree.

struct node* insert_frequency(struct node* record, struct node* root,int num, int numberOf_frequency){ //level order insertion  to create binary tree

    if (num <= numberOf_frequency){

        struct node* newNode = create(record[num].frequency,record[num].word); //create new node for each node if current level is less than total number of data
        root = newNode;

        root->left = insert_frequency(record,root->left, 2 * num + 1, numberOf_frequency);

        root->right = insert_frequency(record,root->right, 2 * num + 2, numberOf_frequency);

    }

    return root;
}

int depth=0; // show node's level
int total_time=0; // to calculate total time

void inOrder(struct node* temp){ //print tree for binary search tree for part a.

    if(temp== NULL){
        return;
    }
    depth++; //increase for  each level
    inOrder(temp->left);
    printf(" %-15s    %-15d  \n",temp->word,temp->frequency);
    total_time=total_time+(temp->frequency)*depth; //total time formula (using frequency since frequency is related to number of access
    inOrder(temp->right);
    depth--; //in order to come to node

}
int time=0;// show node's level
int level =0; // to calculate total time
void inOrder_f(struct node* temp){  //print tree for binary tree for part c.

    if(temp== NULL){
        return;
    }
    level++; //increase for  each level
    inOrder_f(temp->left);
    printf("  %-15s    %-15d  \n",temp->word,temp->frequency);
    time=time+(temp->frequency)*level;  //total time formula (using frequency since frequency is related to number of access
    inOrder_f(temp->right);
    level--; //in order to come to node

}
int compare(const void *q, const void *p){ //to compare struct array's frequency that store data of node's
    struct node *freq1 = (struct node *)q;
    struct node *freq2 = (struct node *)p;

    return -(freq1->frequency - freq2->frequency); //from great to less.
}


int main() {

    //to calculate number of line
    int i=1;
    // to store taken date from file
    char *value;
    int numberOfOrder;
    int numberOfFrequency;


    struct node *root=NULL,*temp; //for binary search tree that using word
    struct node* root_char=NULL,*temp_char; //for binary search tree that using char.

    FILE *file;

    file=fopen("C:\\Users\\90537\\CLionProjects\\untitled\\input.txt","r"); //open file to calculate total line of each file
    int counter_line = 0;
    char line[100];
    if(file) {

        while (!feof(file)) { //read line by line until end of the file.

            while (fgets(line, sizeof(line), file)) {
                counter_line++;
            }
        }
    }
    fclose(file);

    file=fopen("C:\\Users\\90537\\CLionProjects\\untitled\\input.txt","r"); //to read file and store data in struct array

    struct node* record = (struct node*)(malloc(counter_line *sizeof(struct node))); //create struct array

    if(file)
    {

        while(!feof(file)) { //read line by line until end of the file.

            while (fgets(line, sizeof(line), file)) {

                value = strtok(line, ", "); //order (until comma)
                numberOfOrder = atoi(value);
                record[i].order = numberOfOrder;

                value = strtok(NULL, ","); //word (until comma)
                strcpy(record[i].word, value);

                value = strtok(NULL, " \n"); //frequency (until space)
                numberOfFrequency = atoi(value);
                record[i].frequency = numberOfFrequency;

                //insertion by using word for part a
                temp=create(record[i].frequency,record[i].word);

                if(root==NULL) {
                    root = temp;
                }
                else {
                    insert(root, temp);
                }


                i++; //next line

            }
        }
    }
    // frequency is related to number of access, so node that has got a greater frequency must be the top of tree.
    qsort(record, counter_line+1, sizeof(struct node), compare); //order frequency in struct array from great to less


    for (int j = 0; j < counter_line; ++j) {
        record[j] = record[j+1];
    }


    RootNode = insert_frequency(record,RootNode,0, counter_line-1); //insert binary tree for part c

    printf("\n");
    printf("Binary search tree struct by using words (part a)\n");
    printf("\n");
    printf(" WORD            FREQUENCY \n");
    printf("\n");
    inOrder(root); //print by using order of char in bst for part a
    printf("\n");
    printf(" Total access time :  %d \t \n", total_time);
    printf("\n");



    printf("Binary tree struct by using frequency (part c)\n");
    printf("\n");
    printf(" WORD            FREQUENCY \n");
    printf("\n");
    inOrder_f(RootNode);// print by using frequency in bt for part c
    printf("\n");
    printf(" Total access time :  %d\t \n", time);
    printf("\n");


    return 0;
}