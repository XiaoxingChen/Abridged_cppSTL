//chenxx 2015/10/18 v1.0
#ifndef LIST_H
#define LIST_H
//#define RUN_IN_ARM
#ifndef RUN_IN_ARM
typedef unsigned char			u8;
typedef signed char				s8;
typedef unsigned short		u16;
typedef signed short			s16;
typedef unsigned int			u32;
typedef signed int				s32;
#else
#include <string.h>
#include "stm32f10x.h"
#endif
template <typename T>
class list
{
public:	
	struct Node
	{
	public:
		Node* next_;
		Node* prev_;
		T elem_;
		Node() :
			next_(this),
			prev_(this)
		{}
		Node(Node* next, Node* prev) :
			next_(next),
			prev_(prev)
		{}
		~Node()
		{}
	};

	typedef size_t size_type;
	typedef Node* Iterator;

	list() :
		begin_(&keepNode_),
		size_(0)
	{
		/*begin_->elem_ = {0};*/
	}
	list(T* elemArray, size_type size) :
		begin_(&keepNode_),
		size_(0)
	{
		begin_->elem_ = 0;
		for (size_type i = 0; i < size; i++)
		{
			push_back(*(elemArray));
		}
	}
	~list()
	{
		clear();
	}

	//
	// list operation
	//
	list& operator = (const list& other)
	{
		Node* it;
		if (this != &other)
		{
			clear();
			it = other.begin_->next_;
			while (it != other.begin_)
			{
				this->push_back(it->elem_);
				it = it->next_;
			}
		}
		return (*this);
	}
	void clear()
	{
		Node* it;
		it = begin_->prev_;
		while (it != begin_)
		{
			destroy(it);
			it = begin_->prev_;
		}
		size_ = 0;
	}
	Node*& back()
	{
		return begin_->prev_;
	}
	void pop_back()
	{
		Node* it;
		it = begin_->prev_;
		if (it != begin_)
			destroy(it);
	}
	void push_back(T elem)
	{
		Node* it_end;
		it_end = begin_->prev_;
		begin_->prev_ = new Node(begin_, it_end);
		it_end->next_ = begin_->prev_;
		begin_->prev_->elem_ = elem;

		size_++;
	}
	Node*& front()
	{
		return begin_->next_;
	}
	void pop_front()
	{
		Node* it;
		it = begin_->next_;
		if (it != begin_)
			destroy(it);
	}
	void push_front(T elem)
	{
		insert(begin_, elem);
	}
	void insert(Node* position, T elem)
	{
		Node* it;
		it = position->next_;
		position->next_ = new Node(it, position);
		it->prev_ = position->next_;
		position->next_->elem_ = elem;

		size_++;
	}
	void destroy(Node* position)
	{
		if (position != begin_)
		{
			position->prev_->next_ = position->next_;
			position->next_->prev_ = position->prev_;

			delete position;
			size_--;
		}
	}
	size_t size() const
	{
		return size_;
	}

	Node* begin_;
private:
	/*Node<T>* it_;*/
	Node keepNode_;
	size_t size_;

};
#ifndef RUN_IN_ARM
template <typename T>
void coutList(const list<T>& listIn)
{
	/*list<T>::Iterator it;*/
	list<T>::Iterator it;
	it = listIn.begin_;
	do
	{
		cout << "elem = " << it->elem_ << endl;
		it = it->next_;
	} while (it != listIn.begin_);
}
template <typename T>
void checkList(const list<T>& listIn)
{
	list<T>::Iterator it;
	/*Node<T>* it;*/
	it = listIn.begin_;
	unsigned char errorFlag = 0;
	do
	{
		if (it->next_->prev_ != it)
			errorFlag++;
	} while (it != listIn.begin_);
	cout << "checkList Error number: " << (int)errorFlag << endl;
}
#endif
#endif 
/*End of File*/

