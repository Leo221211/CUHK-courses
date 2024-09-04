package csci2100;

import java.math.BigInteger;
import java.util.Hashtable;
import csci2100.MemMap.MemMapNode;



public class MemoryManager_linear_version { 

    public enum MemoryStrategy {
        FIRST_FIT,
        BEST_FIT,
        WORST_FIT;
    }

    private MemoryStrategy strategy;

    public final BigInteger TOTAL_BYTES = new BigInteger("4294967296");   // 4GB = 4*1024*1024*1024 Bytes

    MemMap memMap;
    HashTable hTofSize, hTofAddr;
    BigInteger maxBlockSize;

    // constructor
    public MemoryManager_linear_version(MemoryStrategy strategy) {
        this.strategy = strategy;
        // TODO
        // Initialize the hash tables for memory storage.
        // int[] initValues = new int[99];
        //  HashTable<int> ht = new HashTable<int>(initValues);
        // HashTable<Integer> ht = new HashTable<Integer>(initValues);
        // Do not need to return anything.

        // init memMap
        memMap = new MemMap(TOTAL_BYTES);       // new memMap, first free node already init
        // memMap.insert(null, new MemMapNode(new BigInteger("0"), TOTAL_BYTES, false));      // initially, there is only 1 free node in the memMap

        // init hTofSize: 1 free block and a max size
        hTofSize = new HashTable();
        hTofSize.put(TOTAL_BYTES, memMap.firstNode);        // initially, only 1 free node
        maxBlockSize = TOTAL_BYTES;                                        // maxBlockSize

        // init hTofSAddr
        hTofAddr = new HashTable();
        hTofAddr.put(new BigInteger("0"), memMap.firstNode);            // initially only 1 node

        // testing: print out the 3 structures
        System.out.println("Init finished, current status:");
        print3Tables();
    }

