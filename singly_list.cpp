#include <iostream>
using namespace std;
enum Error_code
{
	Range_error, overflow, underflow,success, fail
};
template <class Node_entry>
struct Node {
	Node_entry entry;//数据域
	Node<Node_entry> *next;//指针域
	Node() {
		next = NULL;
	}
	Node(Node_entry item, Node<Node_entry>* link = NULL)
	{
		entry = item;
		next = link;
	}

	//此处提供了两个构造函数，彼此间是函数的重载关系，函数的具体实现与4.1.3中的方法基本一样。
};

template <class List_entry>
class List {
public:
	List(const List<List_entry>& copy);	//拷贝构造函数
	~List()
	{
		clear();
	}//析构函数
	void operator = (const List<List_entry>& copy);
	//赋值运算符号的重载
	List()  //构造函数
	{
		count = 0;
		head = NULL;
	}
	int size() const;
	bool empty() const;
	void clear();
	Error_code retrieve(int position, List_entry& x) const;
	Error_code replace(int position, const List_entry& x);
	Error_code remove(int position, List_entry& x);
	Error_code insert(int position, const List_entry& x);
	void traverse(void(*visit)(List_entry &));
protected:
	int count;	//结点数量
	Node <List_entry> *head;	//单链表的头指针
	Node <List_entry> * set_position(int position) const;
	//获得第position个结点的位置——返回指针
};

template <class List_entry>
Node<List_entry>* List<List_entry>::set_position(int position) const {
	Node <List_entry> *q = head;
	for (int i = 0; i < position; i++)
		q = q->next;
	return q;
}

template <class List_entry>
int List <List_entry>::size() const {
	return count;
}



template <class List_entry>
bool List<List_entry>::empty() const
{
	return (count == 0);
}

template <class List_entry>
void List<List_entry>::clear()
{
	Node<List_entry> *q, *p;	//删除list中存储的元素
	for (p = head; p; p = q)	// for循环写出了while的用法，值得学习借鉴
	{
		q = p->next;
		delete p;
	}
	count = 0;
	head = NULL;
}

template <class List_entry>
Error_code List<List_entry>::replace(int position, const List_entry& x)
{
	if (position < 0 || position >= count)
		return Range_error;
	set_position(position)->entry = x;
	return success;
}

template <class List_entry>
Error_code List<List_entry> ::retrieve(int position, List_entry &x) const
{
	if (position < 0 || position >= count)
		return Range_error;
	x = set_position(position)->entry;
	return success;
}//如果position值非法，返回出错信息，否则根据position的值，取得表中的第position个元素，并由x返回

template <class List_entry>
Error_code List<List_entry>::insert(int position, const List_entry& x) {
	if (position<0 || position>count)   return Range_error;
	Node <List_entry> *new_node, *previous, *following;
	if (position>0) {
		previous = set_position(position - 1);
		//寻找插入点前一个结点位置
		following = previous->next;
	}
	else   following = head; //定位插入点的后继位置
	new_node = new Node<List_entry>(x, following);
	//生成一个新结点并插在following之前
	if (position == 0)  head = new_node;
	//在0号位置插入时，将head指向新插入结点
	else 	previous->next = new_node;
	//其他位置插入时，将新结点连接在previous之后
	count++;	//计数器变化
	return success;
}


template <class List_entry>
Error_code List<List_entry>::remove(int position, List_entry &x)
{

	if (count == 0)
		return underflow;
	if (position < 0 || position >= count)
		return Range_error;
	else
	{
		x = set_position(position)->entry;
		Node<List_entry>* previous;
		Node<List_entry>* current;
		previous = set_position(position - 1);
		current = set_position(position);
		previous->next = current->next;
		delete current;
		count--;
		return success;
	}
}

template <class List_entry>
List <List_entry>::List(const List<List_entry>& copy)
{
	count = copy.count;
	Node<List_entry> *new_node, *old_node = copy.head;
	if (old_node == NULL) head = NULL;
	else {
		new_node = head = new Node<List_entry>(old_node->entry);
		while (old_node->next != NULL) {
			old_node = old_node->next;
			new_node->next = new Node<List_entry>(old_node->entry);
			new_node = new_node->next;
		}
	}
}

template <class List_entry>
void List<List_entry>::operator = (const List<List_entry> &copy) {
	List new_copy(copy);
	clear();
	count = new_copy.count;
	head = new_copy.head;
	new_copy.count = 0;
	new_copy.head = NULL;
}

template<class List_entry>
void List<List_entry>::traverse(void(*visit)(List_entry &))
{
	Node<List_entry> *q;
	for (q = head; q; q = q->next)
		(*visit) (q->entry);
}void main(){	List<int> lis;
	for (int i = 0; i < 5; i++)
	{
		lis.insert(0, i);
	}
	cout << lis.size() << endl;
	int num;
	lis.retrieve(4, num);
	cout << num << endl;
	lis.remove(3, num);
	cout << num << endl;}