from MemoryManager import MemoryManager, MemoryStrategy
from MemoryOperation import MemoryOperation, MemoryOperationType


def read_operations_from_file(file_path):
    input_file = open(file_path, mode='r')
    memory_operations = []
    for line in input_file.readlines():
        line = line.strip()
        if line == "":
            continue
        str_op = line.replace("\n", "").replace("\r", "").replace(" ", "").split(",")
        op_type_int = int(str_op[0])
        size = None if str_op[1] == "" else int(str_op[1])
        addr = None if str_op[2] == "" else int(str_op[2])
        if len(str_op) > 3:
            expected_addr = None if str_op[3] == "" else int(str_op[3])
        else:
            expected_addr = None
        memory_operations.append({
            "op": MemoryOperation(
                op_type=MemoryOperationType.REQUEST if op_type_int == 1 else MemoryOperationType.RELEASE,
                addr=addr, size=size),
            "expected_addr": expected_addr})
    input_file.close()
    return memory_operations


class TestContext:
    def __init__(self, memory_manager):
        self.memory_manager = memory_manager

    def basic_test_on(self, test_file_path):
        test_cases = read_operations_from_file(test_file_path)
        print(f"Start test on {test_file_path}.")
        for test_case in test_cases:
            if test_case["op"].op_type == MemoryOperationType.REQUEST:
                ret = self.memory_manager.request(test_case["op"])
                if test_case["expected_addr"] is not None:
                    assert ret == test_case["expected_addr"], \
                        f"Test failed at the case [{test_case['op']}]. \n" \
                        f"\t > Expected allocated address is `{test_case['expected_addr']}`, \n" \
                        f"\t > but got `{ret}`."
            elif test_case["op"].op_type == MemoryOperationType.RELEASE:
                self.memory_manager.release(test_case["op"])
        print(f"All test passed for {test_file_path}.")


if __name__ == "__main__":
    # This test code is only for you to debug the basic implementation of MemoryManager.
    # Please note that these are not final test cases for assessment.
    memory_manager_to_test = MemoryManager(strategy=MemoryStrategy.BEST_FIT)
    # Pass your `MemoryManager` implementation instance to the `TestContext` class.
    test_context = TestContext(memory_manager=memory_manager_to_test)
    test_context.basic_test_on("../Data/test_initialization_operations.csv")
    test_context.basic_test_on("../Data/test_operations_set_1.csv")
