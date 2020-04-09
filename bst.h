#include "arrayqueue.h"
#include <iostream>
//T must be a comparable type
template <typename T>
class BST{
	struct Node{
		T data_;
		Node* left_;
		Node* right_;
		Node(const T data=T{},Node* left=nullptr,Node* right=nullptr){
			data_=data;
			left_=left;
			right_=right;
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

	//insert data into subtree
	void insert(const T& data, Node*& subtree){
		if(subtree==nullptr){
			subtree = new Node(data);
		}
		else{
			if(data < subtree->data_){
				insert(data, subtree->left_);
			}
			else{
				insert(data, subtree->right_);
			}
		}
	}

	//detach and return the address of the smallest node
	//in subtree
	Node* detachSmallest(Node*& subtree){

	}

	//remove the node containing data from the subtree
	void remove(const T& data, Node*& subtree){
		if(subtree != nullptr){
			if(data == subtree->data_){
				Node* rm=subtree;
				if(subtree->left_== nullptr && subtree->right_== nullptr){
					//leaf node
					subtree = nullptr;
				}
				else if (subtree->left_!=nullptr && subtree->right==nullptr){
					//only have left subtree

				}
				else if(subtree->right_!=nullptr && subtree->left_==nullptr){
					//only have right subtree
				}
				else{
					//two children
					Node* inorderSuccessor = detach(subtree->right_);
					//...

				}


				delete rm;

			}
			else{
				if(data < subtree->data_){
					remove(data,subtree->left_);
				}
				else{
					remove(data,subtree->right_);
				}
			}

		}
	}

public:
	BST(){
		root_=nullptr;
	}
	void insert(const T data){
		insert(data,root_);
	}

	void insertIterative(const T& data){
		if(root_==nullptr){
			root_=new Node(data);
		}
		else{
			Node* curr=root_;
			while(curr!=nullptr){
				if(data < curr->data_){
					if(curr->left_!=nullptr){
						curr=curr->left_;
					}
					else{
						curr->left_=new Node(data);
						curr=nullptr;
					}
				}
				else{
					if(curr->right_!=nullptr){
						curr=curr->right_;
					}
					else{
						curr->right_=new Node(data);
						curr=nullptr;
					}
				}
			}

		}
	}
	void remove(const T data){
		remove(data, root_);
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
