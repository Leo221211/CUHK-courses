#include <stdio.h>

int main()
{
    /*
    typedef struct{
        int data;
        Node *next = NULL;
    } Node;
    */

    /*
    struct Node{
        int data;
        struct Node *next;
    };
    */
   
    typedef struct Node Node;
    Node{
        int data;
        Node *ptr;
    };




    return 0;
}