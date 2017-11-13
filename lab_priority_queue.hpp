#ifndef LAB_PRIORITY_QUEUE
#define LAB_PRIORITY_QUEUE

#include "labafx.hpp"
#include<vector>
namespace Lab {

template <typename value_t, typename Comp = Lab::less<value_t>> 
class priority_queue {
public:
  priority_queue()
	{
		sum=0;
		value_t t; 
		node.push_back(t);
	}
  int size() const
	{
		return sum;
	}
  void push(const value_t & t)
	{
		sum++;
    node.push_back(t);
    int now=sum;
		for(;now>1;now/=2)
		{
      if(node[now/2]<node[now])
			  std::swap(node[now],node[now/2]);
			else
				break;
		}
	}
  const value_t &top() const
	{
		return node[1];
	}
  void pop()
	{
    node[1]=node[sum];
		sum--;
		node.pop_back();
		int now=1;
    for(;;)
		{
			int l=2*now;
			int r=l+1;
			if(l>sum)
				break;
			if(r>sum)
			{
				if(node[l]>node[now])
					std::swap(node[l],node[now]);
				break;
			}
			int tt;
			if(node[l]<node[r])
				tt=r;
			else
				tt=l;
			if(node[now]<node[tt])
			{
				std::swap(node[now],node[tt]);
			  now=tt;
			}
			else
				break;
		}
	}
  ~priority_queue()
	{
    node.clear();
		sum=0;
	}
private:
  int sum;
	std::vector<value_t> node;
  // add your data and function here
};
}

#endif
