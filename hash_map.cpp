#include <iostream>
#include <string>
#include <memory>
#include <vector>

class Node
{
public:
    std::string key;
    int value;
    std::unique_ptr<Node> next;

    Node(std::string key, int value) : key{key}, value{value}, next{nullptr}
    {
    }
};

class HashTable
{
private:
    static const int SIZE = 7;
    std::unique_ptr<Node> dataMap[SIZE];

public:
    /**
     * @brief Prints all the key-value pairs in the hash table.
     */
    void printTable()
    {
        for (size_t i = 0; i < SIZE; i++)
        {
            if (dataMap[i])
            {
                Node *temp = dataMap[i].get();
                while (temp)
                {
                    std::cout << "{" << temp->key << ": " << temp->value << "}" << std::endl;
                    temp = temp->next.get();
                }
            }
        }
    }
    /**
     * @brief Generates a hash value for the given key.
     * @param key The input key for which the hash value is calculated.
     * @return The hash value of the key.
     */
    size_t hash(std::string key)
    {
        size_t hash{0};
        for (const auto &c : key)
        {
            size_t asciivalue = int(c);
            hash = (hash + asciivalue * 23) % SIZE;
        }
        return hash;
    }
    /**
     * @brief Adds a key-value pair to the hash table.
     * @param key The key to be inserted.
     * @param value The corresponding value for the key.
     */
    void set(std::string key, size_t value)
    {
        auto index = hash(key);
        std::unique_ptr<Node> newNode = std::make_unique<Node>(key, value);
        if (dataMap[index] == nullptr)
        {
            dataMap[index] = std::move(newNode);
        }
        else
        {
            Node *temp = dataMap[index].get();
            while (temp->next != nullptr)
            {
                temp = temp->next.get();
            }
            temp->next = std::move(newNode);
        }
    }
    /**
     * @brief Retrieves the value associated with the given key.
     * @param key The key for which the value is to be retrieved.
     * @return The value associated with the key. If the key is not found, returns 0.
     */
    int get(std::string key)
    {
        size_t index = hash(key);
        Node *temp = dataMap[index].get();
        while (temp)
        {
            if (temp->key == key)
                return temp->value;
            temp = temp->next.get();
        }
        return 0;
    }
    /**
     * @brief Returns a vector containing all the keys in the hash table.
     * @return A vector of strings containing all the keys.
     */
    std::vector<std::string> keys()
    {
        std::vector<std::string> allKeys;
        for (size_t index = 0; index < SIZE; index++)
        {
            Node *temp = dataMap[index].get();
            while (temp)
            {
                allKeys.push_back(temp->key);
                temp = temp->next.get();
            }
        }
        return allKeys;
    }
};

int main()
{
    std::unique_ptr<HashTable> hash = std::make_unique<HashTable>();
    hash->set("Adam", 20);
    hash->set("Chris", 30);
    hash->set("Betina", 40);

    // Test printTable function
    std::cout << "Printing the hash table:\n";
    hash->printTable();

    // Test get function
    std::cout << "Value for 'Adam': " << hash->get("Adam") << std::endl;

    // Test keys function
    auto keys = hash->keys();
    std::cout << "All keys in the hash table: ";
    for (const auto &k : keys)
        std::cout << k << " ";
    std::cout << std::endl;
}