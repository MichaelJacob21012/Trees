#ifndef TREE_H
#define TREE_H

#include "treenode.h"

// TODO your code goes here:

template<typename T>
class BinarySearchTree{
private:
	unique_ptr<TreeNode<T>> root;
public:
	BinarySearchTree(){}

	void write(ostream & o) const {
		root->write(o);
	}

	TreeNode<T>* insert(const T content){
		TreeNode<T>* addition =  new TreeNode<T>(content);
		if (root == nullptr){
			root.reset(addition);
			return addition;
		}
		TreeNode<T>* current = root.get();
		while (current){
			if (content < current->data){
				if (current->leftChild){
					current = current->leftChild.get();
				}
				else{
					current->setLeftChild(addition);
					break;
				}
			}
			else if(current->data < content){
				if (current->rightChild){
					current = current->rightChild.get();
				}
				else{
					current->setRightChild(addition);
					break;
				}
			}
			else {
				TreeNode<T>* location =  current;
				return location;
			}
		}
		if (addition && addition->parent && addition->parent->parent){
			if (addition-> parent ->parent -> balanceFactor() == 2){
				if (addition -> parent -> balanceFactor() == 1){
					rightRotation(addition);
				}
				else if (addition -> parent -> balanceFactor() == -1){
					leftRightRotation(addition);
				}
			}
			else if (addition-> parent ->parent -> balanceFactor() == -2){
				if (addition -> parent -> balanceFactor() == 1){
					rightLeftRotation(addition);
				}
				else if (addition -> parent -> balanceFactor() == -1){
					leftRotation(addition);
				}
			}
		}
		return addition;
	}
	TreeNode<T>* find(const T content) const{
		TreeNode<T>* current = root.get();
		while (current){
			if (content < current->data){
				current = current->leftChild.get();
			}
			else if(current->data < content){
				current = current->rightChild.get();
			}
			else{
				return current;
			}
		}
		return current;
	}
	BinarySearchTree (const BinarySearchTree &other){
		TreeNodeIterator<T> itr = other.begin();
		for (auto element : other){
			insert(element);
		}
	}
	BinarySearchTree & operator=(const BinarySearchTree &other){
		TreeNodeIterator<T> itr = other.begin();
		for (auto element : other){
			insert(element);
		}
		return *this;
	}
	TreeNodeIterator<T> begin() const{
		if (root == nullptr){
			return TreeNodeIterator<T>(nullptr);
		}
		TreeNode<T>* beginning = root.get();
		while(beginning->leftChild){
			beginning = beginning->leftChild.get();
		}
		return TreeNodeIterator<T>(beginning);
	}
	TreeNodeIterator<T> end() const{
		return TreeNodeIterator<T>(nullptr);
	}
	int maxDepth() const{
		return (root->maxDepth());
	}
private:

	void leftRotation(TreeNode<T>* node){
		TreeNode<T>* a = node->parent->parent;
		TreeNode<T>* b = node->parent;
		if (a -> parent){
			TreeNode<T>* c = a->parent;
			if (a->data < c->data){
				c->setLeftChild(b);
			}
			else{
				c->setRightChild(b);
			}
		}
		else{
			root.release();
			root.reset(b);
		}
		b->setLeftChild(a);
		a->setRightChild(nullptr);
	}
	void rightRotation(TreeNode<T>* node){
		TreeNode<T>* a = node->parent->parent;
		TreeNode<T>* b = node->parent;
		if (a -> parent){
			TreeNode<T>* c = a->parent;
			if (a->data < c->data){
				c->setLeftChild(b);
			}
			else{
				c->setRightChild(b);
			}
		}
		else{
			root.release();
			root.reset(b);
		}
		b->setRightChild(a);
		a->setLeftChild(nullptr);
	}
	void leftRightRotation(TreeNode<T>* node){
		TreeNode<T>* a = node->parent->parent;
		TreeNode<T>* b = node->parent;
		if (a -> parent){
			TreeNode<T>* c = a->parent;
			if (a->data < c->data){
				c->setLeftChild(node);
			}
			else{
				c->setRightChild(node);
			}
		}
		else{
			node->parent = nullptr;
			root.release();
			root.reset(node);
		}
		node->setLeftChild(b);
		node->setRightChild(a);
		a->setLeftChild(nullptr);
		b->setRightChild(nullptr);


	}
	void rightLeftRotation(TreeNode<T>* node){
		TreeNode<T>* a = node->parent->parent;
		TreeNode<T>* b = node->parent;
		if (a -> parent){
			TreeNode<T>* c = a->parent;
			if (a->data < c->data){
				c->setLeftChild(node);
			}
			else{
				c->setRightChild(node);
			}
		}
		else{
			root.release();
			root.reset(node);
		}
		node->setLeftChild(a);
		node->setRightChild(b);
		a->setRightChild(nullptr);
		b->setLeftChild(nullptr);
	}
};


// do not edit below this line

#endif
