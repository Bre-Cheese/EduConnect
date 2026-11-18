#ifndef BST_H
#define BST_H

using namespace std;

template <typename T>
class BSTNode 
{
    public:
    
    T data;

    BSTNode<T>* lchild;
    BSTNode<T>* rchild;

    int height = 1;

    BSTNode(T data)
    {
        this->data = data;
        lchild = nullptr;
        rchild = nullptr;
    }

    BSTNode(T data, T* lchild, T* rchild)
    {
        this->data = data;
        this->lchild = lchild;
        this->rchild = rchild;
    }
};


template <typename T>
class BST
{
private:

    BSTNode<T>* root;
    int height = 0;

    // Returns the height of a node.
    int getHeight(BSTNode<T>* node)
    {
        if (node == nullptr)
            return 0;

        return node->height;
    }

    // Calculates the balance factor.
    int getBalance(BSTNode<T>* node)
    {
        if (node == nullptr)
            return 0;

        return getHeight(node->lchild)
             - getHeight(node->rchild);
    }

    // Updates the height of a node.
    void updateHeight(BSTNode<T>* node)
    {
        int lHeight = getHeight(node->lchild);
        int rHeight = getHeight(node->rchild);

        if (lHeight > rHeight)
        {
            node->height = 1 + lHeight;
        }
        else
        {
            node->height = 1 + rHeight;
        }
    }

    // Performs a right rotation.
    BSTNode<T>* rotateRight(BSTNode<T>* y)
    {
        BSTNode<T>* x = y->lchild;
        BSTNode<T>* T2 = x->rchild;

        x->rchild = y;
        y->lchild = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // Performs a left rotation.
    BSTNode<T>* rotateLeft(BSTNode<T>* x)
    {
        BSTNode<T>* y = x->rchild;
        BSTNode<T>* T2 = y->lchild;

        y->lchild = x;
        x->rchild = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // Recursive insertion and balancing.
    BSTNode<T>* insert(BSTNode<T>* node, T toAdd)
    {
        // Normal BST insertion.
        if (node == nullptr)
            return new BSTNode<T>(toAdd);

        if (toAdd < node->data)
        {
            node->lchild = insert(node->lchild, toAdd);
        }
        else if (toAdd > node->data)
        {
            node->rchild = insert(node->rchild, toAdd);
        }
        else
        {
            return node;
        }

        // Update height.
        updateHeight(node);

        // Calculate balance factor.
        int balance = getBalance(node);

        // LEFT LEFT CASE
        if (balance > 1 && toAdd < node->lchild->data)
        {
            return rotateRight(node);
        }

        // RIGHT RIGHT CASE
        if (balance < -1 && toAdd > node->rchild->data)
        {
            return rotateLeft(node);
        }

        // LEFT RIGHT CASE
        if (balance > 1 && toAdd > node->lchild->data)
        {
            node->lchild = rotateLeft(node->lchild);

            return rotateRight(node);
        }

        // RIGHT LEFT CASE
        if (balance < -1 && toAdd < node->rchild->data)
        {
            node->rchild = rotateRight(node->rchild);

            return rotateLeft(node);
        }

        return node;
    }

    BSTNode<T>* minValueBSTNode(BSTNode<T>* node) {
        BSTNode<T>* current = node;

        while (current->lchild != nullptr)
            current = current->lchild;

        return current;
    }

    BSTNode<T>* search_int(T param, BSTNode<T>* index) //I wrote this (you can tell by the psychotic formatting)
    {
        if (index == nullptr)                                { return nullptr; }
        if (param == index->data)                            { return index; }
        if (param < index->data && index->lchild != nullptr) { return search_int(param, index->lchild); }
        if (param > index->data && index->rchild != nullptr) { return search_int(param, index->rchild); }
        
        return nullptr;
    }

    BSTNode<T>* deleteBSTNode_int(T param, BSTNode<T>* index) {
        // Step 1: Perform normal BST deletion
        if (index == nullptr)
            return index;

        if (param < index->data) {
            index->lchild = deleteBSTNode_int(param, index->lchild);
        }
        else if (param > index->data) {
            index->rchild = deleteBSTNode_int(param, index->rchild);
        }
        else {

            // BSTNode has no children or only one child
            if (index->lchild == nullptr || index->rchild == nullptr) {

                BSTNode<T>* temp = index->lchild ? index->lchild : index->rchild;

                // No children
                if (temp == nullptr) {
                    temp = index;
                    index = nullptr;
                }
                // One child
                else {
                    *index = *temp;
                }

                delete temp;
            }

            // BSTNode has two children
            else {
                BSTNode<T>* temp = minValueBSTNode(index->rchild);

                index->data = temp->data;

                index->rchild = deleteBSTNode_int(temp->data, index->rchild);
            }
        }

        // If tree is now empty
        if (index == nullptr)
            return index;

        // Step 2: Update height
        if ( getHeight(index->lchild) > getHeight(index->rchild) )
        {
            index->height = 1 + getHeight(index->lchild);
        }
        else
        {
            index->height = 1 + getHeight(index->rchild);
        }

        // Step 3: Calculate balance factor
        int balance = getBalance(index);

        // Step 4: Rebalance if necessary

        // Left Left Case
        if (balance > 1 && getBalance(index->lchild) >= 0)
            return rotateRight(index);

        // Left Right Case
        if (balance > 1 && getBalance(index->lchild) < 0) {
            index->lchild = rotateLeft(index->lchild);
            return rotateRight(index);
        }

        // Right Right Case
        if (balance < -1 && getBalance(index->rchild) <= 0)
            return rotateLeft(index);

        // Right Left Case
        if (balance < -1 && getBalance(index->rchild) > 0) {
            index->rchild = rotateRight(index->rchild);
            return rotateLeft(index);
        }

        return index;
    }

public:

    BST()
    {
        root = nullptr;
    }

    BST(T source)
    {
        root = nullptr;
        add(source);
    }

    BST(T* source, int len)
    {
        root = nullptr;

        for (int i = 0; i < len; i++)
        {
            add(source[i]);
        }
    }

    void add(T toAdd)
    {
        root = insert(root, toAdd);
        height = search(toAdd)->height;
    }

    BSTNode<T>* search(T param) //I wrote this
    {
        return search_int(param, root);
    }

    BSTNode<T>* deleteBSTNode(T param)
    {
        return deleteBSTNode_int(param, root);
    }
    
};

#endif

