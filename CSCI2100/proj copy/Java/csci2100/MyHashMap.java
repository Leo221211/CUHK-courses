import java.util.Objects;//Objects类的equals方法是判断两个对象是否相等。
                        //在比较两个对象的时候，Object.equals方法容易抛出空指针异常。
public class MyHashMap<K, V> {

    private class Entry<K, V>{      //将Entry定义为成员内部类，里面封装了Entry自己的put和get方法
        private K key;
        private V value;
        private long hash;

        private Entry<K, V> next;   //用next实现链表
        private Entry(K key, V value){
            this.key = key;
            this.value = value;
            this.hash = this.key.hashCode();
        }
        private void put(Entry<K, V> entry){
            if(this.hash == entry.hash && Objects.equals(this.key, entry.key)){
                this.value = entry.value;   //覆盖
            }
            else{
                if(Objects.isNull(this.next)){
                    this.next = entry;
                    size ++;        //这里不能用this.size;  this.size表示这个类的size，这里是内部类，直接使用外部的size
                }else{
                    this.next.put(entry);   //递归
                }
            }
        }

        private Entry<K, V> get(K key){
            if(Objects.equals(key, this.key))
                return this;
            if(Objects.isNull(this.next))
                return null;
            return this.next.get(key);  //递归
        }
    }

    private int size;
    private Entry[] entries;
    private static final int DEFAULT_LENGTH = 4;

    public MyHashMap(int entryLength){      //MyHashMap构造函数
        this.entries = new Entry[entryLength];
    }
    public MyHashMap(){       //MyHashMap<Integer, Integer> map = new MyHashMap<>();
        this(DEFAULT_LENGTH); //如上不指明哈希表的长度的时候，调用这个构造函数
    }
    public int size(){
        return this.size;
    }
    private int hash(K key){    //计算entries数组的下标
        return key.hashCode() % entries.length;
    }

    /**
     * MyHashMap自己的put,get方法，实际上利用内部类Entry的put,get方法
     * @param key
     * @param value
     */
    public void put(K key, V value){
        Entry<K, V> entry = new Entry<>(key, value);
        int index = this.hash(key);
        if(Objects.isNull(entries[index])){
            entries[index] = entry;
            size ++;
        }
        else{
            entries[index].put(entry);
        }
    }

    public V get(K key){
        int index = this.hash(key);
        if(Objects.isNull(entries[index]))
            return null;
        Entry<K, V> entry = this.entries[index].get(key);
        return entry == null ? null : entry.value;
    }

    public boolean isEmpty(){
        return this.size > 0;
    }

    //for test
    public static void main(String[] args) {
        MyHashMap<Integer, Integer> map = new MyHashMap<>();
        map.put(1,1);
        map.put(2,2);
        map.put(3,3);
        System.out.println(map.get(1));
        System.out.println(map.size());
    }
}
