package test;
import java.math.BigInteger;

class MiscellTest {
    public static void main(String[] args) {
        for(BigInteger i = new BigInteger("0"); i.compareTo(new BigInteger("10")) == -1; i = i.add(new BigInteger("1"))) {
            System.out.println(i);
        }
    }
}