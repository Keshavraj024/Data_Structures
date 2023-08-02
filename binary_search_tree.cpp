#include <iostream>
#include <memory>

class Node
{
public:
    int value;
    Node *left;
    Node *right;

    Node(int value) : value(value),
                      left(nullptr),
                      right(nullptr)
    {
    }
};

class BinarySearchTree
{
private:
    Node *root;

public:
    BinarySearchTree() : root(nullptr)
    {
    }

     /**
     * @brief Inserts a new value into the Binary Search Tree.
     * @param value The value to be inserted.
     * @return true if insertion is successful, false otherwise.
     */
    bool insert(int value)
    {
        Node *newNode = new Node(value);
        if (root == nullptr)
        {
            root = newNode;
            return true;
        }
        Node *temp = root;
        while (temp)
        {
            if (newNode == temp)
                return false;
            if (newNode->value > temp->value)
            {
                if (temp->right == nullptr)
                {
                    temp->right = newNode;
                    return true;
                }
                temp = temp->right;
            }
            else
            {
                if (temp->left == nullptr)
                {
                    temp->left = newNode;
                    return true;
                }
                temp = temp->left;
            }
        }
    }

    /**
     * @brief Checks if the Binary Search Tree contains the given value.
     * @param value The value to search for.
     * @return true if the value is found, false otherwise.
    */
    bool contains(int value)
    {
        Node *temp = root;
        while (temp)
        {
            if (temp->value == value)
                return true;
            if (temp->value < value)
            {
                temp = temp->right;
            }
            else
            {
                temp = temp->left;
            }
        }
        return false;
    }

    /**
     * @brief Prints the Binary Search Tree in-order traversal.
     */
    void printTree(Node *node)
    {
        if (node)
        {
            printTree(node->left);
            std::cout << node->value << " ";
            printTree(node->right);
        }
    }

    void printTree()
    {
        if (root == nullptr)
        {
            std::cout << "No nodes are in the tree" << std::endl;
            return;
        }
        printTree(root);
        std::cout << std::endl;
    }
};

int main()
{
    std::unique_ptr<BinarySearchTree> bst = std::make_unique<BinarySearchTree>();
    bst->insert(10);
    bst->insert(9);

    std::cout << "Is 9 present in the tree ? : " << std::boolalpha << bst->contains(9) << std::endl;
    std::cout << "Is 11 present in the tree ? : " << std::boolalpha << bst->contains(11) << std::endl;

    std::cout << "The nodes in the tree are : ";
    bst->printTree();

    return 0;
}
