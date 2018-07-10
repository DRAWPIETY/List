#include <iostream>

using namespace std;

int const max_list = 10;

enum Error_code
{
	success, fail, range_out,underflow,overflow
};


template <class List_entry>
class List
{
public:
	List();
	int size() const;
	bool full() const;
	bool empty() const;
	void clear();
	void traverse(void (*vist)(List_entry &));
	Error_code retrieve(int position, List_entry &x) const;
	Error_code replace(int position, const List_entry &x);
	Error_code remove(int position, List_entry &x);
	Error_code insert(int position, const List_entry x);
protected:
	int count;
	List_entry entry[max_list];
};

template <class List_entry>
List<List_entry>::List()
{
	count = 0;
}

template <class List_entry>
int List<List_entry>::size() const
{
	return count;
}

template <class List_entry>
bool List<List_entry>::full() const
{
	return count >= max_list;
}

template <class List_entry>
bool List<List_entry>::empty() const
{
	return count <= 0;
}

template <class List_entry>
void List<List_entry>::clear()
{
	count = 0;
}


template <class List_entry>
void List<List_entry>::traverse(void(*visit)(List_entry &))
{
	for(int i = 0; i < count; i++)
		(*visit)(entry[i]);
}


template <class List_entry>
Error_code List<List_entry>::retrieve(int position, List_entry &x)const
{
	if(position < 0 || position >= count)
		return range_out;
	else
		x = entry[position];
	return success;
}

template <class List_entry>
Error_code List<List_entry>::replace(int position, const List_entry &x)
{
	if(position < 0 || position >= count)
		return range_out;
	else
		entry[position] = x;
	return success;
}

template <class List_entry>
Error_code List<List_entry>::remove(int position, List_entry &x)
{
	if(position == 0)
		return underflow;
	if(position < 0 || position >= count)
		return range_out;
	x = entry[position];
	count--;
	while(position < count)
	{
		entry[position] = entry[position + 1];
		position++;
	}
	return success;
}

template <class List_entry>
Error_code List<List_entry>::insert(int position, List_entry x)
{
	if(full())
		return overflow;
	if(position < 0 || position > count)
		return range_out;
	for(int i = count - 1; i >= position; i--)
		entry[i + 1] = entry[i];
	entry[position] = x;
	count++;
	return success;
}

void main()
{
	List<int> lis;
	for (int i = 0; i < 5; i++)
	{
		lis.insert(0, i);
	}
	cout << lis.size() << endl;
	int num;
	lis.retrieve(4, num);
	cout << num << endl;
	lis.remove(3, num);
	cout << num << endl;
	
}