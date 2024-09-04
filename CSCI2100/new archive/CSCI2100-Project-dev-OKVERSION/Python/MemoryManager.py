import enum

from MemoryOperation import MemoryOperation


class MemoryStrategy(enum.Enum):
    FIRST_FIT = 0
    BEST_FIT = 1
    WORST_FIT = 2


class MemoryManager:

    def __init__(self, strategy: MemoryStrategy) -> None:
        self.strategy = strategy
        # TODO:
        #  Initialize the hash tables for memory storage.
        #  Do not need to return anything.
        pass

    def request(self, op: MemoryOperation) -> int:
        # TODO:
        #  Accepts a space request (of a specified number of bytes that may include an optional starting byte address),
        #   and allocate memory.
        #  If the memory is not available (is occupied already), the request should not be accepted.
        #  Remember to allocate the memory according to current strategy (self.strategy) unless the address is given.
        #  Return the allocated address if the memory is allocated successfully.
        #  Otherwise, return -1.
        pass

    def release(self, op: MemoryOperation) -> bool:
        # TODO:
        #  Accepts a space release (with a defined starting byte address and its corresponding number of bytes),
        #   and release memory.
        #  Return True if the memory is released successfully.
        #  Otherwise, return False.
        pass

    def is_valid_op(self, op: MemoryOperation) -> bool:
        # TODO: return if the given memory operation is valid for current memory.
        #  If the operation is a REQUEST operation,
        #   then return True if the memory block(s) it request is/are available, otherwise return False.
        #  If the operation is a RELEASE operation,
        #   then return True if the memory block(s) is already occupied (allocated), otherwise return False.
        pass