    public int request(MemoryOperation op) {
        // TODO
        // Accepts a space request and allocate memory
        // If the memory is not available, the request should not be accepted
        // Allocate the memory according to the current strategy unless the address is given
        // Return the allocated address if the memory is allocated successfully, otherwise return -1

        MemMapNode toInsert = memMap.firstNode;
        // Debug.printFileNameAndLineNumber();

        // request without size: find the valid memMapNode (or else return -1)
        // for this kind of search, the address returned must be the first address of a memMap block
        if(op.getAddr() == null) {

            switch (strategy) {

                case FIRST_FIT:
                    // Debug.printFileNameAndLineNumber();
                    // linearly search by hash table to find the first available address
                    BigInteger currAddr = new BigInteger("0");
                    MemMapNode currMemMapNode = (MemMapNode) hTofAddr.get(currAddr);
                    while(true) {     // loop through the table
                        if (currMemMapNode == null) {return -1;}        // already finished looping, can't find any valid address

                        if(currMemMapNode.size.compareTo(op.getSize()) !=  -1) {    // if size bigger or equals to the request size: found the one
                            op.setAddr(currAddr);
                            toInsert = currMemMapNode;
                            break;
                        }


                        currAddr = currAddr.add(currMemMapNode.size);
                        currMemMapNode = (MemMapNode) hTofAddr.get(currAddr);
                    } 


                    // Debug.dbgPrint("curr addr: " + currAddr);
                    break;
            
                case BEST_FIT:
                    // search in the size hash table to get the the address with the best size (or return invalid)
                    boolean notFoundFlagBF = true;
                    for(BigInteger i = op.getSize(); i.compareTo(maxBlockSize) != 1/* i <= max*/; i = i.add(new BigInteger("1"))) {      // getSize to maxSize
                        MemMapNode nodeFound = (MemMapNode)hTofSize.get(i);
                        if(nodeFound != null) {   // found the node

                            op.setAddr(nodeFound.startingAddr);
                            toInsert = nodeFound;
                            notFoundFlagBF = false;
                            break;
                        }
                    }

                    if(notFoundFlagBF) {return -1;}       // not found in the end
                    break;

                default:    // Worst fit
                    // return the address of the max size: the backward search of BestFit
                    boolean notFoundFlagWF = true;
                    for(BigInteger i = maxBlockSize; i.compareTo(op.getSize()) != -1/* i >= intended size */; i = i.add(new BigInteger("-1"))) {      //  maxSize to getSize()
                        MemMapNode nodeFound = (MemMapNode)hTofSize.get(i);
                        if(nodeFound != null) {   // found the node
                            op.setAddr(nodeFound.startingAddr);
                            toInsert = nodeFound;
                            notFoundFlagWF = false;
                            break;
                        }
                    }

                    if(notFoundFlagWF) {return -1;}       // not found in the end
                    break;
            }
        }

        // request with address: find the valid memMapNode or else return -1
        else{
            System.out.println("not supported so far");
            System.exit(0);
        }

        // Debug.printFileNameAndLineNumber();
        // insert by updating 3 structures, and return the inserted address

        /// mMNode2: the requested block
        //// update in memMap  
        MemMapNode mMNode2 = new MemMapNode(op.getAddr(), op.getSize(), true);           
        memMap.insert(toInsert, mMNode2);

        //// update in hTofAddr
        hTofAddr.put(mMNode2.startingAddr, mMNode2);

        //// update in hTofSize
        hTofSize.put(mMNode2.size, mMNode2);
        // no need to update maxBlockSize, since it is a sub block of toInsert


        /// mMNode1: the part of block before requested block
        
        if (toInsert.startingAddr.compareTo(op.getAddr()) == -1) {   // startingAddr < request address: there is mMNode1
            //// update in memMap                    
            MemMapNode mMNode1 = new MemMapNode(toInsert.startingAddr, op.getAddr().subtract(toInsert.startingAddr), false);    // update in memMap
            memMap.insert(mMNode1, toInsert);

            //// update in hTofAddr
            hTofAddr.put(toInsert.startingAddr, mMNode1);

            //// update in hTofSize
            hTofSize.put(mMNode1.size, mMNode1);
            // no need to update maxBlockSize, since it is a sub block of toInsert
        }


        /// mMNode3: the part of block after requested block
        BigInteger mMNode3Start = mMNode2.startingAddr.add(mMNode2.size); // mMNode2.start + mMNode2.size
        BigInteger toInsertEnd = toInsert.startingAddr.add(toInsert.size).subtract(new BigInteger("1"));// toInsert.start + toInsert.size - 1
        if (mMNode3Start.compareTo(toInsertEnd) == -1) {   // <: if mMNode3 exist   
            //// update in memMap                     
            MemMapNode mMNode3 = new MemMapNode(mMNode3Start, toInsertEnd.subtract(mMNode3Start).add(new BigInteger("1")), false);    // update in memMap, size = toInsertEnd - mMNode3Start + 1
            memMap.insert(mMNode2, mMNode3);   

            //// update in hTofAddr
            hTofAddr.put(mMNode3Start, mMNode3);

            //// update in hTofSize
            hTofSize.put(mMNode3.size, mMNode3);
            // no need to update maxBlockSize, since it is a sub block of toInsert
        }


        /// delete toInsert
        //// update in memMap
        memMap.delete(toInsert);

        //// update in hTofAddr
        hTofAddr.remove(toInsert.startingAddr, toInsert);

        //// update in hTofSize
        hTofSize.remove(toInsert.size, toInsert);
        // Debug.printFileNameAndLineNumber();
        if(toInsert.size == maxBlockSize) {     // backward search until find the new max block size
            for(BigInteger tempSize = maxBlockSize; tempSize.compareTo(new BigInteger("0")) == 1 /*tempSize > 0*/; tempSize = tempSize.subtract(new BigInteger("1"))) {
                // Debug.dbgPrint("tempSize: " + tempSize);
                if(hTofSize.containsKey(tempSize)) {
                    maxBlockSize = tempSize;
                    break;
                }
            }
        }

        // testing
        System.out.println("request done, the current structure:");
        print3Tables();

        // return address
        return op.getAddr().intValue();       
    }

    public boolean release(MemoryOperation op) {
        // TODO
        // Accepts a space release and release memory
        // Return true if the memory is released successfully, otherwise return false
        return false;
    }

    /**
     * for release and request(with address): use this function to check if it is valid
     * @param op
     * @return
     */
    public boolean isValidOp(MemoryOperation op) {
        // TODO
        // Return if the given memory operation is valid for current memory
        // If the operation is a REQUEST operation, return true if the memory block(s) it request is/are available, otherwise return false
        // If the operation is a RELEASE operation, return true if the memory block(s) is already occupied (allocated), otherwise return false
        return false;
    }

    /**
     * test only
     */
    void print3Tables() {
        // print mem map
        System.out.println("memMap: (addr, size, occupation status)");
        memMap.printMemMap();
        System.out.println();

        System.out.print("\nhTofAddr: (starting addr, memMapAddr)");
        hTofAddr.dump();

        System.out.print("\nhTofSize: (size, memMapAddr)");
        hTofSize.dump();
        System.out.println("with max block size:" + maxBlockSize + "\n");
    }

    public static void main(String[] args) {
        // init 
        MemoryManager_linear_version memManager = new MemoryManager_linear_version(MemoryStrategy.FIRST_FIT);
    }
}
