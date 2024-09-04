package csci2100;

import java.util.*;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Test {
    private final MemoryManager memoryManager;

    public Test(MemoryManager memoryManager) {
        this.memoryManager = memoryManager;
    }

    public void basicTestOn(String testFilePath) {
        Map<MemoryOperation, Integer> testCases = readOperationsFromFile(testFilePath);
        System.out.println("Start test on " + testFilePath + ".");

        for (Map.Entry<MemoryOperation, Integer> entry : testCases.entrySet()) {
            System.out.println(entry.getKey());
            MemoryOperation memoryOperation = entry.getKey();
            Integer expectedAddr = entry.getValue();
            if (MemoryOperation.MemoryOperationType.REQUEST.equals(memoryOperation.getOpType()) ) {
                // System.out.println("\n\nrequst for address: " + memoryOperation.getAddr() + " size: " + memoryOperation.getSize());
                Integer ret = this.memoryManager.request(memoryOperation);
                if (expectedAddr != null) {
                    assert ret.equals(expectedAddr) :
                            "Test failed at the case [" + memoryOperation + "]. \n" +
                                    "\t > Expected allocated address is `" + expectedAddr + "`, \n" +
                                    "\t > but got `" + ret + "`.";
                }
            } else if (memoryOperation.getOpType() == MemoryOperation.MemoryOperationType.RELEASE) {
                // System.out.println("\n\nrelease for address: " + memoryOperation.getAddr() + " size: " + memoryOperation.getSize());
                this.memoryManager.release(memoryOperation);
            }
        }

        System.out.println("All test passed for " + testFilePath + ".");
    }

    private Map<MemoryOperation, Integer> readOperationsFromFile(String filePath) {
        Map<MemoryOperation, Integer> memoryOperations = new LinkedHashMap<>();

        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = reader.readLine()) != null) {
                line = line.trim();
                if (line.isEmpty()) {
                    continue;
                }

                String[] strOp = line.replaceAll("\\n", "").replaceAll("\\r", "").replaceAll(" ", "").split(",");
                int opTypeInt = Integer.parseInt(strOp[0]);
                Integer size = strOp[1].isEmpty() ? null : Integer.parseInt(strOp[1]);
                Integer addr = strOp[2].isEmpty() ? null : Integer.parseInt(strOp[2]);
                Integer expectedAddr = strOp.length > 3 && !strOp[3].isEmpty() ? Integer.parseInt(strOp[3]) : null;
                memoryOperations.put(new MemoryOperation(
                                opTypeInt == 1 ? MemoryOperation.MemoryOperationType.REQUEST : MemoryOperation.MemoryOperationType.RELEASE,
                                addr,
                                size),
                        expectedAddr);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        return memoryOperations;
    }

    public static void main(String[] args) {
        // This test code is only for you to debug the basic implementation of MemoryManager.
        // Please note that these are not final test cases for assessment.
        MemoryManager memoryManagerToTest = new MemoryManager(MemoryManager.MemoryStrategy.BEST_FIT);
        String currentDirectory = System.getProperty("user.dir");
        System.out.println(currentDirectory);
        // Pass your `MemoryManager` implementation instance to the `Test` class.
        Test test = new Test(memoryManagerToTest);

        // test.basicTestOn("../Data/test_operations_set_1.csv");
        // test.basicTestOn("../Data/WORST_FIT.csv");
        test.basicTestOn("../Data/BEST_FIT.csv");
        // test.basicTestOn("../Data/ERRONEOUS_ALLOCATION_BEST_FIT.csv");
        // test.basicTestOn("../Data/FIRST_FIT.csv");
        
        // test.basicTestOn("../Data/my_test.csv");
    }
}