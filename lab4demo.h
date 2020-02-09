#include <iostream>

template <typename T>
class DList{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data=T{},Node* next=nullptr, Node* prev=nullptr){
			data_=data;
			next_=next;
			prev_=prev;
		}
	};
	Node* front_;
	Node* back_;
public:
	DList(){
		front_=nullptr;
		back_=nullptr;
	}
	void push_front(const T& data);
	~DList();

	//iterators are effectively pointers wrapped inside 
	//an object
	class const_iterator{
	friend class DList;
	protected:
		Node* curr_;    //this is the node being referred to
		const DList* theList_;
		const_iterator(const DList* theList, Node* n){
			curr_=n;
			theList_=theList;
		}
	public:
		const_iterator(){
			curr_=nullptr;
			theList_=nullptr;
		}
		const_iterator operator++(){
			//++x
			curr_=curr_->next_;
			return *this;
		}
		const_iterator operator++(int){
			//x++
			const_iterator rc = *this;
			curr_=curr_->next_;
			return rc;
		}
		const_iterator operator--(){
			if(curr_!=nullptr){
				curr_=curr_->prev_;
			}
			else{
				curr_=theList_->back_;
			}
			return *this;
		}
		const_iterator operator--(int){}
		bool operator==(const_iterator rhs){

		}
		bool operator!=(const_iterator rhs){
			return curr_ != rhs.curr_;
		}
		const T& operator*()const{
			return curr_->data_;
		}
	};
	class iterator:public const_iterator{
		iterator(DList* theList_, Node* n):
		const_iterator(theList_,n){}
	public:
		iterator();
		iterator operator++(){
			this->curr_=this->curr_->next_;
			return *this;			
		}
		iterator operator++(int){}
		iterator operator--(){}
		iterator operator--(int){}
		T& operator*(){}
		const T& operator*()const{}

	};

	//these belong to DList
	const_iterator cbegin() const{
		return const_iterator(this, front_);
	}
	iterator begin(){}
	const_iterator cend() const{return const_iterator(this,nullptr);}
	iterator end(){}
};


template <typename T>
void DList<T>::push_front(const T& data){

}


template <typename T>
DList<T>::~DList(){

}
template <typename T>
class Sentinel{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data=T{},Node* next=nullptr, Node* prev=nullptr){
			data_=data;
			next_=next;
			prev_=prev;
		}
	};
	Node* front_;
	Node* back_;
public:
	Sentinel(){
		front_=new Node();
		back_=new Node();
		front_->next_=back_;
		back_->prev_=front_;
	}
	void push_front(const T& data);
	~Sentinel();

	class const_iterator{
	public:
		const_iterator(){}
		const_iterator operator++(){}
		const_iterator operator++(int){}
		const_iterator operator--(){}
		const_iterator operator--(int){}
		bool operator==(const_iterator rhs){}
		bool operator!=(const_iterator rhs){}
		const T& operator*()const{}
	};
	class iterator:public const_iterator{
	public:
		iterator();
		iterator operator++(){}
		iterator operator++(int){}
		iterator operator--(){}
		iterator operator--(int){}
		T& operator*(){}
		const T& operator*()const{}
	};
	const_iterator cbegin() const{}
	iterator begin(){}
	const_iterator cend() const{}
	iterator end(){}
};


template <typename T>
void Sentinel<T>::push_front(const T& data){

}


template <typename T>
Sentinel<T>::~Sentinel(){

}
