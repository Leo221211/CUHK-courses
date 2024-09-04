#ifndef MEMORYOPERATION_H
#define MEMORYOPERATION_H
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
#pragma once

// Enum class to represent the memory operation type
enum class MemoryOperationType {
    REQUEST = 0,
    RELEASE = 1
};

// Class to represent a memory operation
class MemoryOperation {
private:
    MemoryOperationType op_type;
    int addr;  // can use a suitable data type based on address range
    int size;

public:
    MemoryOperation(MemoryOperationType opType, int address = -1, int s = -1) : op_type(opType), addr(address), size(s) {
        // Ensure the correct parameters are provided based on the operation type
        if (op_type == MemoryOperationType::REQUEST) {
            assert(size != -1 && "The parameter `size` must be given in a REQUEST operation.");
        } else if (op_type == MemoryOperationType::RELEASE) {
            assert(size != -1 && "The parameter `size` must be given in a RELEASE operation.");
            assert(addr != -1 && "The parameter `addr` must be given in a RELEASE operation.");
        } else {
            assert(false && "Invalid operation type.");
        }
    }

    // Getter functions, if needed
    MemoryOperationType getOpType() const { return op_type; }
    int getAddr() const { return addr; }
    int getSize() const { return size; }

    string toString() const {
        ostringstream oss;
        oss << "MemoryOperation: op_type=" << static_cast<int>(op_type) << ", addr=" << addr << ", size=" << size << ".";
        return oss.str();
    }
};

#endif // MEMORYOPERATION_H
