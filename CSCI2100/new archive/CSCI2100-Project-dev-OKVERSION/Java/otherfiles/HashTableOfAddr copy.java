package csci2100;

public class HashTableOfAddr {
    /**
     * structure of each node in hash table
     */
    private static class HTNode{
        Object key;         // address
        Object value;       // MemMapNode
        HTNode next;
    }

    /**
     * hash table array
     */
    private HTNode[] htArray;

    /**
     * the number of total elements in the hash table (n)
     */
    private int eleNum;

    private final int MIN_HTARRY_SIZE = 2;

    // private enum ResizeType{
    //     DOUBLE, HALF
    // }

    /**
     * constructor: create an empty hash table array with size m = 64 else specified
     */
    public HashTableOfAddr() {
        // Create a hash table with an initial size of 64.
        htArray = new HTNode[MIN_HTARRY_SIZE];
        eleNum = 0;
    }
    // public HashTableOfAddr(int initialSize) {
    //     // Create a hash table with a specified initial size.
    //     // Precondition: initalSize > 0.
    //     htArray = new HTNode[initialSize];
    // }

    /**
     * print out the hash table
     */
    void dump() {
        System.out.println();
        for (int i = 0; i < htArray.length; i++) {
            System.out.print(i + ":");
            HTNode list = htArray[i]; // For traversing linked list number i.
            while (list != null) {
                System.out.print("  (" + list.key + "," + list.value + ")");
                list = list.next;
            }
            System.out.println();
        }
    } // end dump()

    /**
     * insert a key value pair
     * if with the same key, there will be 2 elements with the same key
     */
    public void put(Object key, Object value) {
        int bucket = hash(key);             // bucket: entry of the hash table array

        // add the new key to the corresponding bucket
        HTNode newNode = new HTNode();
        newNode.key = key;
        newNode.value = value;
        newNode.next = htArray[bucket];
        htArray[bucket] = newNode;
        eleNum++; // Count the newly added key.

        // check if need to resize
        if (eleNum >= 0.75 * htArray.length) {
            resize();
        }
    }

    /**
     * query: input the key
     * @return if exist output the value (reference to the node of the MemMap), else return null
     */
    public Object get(Object key) {
        int bucket = hash(key);         // the bucket the kvp should be in
        HTNode list = htArray[bucket];  // list is the node in the bucket: to linearly search the bucket

        while (list != null) {
            if (list.key.equals(key))
                return list.value;
            list = list.next; // Move on to next node in the list.
        }
        return null;
    }

    /**
     * query: input the key, get the minimum
     * @param key
     * @return
     */
    public Object getMin(Object key) {
        int bucket = hash(key);         // the bucket the kvp should be in
        HTNode list = htArray[bucket];  // list is the node in the bucket: to linearly search the bucket

        while (list != null) {
            if (list.key.equals(key))
                return list.value;
            list = list.next; // Move on to next node in the list.
        }
        return null;
    }

    /**
     * remove the kvp
     * assume the key must be inside the hash table (else only a warning)
     */
    public void remove(Object key) {
        int bucket = hash(key); 
        if (htArray[bucket] == null) {  // didn't find the key
            System.out.println("Didn't find the key in remove process!");
            return;
        }

        if (htArray[bucket].key.equals(key)) {  // the first element in the HT linked list is the kvp to be removed
            htArray[bucket] = htArray[bucket].next;
            eleNum--; // Remove new number of items in the table.
            return;
        }

        HTNode prev = htArray[bucket]; 
        HTNode curr = prev.next;
        while (curr != null && !curr.key.equals(key)) {
            curr = curr.next;
            prev = curr;
        }       // search until finding the kvp to be removed

        if (curr != null) {     // found the kvp
            prev.next = curr.next;
            eleNum--; // Record new number of items in the table.
            return;
        }

        // didn't find the kvp at last
        System.out.println("Didn't find the key in remove process!");
        return;
    }

    /**
     * check if have the kvp
     * @param key
     * @return: true or false
     */
    public boolean containsKey(Object key) {
        // Test whether the specified key has an associated value
        // in the table.
        int bucket = hash(key); // In what location should key be?
        HTNode list = htArray[bucket]; // For traversing the list.
        while (list != null) {
            // If we find the key in this node, return true.
            if (list.key.equals(key))
                return true;
            list = list.next;
        }
        // If we get to this point, we know that the key does
        // not exist in the table.
        return false;
    }

    /**
     * @return return element num (n) of the hash table
     */
    public int size() {
        // Return the number of key/value pairs in the table.
        return eleNum;
    }

    /**
     * the hash function
     * @param key
     * @return
     */
    private int hash(Object key) {
        // Compute a hash code for the key; key cannot be null.
        // The hash code depends on the size of the table as
        // well as on the value returned by key.hashCode().
        return (Math.abs(key.hashCode())) % htArray.length;
    }



    /**
     * resize
     */
    private void resize(/*ResizeType type*/) {
        // HTNode[] newtable;
        // if (type.equals(ResizeType.DOUBLE)) {
        //     newtable = new HTNode[htArray.length * 2];
        // }
        // else {
        //     if(htArray.length <= MIN_HTARRY_SIZE) {return;}       // if size is already smaller than default size, than don't make it smaller
        //     newtable = new HTNode[htArray.length / 2];
        // }
        HTNode[] newtable = new HTNode[htArray.length * 2];
        for (int i = 0; i < htArray.length; i++) {
            HTNode list = htArray[i];
            while (list != null) {
                HTNode next = list.next; 
                int hash = (Math.abs(list.key.hashCode())) % newtable.length;   // find the hash value of this HTNode
                list.next = newtable[hash];
                newtable[hash] = list;
                list = next; // Move on to the next node in the OLD table.
            }
        }
        htArray = newtable; // Replace the table with the new table.
    } // end resize()
}
