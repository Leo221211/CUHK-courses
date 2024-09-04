package csci2100;

public class Debug {

    // turn on or off debug mode
    public static final boolean isDebugging = false;

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

    public static void dbgPrint(String s) {
        if(!isDebugging) return;
        
        System.out.println(s);
    }
}
