package csci2100;

import java.math.BigInteger;

import csci2100.MemMap.MemMapNode;

public class MemoryManager {

    public enum MemoryStrategy {
        FIRST_FIT,
        BEST_FIT,
        WORST_FIT;
    }

    private MemoryStrategy strategy;

    public static final BigInteger TOTAL_BYTES = MemMap.maxSize; 
    
    // if is true, implement the release mode updated in discussion board:
    // if there are free block in the memory,
    // memory manager will return false
    boolean newReleaseMode = false;


    MemMap memMap;
    HashTable htOfFreeSize, htOfAddr;
    BigInteger maxBlockSize;


    /**
     * constructor
     * @param strategy
     */
    public MemoryManager(MemoryStrategy strategy) {
        this.strategy = strategy;


        // init memMap
        memMap = new MemMap(TOTAL_BYTES); // new memMap, first free node already init

        // init htOfFreeSize: 1 free block and a max size
        htOfFreeSize = new HashTable();
        htOfFreeSize.put(TOTAL_BYTES, memMap.firstNode); // initially, only 1 free node
        maxBlockSize = TOTAL_BYTES; // maxBlockSize

        // init hTofAddr
        htOfAddr = new HashTable();
        htOfAddr.put(new BigInteger("0"), memMap.firstNode); // initially only 1 node

        // testing: print out the 3 structures
        Debug.dbgPrint("Init finished, current status:\n");
        print3Tables();
    }

