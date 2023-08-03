#include <iostream>
#include <memory>
#include <climits>

class Node
{
public:
    int value;
    std::shared_ptr<Node> next;

    Node(int value) : value(value), next(nullptr) {}
};

class Stack
{
private:
    std::shared_ptr<Node> top;
    size_t height;

public:
    /**
     * @brief Constructor to create a new stack with a single initial value.
     *
     * @param value The initial value for the top of the stack.
     */
    Stack(int value) : top(std::make_shared<Node>(value)), height(1) {}

    /**
     * @brief Print the elements of the stack from top to bottom.
     */
    void printStack() const
    {
        std::shared_ptr<Node> current = top;
        while (current)
        {
            std::cout << current->value << std::endl;
            current = current->next;
        }
    }

    /**
     * @brief Push a new value onto the top of the stack.
     * 
     * @param value The value to be pushed onto the stack.
     */
    void push(int value)
    {
        std::shared_ptr<Node> newNode = std::make_shared<Node>(value);
        newNode->next = top;
        top = newNode;
        height++;
    }

    /**
     * @brief Pop the top element from the stack and return its value.
     * 
     * @return The value of the popped element. Returns INT_MIN if the stack is empty.
     */
    int pop()
    {
        if (height == 0)
            return INT_MIN;

        int val = top->value;
        top = top->next;
        height--;
        return val;
    }
};

int main()
{
    std::unique_ptr<Stack> S = std::make_unique<Stack>(2);
    S->push(10);
    S->printStack();
    return 0;
}
