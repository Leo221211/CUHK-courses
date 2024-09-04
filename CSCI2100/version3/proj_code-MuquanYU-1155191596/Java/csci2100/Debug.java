package csci2100;

public class Debug {

    /**
     * turn on or off debug mode. if isDebugging == true, 
     * then after each operation the structure of the 2 hash tables, \
     * the memory map, and the anchor point will be printed out
     */
    public static final boolean isDebugging = true;


    /**
     * to print the file name and the line number
     */
    public static void printFileNameAndLineNumber() {
        if(!isDebugging) return;

        StackTraceElement[] stackTrace = Thread.currentThread().getStackTrace();
        
        if (stackTrace.length >= 3) {
            StackTraceElement caller = stackTrace[2];
            String fileName = caller.getFileName();
            int lineNumber = caller.getLineNumber();
            
            System.out.print("executed: File name: " + fileName);
            System.out.println("; Line number: " + lineNumber);
        }
    }

    /**
     * Same with System.out.print(), 
     * except that it will only be printed out when debug mode is on
     * @param s the string to be printed
     */
    public static void dbgPrint(String s) {
        if(!isDebugging) return;
        
        System.out.println(s);
    }
}
