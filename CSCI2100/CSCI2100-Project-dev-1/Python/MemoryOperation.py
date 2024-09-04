import enum


class MemoryOperationType(enum.Enum):
    REQUEST = 0
    RELEASE = 1


class MemoryOperation:
    def __init__(self, op_type: MemoryOperationType, addr: int = None, size: int = None):
        if op_type == MemoryOperationType.REQUEST:
            assert size is not None, "The parameter `size` must be given in a REQUEST operation."
        elif op_type == MemoryOperationType.RELEASE:
            assert size is not None, "The parameter `size` must be given in a RELEASE operation."
            assert addr is not None, "The parameter `addr` must be given in a RELEASE operation."
        else:
            assert False, "Invalid operation type."
        self.addr = addr
        self.size = size
        self.op_type = op_type

    def __str__(self):
        return f"MemoryOperation: op_type={self.op_type}, addr={self.addr}, size={self.size}."

