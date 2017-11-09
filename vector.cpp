#include "lab_vector.hpp"
#include "labafx.hpp"
#include<iostream>
#include<cstdio>
#include<cstddef>//size_t
namespace lab{
T & vector::iterator::operator*()
{
	return *t;
}
iterator vector::iterator::operator+(int n)
{
	iterator ite=*this;
	ite.t+=n;
	return ite;
}
iterator vector::iterator::operator-(int n)
{
	iterator ite=*this;
	ite.t-=n;
	return ite;
}
iterator vector::begin()
{
	return iterator(&store[0]);
}
iterator vector::end()
{
	return iterator(&store[sizeQAQ]);
}
size_t vector::size()
{
	return sizeQAQ;
}
void vector::push_pack(const T &item)
{
  if(sizeQAQ=biggest)
	{
		restruction();
	}
	store[sizeQAQ++]=item;
}
void vector::pop_back()//empty???
{
	erase(end()-1);
}
void vector::erase(iterator ite)
{
	int dis=ite.t-begin().t;
	if(sizeQAQ)
	{
	  memmove(store+dis,store+dis+1,(sizeQAQ-dis-1)*sizeof(T));//
	  store[--sizeQAQ]=T();
	}
}
void vector::clear()
{
  if(sizeQAQ)
		erase(end()-1);
}
size_t vector::capacty()
{
	return biggest;
}
void vector::shrink_to_fit()//????????????
{
	T* mi=end().t;
	T* mid=&(store[biggest]);
	for(;mid!=mi;)
	{
		T* midd=mid;
		mid--;
		delete midd;
	}
	biggest=sizeQAQ;
}
void vector::reserve(size_t resv_size)//
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
}
