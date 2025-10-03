#include "leftistHeap.h"

// Initialize an instance of LeftistNode
LeftistNode::LeftistNode(int key, LeftistNode *lt, LeftistNode *rt, int np)
{
    // Write your code below this line ----------------------------------------------------------------
    this->key=key;
    left=lt;
    right=rt;
    npl = np;
}

LeftistNode::~LeftistNode()
{
    // Write your code below this line ----------------------------------------------------------------

}

// Implement a default constructor for a empty LeftistHeap
LeftistHeap::LeftistHeap()
{
    // Write your code below this line ----------------------------------------------------------------
    root = nullptr;
}


// Implement a destructor for LeftistHeap
// All nodes should be properly deleted to avoid memory leaks
LeftistHeap::~LeftistHeap()
{
    // Write your code below this line ----------------------------------------------------------------
    this->makeEmpty();

}

void LeftistHeap::merge(LeftistHeap &rhs)
{   
    root = merge(root, rhs.root);
}

// Implement the merge function that takes roots of two LeftistHeaps and merges them into one returns the root of merged heap
LeftistNode *LeftistHeap::merge(LeftistNode *h1, LeftistNode *h2)
{
    // Write your code below this line ----------------------------------------------------------------
    if (h1 == nullptr) return h2;
    if (h2 == nullptr) return h1;

    if (h1->key > h2->key) {
        std::swap(h1, h2);
    }
    // Now h1->key <= h2->key
    h1->right = merge(h1->right, h2);

    // Ensure leftist property: left child has >= npl than right
    int nl = (h1->left ? h1->left->npl : -1);
    int nr = (h1->right ? h1->right->npl : -1);

    if (nr > nl) {
        swapChildren(h1);
        std::swap(nl, nr);
    }

    // npl: one plus minimum of children’s npl
    h1->npl = min(nl,nr);

    return h1;
    
}

// Implement a function to swap the children of a node (Exchange the left and right children of the provided node)
// Ensure the left child becomes the right child and vice versa.
void LeftistHeap::swapChildren(LeftistNode *t)
{
    // Write your code below this line ----------------------------------------------------------------
    LeftistNode* temp = t->left;
    t->left = t->right;
    t->right = temp;
}

// Implement a insertion function to insert a new key into the heap.
void LeftistHeap::insert(int &x)
{
    // Write your code below this line ----------------------------------------------------------------
    root = merge(root, new LeftistNode(x, nullptr, nullptr, 0));

}

// Implement this function to retrieve the smallest key in the heap.
int LeftistHeap::findMin() const
{
    // Write your code below this line ----------------------------------------------------------------
    if (root == nullptr) {
        throw std::underflow_error("Heap is empty");
    }
    return root->key;
}

// Delete minimum function: Remove and return the smallest key from the heap.
void LeftistHeap::deleteMin(int &minItem)
{
    if (root == nullptr) {
        // error
        return;
    }

    minItem = root->key;

    LeftistNode *oldRoot = root;
    LeftistNode *leftSub = root->left;
    LeftistNode *rightSub = root->right;

    oldRoot->left = nullptr;
    oldRoot->right = nullptr;

    root = merge(leftSub, rightSub);
    delete oldRoot;
}


// Check if the heap is empty
bool LeftistHeap::isEmpty() const
{
    // Write your code below this line ----------------------------------------------------------------
    if (!root){
        return true;
    }
    return false;
}

void LeftistHeap::makeEmpty()
{
    makeEmpty(root);
    root = nullptr;
}

// Implement a helper function for makeEmpty that delete all nodes starting from the given node.
void LeftistHeap::makeEmpty(LeftistNode *t)
{
    // Write your code below this line ----------------------------------------------------------------
    if (t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
}
