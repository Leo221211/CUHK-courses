package memorg;

import java.util.Hashtable;

public class MemoryManager {
    public enum MemoryStrategy {
        FIRST_FIT,
        BEST_FIT,
        WORST_FIT;
    }

    private MemoryStrategy strategy;

    public MemoryManager(MemoryStrategy strategy) {
        this.strategy = strategy;
        // TODO
        // Initialize the hash tables for memory storage.
        // Do not need to return anything.
    }

    public int request(MemoryOperation op) {
        // TODO
        // Accepts a space request and allocate memory
        // If the memory is not available, the request should not be accepted
        // Allocate the memory according to the current strategy unless the address is given
        // Return the allocated address if the memory is allocated successfully, otherwise return -1
        return -1;
    }

    public boolean release(MemoryOperation op) {
        // TODO
        // Accepts a space release and release memory
        // Return true if the memory is released successfully, otherwise return false
        return false;
    }

    public boolean isValidOp(MemoryOperation op) {
        // TODO
        // Return if the given memory operation is valid for current memory
        // If the operation is a REQUEST operation, return true if the memory block(s) it request is/are available, otherwise return false
        // If the operation is a RELEASE operation, return true if the memory block(s) is already occupied (allocated), otherwise return false
        return false;
    }
}