    public int request(MemoryOperation op) {
        // TODO
        // Accepts a space request and allocate memory
        // If the memory is not available, the request should not be accepted
        // Allocate the memory according to the current strategy unless the address is
        // given
        // Return the allocated address if the memory is allocated successfully,
        // otherwise return -1

        MemMapNode toInsert = null;
        // Debug.printFileNameAndLineNumber();

        // request without size: find the valid memMapNode (or else return -1)
        // for this kind of search, the address returned must be the first address of a
        // memMap block
        if (op.getAddr() == null) {

            switch (strategy) {

                case FIRST_FIT:
                    // Debug.printFileNameAndLineNumber();
                    // loop through hash table by address to find the first available address
                    BigInteger currAddr = new BigInteger("0");
                    MemMapNode currMemMapNode = (MemMapNode) htOfAddr.get(currAddr);
                    while (true) { // loop through the table
                        if (currMemMapNode == null) {
                            Debug.dbgPrint("invalid operation");
                            return -1;
                        } // already finished looping, can't find any valid address

                        if (currMemMapNode.size.compareTo(op.getSize()) != -1 && !currMemMapNode.isOccupied) { // if size bigger or equals to the request size and not occupied: found the one
                            op.setAddr(currAddr);
                            toInsert = currMemMapNode;
                            break;
                        }

                        currAddr = currAddr.add(currMemMapNode.size);
                        currMemMapNode = (MemMapNode) htOfAddr.get(currAddr);
                    }
                    if(toInsert == null) {return -1;}

                    // Debug.dbgPrint("curr addr: " + currAddr);
                    break;

                case BEST_FIT:

                    // find the kvp in htOfFreeSize: whose key(size) is successor of op.getSize()
                    // and has the least starting address
                    toInsert = htOfFreeSize.getSuccKeyMinAddr(op.getSize());    // might be an occupied block
                    if(toInsert == null) {return -1;}
                    op.setAddr(toInsert.startingAddr);
                    // Debug.dbgPrint("current best fit address is " + toInsert.startingAddr + "should be same with op.getAddr(): " + op.getAddr()); // 520200
                    break;

                default: // Worst fit

                    if (maxBlockSize.compareTo(op.getSize()) == 1) {
                        MemMapNode curr = (MemMapNode) htOfFreeSize.getMinAddr(maxBlockSize);
                        op.setAddr(curr.startingAddr);
                        toInsert = curr;
                    } else {
                        Debug.dbgPrint("invalid operation");
                        return -1;
                    }
                    break;
            }
        }

        // request with address: find the valid memMapNode or else return -1
        else {
            // check address in range
            if(op.getAddr().compareTo(new BigInteger("0")) == -1 || op.getAddr().compareTo(TOTAL_BYTES.subtract(new BigInteger("1"))) == 1) {return -1;}        // < 0 or > max - 1

            // first find the MemMapNode of the target address
            toInsert = htOfAddr.getPredKey(op.getAddr());
            if (toInsert == null) {
                Debug.dbgPrint("wrong. toInsert is null");
            }

            // check if it is valid, if not return -1
            /// if the MemMapNode is already occupied, invalid
            if (toInsert.isOccupied) {
                Debug.dbgPrint("invalid operation");
                return -1;
            }

            /// if the end address of the request block > end address of toInsert, invalid
            BigInteger requestEnd = op.getAddr().add(op.getSize()).subtract(new BigInteger("1"));
            BigInteger toInsertEnd = toInsert.startingAddr.add(toInsert.size).subtract(new BigInteger("1"));
            if (requestEnd.compareTo(toInsertEnd) == 1) {
                Debug.dbgPrint("invalid operation");
                return -1;
            }

            // otherwise it is valid, go and insert
        }

        // Debug.printFileNameAndLineNumber();
        // insert by updating 3 structures, and return the inserted address
        // Debug.dbgPrint("insert block's starting address: " + toInsert.startingAddr);

        /// mMNode2: the requested block
        //// update in memMap
        MemMapNode mMNode2 = new MemMapNode(op.getAddr(), op.getSize(), true);
        memMap.insert(toInsert, mMNode2);

        //// update in htOfAddr
        htOfAddr.put(mMNode2.startingAddr, mMNode2);

        //// update in htOfFreeSize
        // htOfFreeSize.put(mMNode2.size, mMNode2);    // wrong: mMNode2 is occupied
        // no need to update maxBlockSize, since it is a sub block of toInsert

        /// mMNode1: the part of block before requested block
        if (toInsert.startingAddr.compareTo(op.getAddr()) == -1) { // startingAddr < request address: there is mMNode1
            //// update in memMap
            // Debug.dbgPrint("op.getAddr(), toInsert.startingAddr" + op.getAddr() + " " +
            MemMapNode mMNode1 = new MemMapNode(toInsert.startingAddr, op.getAddr().subtract(toInsert.startingAddr),
                    false); // update in memMap

            memMap.insert(toInsert, mMNode1);

            //// update in htOfAddr
            htOfAddr.put(toInsert.startingAddr, mMNode1);

            //// update in htOfFreeSize
            htOfFreeSize.put(mMNode1.size, mMNode1);    // mMNode1 must be free
            // no need to update maxBlockSize, since it is a sub block of toInsert
        }

        /// mMNode3: the part of block after requested block
        BigInteger mMNode3Start = mMNode2.startingAddr.add(mMNode2.size); // mMNode2.start + mMNode2.size
        BigInteger toInsertEnd = toInsert.startingAddr.add(toInsert.size).subtract(new BigInteger("1"));// toInsert.start
                                                                                                        // +
                                                                                                        // toInsert.size
                                                                                                        // - 1
        if (mMNode3Start.compareTo(toInsertEnd) == -1) { // <: if mMNode3 exist
            //// update in memMap
            MemMapNode mMNode3 = new MemMapNode(mMNode3Start,
                    toInsertEnd.subtract(mMNode3Start).add(new BigInteger("1")), false); // update in memMap, size =
                                                                                         // toInsertEnd - mMNode3Start +
                                                                                         // 1
            memMap.insert(mMNode2, mMNode3);

            //// update in htOfAddr
            htOfAddr.put(mMNode3Start, mMNode3);

            //// update in htOfFreeSize
            htOfFreeSize.put(mMNode3.size, mMNode3);    // mMNode3 must be free
            // no need to update maxBlockSize, since it is a sub block of toInsert
        }

        /// delete toInsert
        //// update in memMap
        memMap.delete(toInsert);

        //// update in htOfAddr
        htOfAddr.remove(toInsert.startingAddr, toInsert);

        //// update in htOfFreeSize
        htOfFreeSize.remove(toInsert.size, toInsert);
        // Debug.printFileNameAndLineNumber();
        if (toInsert.size == maxBlockSize) {
            maxBlockSize = htOfFreeSize.getMaxBlockSize();
        }

        // testing
        Debug.dbgPrint("request done, the current structure:");
        print3Tables();

        // return address
        // Debug.dbgPrint("the returned value is " + op.getAddr().intValue());
        return op.getAddr().intValue();
        
    }

