#ifndef LAB_LIST_HPP_
#define LAB_LIST_HPP_
namespace Lab {
template<typename Type>
class list {
public:
	struct node
	{
		node *pre;
		node *next;
		Type data;
	};
  list();
  void push_back(const Type &elem);
  void push_front(const Type &elem);

  class iterator {
  public:
		iterator();
		iterator(node *tt);
    Type &operator*();
    // assume zht asking for prefix increment
    // make him unhappy
    iterator &operator++();
    iterator &operator--();
		node *Pre()
		{
			return t->pre;
		}
		node *Next() 
		{
			return t->next;
		}
		node *self()
		{
			return t;
		}
    bool operator==(const iterator &another) const;
    bool operator!=(const iterator &another) const;
  private:
		node *t;
    // add your data and function here
  };

  iterator begin();
  iterator end();
  int size() const;
  void pop_front();
  void pop_back();
  void erase(iterator iter);
  void clear();
  ~list();

private:
	node *first;
	node *last;
	int sum;
  // add your data and function here
};
template<typename Type>
list<Type>::list()
{
  sum=0;
	first=NULL;
	last=NULL;
}
template<typename Type>
list<Type>::iterator::iterator()
{
  t=NULL;
}
template<typename Type>
list<Type>::iterator::iterator(node* tt)
{
	t=tt;
}
template<typename Type>
Type &list<Type>::iterator::operator*()
{
	return t->data;
}
template<typename Type>
typename list<Type>::iterator & list<Type>::iterator::operator++()
{
  t=t->next;
	return *this;
}
template<typename Type>
typename list<Type>::iterator & list<Type>::iterator::operator--()
{
	t=t->pre;
	return *this;
}
template<typename Type>
bool list<Type>::iterator::operator==(const iterator &another) const
{
  return t==another.t;
}
template<typename Type>
bool list<Type>::iterator::operator!=(const iterator &another) const
{
	return t!=another.t;
}
template<typename Type>
void list<Type>::push_back(const Type &elem)
{
  node* newnode=new node;
	newnode->data=elem;
	newnode->pre=last;
	newnode->next=NULL;
	if(last)
		last->next=newnode;
	last=newnode;
	if(!sum)
		first=newnode;
	sum++;
}
template<typename Type>
void list<Type>::push_front(const Type &elem)
{
	node* newnode=new node;
  newnode->data=elem;
	newnode->pre=NULL;
	newnode->next=first;
	if(first)
		first->pre=newnode;
	first=newnode;
	if(!sum)
		last=newnode;
	sum++;
}
template<typename Type>
typename list<Type>::iterator list<Type>::begin()
{
	return iterator(first);
}
template<typename Type>
typename list<Type>::iterator list<Type>::end()
{
	return iterator(last);
}
template<typename Type>
int list<Type>::size() const
{
	return sum;
}
template<typename Type>
void list<Type>::pop_front()
{
  node *node1=first->next;
	if(node1)
		node1->pre=NULL;
	delete first;
	first=node1;
	sum--;
}
template<typename Type>
void list<Type>::pop_back()
{
	node *node1=last->pre;
	if(node1)
		node1->next=NULL;
	delete last;
	last=node1;
	sum--;
}
template<typename Type>
void list<Type>::erase(iterator iter)
{
	node *node1=iter.Pre();
	node *node2=iter.Next();
	if(node1!=NULL)
		node1->next=node2;
	if(node2!=NULL)
		node2->pre=node1;
	delete iter.self();
	sum--;
}
template<typename Type>
void list<Type>::clear()
{
	for(;first;first=first->next)
		erase(first);
	first=last=NULL;
	sum=0;
}
template<typename Type>
list<Type>::~list()
{
	clear();
}
}

#endif
// (.*) \(\*(.*)\)\(.*?desc[,]?(.*)\)
// (.*)\(\*(.*)\)\(.*?iter[,]?(.*)\)
