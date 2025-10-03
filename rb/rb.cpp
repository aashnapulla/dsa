#include "rb.h"
using ptr = RedBlackTree::ptr;

RedBlackTree::RedBlackTree(){}

const ptr RedBlackTree::getRoot() const
{ 
	return root; 
}

ptr RedBlackTree::insert(int data)
{
	ptr newnodePtr = new node(data);
	if (!root) {
		root = newnodePtr;
		root->color = 0; // set root color as black
		return newnodePtr;
	}
	insert(root, newnodePtr);
	return newnodePtr;
}

ptr RedBlackTree::sibling(ptr n) {
        if (!n || !n->parent) return nullptr;
        if (n->parent->left == n) return n->parent->right;
        return n->parent->left;
    }

// auxiliary function to perform RBT insertion of a node
// you may assume start is not nullptr
void RedBlackTree::insert(ptr start, ptr newnodePtr)
{
	// choose direction
	ptr x = start;
	ptr y = nullptr;
	ptr n = newnodePtr;

	while (x!=nullptr){
		y=x;
		if (x->data > n->data){
			x = x->left;
		}
		else {
			x = x->right;
		}
	}

	if (y->data > n->data){
		y->left = n;
	}

	else {
		y->right = n;            
	}

	n->parent = y;
	n->color = 1;
	return;
}

// Credits to Adrian Schneider
void RedBlackTree::printRBT(ptr start, const std::string& prefix, bool isLeftChild) const
{
	if (!start) return;

	std::cout << prefix;
	std::cout << (isLeftChild ? "|--" : "|__" );
	// print the value of the node
	std::cout << start->data << "(" << start->color << ")" << std::endl;
	// enter the next tree level - left and right branch
	printRBT(start->left, prefix + (isLeftChild ? "│   " : "    "), true);
	printRBT(start->right, prefix + (isLeftChild ? "│   " : "    "), false);
}

// Function performing right rotation
// of the passed node
void RedBlackTree::rightrotate(ptr loc)
{
	ptr a = loc;
	ptr b = loc->left;
	ptr temp = b->right;
	b->right = a;
	a->left = temp;

	b->parent = a->parent;
	a->parent = b;
	if (temp) temp->parent = a;

	if (b->parent == nullptr){
		root =b;
	}
	else if (b->parent->left == a){
		b->parent->left = b;
	}
	else {
		b->parent->right = b;
	}
	return;
}

// Function performing left rotation
// of the passed node
void RedBlackTree::leftrotate(ptr loc)
{
	ptr a = loc;
	ptr b = loc->right;
	ptr temp = b->left;
	b->left = a;
	a->right = temp;

	b->parent = a->parent;
	a->parent = b;
	if (temp) temp->parent = a;

	if (b->parent == nullptr){
		root =b;
	}
	else if (b->parent->left == a){
		b->parent->left = b;
	}
	else {
		b->parent->right = b;
	}
	return;
}

// This function fixes violations
// caused by RBT insertion
void RedBlackTree::fixup(ptr loc)
{	
	ptr n = loc;
	if (n==root){
		n->color = 0;
		return; 
	}

	ptr p = n->parent;
	if (p->color == 0){
		return;
	}

	else if (p->color == 1){        
		ptr g = p->parent;
		ptr u = sibling(p);

		if (u != nullptr && u->color == 1){
			p->color=0;
			u->color=0;
			g->color=1;
			fixup(g);
			return;
		}

		if ((g->left == p && p->right == n) || (g->right == p && p->left == n)){
			if (p->left == n){
				rightrotate(p);
			}
			else if (p->right == n) {
				leftrotate(p);
			}
		}
		if (g->left == p){
			rightrotate(g);
		}
		else if (g->right == p){
			leftrotate(g);
		}
		int s = g->color;
		g->color = p->color;
		p->color = s;
		return;
		
	}

}

// Function to print inorder traversal
// of the fixated tree
void RedBlackTree::inorder(ptr start) const
{
	if (!start)
		return;
	
	inorder(start->left);
	std::cout << start->data << " ";
	inorder(start->right);
}