    public boolean release(MemoryOperation op) {
        // TODO
        // Accepts a space release and release memory
        // Return true if the memory is released successfully, otherwise return false

        // check address in range
        if(op.getAddr().compareTo(new BigInteger("0")) == -1 || op.getAddr().compareTo(TOTAL_BYTES.subtract(new BigInteger("1"))) == 1) {return false;}        // < 0 or > max - 1

        // find the current block
        MemMapNode currMemMapNode = htOfAddr.getPredKey(op.getAddr());
        
        // if current block is free and all of target block is inside current block, return false
        BigInteger currMMNodeEnd = currMemMapNode.startingAddr.add(currMemMapNode.size).subtract(new BigInteger("1"));
        BigInteger tarEndAddr = op.getAddr().add(op.getSize()).subtract(new BigInteger("1"));
        if(!currMemMapNode.isOccupied && currMMNodeEnd.compareTo(tarEndAddr) == 1) {
            Debug.dbgPrint("invalid operation");
            return false;
        }
        if(op.getAddr().add(op.getSize()).compareTo(MemMap.maxSize) == 1) {
            Debug.dbgPrint("invalid operation: release out of bounds");
            return false;
        }

        if(newReleaseMode) {
            // added: new version of checking valid: from currMemMapNode to last MemMapNode should all be allocated
            MemMapNode testingCurr = currMemMapNode;
            BigInteger testingCurrEnd = currMMNodeEnd;
            while(testingCurrEnd.compareTo(tarEndAddr) == -1) {  // currMMNend < tarEnd: not over yet
                // check
                if(!testingCurr.isOccupied) {
                    Debug.dbgPrint("invalid operation: conflict current rule");
                    return false;
                }

                testingCurr = testingCurr.nextNode;
                testingCurrEnd = testingCurr.startingAddr.add(testingCurr.size).subtract(new BigInteger("1"));
            }
        }


        // check whole target block and get (N1stt, N1end) -> (N2stt, N2end) -> (N3stt, N3end)
        BigInteger N1stt, N1end, N2stt, N2end, N3stt, N3end;
        if(currMemMapNode.isOccupied) {     // if the start address is in the occupied block
            N1stt = currMemMapNode.startingAddr;
            N1end = op.getAddr().subtract(new BigInteger("1"));
            N2stt = op.getAddr();
        }
        else {  // if the start address is in free block
            N1stt = N1end = N2stt = currMemMapNode.startingAddr;
        }

        // loop through the blocks overlapping with target block and delete them
        MemMapNode prev = currMemMapNode.prevNode;      // for inserting N1, N2, N3
        while(currMMNodeEnd.compareTo(tarEndAddr) == -1) {  // currMMNend < tarEnd: not over yet
            // delete this MemMapNode
            memMap.delete(currMemMapNode);

            // update htOfAddr
            htOfAddr.remove(currMemMapNode.startingAddr, currMemMapNode);

            // update hTofSize and maxSize
            if(!currMemMapNode.isOccupied) {
                htOfFreeSize.remove(currMemMapNode.size, currMemMapNode);
                if(currMemMapNode.size.compareTo(maxBlockSize) == 0) {     
                    maxBlockSize = htOfFreeSize.getMaxBlockSize();
                }
            }
            
            // update

            currMemMapNode = currMemMapNode.nextNode;
            currMMNodeEnd = currMemMapNode.startingAddr.add(currMemMapNode.size).subtract(new BigInteger("1"));
        }
        // delete this MemMapNode
        // Debug.dbgPrint("want to delete node with starting add: " + currMemMapNode.startingAddr + " now the table is: "); print3Tables();
        // memMap.delete(currMemMapNode);      // delete it at last
        // update htOfAddr
        htOfAddr.remove(currMemMapNode.startingAddr, currMemMapNode);
        // update hTofSize and maxSize
        if(!currMemMapNode.isOccupied) {
            htOfFreeSize.remove(currMemMapNode.size, currMemMapNode);
            if(currMemMapNode.size.compareTo(maxBlockSize) == 0) {     
                maxBlockSize = htOfFreeSize.getMaxBlockSize();
            }
        }

        // get N2end, N3stt, N3end
        if(currMemMapNode.isOccupied) {
            N2end = tarEndAddr;
            N3stt = tarEndAddr.add(new BigInteger("1"));
            N3end = currMMNodeEnd;
        }
        else {      // the memMapNode is free, then no N3
            N2end = N3end = N3stt = currMMNodeEnd;
        }

        // Debug.dbgPrint("(N1stt, N1end) -> (N2stt, N2end) -> (N3stt, N3end): " + "(" + N1stt +","+ N1end+") -> ("+N2stt+","+ N2end+") -> ("+N3stt+","+ N3end+")");   // correct



        // insert N1, N2, N3 after prev (if prev is null than insert in the first node)
        /// insert N2
        MemMapNode n2 = new MemMapNode(N2stt, N2end.subtract(N2stt).add(new BigInteger("1")), false);
        memMap.insert(prev, n2);
        // Debug.dbgPrint("n2 inserted");
        // update 2 hT (n2 must be free)
        htOfAddr.put(n2.startingAddr, n2);
        htOfFreeSize.put(n2.size, n2);      // n1 must be alloc
        if(n2.size.compareTo(maxBlockSize) == 1) {
            maxBlockSize = n2.size;
        }
    

        boolean frontMergeFlag = true;
        boolean backMergeFlag = true;

        /// if exist, insert N1
        if(N1stt.compareTo(N1end) == -1) {
            MemMapNode n1 = new MemMapNode(N1stt, N1end.subtract(N1stt).add(new BigInteger("1")), true);
            memMap.insert(prev, n1);
            // update 2 hT
            htOfAddr.put(n1.startingAddr, n1);

            Debug.printFileNameAndLineNumber();
            frontMergeFlag = false;     // there is an allocated block, so no need to merge
        }

        /// if exist, insert N3
        if(N3stt.compareTo(N3end) == -1) {
            MemMapNode n3 = new MemMapNode(N3stt, N3end.subtract(N3stt).add(new BigInteger("1")), true);
            memMap.insert(n2, n3);
            // update 2 hT
            htOfAddr.put(n3.startingAddr, n3);
            Debug.dbgPrint("N3stt" + N3stt + " N3end " + N3end);
            Debug.printFileNameAndLineNumber();
            backMergeFlag = false;     // there is an allocated block, so no need to merge
        }

        memMap.delete(currMemMapNode);      // delete it at last

        Debug.dbgPrint("backMergeFlag " +  frontMergeFlag + " n2.prevNode " + n2.prevNode + "n2.prevNode.isOccupied" + n2.prevNode.isOccupied);
        // check if consecutive node, if yes, merge
        if(backMergeFlag && n2.nextNode != null &&  !n2.nextNode.isOccupied) {      // need to merge back
            MemMapNode back = n2.nextNode;
            // delete back and n2 in 2 hash tables
            htOfAddr.remove(back.startingAddr, back);
            htOfFreeSize.remove(back.size, back);
            htOfAddr.remove(n2.startingAddr, n2);
            htOfFreeSize.remove(n2.size, n2);

            // merge
            memMap.merge(n2);

            // update n2 in hash table
            htOfAddr.put(n2.startingAddr, n2);
            htOfFreeSize.put(n2.size, n2);

            // update maxSize
            maxBlockSize = htOfFreeSize.getMaxBlockSize();

        }
        
        if(frontMergeFlag && n2.prevNode != null &&  !n2.prevNode.isOccupied) {     // need to merge front
            MemMapNode front = n2.prevNode;

            // delete front and n2 in 2 hash tables
            htOfAddr.remove(front.startingAddr, front);
            htOfFreeSize.remove(front.size, front);
            htOfAddr.remove(n2.startingAddr, n2);
            htOfFreeSize.remove(n2.size, n2);

            // merge front
            memMap.merge(front);

            // update front in hash table
            htOfAddr.put(front.startingAddr, front);
            htOfFreeSize.put(front.size, front);

            // update maxBlockSize
            maxBlockSize = htOfFreeSize.getMaxBlockSize();
        }



        print3Tables();

        return true;
    }

    /**
     * if debug mode is on, it will print the 3 tables and part of the anchor points
     */
    void print3Tables() {
        if(!Debug.isDebugging) return;
        
        // print mem map
        System.out.println("memMap: (start, size, occupation status, end)");
        memMap.printMemMap();
        System.out.println();

        System.out.print("\nhtOfAddr: (starting addr, starting addr)");
        htOfAddr.dump();

        System.out.print("\nhtOfFreeSize: (size, starting address)");
        htOfFreeSize.dump();
        System.out.println("with max block size:" + maxBlockSize + "\n");

        System.out.println("part of anchors in address-startingAddr: ");
        for(int i = 0; i < htOfAddr.anchor.length; i += 50 ) {
            System.out.print(htOfAddr.anchorDist.multiply(new BigInteger(String.valueOf(i))) +"-" + htOfAddr.anchor[i] +" ");      // address-Node
        }
        System.out.println("\n\n\n");
    }
}
