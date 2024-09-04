package csci2100;

import java.math.BigInteger;

// already done, each MemoryOperation object is an operation, either request or release. Also contains other details

public class MemoryOperation {
    private MemoryOperationType opType;
    private Integer addr;
    private Integer size;
    public enum MemoryOperationType {
        REQUEST,
        RELEASE;
    }

    public MemoryOperationType getOpType() {
        return opType;
    }

    public BigInteger getAddr() {
        if(addr != null)
            return new BigInteger(Integer.toString(addr));
        
        return null;
    }

    public BigInteger getSize() {
        return new BigInteger(Integer.toString(size));
    }

    public void setAddr(BigInteger addrToBeSet) {
        addr = addrToBeSet.intValue();
    }

    public MemoryOperation(MemoryOperationType opType, Integer addr, Integer size) {
        if (opType == MemoryOperationType.REQUEST) {
            assert size != null : "The parameter `size` must be given in a REQUEST operation.";
        } else if (opType == MemoryOperationType.RELEASE) {
            assert size != null : "The parameter `size` must be given in a RELEASE operation.";
            assert addr != null : "The parameter `addr` must be given in a RELEASE operation.";
        } else {
            assert false : "Invalid operation type.";
        }
        this.opType = opType;
        this.addr = addr;
        this.size = size;
    }

    public String toString() {
        return "MemoryOperation: opType=" + opType + ", addr=" + addr + ", size=" + size + ".";
    }
}
