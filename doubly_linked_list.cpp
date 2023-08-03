#include <iostream>
#include <memory>
#include <utility>

class Node
{
public:
    int value;
    std::unique_ptr<Node> next;
    Node *prev;

    Node(int value)
    {
        this->value = value;
        next = nullptr;
        prev = nullptr;
    }
};

class DoublyLinkedList
{
private:
    std::unique_ptr<Node> head;
    Node *tail;
    int length;

public:
    /**
     * @brief Constructor to initialize the doubly linked list with a given value.
     *
     * @param value The value to be set for the initial node.
     */
    DoublyLinkedList(int value)
    {
        head = std::make_unique<Node>(value);
        tail = head.get();
        length = 1;
    }
    /**
     * @brief Prints the elements of the doubly linked list in the forward direction.
     */
    void printList()
    {
        Node *current = head.get();
        while (current)
        {
            std::cout << current->value << std::endl;
            current = current->next.get();
        }
    }
    /**
     * @brief Prints the value of the head node.
     */
    void getHead() const
    {
        std::cout << "Head is " << head->value << std::endl;
    }
    /**
     * @brief Prints the value of the tail node.
     */
    void getTail() const
    {
        std::cout << "Tail is " << tail->value << std::endl;
    }
    /**
     * @brief Prints the length of the doubly linked list.
     */
    void getLength() const
    {
        std::cout << "Length is " << length << std::endl;
    }
    /**
     * @brief Appends a new node with the given value to the end of the doubly linked list.
     *
     * @param value The value to be added to the new node.
     */
    void append(int value)
    {
        std::unique_ptr<Node> newNode = std::make_unique<Node>(value);
        if (length == 0)
        {
            head = std::move(newNode);
            tail = head.get();
        }
        else
        {
            tail->next = std::move(newNode);
            tail->next->prev = tail;
            tail = tail->next.get();
        }
        length++;
    }
    /**
     * @brief Deletes the last node from the doubly linked list.
     */
    void deleteLast()
    {
        if (length == 0)
            return;
        if (length == 1)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        // delete temp;
        length--;
    }
    /**
     * @brief Prepends a new node with the given value to the beginning of the doubly linked list.
     *
     * @param value The value to be added to the new node.
     */
    void prepend(int value)
    {
        std::unique_ptr<Node> newNode = std::make_unique<Node>(value);
        if (length == 0)
        {
            head = std::move(newNode);
            tail = head.get();
        }
        else
        {
            head->prev = newNode.get();
            newNode->next = std::move(head);
            head = std::move(newNode);
        }
        length++;
    }
    /**
     * @brief Returns the node at the specified index in the doubly linked list.
     *
     * @param index The index of the node to retrieve.
     * @return Node* A pointer to the node at the specified index, or nullptr if the index is out of bounds.
     */
    Node *get(int index)
    {
        if (index < 0 || index > length - 1)
            return nullptr;
        Node *temp = head.get();
        if (index < length / 2)
        {
            for (int i = 0; i < index; i++)
            {
                temp = temp->next.get();
            }
        }
        else
        {
            temp = tail;
            for (int i = length - 1; i > index; i--)
            {
                temp = temp->prev;
            }
        }
        return temp;
    }
    /**
     * @brief Deletes the first node from the doubly linked list.
     */
    void deleteFirst()
    {
        if (length == 0)
            return;
        // Node *temp = head.get();
        if (length == 1)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            head = std::move(head->next);
            head->prev = nullptr;
        }
        // delete temp;
        length--;
    }
    /**
     * @brief Sets the value of the node at the specified index in the doubly linked list.
     *
     * @param index The index of the node to set the value for.
     * @param value The new value to set for the node.
     * @return bool True if the value was successfully set, false otherwise (index out of bounds).
     */
    bool set(int index, int value)
    {
        Node *temp = get(index);
        if (temp)
        {
            temp->value = value;
            return true;
        }
        return false;
    }
    /**
     * @brief Inserts a new node with the given value at the specified index in the doubly linked list.
     *
     * @param index The index at which to insert the new node.
     * @param value The value to be added to the new node.
     * @return bool True if the insertion was successful, false otherwise (index out of bounds).
     */
    bool insert(int index, int value)
    {
        if (index < 0 || index > length)
            return false;

        if (index == 0)
        {
            prepend(value);
            return true;
        }
        if (index == length)
        {
            append(value);
            return true;
        }

        std::unique_ptr<Node> newNode = std::make_unique<Node>(value);
        Node *after = get(index);
        Node *before = get(index - 1);

        if (after && before)
        {
            after->prev = newNode.get();
            newNode->prev = before;
            after->prev->next = std::move(before->next);
            before->next = std::move(newNode);
            length++;
            return true;
        }
        return false;
    }
    /**
     * @brief Deletes the node at the specified index from the doubly linked list.
     *
     * @param index The index of the node to delete.
     */
    void deleteNode(int index)
    {
        if (index < 0 || index > length - 1)
            return;
        if (index == 0)
        {
            return deleteFirst();
        }
        if (index == length - 1)
        {
            return deleteLast();
        }
        Node *temp = get(index);
        temp->next->prev = temp->prev;
        temp->prev->next = std::move(temp->next);
        length--;
    }
};

int main()
{

    std::unique_ptr<DoublyLinkedList> dll = std::make_unique<DoublyLinkedList>(7);

    dll->append(10);
    dll->deleteLast();
    dll->prepend(20);
    dll->deleteFirst();
    dll->append(21);
    dll->append(22);
    dll->append(23);
    dll->append(24);
    dll->set(0, 25);
    dll->insert(1, 25);
    dll->deleteNode(3);

    std::cout << "Doubly Linked List:" << std::endl;
    dll->printList();
    dll->getHead();
    dll->getTail();
    dll->getLength();
}