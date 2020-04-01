#include "arrayqueue.h"
#include <iostream>
//T must be a comparable type
template <typename T>
class AVL{
	struct Node{
		T data_;
		Node* left_;
		Node* right_;
		int height_;    //height of the subtree with this node
		                //as root
		Node(const T data=T{}){
			data_=data;
			left_=nullptr;
			right_=nullptr;
			height_=1
		}
		void updateHeight() {
			int heightLeft=left_?left_->height_:0;
			int heightRight=right_?right_height_:0;
			height_=(heightRight > heightLeft)?heightRight+1:heightLeft+1;
		}
		int balance() const{
			int heightLeft=left_?left_->height_:0;
			int heightRight=right_?right_height_:0;
			return heightRight-heightLeft;			
		}
	};

	Node* root_;
	//given the root of a subtree, this function
	//prints the values of the subtree in an 
	//inorder manner (smallest to biggest ordering)
	void printInorder(const Node* rootOfSubtree) const{
		if(rootOfSubtree!=nullptr){
			//print every value smaller than current node
			//inorder. these are in the left subtree
			printInorder(rootOfSubtree->left_);
			//print current node
			std::cout << rootOfSubtree->data_ << " ";
			//print every value bigger than the curernt node
			//inorder.  these are in the right subtree
			printInorder(rootOfSubtree->right_);
		}
	}

	void printPreorder(const Node* rootOfSubtree) const{
		if(rootOfSubtree!=nullptr){
			std::cout << rootOfSubtree->data_ << " ";
			printPreorder(rootOfSubtree->left_);
			printPreorder(rootOfSubtree->right_);
		}
	}

	void printPostorder(const Node* rootOfSubtree) const{
		if(rootOfSubtree!=nullptr){
			printPostorder(rootOfSubtree->left_);
			printPostorder(rootOfSubtree->right_);
			std::cout << rootOfSubtree->data_ << " ";
		}
	}
	void insert(const T data, Node*& rootOfSubtree){
		if(rootOfSubtree == nullptr){
			rootOfSubtree=new Node(data);
		}
		else{
			if(data < rootOfSubtree->data_){
				insert(data,rootOfSubtree->left_);
			}
			else{
				insert(data,rootOfSubtree->right_);
			}

			int nodeBalance = rootOfSubtree->balance();
			if(nodeBalance >= 2){
				int childBalance=rootOfSubtree->right_->balance();
				if(childBalance > 0){
					leftRotate(rootOfSubtree);
					rootOfSubtree->left_->updateHeight();
				}
				else{
					rightRotate(rootOfSubtree->right_);
					leftRotate(rootOfSubtree);
					rootOfSubtree->left_->updateHeight();
					rootOfSubtree->right_->updateHeight();

				}

			}
			else if(nodeBalance<= -2){
				int childBalance=rootOfSubtree->left_->balance();
				if(childBalance < 0){
					rightRotate();
				}
				else{
					leftRotate();
					rightRotate();
				}
			}


			rootofSubtree->updateHeight();
		}
	}

	void rightRotate(Node*& rootofSubtree){
	}
	void leftRotate(Node*& rootofSubtree){
		Node* Bptr=rootOfSubtree->right_;
		Node* Yptr=Bptr->left_;
		rootOfSubtree->right=Yptr;
		Bptr-left_=rootofSubtree;
		rootOfSubtree=Bptr;


	}

public:
	AVL(){
		root_=nullptr;
	}

	void insert(const T data){
		insert(data,root_);
	}
	void printInorder() const{
		printInorder(root_);
		std::cout << std::endl;
	}
	void printPreorder() const{
		printPreorder(root_);
		std::cout << std::endl;
	}
	void printPostorder() const{
		printPostorder(root_);		
		std::cout << std::endl;
	}
	void printBreadthfirst() const{
		Queue<Node*> theNodes;
		if(root_){
			theNodes.enqueue(root_);
		}
		while(!theNodes.isEmpty()){
			Node* curr=theNodes.front();
			theNodes.dequeue();
			std::cout << curr->data_ << " ";
			if(curr->left_){
				theNodes.enqueue(curr->left_);
			}
			if(curr->right_){
				theNodes.enqueue(curr->right_);
			}
		}

		std::cout << std::endl;

	}











};
