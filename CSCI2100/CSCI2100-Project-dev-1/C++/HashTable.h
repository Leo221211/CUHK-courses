#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>

template <typename T>
class HashTable {
public:
    HashTable(const std::vector<T>& values){
        // TODO: initialize the hash table.
        // You can define or choose object type based on your needs.
        // Do not need to return anything.
    }
    bool delete(int key){
        // TODO: delete an existing value.
        // Return True if successfully deleted, False if the key does not exist in the database.
    }
    void insert(const T& value){
        // TODO: insert a new value into the database.
        // Do not need to return anything.
    }
    int query(int key){
        // TODO: query by key. Return None if the key does not exist.
        // Return the query result. Return None if the key does not exist in the database.
    }

private:
    // TODO: Declare internal data structures and helper methods for hash table.
};

#endif // HASHTABLE_H
