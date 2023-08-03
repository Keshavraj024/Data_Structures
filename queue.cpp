#include <iostream>
#include <memory>
#include <limits.h>
#include <utility>

class Node
{
public:
    int value;
    std::unique_ptr<Node> next;

    Node(int value)
    {
        this->value = value;
        next = nullptr;
    }
};

class Queue
{
private:
    std::unique_ptr<Node> first;
    Node *last;
    int length;

public:
    /**
     * @brief Constructor to create a new queue with a single initial value.
     *
     * @param value The initial value for the first element in the queue.
     */
    Queue(int value)
    {
        first = std::make_unique<Node>(value);
        last = first.get();
        length = 1;
    }
    /**
     * @brief Print the elements of the queue.
     */
    void printQueue()
    {
        Node *current = first.get();
        while (current)
        {
            std::cout << current->value << std::endl;
            current = current->next.get();
        }
    }
    /**
     * @brief Add an element to the end of the queue.
     *
     * @param value The value to be added to the queue.
     */
    void enqueue(int value)
    {
        std::unique_ptr<Node> newNode = std::make_unique<Node>(value);
        if (length == 0)
        {
            first = std::move(newNode);
            last = first.get();
        }
        else
        {
            last->next = std::move(newNode);
            last = last->next.get();
        }
        length++;
    }
    /**
     * @brief Remove and return the first element from the queue.
     *
     * @return The value of the dequeued element. Returns INT_MIN if the queue is empty.
     */
    int dequeue()
    {
        if (length == 0)
            return INT_MIN;
        int dequeuedValue = first->value;
        if (length == 1)
        {
            first = nullptr;
            last = nullptr;
        }
        else
        {
            first = std::move(first->next);
        }
        length--;
        return dequeuedValue;
    }
    /**
     * @brief Get the length of the queue.
     *
     * @return The length of the queue.
     */
    void getLength()
    {
        std::cout << "Length of the queue is " << length << std::endl;
    }
};

int main()
{
    std::unique_ptr<Queue> q = std::make_unique<Queue>(10);
    q->enqueue(20);
    q->enqueue(30);
    q->enqueue(40);
    auto elementRemoved = q->dequeue();
    std::cout << "Element removed from the queue is :" << elementRemoved << std::endl;
    std::cout << "The elements in the queue are : " << std::endl;
    q->printQueue();
    q->getLength();
}