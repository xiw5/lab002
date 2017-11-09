#ifndef LAB_VECTOR_HPP_
#define LAB_VECTOR_HPP_

#include "labafx.hpp"
#include<cstdio>
#include<cstring>
namespace Lab {
template <typename T> class vector {
public:
  vector();
  class iterator {
  public:
    T &operator*();
    iterator operator+(int n);
		iterator operator-(int n);
    // zht does not require the followings, make him happy.
    // iterator& operator++();
    // iterator operator++(int);
  private:
		T* t;
    // add your data and function here
  };
  iterator begin();
  iterator end();
  size_t size();
  void push_back(const T &item);
  void pop_back();
  void erase(iterator iter);
  void clear();
  size_t capacity();
  void shrink_to_fit();
  void reserve(size_t resv_size);
  ~vector();

private:
	T* store;
	int sizeQAQ;
	int biggest;
	void restruction()
	{
		biggest=biggest*3-1;//??????????????????
		T* newstore=new T[biggest+1];// end???????????????????
		if(store)
		{
      memcpy(newstore,store,sizeQAQ*sizeof(T));
			delete[] store;
		}
		store=newstore;
	}
  // add your data and function here
};
}

#endif
