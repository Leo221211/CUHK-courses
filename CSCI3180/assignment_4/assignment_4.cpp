/* CSCI3180 Principles of Programming Languages
 *
 * --- Declaration ---
 * For all submitted files, including the source code files and the written
 * report, for this assignment:
 *
 * I declare that the assignment here submitted is original except for source
 * materials explicitly acknowledged. I also acknowledge that I am aware of
 * University policy and regulations on honesty in academic work, and of the
 * disciplinary guidelines and procedures applicable to breaches of such policy
 * and regulations, as contained in the website
 * http://www.cuhk.edu.hk/policy/academichonesty/
 *
 * Name: Muquan YU
 *  Student ID: 1155191596
 * Email Address: mqyu@link.cuhk.edu.hk
 *
 * Source material acknowledgements (if any):
 *
 * Students whom I have discussed with (if any):
 */

#include <iostream>

template <typename T>
class LinkedList
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(T val) : data(val), next(nullptr) {}
    };

    Node *head;

public:
    LinkedList() : head(nullptr) {}

    // Method to add a new element to the end of the list
    void append(T value)
    {
        Node *newNode = new Node(value);
        if (!head)
        {
            head = newNode;
            return;
        }
        Node *temp = head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // Exercise 1 (10 pts)
    // Method to reverse the linked list
    void reverse()
    {
        // your code here
        Node *prev = nullptr, *current = head, *next = nullptr;
        while (current)
        {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    // Exercise 2 (10 pts)
    // Method to apply a member function to each element of the list
    void foreach (void (*func)(T))
    {
        Node* temp = head;
        while (temp) {
            func(temp->data);
            temp = temp->next;
        }
    }

    ~LinkedList()
    {
        Node *current = head;
        Node *nextNode;
        while (current)
        {
            nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

// Exercise 3 (5 pts)
void printInt(int value)
{
    std::cout << value << " ";
}

void printList(LinkedList<int> &list)
{
    // your code here
    list.foreach(printInt);
    std::cout << std::endl;
}

// Exercise 4 (5 pts)
 void printListInc(LinkedList<int> &list)
{
    list.foreach([](int value) { 
        std::cout << (value + 1) << " "; 
    });
    std::cout << std::endl;
}

int main()
{
    // Exercise 5 (5 pts)
    // your code here
    LinkedList<int> linkedList1;
    linkedList1.append(1);
    linkedList1.append(2);
    linkedList1.append(3);
    linkedList1.append(4);
    // your code here
    printList(linkedList1);

    // Exericse 6 (5 pts)
    // your code here
    LinkedList<int> linkedList2;
    // LinkedList<int> linkedList2;
    linkedList2.append(1.1);
    linkedList2.append(2);
    linkedList2.append(3.3);
    linkedList2.append(4);
    // your code here
    printListInc(linkedList2);

    // // Exercise 7 (5 pts)
    // // your code here
    // LinkedList<void*> linkedList3;
    // linkedList3.append(0);
    // linkedList3.append("zero");
    // linkedList3.append(1);
    // // your code here
    // linkedList3.reverse();
    // Reason: In C++, we cannot implicitly convert int and const char* variable shown above to a same type. But for the linked list, it has to be a same type.
    


    // Exercise 8 (5 pts)
    // your code here
    LinkedList<int> linkedList4;
    linkedList4.append(0);
    linkedList4.append('z');
    linkedList4.append(1);
    // your code here
    printListInc(linkedList4);

    return 0;
}

////