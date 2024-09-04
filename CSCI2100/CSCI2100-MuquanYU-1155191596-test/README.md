## NOTE
(1) Modify the total size of the memory by editing the final field maxSize in class MemMap in MemMap.java

(2) Set the field isDebugging in class Debug to true/false to turn on/off the debug mode. If debug mode turned on, the structure of memMap, 2 hash tables and the anchor point array will be printed out.

(3) The code uses class BigInteger to store the address since the address might overflow. So the speed might be slower than those code implemented by class Integer. However in terms of big-O notation, the efficiency should be the same. So please look at my project report to check efficiency.

(4) to compile and run the code, input the following commands
```
cd Java/csci2100/
javac HashTable.java MemoryOperation.java MemoryManager.java Debug.java MemMap.java Test.java

cd ..
java -ea csci2100.Test
```
