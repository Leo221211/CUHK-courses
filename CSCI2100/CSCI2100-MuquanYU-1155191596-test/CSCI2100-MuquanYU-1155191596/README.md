## NOTE
(1) Modify the total size of the memory by editing the final field maxSize in class MemMap in MemMap.java. The default size is set to 4GB

(2) Set the field isDebugging in class Debug to true/false to turn on/off the debug mode. If debug mode turned on, the structure of memMap, 2 hash tables and the anchor point array will be printed out.

(3) The code uses class BigInteger to store the address since the address might overflow. So the speed might be slower than those code implemented by class Integer. However in terms of big-O notation, the efficiency should be the same. So please look at my project report to check efficiency.

(4) to compile and run the code, input the following commands
```
cd Java/csci2100/
javac HashTable.java MemoryOperation.java MemoryManager.java Debug.java MemMap.java Test.java

cd ..
java -ea csci2100.Test
```


## EXPLANATION OF PROGRAM FILES AND DATA STRUCTURES
the memory map (implemented in linked list) and the hash table aided by anchor points is the main data structure of my algorithm.
The code for memory map is in file MemMap.java
The code for hash table is in HashTable.java

Other program files include:
Debug.java: storing debugging functions.
MemoryManager.java: the interface to perform memory managing operations. The detailed algorithm for managing request and release is inside.
MemoryOperation.java: given file. Managing and translating different kinds of memory operations
Test.java: given file. To perform tests on the memory manager.

Data and output files:
Data/ contains the test cases in .csv files.
Out/ contains the output of executing test cases with debug mode on and the total memory size set to 1024 bytes.