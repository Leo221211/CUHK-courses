package csci2100;

import java.math.BigInteger;
import java.util.Scanner;

import csci2100.MemMap.MemMapNode;

// is a linked list, 
// each node contains: (1)starting add (2)size (3) occupation status (3)ownership (4)protection (5) prevNode (6) nextNode
public class MemMap {
    // define each node
    public static class MemMapNode {
        BigInteger startingAddr;
        BigInteger size;
        boolean isOccupied;
        MemMapNode prevNode;
        MemMapNode nextNode;
        // int ownership;
        // int protection;

        public MemMapNode (BigInteger startingAddr, BigInteger size, boolean isOccupied) {
            this.startingAddr = startingAddr;
            this.size = size;
            this.isOccupied = isOccupied;
        }

        @Override
        public String toString() {
            return startingAddr.toString();
        }
    }

    /**
     * modify the total size in of the memory (in bytes)
     */
    // public static BigInteger maxSize = new BigInteger("4294967296"); // 4GB = 4*1024*1024*1024 Bytes
    // public static BigInteger maxSize = new BigInteger("1024");
    // public static BigInteger maxSize = new BigInteger("1024000");
    public static BigInteger maxSize = new BigInteger("1027140");
    
    

    public MemMapNode firstNode;

    /**
     * constructor
     * @param totalSize total size of the hash table
     */
    public MemMap(BigInteger totalSize) {
        firstNode = new MemMapNode(new BigInteger("0"), totalSize, false);
    }




    /**
     * insert a node into the MemMap after the given node
     * @param prev the node to be before the insert node. If prev is null, insert at the start
     * @param curr the current node to be inserted
     */
    public void insert(MemMapNode prev, MemMapNode curr) {
        if (prev == null) {   // insert from the start
            curr.nextNode = firstNode;
            firstNode.prevNode = curr;
            firstNode = curr;
        }
        else if (prev.nextNode == null) {    // to insert is last MemMapNode
            prev.nextNode = curr;
            curr.prevNode = prev;
        }
        else {  // is some node at the middle
            MemMapNode next = prev.nextNode;
            curr.prevNode = prev;
            curr.nextNode = next;
            prev.nextNode = curr;
            next.prevNode = curr;
        }
    }

    /**
     * delete the node
     * @param curr the node to be deleted
     */
    public void delete(MemMapNode curr) {
        if (curr.prevNode == null) {    // delete the first node
            firstNode = curr.nextNode;
            // Debug.dbgPrint("curr is " + curr.startingAddr + " curr.prevNode is " + curr.prevNode);
            curr.nextNode.prevNode = null;
        }
        else if (curr.nextNode == null) {    // delete the last node
            curr.prevNode.nextNode = null;
        }
        else {          // delete a middle node
            curr.prevNode.nextNode = curr.nextNode;
            curr.nextNode.prevNode = curr.prevNode;
        }
    }

    /**
     * give the previous node, merge prev and prev.nextNode
     * if prev is the last node, just do nothing
     * actually not used in the algorithm, that is because my later version of design doesn't need the merge operation, but I kept it for the completeness of the class
     * the new node will have a reference, startingAddr and occupation status same with prev, with size updated
     * @param prev
     */
    public void merge(MemMapNode prev) {
        // check if prev is the last node
        if (prev.nextNode == null) {
            return;
        }
        
        MemMapNode next = prev.nextNode;
        // update size
        prev.size = prev.size.add(next.size) ;         

        // if next is the last node
        if (next.nextNode == null) {
            prev.nextNode = null;
        }
        else {
            prev.nextNode = next.nextNode;
            next.nextNode.prevNode = prev;
        }
    }

    /**
     * testing function
     * print by (start addr, size, occupation status) -> next
     */
    void printMemMap() {
        MemMapNode curr = firstNode;

        while (curr != null) {
            ;
            if(curr.isOccupied) {
                System.out.print("(" + curr.startingAddr + ", " + curr.size + ", " + "O, " + (curr.startingAddr.add(curr.size).subtract(new BigInteger("1")) + ")->"));
            }
            else {
                System.out.print("(" + curr.startingAddr + ", " + curr.size + ", " + "F, " + (curr.startingAddr.add(curr.size).subtract(new BigInteger("1")) + ")->"));
            }

            curr = curr.nextNode;
        }
    }


    /**
     * testing only
     * if want to return null, input -1
     */
    MemMapNode get(int index) {
        if(index < 0) {return null;}
        MemMapNode curr = firstNode;
        for(int i = 0; i < index; i ++) {
            curr = curr.nextNode;
        }

        if (curr == null) {System.exit(0);}
        return curr;
    }


}


/**
 * only for testing
 */
class MyTestMemMap {
    public static void main(String[] args) {
        MemMap memMap = new MemMap(new BigInteger("1024"));
        memMap.printMemMap();

        int index;
        Scanner scn = new Scanner(System.in);
        while (true) {
            System.out.println("\nMenu:");
            System.out.println("   1. insert");
            System.out.println("   2. delete");
            System.out.println("   3. merge");
            System.out.println("Enter your command:  ");
            switch (scn.nextInt()) {
                case 1:
                    System.out.println("input insert prev index (-1 for inserting in the front):");
                    index = scn.nextInt();
                    System.out.println("input insert node");
                    memMap.insert(memMap.get(index), readMMNodefromKB());
                    break;
                case 2:
                    System.out.println("input delete index:");
                    index = scn.nextInt();
                    memMap.delete(memMap.get(index));
                    break;
                case 3:
                    System.out.println("input prev index:");
                    index = scn.nextInt();
                    memMap.merge(memMap.get(index));;
                    break;
                default:
                    System.out.println("   Illegal command.");
                    break;
            }

            System.out.println();
            memMap.printMemMap();
            System.out.println();
        }
    }



    // testing only
    public static MemMapNode readMMNodefromKB() {
        Scanner kb = new Scanner(System.in);
        System.out.println("input starting addr, size, and occupation status (0 for free, 1 for all0c):");
        BigInteger addr = new BigInteger(kb.next());
        BigInteger size = new BigInteger(kb.next());
        boolean occ = true;
        if(kb.nextInt() ==  0){
            occ = false;
        }

        return new MemMapNode(addr, size, occ);
    }
}