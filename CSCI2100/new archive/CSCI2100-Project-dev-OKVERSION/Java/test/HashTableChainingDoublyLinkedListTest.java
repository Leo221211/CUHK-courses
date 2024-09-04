/*
 *    Java Program to Implement Hash Tables Chaining with Doubly Linked Lists 
 */

import java.util.Scanner;

/* Node for doubly linked list */
class DLLNode
{
    DLLNode next, prev;
    int data;

    /* Constructor */
    public DLLNode(int x)
    {
        data = x;
        next = null;
        prev = null;
    }
}

/* Class HashTableChainingDoublyLinkedList */
class HashTableChainingDoublyLinkedList
{
    private DLLNode[] table;
    private int size ;      // size of elements

    /* Constructor */
    // input table size, generate the table of [tableSize] cells
    public HashTableChainingDoublyLinkedList(int tableSize)
    {
        table = new DLLNode[ nextPrime(tableSize) ];    // size of the table is prime num, same scale with the total element num n
        size = 0;
    }

    /* Function to check if hash table is empty */
    public boolean isEmpty()
    {
        return size == 0;
    }
    /* Function to clear hash table */
    public void makeEmpty()
    {
        int l = table.length;
        table = new DLLNode[l];
        size = 0;
    }
    /* Function to get size */
    public int getSize()
    {
        return size;
    }

    /* Function to insert an element */
    public void insert(int val)
    {
        size++;
        int pos = myhash(val);        
        DLLNode nptr = new DLLNode(val);
        DLLNode start = table[pos];                
        if (table[pos] == null)
            table[pos] = nptr;            
        else
        {
            nptr.next = start;
            start.prev = nptr;
            table[pos] = nptr;
        }    
    }
    /* Function to remove an element */
    public void remove(int val)
    {
        try
        {
            int pos = myhash(val);    
            DLLNode start = table[pos];
            DLLNode end = start;
            if (start.data == val)
            {
                size--;
                if (start.next == null)
                {
                    table[pos] = null;
                    return;
                }                
                start = start.next;
                start.prev = null;
                table[pos] = start;
                return;
            }

            while (end.next != null && end.next.data != val)
                end = end.next;
            if (end.next == null)
            {
                System.out.println("\nElement not found\n");
                return;
            }
            size--;
            if (end.next.next == null)
            {
                end.next = null;
                return;
            }
            end.next.next.prev = end;
            end.next = end.next.next;

            table[pos] = start;
        }
        catch (Exception e)
        {
            System.out.println("\nElement not found\n");
        }
    }

    /* Function myhash */
    private int myhash(Integer x )
    {
        int hashVal = x.hashCode( );
        hashVal %= table.length;
        if (hashVal < 0)
            hashVal += table.length;
        return hashVal;
    }


    /* Function to generate next prime number >= n */
    private static int nextPrime( int n )
    {
        if (n % 2 == 0)
            n++;
        for ( ; !isPrime( n ); n += 2);

        return n;
    }
    /* Function to check if given number is prime */
    private static boolean isPrime( int n )
    {
        if (n == 2 || n == 3)
            return true;
        if (n == 1 || n % 2 == 0)
            return false;
        for (int i = 3; i * i <= n; i += 2)
            if (n % i == 0)
                return false;
        return true;
    }

    /* Function to print hash table */
    public void printHashTable ()
    {
        System.out.println();
        for (int i = 0; i < table.length; i++)
        {
            System.out.print ("Bucket " + i + ":  ");            

            DLLNode start = table[i];
            while(start != null)
            {
                System.out.print(start.data +" ");
                start = start.next;
            }
            System.out.println();
        }
    }    

}

/* Class HashTableChainingDoublyLinkedListTest */
public class HashTableChainingDoublyLinkedListTest
{ 
    public static void main(String[] args) 
    {
        Scanner scan = new Scanner(System.in);
        System.out.println("Hash Table Test\n\n");
        System.out.println("Enter size");
        /* Make object of HashTableChainingDoublyLinkedList */
        HashTableChainingDoublyLinkedList htcdll = new HashTableChainingDoublyLinkedList(scan.nextInt() );

        char ch;
        /*  Perform HashTableChainingDoublyLinkedList operations  */
        do    
        {
            System.out.println("\nHash Table Operations\n");
            System.out.println("1. insert ");
            System.out.println("2. remove");
            System.out.println("3. clear");
            System.out.println("4. size"); 
            System.out.println("5. check empty");
 
            int choice = scan.nextInt();             
            switch (choice)
            {
            case 1 : 
                System.out.println("Enter integer element to insert");
                htcdll.insert( scan.nextInt() ); 
                break;                          
            case 2 :                  
                System.out.println("Enter integer element to delete");
                htcdll.remove( scan.nextInt() ); 
                break; 
            case 3 : 
                htcdll.makeEmpty();
                System.out.println("Hash Table Cleared\n");
                break;
            case 4 : 
                System.out.println("Size = "+ htcdll.getSize() );
                break; 
            case 5 : 
                System.out.println("Empty status = "+ htcdll.isEmpty() );
                break;        
            default : 
                System.out.println("Wrong Entry \n ");
                break;   
            } 
            /* Display hash table */ 
            htcdll.printHashTable();  
 
            System.out.println("\nDo you want to continue (Type y or n) \n");
            ch = scan.next().charAt(0);                        
        } while (ch == 'Y'|| ch == 'y');  
    }
}