class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None

    # Method to add a new element to the end of the list
    def append(self, value):
        new_node = Node(value)
        if not self.head:
            self.head = new_node
            return
        current = self.head
        while current.next:
            current = current.next
        current.next = new_node

    # Exercise 9 (10 pts)
    # Method to reverse the linked list
    def reverse(self):
        # your code here
        prev = None
        current = self.head
        while current:
            next_node = current.next
            current.next = prev
            prev = current
            current = next_node
        self.head = prev

    # Exercise 10 (10 pts)
    # Method to apply a function to each element of the list
    def foreach(self, func):
        # your code here
        current = self.head
        while current:
            func(current.data)
            current = current.next
            
# Exercise 11 (10 pts)
def print_list(linked_list):
    # your code here
    linked_list.foreach(lambda x: print(x, end=" "))
    print()

# Exercise 12 (5 pts)
def print_list_inc(linked_list):
    # your code here
    linked_list.foreach(lambda x: print(x + 1, end=" "))
    print()

if __name__ == "__main__":
    # Exercise 13 (5 pts)
    # your code here
    linked_list_1 = LinkedList()
    linked_list_1.append(1)
    linked_list_1.append(2)
    linked_list_1.append(3)
    linked_list_1.append(4)
    # your code here
    print_list(linked_list_1)
    
    # Exercise 14 (5 pts)
    # your code here
    linked_list_2 = LinkedList()
    linked_list_2.append(1.1)
    linked_list_2.append(2)
    linked_list_2.append(3.3)
    linked_list_2.append(4)
    # your code here
    print_list_inc(linked_list_2)
    
    # Exercise 15 (5 pts)
    # your code here
    linked_list_3 = LinkedList()
    linked_list_3.append(0)
    linked_list_3.append("zero")
    linked_list_3.append(1)
    # your code here
    linked_list_3.reverse()
    # print_list(linked_list_3)
    
    # Exercise 16 (5 pts)
    # your code here
    linked_list_4 = LinkedList()    
    linked_list_4.append(0)
    linked_list_4.append('z')
    linked_list_4.append(1)
    # your code here
    print_list_inc(linked_list_4)

####