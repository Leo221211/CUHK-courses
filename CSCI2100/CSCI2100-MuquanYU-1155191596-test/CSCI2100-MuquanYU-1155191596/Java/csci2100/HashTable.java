package csci2100;

import java.math.BigInteger;
// import java.util.Scanner;

import csci2100.MemMap.MemMapNode;

class HashTable {
    /**
     * structure of each node in hash table
     */
    private static class HTNode {
        BigInteger key; // address for hTOfAddr, size for hTOfSize, both of type BigInteger
        MemMapNode memMapNode; // MemMapNode
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

    /**
     * the minimum size of the dynamic hash table
     */
    private final int MIN_HTARRY_SIZE = 2;

    /**
     * anchor: to find the current block in O(1) time
     * only need to be updated when there is insert
     * formula:
     * first anchor point is 0
     * last anchor point is 
     * the address for the ith anchor is  i*anchorDist
     * the index   for the address addr is addr/anchorDist
     */
    MemMapNode[] anchor;
    BigInteger anchorDist = MemMap.maxSize.divide(new BigInteger("1000"));
    int anchor_num = (int)(MemMap.maxSize.divide(anchorDist).add(new BigInteger("1"))).intValue();
    
    /**
     * constructor: create an empty hash table array with size m = 64 else specified
     */
    public HashTable() {
        // Create a hash table with an initial size of 64.
        htArray = new HTNode[MIN_HTARRY_SIZE];
        eleNum = 0;

        // anchor
        if(anchor_num < 1) {System.out.println("Invalid anchorDist, change one (maybe smaller)"); System.exit(-1);}
        anchor = new MemMapNode[anchor_num];

        // Debug.dbgPrint("anchor.length: " + anchor.length + " anchorDist: " + anchorDist.intValue() + " anchor_num: "  + anchor_num);
        
    }


    /**
     * print out the hash table
     */
    void dump() {
        System.out.println();
        for (int i = 0; i < htArray.length; i++) {
            System.out.print(i + ":");
            HTNode list = htArray[i]; // For traversing linked list number i.
            while (list != null) {
                System.out.print("  (" + list.key + "," + list.memMapNode + ")");
                list = list.next;
            }
            System.out.println();
        }
    }

    /**
     * insert a key memMapNode pair
     * if with the same key, there will be 2 elements with the same key
     * update anchor[]
     */
    public void put(BigInteger key, MemMapNode memMapNode) {
        // check if need to expand
        if (eleNum >= 2 * htArray.length) {
            expand();
        }

        int bucket = hash(key); // bucket: entry of the hash table array

        // add the new key to the corresponding bucket
        HTNode newNode = new HTNode();
        newNode.key = key;
        newNode.memMapNode = memMapNode;
        newNode.next = htArray[bucket];
        htArray[bucket] = newNode;
        eleNum++; // Count the newly added key.

        // update anchor: for all anchor in the range of the input memMapNode, update its reference
        BigInteger start =  memMapNode.startingAddr;
        BigInteger end =  memMapNode.startingAddr.add(memMapNode.size).subtract(new BigInteger("1"));


        // for all anchors in range, update
        int startIdx =  start.divide(new BigInteger(String.valueOf(anchorDist))).intValue();
        int enxIdx =  end.divide(new BigInteger(String.valueOf(anchorDist))).intValue();


        if(start.mod(new BigInteger(String.valueOf(anchorDist))).equals(new BigInteger("0"))) {
            anchor[startIdx] = memMapNode;
        }

        for(int i = startIdx + 1; i <= enxIdx; i ++) {
            anchor[i] = memMapNode;
        }
    }

    /**
     * query: input the key
     * 
     * @return if exist output the memMapNode (reference to the node of the MemMap),
     *         else return null
     *         not modified, only get the first one met in hash table
     */
    public MemMapNode get(BigInteger key) {
        int bucket = hash(key); // the bucket the kvp should be in
        HTNode list = htArray[bucket]; // list is the node in the bucket: to linearly search the bucket

        while (list != null) {
            if (list.key.equals(key))
                return list.memMapNode;
            list = list.next; // Move on to next node in the list
        }
        return null;
    }

