#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include "MemoryOperation.h"
#include <vector>

enum class MemoryStrategy {
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT
};

class MemoryManager {
public:
    MemoryManager(MemoryStrategy strategy){
        // TODO:
        // Initialize the hash tables for memory storage.
        // Do not need to return anything.
    }
    int request(const MemoryOperation& op){
        return -1; // placeholder return for now
        // TODO:
        // Accepts a space request (of a specified number of bytes that may include an optional starting byte address),
        // and allocate memory.
        // If the memory is not available (is occupied already), the request should not be accepted.
        // Remember to allocate the memory according to current strategy (self.strategy) unless the address is given.
        // Return the allocated address if the memory is allocated successfully.
        // Otherwise, return -1.
    }
    bool release(const MemoryOperation& op){
        return false; // placeholder return for now
        // TODO:
        // Accepts a space release (with a defined starting byte address and its corresponding number of bytes),
        // and release memory.
        // Return True if the memory is released successfully.
        // Otherwise, return False.
    }
    bool isValidOp(const MemoryOperation& op){
        // TODO: return if the given memory operation is valid for current memory.
        // If the operation is a REQUEST operation,
        // then return True if the memory block(s) it request is/are available, otherwise return False.
        // If the operation is a RELEASE operation,
        // then return True if the memory block(s) is already occupied (allocated), otherwise return False.
    }

private:
    MemoryStrategy strategy;
    // TODO: Declare internal data structures and helper methods for memory management.
};

#endif // MEMORYMANAGER_H
