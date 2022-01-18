#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;

#include <memory>
using std::unique_ptr;

#include <utility>
using std::pair;

// TODO your code for the TreeNode class goes here:

template<typename T>
class TreeNode{
public:
	T data;
	unique_ptr<TreeNode<T>> leftChild;
	unique_ptr<TreeNode<T>> rightChild;
	TreeNode<T>* parent;

	TreeNode(T content)
	:data(content),parent(nullptr){
	}

	void setLeftChild(TreeNode<T>* child){
		leftChild.release();
		if(child){
			leftChild.reset(child);
			leftChild->parent = this;
		}
	}

	void setRightChild(TreeNode<T>* child){
		rightChild.release();
		if(child){
			rightChild.reset(child);
			rightChild->parent = this;
		}
	}

	ostream & write(ostream & o) const{
		if (leftChild){
			leftChild->write(o);
		}
		o	<< " "
				<< data
				<< " ";
		if(rightChild){
			rightChild->write(o);
		}
		return o;
	}

	int maxDepth() const{
		if (!this){
			return 0;
		}
		if (!leftChild && !rightChild){
			return 1;
		}
		return std::max((leftChild->maxDepth()),(rightChild->maxDepth())) + 1;
	}
	int balanceFactor() const{
		return (leftChild->maxDepth()- rightChild->maxDepth());
	}
};
template<typename T>
class TreeNodeIterator{
private:

	TreeNode<T>* current;

public:

	TreeNodeIterator(TreeNode<T>* currentIn)
: current(currentIn) {
	}

	T & operator*() {
		return current->data;
	}

	void operator++(){
		if (current->rightChild){
			current = current->rightChild.get();
			while(current -> leftChild){
				current = current->leftChild.get();
			}
		}
		else if (current -> parent == nullptr){
			current == nullptr;
		}
		else if(current->data < current->parent->data){
			current = current->parent;
		}
		else{
			while(current -> parent -> data < current -> data){
				current = current -> parent;
				if (current -> parent == nullptr){
					current = nullptr;
					return;
				}
			}
			current = current -> parent;
		}
	}

	bool operator==(const TreeNodeIterator<T> other) const{
		if (current == (other.current)){
			return true;
		}
		return false;
	}

	bool operator!=(const TreeNodeIterator<T> other) const{
		if (current == (other.current)){
			return false;
		}
		return true;
	}

};

// do not edit below this line

#endif