    /**
     * modified get: if several values with the same key: get the memMapNode with
     * the smallest value.startingAddr
     * 
     * @param key
     * @return
     */
    public MemMapNode getMinAddr(BigInteger key) {
        int bucket = hash(key); // the bucket the kvp should be in
        HTNode list = htArray[bucket]; // list is the node in the bucket: to linearly search the bucket

        BigInteger tempMaxAddr = MemMap.maxSize;
        MemMapNode temp = null;

        while (list != null) {
            if (list.key.equals(key)) {
                // Debug.dbgPrint("tempMaxAddr is " + tempMaxAddr);    // null
                if (tempMaxAddr.compareTo(list.memMapNode.startingAddr) == 1) {
                    tempMaxAddr = list.memMapNode.startingAddr;
                    temp = list.memMapNode;
                }
            }
            list = list.next; // Move on to next node in the list.
        }

        return temp;
    }

    /**
     * modified get: get the kvp with successor of the key of smallest addr: 
     * loop through the hash table bucket by bucket
     *      for BEST_FIT search: search in hTOfSize successor of op.getSize()
     * @param key
     * @return
     */
    public MemMapNode getSuccKeyMinAddr(BigInteger key) {
        BigInteger tempMinKey = MemoryManager.TOTAL_BYTES;
        MemMapNode temp = null;

        for(int bucket = 0; bucket < htArray.length; bucket ++) {   // for all buckets
            HTNode list = htArray[bucket];
            
            while (list != null) {                                  // for all nodes in the bucket
                // Debug.dbgPrint("now checking block with size: " + list.key);
                // Debug.dbgPrint("list.key.compareTo(tempMinKey) == -1: " + (list.key.compareTo(tempMinKey) == -1) + " list.key.compareTo(key) != -1: " + (list.key.compareTo(key) != -1));
                if(list.key.compareTo(tempMinKey) != 1 && list.key.compareTo(key) != -1) {   // new key(size) < than temp min key(size) and >= key
                    tempMinKey = list.key;
                    temp = list.memMapNode;
                    // Debug.dbgPrint("temp min size updated to: " + temp.size);
                }

                // new key(size) = temp min key(size): find the smallest addr
                else {
                    // Debug.dbgPrint(" list.memMapNode " +  list.memMapNode + "; temp " + temp);   // temp is null
                    if(list.key.compareTo(tempMinKey) == 0 && list.memMapNode.startingAddr.compareTo(temp.startingAddr) == -1) {   // list.addr < temp.addr
                        tempMinKey = list.key;
                        temp = list.memMapNode;
                        // Debug.dbgPrint("temp min size updated to: " + temp.size);
                    }
                }
                list = list.next; // Move on to next node in the list.
            }
        }

        // Debug.dbgPrint("search done, the target address is: " + temp.startingAddr);
        return temp;        // if not found then return null
    }

    /**
     * modified get: get the kvp with predecessor of the key of smallest addr: 
     * loop through the hash table bucket by bucket from predecessor anchor point
     *      for finding the MemMapNode of any given address: 
     *      search in the hTofAddr for the target address. the kvp is the MemMapNode the target address is at
     * @param key
     * @return
     */
    public MemMapNode getPredKey(BigInteger key) {
        BigInteger tempMinKey = new BigInteger("-1");          // temperary min address
        MemMapNode temp = null;

        MemMapNode anchorNode;
        try {
            anchorNode = anchor[key.divide(anchorDist).intValue()];
        }
        catch(ArrayIndexOutOfBoundsException e) {
            return null;
        }
        int bucket =  hash(anchorNode.startingAddr);

        // error handling: unless not found
        for(; bucket < htArray.length; bucket ++) {   // for all buckets after anchor node
            HTNode list = htArray[bucket];
            
            while (list != null) {                                  // for all nodes in the bucket
                // Debug.dbgPrint("tempMinKey < key");
                if(list.key.compareTo(tempMinKey) == 1 && list.key.compareTo(key) != 1) {   // new key(addr) > than temp min key(addr) and <= key(addr)
                    // Debug.dbgPrint("found 1 OK predecessor");
                    tempMinKey = list.key;
                    temp = list.memMapNode;
                }

                list = list.next; // Move on to next node in the list.
            }
        }

        return temp;
    }

