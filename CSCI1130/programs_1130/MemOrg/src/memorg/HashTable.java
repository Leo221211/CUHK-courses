package memorg;

import java.math.BigInteger;

public class HashTable<T> {

    public HashTable(T[] values) {
        // TODO: initialize the hash table.
        // You can define or choose type T based on your needs.
    }

    public boolean delete(BigInteger key) {
        // TODO: delete an existing value.
        // Return true if successfully deleted, false if the key does not exist in the database.
        return false;
    }

    public void insert(T value) {
        // TODO: insert a new value into the database.
        // Do not need to return anything.
    }

    public T query(BigInteger key) {
        // TODO: query by key. Return null if the key does not exist.
        // Return the query result. Return null if the key does not exist in the database.
        return null;
    }
    
    private static int nextPrime( int n )
    {
        if (n % 2 == 0)
            n++;
        for ( ; !isPrime( n ); n += 2);
 
        return n;
    }
    /* Function to check if given number is prime */
    private static boolean isPrime( int n )
    {
        if (n == 2 || n == 3)
            return true;
        if (n == 1 || n % 2 == 0)
            return false;
        for (int i = 3; i * i <= n; i += 2)
            if (n % i == 0)
                return false;
        return true;
    }
}
