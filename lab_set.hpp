#ifndef LAB_SET_HPP_
#define LAB_SET_HPP_

#include "labafx.hpp"
#include<vector>
// DO NOT MODIFY BELOW

namespace Lab {
template <typename T> class set {
public:
	struct node
	{
		bool color;
		node *(tr[2]);
		node *fa;
		//int number;
		node *pre;
		node *next;
		T value;
	};
	//std::vector<node> tree;
  set()
	{
    sum=0;
		root=NULL;
	} 
  int size() const
	{
		return sum;
	}
	void rotate(node *x)
	{
	  node *y=x->fa;
		node *z=y->fa;
    int l;
		int r;
		if(y->tr[0]==x)
			l=0;
		else
			l=1;
		r=l^1;
		if(y==root)
			root=x;
		else
		{
			if(z->tr[0]==y)
				z->tr[0]=x;
			else
				z->tr[1]=x;
		}
		x->fa=z;
		y->fa=x;
		if(x->tr[r]!=NULL)
		  x->tr[r]->fa=y;
		y->tr[l]=x->tr[r];
		x->tr[r]=y;
	}
	void insertupdata(node *x)// can alter
	{
    for(;x->fa!=NULL&&x->fa->color==0;)
		{
			node *y=x->fa;
			node *z=y->fa;
			int l;
			int r;
			if(y==z->tr[0])
				l=0;
			else
				l=1;
			r=l^1;
			if(z->tr[r]!=NULL&&z->tr[r]->color==0)
			{
				z->tr[r]->color=1;
				y->color=1;
				z->color=0;
				x=z;
				continue;
			}
			if(y->tr[r]==x)
			{
				rotate(x);
				std::swap(x,y);
			}
			y->color=1;
			z->color=0;
			rotate(y);
		}
    root->color=1;
	}
  void insert(const T &item)
	{
		//std::cout<<"1 "<<item<<std::endl;
		T max=item;
		node *maxx=NULL;
		T min=item;
		node *minn=NULL;
    node *newnode=new node;
    newnode->color=0;
		newnode->tr[0]=NULL;
		newnode->tr[1]=NULL;
		newnode->fa=NULL;
		newnode->pre=NULL;
		newnode->next=NULL;
		newnode->value=item;
		//newnode.number=sum;
		//tree.push_back(newnode);
		if(root==NULL)
      root=newnode;
		else
		{
			node *x=root;
			node *y;
			for(;x!=NULL;)
			{
				y=x;
				if(x->value>item)
				{
					if(x->value<max||max==item)
					{
						max=x->value;
						maxx=x;
					}
					x=x->tr[0];
				}
				else
				{
					if(x->value>min||min==item)
					{
						min=x->value;
						minn=x;
					}
					x=x->tr[1];
				}
			}
			newnode->fa=y;
      if(y->value>item)
				y->tr[0]=newnode;
			else
				y->tr[1]=newnode;
	    if(maxx!=NULL)
			{
				newnode->next=maxx;
				maxx->pre=newnode;
			}
			if(minn!=NULL)
			{
				newnode->pre=minn;
				minn->next=newnode;
			}
	  }
		insertupdata(newnode);
    sum++;
	}
  class iterator {
  public:
    const T &operator*()
		{
			return t->value;
		}
		node* ret()
	  {
			return t;
		}
		iterator()
		{
			t=NULL;
		}
		iterator(node *tt)
		{
			t=tt;
		}	
		iterator& operator++()
		{
			t=t->next;
			return *this;
		}
		iterator& operator--()
		{
			t=t->pre;
			return *this;
		}
    iterator operator++(int)	// for iter++
		{
			iterator iter=this;
			++this;
			return iter;
		}
    iterator operator--(int)
		{
		  iterator iter=this;
			--this;
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
  private:
    node *t;
    // add your data and function here
  };
  iterator find(const T &item)
	{
		node *x=root;
		for(;x->value!=item;)
		{
			if(x->value>item)
				x=x->tr[0];
			else
				x=x->tr[1];
		}
		return iterator(x);
	}
	void eraseupdata(node *x,node *father)
	{
		node *brother;
    for(;(x==NULL||x->color==1)&&x!=root;)
	    {
				int l;
				int r;
				if(father->tr[0]==x)
					l=0;
				else
					l=1;
				r=l^1;
				brother=father->tr[r];
				if(brother->color==0)
				{
					brother->color=1;
					father->color=0;
					rotate(brother);
					brother=father->tr[r];
				}
        if((brother->tr[0]==NULL||brother->tr[0]->color)&&(brother->tr[1]==NULL||brother->tr[1]->color))
				{
          brother->color=0;
				  x=father;
					father=x->fa;
				}
				else
				{
					if(brother->tr[r]==NULL||brother->tr[r]->color)
					{
						brother->tr[l]->color=1;
						brother->color=0;
						rotate(brother->tr[l]);
						brother=father->tr[r];
					}
					brother->color=father->color;
					father->color=1;
					brother->tr[r]->color=1;
					rotate(brother);
					x=root;
					break;
				}
			}
		if(x!=NULL)
			x->color=1;
	}
  void erase(iterator it)
	{
	//	printf("-1 ");
	  sum--;
		node *x=it.ret();
		node *del=x;
		node *child;
		if(x->tr[0]!=NULL&&x->tr[1]!=NULL)
      {
				del=x->tr[0];
				for(;del->tr[1]!=NULL;del=del->tr[1]);
			}
    if(del->tr[0]==NULL)
			child=del->tr[1];
		else 
			child=del->tr[0];
	 if(child!=NULL)
		 child->fa=del->fa;
	 if(del->fa==NULL)
		 root=child;
	 else  if(del==del->fa->tr[0])
		       del->fa->tr[0]=child;
	       else
					 del->fa->tr[1]=child;
	 if(del!=x)
     x->value=del->value;
	 if(del->pre!=NULL)
		 del->pre->next=del->next;
	 if(del->next!=NULL)
		 del->next->pre=del->pre;
   if(del->color==1)
		 eraseupdata(child,del->fa);
	 delete del;
	}
  iterator begin()
	{
		node *x=root;
		if(root==NULL)
      return iterator();
	//	printf("%d %d\n",x,sum);
		for(;x->tr[0]!=NULL;x=x->tr[0]);
		return iterator(x);
	}
  iterator end()//all trouble???????
	{
		if(root==NULL)
			return iterator();
		node *x=root;
		for(;x->tr[1]!=NULL;x=x->tr[1]);
		return iterator(x);
	}
	void nclear(node *x)
	{
		if(x==NULL)
			return;
    nclear(x->tr[0]);
		nclear(x->tr[1]);
		delete x;
		return;
	}
  void clear()
	{
		sum=0;
		node *x=root;
		nclear(x);
    root=NULL;
  }
  ~set()
	{
		clear();
	}

private:
	int sum;
	node *root;
  // add your data and function here
};
}
#endif
