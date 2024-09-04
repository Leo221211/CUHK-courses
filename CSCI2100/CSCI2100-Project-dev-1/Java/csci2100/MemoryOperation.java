package csci2100;


public class MemoryOperation {
    private final MemoryOperationType opType;
    private final Integer addr;
    private final Integer size;
    public enum MemoryOperationType {
        REQUEST,
        RELEASE;
    }

    public MemoryOperationType getOpType() {
        return opType;
    }

    public Integer getAddr() {
        return addr;
    }

    public Integer getSize() {
        return size;
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