    /**
     * 
     * @return
     */
    public BigInteger getMaxBlockSize() {
        BigInteger tempMax = new BigInteger("1");
        for(int bucket = 0; bucket < htArray.length; bucket ++) {   // for all buckets
            HTNode list = htArray[bucket];
            
            while (list != null) {                                  // for all nodes in the bucket
                if(list.memMapNode.size.compareTo(tempMax) == 1) {    // >
                    tempMax = list.memMapNode.size;
                }
                list = list.next; // Move on to next node in the list.
            }
        }
        return tempMax;
    }

    /**
     * remove the kvp
     * assume the key must be inside the hash table (else only a warning)
     */
    public void remove(BigInteger key, MemMapNode memMapNode) {
        // check if need to shrink
        if (eleNum <= 0.5 * htArray.length && htArray.length >= 2 * MIN_HTARRY_SIZE /*4 */) {
            shrink();
        }

        int bucket = hash(key);
        if (htArray[bucket] == null) { // nothing in the bucket
            Debug.dbgPrint("Didn't find the key in remove process in search for (" + key + "," + memMapNode
                    + " no bucket " + bucket);
            return;
        }

        if (htArray[bucket].key.equals(key) && htArray[bucket].memMapNode.equals(memMapNode)) { // the first element in
                                                                                                // the HT linked list is
                                                                                                // the kvp to be removed
            htArray[bucket] = htArray[bucket].next;
            eleNum--; // Remove new number of items in the table.
            // Debug.dbgPrint("1removed (" + key + "," + memMapNode + ")");
            return;
        }

        // not the first of the bucket
        HTNode prev = htArray[bucket];
        HTNode curr = prev.next;
        while (curr != null && !(curr.key.equals(key) && curr.memMapNode.equals(memMapNode))) {
            prev = curr;
            curr = curr.next;
        } // search until finding the kvp to be removed

        if (curr != null) { // found the kvp
            // Debug.dbgPrint("2removed (" + key + "," + memMapNode + ")");
            prev.next = curr.next;
            eleNum--; // Record new number of items in the table.
        } else {
            Debug.dbgPrint("Didn't find the key in remove process in search for (" + key + "," + memMapNode);
        }

    }

    /**
     * check if have the kvp
     * 
     * @param key
     * @return: true or false
     */
    public boolean containsKey(BigInteger key) {
        // Test whether the specified key has an associated memMapNode
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
        // Return the number of key/memMapNode pairs in the table.
        return eleNum;
    }

    /**
     * the hash function
     * @param key
     * @return
     */
    private int hash(BigInteger key) {
        return (Math.abs(key.hashCode())) % htArray.length;
    }


    /**
     * expand
     */
    private void expand(/* ResizeType type */) {
        // HTNode[] newtable;
        // if (type.equals(ResizeType.DOUBLE)) {
        // newtable = new HTNode[htArray.length * 2];
        // }
        // else {
        // if(htArray.length <= MIN_HTARRY_SIZE) {return;} // if size is already smaller
        // than default size, than don't make it smaller
        // newtable = new HTNode[htArray.length / 2];
        // }
        HTNode[] newtable = new HTNode[htArray.length * 2];
        for (int i = 0; i < htArray.length; i++) {
            HTNode list = htArray[i];
            while (list != null) {
                HTNode next = list.next;
                int hash = (Math.abs(list.key.hashCode())) % newtable.length; // find the hash memMapNode of this HTNode
                list.next = newtable[hash];
                newtable[hash] = list;
                list = next; // Move on to the next node in the OLD table.
            }
        }
        htArray = newtable; // Replace the table with the new table.
    } // end expand()

    /**
     * shrink
     */
    private void shrink(/* ResizeType type */) {
        // HTNode[] newtable;
        // if (type.equals(ResizeType.DOUBLE)) {
        // newtable = new HTNode[htArray.length * 2];
        // }
        // else {
        // if(htArray.length <= MIN_HTARRY_SIZE) {return;} // if size is already smaller
        // than default size, than don't make it smaller
        // newtable = new HTNode[htArray.length / 2];
        // }
        HTNode[] newtable = new HTNode[htArray.length / 2];
        for (int i = 0; i < htArray.length; i++) {
            HTNode list = htArray[i];
            while (list != null) {
                HTNode next = list.next;
                int hash = (Math.abs(list.key.hashCode())) % newtable.length; // find the hash memMapNode of this HTNode
                list.next = newtable[hash];
                newtable[hash] = list;
                list = next; // Move on to the next node in the OLD table.
            }
        }
        htArray = newtable; // Replace the table with the new table.
    } // end shrink()
} 
