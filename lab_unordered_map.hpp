#ifndef LAB_UNORDERED_MAP_HPP_
#define LAB_UNORDERED_MAP_HPP_
#define SIZE  701819
#include "labafx.hpp"
namespace Lab {
template <typename Key, typename Value, typename Hash = hash<Key>
          /*, typename KeyEqual=equal_to<Key> */>
// KeyEqual is not required by zht. Make him happy.
class unordered_map {
public:
	struct node
	{
		::std::pair<const Key,Value> data;
		node *next;
		node *pre;
		node *Next;
		node *Pre;
	};
	node *Begin=NULL;
	node *End=NULL;
	node *later;
  node **group;
  unordered_map()
	{
		sum=0;
    group=new node*[SIZE];
	}
  size_t size() const
	{
		return size_t(sum);
	}
  int hash_(Key KEy)
	{
		int Has=Hash()(KEy)%SIZE;
		return Has;
	}
  void insert(::std::pair<Key, Value> kvpair)
	{
    int Ha=hash_(kvpair.first);
    node* newnode=new node{kvpair,NULL,NULL,NULL,NULL};
		if(Begin==NULL)
			Begin=newnode;
		End=newnode;
		newnode->Pre=later;
		newnode->Next=NULL;
		later->Next=newnode;
		later=newnode;
		newnode->next=group[Ha];
		newnode->pre=NULL;
		if(group[Ha])
			group[Ha]->pre=newnode;
		group[Ha]=newnode;
		sum++;
	}
 /* static node *add(node *t) 
	{
     int Ha=hash_(t->data.first);
		 for(Ha=(Ha+1)%SIZE;group[Ha];Ha=(Ha+1)%SIZE);
		 return group[Ha];					
	}*/
  class iterator {
  public:
    // assume Key won't be modified
    // actually priviledge controling is hard
    // since zht doesn't require it. Make him happy
		iterator(node *tt)
		{
			t=tt;
		}
    ::std::pair<const Key, Value> &operator*()
		{
		  return t->data;
		}
    // prefix increment operator is not required by zht. Make him happy
    // NO.
    iterator &operator++()
		{
			t=t->Next;
			return *this;
		}
    iterator &operator--()
		{
			if(t->Pre)
				t=t->Pre;
			return *this;
		}
	 	iterator operator++(int)
		{
			iterator iter=*this;
			++(*this);
			return iter;
		}
    iterator operator--(int)
		{
			iterator iter=*this;
			--(*this);
			return iter;
		}
    bool operator==(const iterator &another) const
		{
			return t==another.t;
		}
    bool operator!=(const iterator &another) const
		{
			return t!=another.t;
		}
		node * self()
		{
			return t;
		}
  private:
		node *t;
    // add your data and function here
  };
  iterator begin()
	{
		return iterator(Begin);
	}
  iterator end()
	{
		return iterator(NULL);
	}
  iterator find(const Key &item)
	{
    int Ha=hash_(item);
		node* tt=group[Ha];
		for(;tt->data.first!=item;tt=tt->next);
		return iterator(tt);
	}
  void erase(iterator iter)
	{
    node *tt=iter.self();
		if(tt->Pre)
		  tt->Pre->Next=tt->Next;
		else
		  Begin=tt->Next;
	  if(tt->Next)
		  tt->Next->Pre=tt->Pre;
	  else
		  End=tt->Pre;	
		int Ha=hash_(tt->data.first);
		if(tt->pre)
		{
			tt->pre->next=tt->next;
			if(tt->next)
				tt->next->pre=tt->pre;
		}
		else
		{
			group[Ha]=tt->next;
			if(tt->next)
				tt->next->pre=NULL;
		}	
		delete tt;
		sum--;
	}
	void clear()
  {
		for(;Begin!=NULL;)
		{
			node *x=Begin;
			Begin=Begin->Next;
			delete x;
		}
	//	delete[] group;
		sum=0;
    Begin=NULL;
  }
  ~unordered_map()
  {
		clear();
	}
private:
	int sum;
  // add your data and function here
};
}
#endif
