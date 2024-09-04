#include "MemoryManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

std::vector<std::pair<MemoryOperation, int> > readOperationsFromFile(const std::string& filePath);

class TestContext {
public:
    TestContext(MemoryManager& memoryManager);
    void basicTestOn(const std::string& testFilePath);

private:
    MemoryManager& memoryManager;
};

std::vector<std::pair<MemoryOperation, int> > readOperationsFromFile(const std::string& filePath) {
    std::vector<std::pair<MemoryOperation, int> > memoryOperations;
    std::ifstream inputFile(filePath);
    std::string line;

    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            continue;
        }
        std::replace(line.begin(), line.end(), ',', ' '); // replace commas with space for easy parsing
        std::istringstream lineStream(line);

        int opTypeInt, size = -1, addr = -1, expectedAddr = -1;
        lineStream >> opTypeInt >> size >> addr >> expectedAddr;

        MemoryOperationType opType = (opTypeInt == 1) ? MemoryOperationType::REQUEST : MemoryOperationType::RELEASE;
        MemoryOperation operation(opType, addr, size);
        
        memoryOperations.push_back(std::make_pair(operation, expectedAddr));
    }

    inputFile.close();
    return memoryOperations;
}

TestContext::TestContext(MemoryManager& memoryManager) : memoryManager(memoryManager) {}

void TestContext::basicTestOn(const std::string& testFilePath) {
    auto testCases = readOperationsFromFile(testFilePath);
    std::cout << "Start test on " << testFilePath << ".\n";

    for (const auto& testCase : testCases) {
        const MemoryOperation& op = testCase.first;
        int expectedAddr = testCase.second;

        if (op.getOpType() == MemoryOperationType::REQUEST) {
            int ret = memoryManager.request(op);
            if (expectedAddr != -1) {
                if (ret != expectedAddr) {
                    std::cerr << "Test failed at the case [" << op.toString() << "]."
                              << "\n\t > Expected allocated address is `" << expectedAddr
                              << "`, \n\t > but got `" << ret << "`.\n";
                    exit(EXIT_FAILURE); // terminate if a test case fails
                }
            }
        } else if (op.getOpType() == MemoryOperationType::RELEASE) {
            memoryManager.release(op);
        }
    }

    std::cout << "All tests passed for " << testFilePath << ".\n";
}

int main() {
    // This test code is only for you to debug the basic implementation of MemoryManager.
    // Please note that these are not final test cases for assessment.
    MemoryManager memoryManager(MemoryStrategy::BEST_FIT);
    // Pass your `MemoryManager` implementation instance to the `TestContext` class.
    TestContext testContext(memoryManager);
    testContext.basicTestOn("../Data/test_initialization_operations.csv");
    testContext.basicTestOn("../Data/test_operations_set_1.csv");
}