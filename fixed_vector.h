/**
******************************************************************************
* @file    fixed_vector.h
* @author  Chenxx
* @version V1.0
* @date    2017-5-19
* @brief   This file defines the fixed vector.
******************************************************************************/
#ifndef FIXED_VECTOR_H
#define FIXED_VECTOR_H
#include <stdint.h>
#include <string.h>

template<typename T>
class fixed_vector_base
{
	public:

/**
	* @brief  	Constructor
	* @array:	static array for queue
	* @size: 	size of static array
	* @retval 	invalid
	*/
		fixed_vector_base(T* ref_array, uint16_t MAX_NUM)
			:static_array_(ref_array),
            N(MAX_NUM),
            size_(0)
		{

		}

/**
	* @brief  push an element to the back of the vector
	* @param  obj
	* @retval Success or Not
	*/
		bool push_back(const T& obj)
		{
			if(size_ == N)
				return false;

			static_array_[size_++] = obj;
			return true;
		}

/**
	* @brief  find the object and remove from the vector
	* @param  value
	* @retval Success or Not
	*/
		bool remove(const T& obj)
		{
			T* ptr = find(obj);
			if(ptr == NULL)
				return false;

			uint16_t dist = static_array_ + sizeof(T) * (size() - 1) - ptr;

			if(dist > 0)
				memmove(ptr, ptr + 1, dist);

			size_--;
			return true;
		}

		void clear()	{ size_ = 0; }

/**
	* @brief  find the object and return the pointer
	* @param  value
	* @retval pointer
	*/
		T* find(const T& obj)
		{
			for(int i = 0; i < size_; i++)
			{
				if(obj == static_array_[i])
					return &static_array_[i];
			}
			return NULL;
		}

/**
	* @brief  Returns a reference to the element at specified location pos.
	* 				No bounds checking is performed.
	* @param 	pos: position of the element to return
	* @retval Reference to the requested element.
	*/
		T& operator[](uint16_t pos)
		{
			return static_array_[pos];
		}

/**
	* @brief  Returns a reference to the element at specified location pos.
	* 				No bounds checking is performed.
	* @param 	pos: position of the element to return
	* @retval Reference to the requested element.
	*/
		const T& operator[] (uint16_t pos) const
		{
			return static_array_[pos];
		}

		uint16_t size() { return size_; }

/**
	* @brief  Returns a reference to the element at specified location pos,
	* 				with bounds checking.
	* @param 	pos: position of the element to return
	* @retval Reference to the requested element.
	*/
	T& at(size_t pos)
	{
		if(!(pos < N))
		{
#ifdef __EXCEPTIONS
			throw static_array_[0];
#else
			while(1);
#endif
		}
		return static_array_[pos];
	}

/**
	* @brief  Returns a reference to the element at specified location pos,
	* 				with bounds checking.
	* @param 	pos: position of the element to return
	* @retval Reference to the requested element.
	*/
	const T& at(size_t pos) const
	{
		if(!(pos < N))
		{
#ifdef __EXCEPTIONS
			throw static_array_[0];
#else
			while(1);
#endif
		}
		return static_array_[pos];
	}

	private:
		// T static_array_[N == 0 ? 1 : N];
        T*& static_array_;
        const uint16_t N;
		uint16_t size_;
};

template <typename T, uint16_t NUM>
class fixed_vector: public fixed_vector_base<T>
{
    public:
        fixed_vector():fixed_vector_base(static_array_, NUM){}
    private:
        T static_array_[NUM == 0 ? 1 : NUM];
};
#endif
//end of file
