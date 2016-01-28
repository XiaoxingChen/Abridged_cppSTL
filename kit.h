/**
  ******************************************************************************
  * @file    kit.h
  * @author  Chenxx
  * @version V1.0
  * @date    2015-10-14
  * @brief   an easy and dummy map.
  ******************************************************************************/
//chenxx 2015/10/19 v1.0
#ifndef KIT_H
#define KIT_H
#include "list.h"
template <typename T>
class kit
{
public:
	
	struct Association
	{
		/*default constructor*/
		Association()
		{}
		/*mostly used constructor*/
		Association(s16 key, const T& item)
			:key_(key), item_(item)
		{}
		/*copy constructor*/	
		Association(const Association& other)
			:key_(other.key_), item_(other.item_)
		{}
		s16 key_;
		T item_;
	};

	/*typedef list<int>::Iterator Iterator;*/
	typedef typename list<Association>::Iterator Iterator;
	kit()
	{}
	~kit()
	{}

	void add(s16 key, T item)
	{
		registry_.push_back(Association(key, item));
	}
	T& handle(s16 key) const
	{
		Iterator it = registry_.begin_->next_;
		while (it != registry_.begin_)
		{
			if (it->elem_.key_ == key)
			{
				return it->elem_.item_;
			}
			it = it->next_;
		}
		return registry_.begin_->elem_.item_;
	}

protected:
	list<Association> registry_;

};



#endif
/*End of File*/
