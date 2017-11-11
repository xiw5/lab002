#ifndef LAB_VECTOR_HPP_
#define LAB_VECTOR_HPP_

#include "labafx.hpp"
#include<cstring>
namespace Lab {
template <typename T> class vector {
public:
  vector();
  class iterator {
  public:
		iterator()
		{
			t=NULL;
		}
		iterator(T *tt)
		{
			t=tt;
		}
    T &operator*();
		int operator-(const iterator &another)
		{
			return t-another.t;
		}
    iterator operator+(int n);
		iterator operator-(int n);
    // zht does not require the followings, make him happy.
    // NOOOOOOOOOOOOO!
    iterator& operator++();
    bool operator==(const iterator &another) const;
    bool operator!=(const iterator &another) const;
    // iterator operator++(int);
  private:
		T* t;
    // add your data and function here
  };
  iterator begin();
  iterator end();
  size_t size() const;
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
	void restruction();
  // add your data and function here
};
template <typename T>
vector<T>::vector()
{
  store=NULL;
	sizeQAQ=0;
	biggest=0;
}
template <typename T>
T & vector<T>::iterator::operator*()
{
	return *t;
}
template <typename T>
typename vector<T>::iterator vector<T>::iterator::operator+(int n)
{
	iterator ite=*this;
	ite.t+=n;
	return ite;
}
template <typename T>
typename vector<T>::iterator vector<T>::iterator::operator-(int n)
{
  iterator ite=*this;
	ite.t-=n;
	return ite;
}
template <typename T>
typename vector<T>::iterator & vector<T>::iterator::operator++()
{
	t++;
	return *this;
}
template <typename T>
bool vector<T>::iterator::operator==(const iterator &another) const
{
	return t==another.t;
}
template <typename T>
bool vector<T>::iterator::operator!=(const iterator &another) const
{
	return t!=another.t;
}
template <typename T>
typename vector<T>::iterator vector<T>::begin()
{
	return iterator(&store[0]);
}
template <typename T>
typename vector<T>::iterator vector<T>::end()
{
	return iterator(&store[sizeQAQ]);
}
template <typename T>
size_t vector<T>::size() const
{
	return size_t(sizeQAQ);
}
template <typename T>
void vector<T>::push_back(const T &item)
{
  if(sizeQAQ==biggest)
	{
		restruction();
	}
	store[sizeQAQ++]=item;
}
template <typename T>
void vector<T>::pop_back()//empty???
{
	erase(end()-1);
}
template <typename T>
void vector<T>::erase(iterator ite)
{
	int dis=ite-begin();
	if(sizeQAQ)
	{
	  memmove(store+dis,store+dis+1,(sizeQAQ-dis-1)*sizeof(T));//
	  store[--sizeQAQ]=T();
	}
}
template <typename T>
void vector<T>::clear()
{
  for(;sizeQAQ;)
		erase(end()-1);
}
template <typename T>
size_t vector<T>::capacity()
{
	return size_t(biggest);
}
template <typename T>
void vector<T>::shrink_to_fit()//????????????
{
	T* mi=&(store[sizeQAQ]);
  store=(T*)realloc(store,(sizeQAQ+1)*sizeof(T));
	biggest=sizeQAQ;
}
template <typename T>
void vector<T>::reserve(size_t resv_size)//
{
   biggest=(int)resv_size;
	 T* newstore=new T[biggest+1];
	 if(store)
	 {
		 memcpy(newstore,store,sizeQAQ*sizeof(T));
		 delete[] store;
	 }
	 store=newstore;
}
template <typename T>
void vector<T>::restruction()
{
		biggest=biggest*3/2+1;//??????????????????
		T* newstore=new T[biggest+1];// end???????????????????
		if(store)
		{
      memcpy(newstore,store,sizeQAQ*sizeof(T));
			delete[] store;
		}
		store=newstore;
}
template <typename T>
vector<T>::~vector()
{
  if(store)
	{
		delete[] store;
		store=NULL;
	}
	sizeQAQ=biggest=0;
}
}
#endif
