package otherfiles;

import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Map;

import csci2100.MemoryManager;
import csci2100.MemoryOperation;
import csci2100.Test;
import csci2100.MemoryManager.MemoryStrategy;
import csci2100.MemoryOperation.MemoryOperationType;

public class Test3 {
    private final MemoryManager memoryManager;

    public Test3(MemoryManager memoryManager) {
        this.memoryManager = memoryManager;
    }

    public void basicTestOn(String testFilePath) {
        Map<MemoryOperation, Integer> testCases = readOperationsFromFile(testFilePath);     // test case are all the data in the file
        System.out.println("Start test on " + testFilePath + ".");

        // check if valid
        for (Map.Entry<MemoryOperation, Integer> entry : testCases.entrySet()) {        // entry is each command of the test case
            MemoryOperation memoryOperation = entry.getKey();
            Integer expectedAddr = entry.getValue();
            if (MemoryOperation.MemoryOperationType.REQUEST.equals(memoryOperation.getOpType()) ) {     // for this command if it is request
                // Debug.dbgPrint("\n\n\n\n\nrequest for address: " + memoryOperation.getAddr() + " size: " + memoryOperation.getSize());
                System.out.println("\n\nrequst for address: " + memoryOperation.getAddr() + " size: " + memoryOperation.getSize());
                Integer ret = this.memoryManager.request(memoryOperation);                              // perform request and get the return value
                if (expectedAddr != null) {                                                             // if it has expected address
                    assert ret.equals(expectedAddr) :                                                   // return must equal to expectedAddr
                            "Test failed at the case [" + memoryOperation + "]. \n" +
                                    "\t > Expected allocated address is `" + expectedAddr + "`, \n" +
                                    "\t > but got `" + ret + "`.";
                }
            } else if (memoryOperation.getOpType() == MemoryOperation.MemoryOperationType.RELEASE) {     // if command is release
                // Debug.dbgPrint("\n\n\n\n\n\nrelease for address: " + memoryOperation.getAddr() + " size: " + memoryOperation.getSize());
                System.out.println("\n\nrelease for address: " + memoryOperation.getAddr() + " size: " + memoryOperation.getSize());
                this.memoryManager.release(memoryOperation);                                             // perform release
            }
        }

        System.out.println("All test passed for " + testFilePath + ".");
    }

    private Map<MemoryOperation, Integer> readOperationsFromFile(String filePath) {                         // read all entries in the csv to a file
        Map<MemoryOperation, Integer> memoryOperations = new HashMap<>();

        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = reader.readLine()) != null) {
                line = line.trim();
                if (line.isEmpty()) {
                    continue;
                }

                // csv is with structure: optype (1 request 0 release); size, addr, expected add
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
        MemoryManager memoryManagerToTest = new MemoryManager(MemoryManager.MemoryStrategy.FIRST_FIT);

        // Pass your `MemoryManager` implementation instance to the `Test` class.
        Test test = new Test(memoryManagerToTest);
        // test.basicTestOn("Data/test_initialization_operations.csv");
        // test.basicTestOn("Data/test_operations_set_1.csv");
        test.basicTestOn("../Data/test_initialization_operations.csv");
        test.basicTestOn("../Data/test_operations_set_1.csv");
        // test.basicTestOn("Data/my_test_insert.csv");
        // test.basicTestOn("Data/my_test_del.csv");
        // test.basicTestOn("Data/my_test.csv");
    }
}
