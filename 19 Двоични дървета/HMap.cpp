#include <iostream>
#include <cstring>
#include <functional>

template<typename KeyType, typename ValueType>
class HMap{
    public:
    HMap(size_t tableSize, std::function<size_t (const KeyType  &)> _h):size(tableSize), h(_h) {
        table = new TableEntry*[tableSize];
        for(int i = 0; i < size; i++){
             table[i] = nullptr;
        }
    }

    ValueType operator[](const KeyType& key)const{
        TableEntry *current = lookup(key);
        if(!current){
            throw "Key not found!"; 
        }
        return current->value;
    }

    ValueType& operator[](const KeyType& key){
        TableEntry *current = lookup(key);
        if(current){
            return current->value;
        } 
        size_t index = h(key) % size;

        ValueType dummy;
        table[index] = new TableEntry{key, dummy,table[index]};
        return table[index]->value;
    }
    HMap<KeyType, ValueType> (const HMap<KeyType, ValueType> &other);
    HMap<KeyType, ValueType>& operator=(const HMap<KeyType, ValueType> &other);
    ~HMap(){
        delete[] table;
    }
     
    private:
    struct TableEntry{
        KeyType key;
        ValueType value;
        TableEntry* next;
    };
    TableEntry**  table;
    size_t size;
    std::function<size_t (const KeyType&)>h; 
    typename HMap<KeyType, ValueType>::TableEntry* lookup(const KeyType& key) {
        size_t index = h(key) % size;
        TableEntry* current = table[index];
        while (current != nullptr && current->key != key) {
            current = current->next;
        }
        return current;
    }


};

int h1(const std::string &key){
    return key.length();
}

int main(){
    HMap<std::string, int> phoneBook(10, h1);
    phoneBook["Jon Doe"] = 1234;
    std::cout << phoneBook["Jon Doe"]; 

}
