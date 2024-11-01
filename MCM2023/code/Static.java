/**
 * class method touch class fields only
 * instance method manipulate instance / class fields
 */

public class Static {
    int i = 2;
    static int c = 3;

    public void foo(){
        i = i + 1;
        c = c + 1;
    }

    public static void main(String[] agrs){
        i = i + 1;
        System.out.println(i + 1);
        // double x = Question1.toRad(2);
    }
}
