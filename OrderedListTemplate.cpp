#include <typeinfo.h>  // for 'typeid' to work
#include <stdio.h>
#include <string>

using namespace std;

template <class T>
class Node
{
public:
	T value;
	Node* next;
	Node* prev;

	Node(T valueNode)
	{
		value = valueNode;
		next = NULL;
		prev = NULL;
	}
};

template <class T>
class OrderedList
{

private:
	bool _ascending;

public:
	Node<T>* head;
	Node<T>* tail;

	OrderedList(bool asc)
	{
		head = NULL;
		tail = NULL;
		_ascending = asc;
	}

	int compare(T v1, T v2)
	{
		if ( typeid(T) == typeid(string) )
		{
		  	int len_1 = v1.size();
			int count = 0;
			string str_1;
			str_1.resize(len_1 + 1);

			for (int i = 0; i < len_1; i++)
			{
				if (v1[i] != ' ')
				{
					str_1[count++] = v1[i];
				}
			}
			str_1[count] = 0;

			int len_2 = v2.size();			
			string str_2;
			str_2.resize(len_2 + 1);
			count = 0;
			for (int i = 0; i < len_2; i++)
			{
				if (v2[i] != ' ')
				{
					str_2[count++] = v2[i];
				}
			}
			str_2[count] = 0;

			//string str_1 = DeleteSpaces(V1);
			//string str_2 = DeleteSpaces(V2);
			int L1 = str_1.size();
			int L2 = str_2.size();

			int min_length;							// get min length for comparison
			if (L1 > L2) min_length = L2;
			else         min_length = L1;

			for (int i = 1; i < min_length; ++i)			// compare the symbols
			{
				if (str_1[i] < str_2[i])      return -1;
				else if (str_1[i] > str_2[i]) return 1;
			}

			if (L1 < L2)  return -1;						// compare the length
			if (L1 > L2)  return  1;
			if (L1 == L2) return  0;
		}
		else
		{
			if (v1 < v2)  return -1;						// universal comparison
			if (v1 == v2) return  0;
			if (v1 > v2)  return  1;
		}
	}


	void add(T value)
	{
		Node<T>* node = head;
		Node<T>* new_node = new Node<T>(value);

		if (!_ascending)
		{
			while (node != NULL)
			{
				int i = compare(node->value, new_node->value);

				if (i == 0 || i == -1)
				{
					insert_after(node->prev, new_node);
					return;  // exit
				}
				node = node->next;
			}
			add_in_tail(new_node);
		}

		else if (_ascending)
		{
			while (node != NULL)
			{
				int i = compare(node->value, new_node->value);
				if (i == 0 || i == 1)
				{
					insert_after(node->prev, new_node);
					return;  // exit
				}
				node = node->next;
			}
			add_in_tail(new_node);
		}
	}

	Node<T>* find(T val)
	{
		Node<T>* node = head;

		while (node != NULL)
		{

			if (node->value == val)
				return node;
			if (_ascending && node->value > val) return NULL;
			if (!_ascending && node->value < val) return NULL;
			node = node->next;
		}
		return NULL;
	}

	void del(T val)
	{
		Node<T>* node = head;
		while (node != NULL)
		{
			if (node->value == val)
			{
				if (node == head && node == tail)
				{
					head = NULL;
					tail = NULL;
					return;
				}
				if (node == head)
				{
					head = node->next;
					head->prev = node->prev;
					return;
				}
				if (node == tail)
				{
					tail = tail->prev;
					tail->next = NULL;
					return;
				}
				else
				{
					node->prev->next = node->next;
					node->next->prev = node->prev;
					return;
				}
			}
			node = node->next;
		}
	}

	void clear(bool asc)
	{
		_ascending = asc;
		Node<T>* node = head;
		while (node != NULL)
		{
			Node<T>* node_del = node;
			node = node->next;
			delete node_del;
		}
		head = NULL;
		tail = NULL;
	}

	int size()
	{
		int count = 0;
		Node<T>* node = head;
		while (node != NULL)
		{
			count++;
			node = node->next;
		}
		return count;
	}

	T* get_all()     // give the filing of ordered list as array
	{
		int count = size();
		Node<T>* node = head;
		T* list = new T[count];

		for (int i = 0; node != NULL; i++)
		{
			list[i] = node->value;
			node = node->next;
		}
		return list;
	}

protected:  //----------------------------------------------
	void insert_after(Node<T>* nodeAfter, Node<T>* nodeToInsert)
	{
		if (nodeAfter == NULL)
		{
			if (head == NULL)
			{
				add_in_tail(nodeToInsert);
				return;
			}
			else
			{
				head->prev = nodeToInsert;
				nodeToInsert->next = head;
				head = nodeToInsert;
				return;
			}
		}
		nodeToInsert->next = nodeAfter->next;
		nodeToInsert->prev = nodeAfter;
		nodeAfter->next = nodeToInsert;

		if (nodeAfter == tail)
		{
			tail = nodeToInsert;
		}
		else nodeToInsert->next->prev = nodeToInsert;
	}

	void add_in_tail(Node<T>* item)
	{
		if (head == NULL) {
			head = item;
			head->next = NULL;
			head->prev = NULL;
		}
		else {
			tail->next = item;
			item->prev = tail;
		}
		tail = item;
	}
};

//========================= TEST ======================================

bool Compare(int* array, int* result, int array_size, int result_size)
{
	if (result_size != array_size)
		return false;
	else
	{
		for (int j = 0; j < result_size; j++)
		{
			if (result[j] != array[j])
			{
				return false;
			}
		}
	}
	return true;
}

int test_OList()
{
   	int test = 0;
/*
	OrderedList<int>* OList = new OrderedList<int>(true);

	OList->add(1);
	OList->add(5);
	OList->add(7);
	OList->add(1);
	OList->add(6);

	int list_size = OList->size();          // get list_size
	int OListResult[5] = { 1,1,5,6,7 };        // get result array
	int* arrayINT = OList->get_all();         // get OList array
	int* arrayResult = OListResult;
	int result_size = sizeof(OListResult) / sizeof(OListResult[0]);  //get result array size
	if (!Compare(arrayINT, arrayResult, list_size, result_size)) test++;  // compare size and filling

	OList->del(6);
	OList->del(1);
	OList->del(7);

	list_size = OList->size();
	int OListResult2[2] = { 1,5 };
	arrayINT = OList->get_all();
	arrayResult = OListResult2;
	result_size = sizeof(OListResult2) / sizeof(OListResult2[0]);
	if (!Compare(arrayINT, arrayResult, list_size, result_size)) test++;

	Node<int>* node = OList->find(1);
	int value = node->value;
	if (value != 1) test++;

	node = OList->find(5);
	value = node->value;
	if (value != 5) test++;

	OList->clear(false);

	OList->add(1);
	OList->add(5);
	OList->add(7);
	OList->add(1);
	OList->add(6);

	list_size = OList->size();
	int OListResult3[5] = { 7,6,5,1,1 };
	arrayINT = OList->get_all();
	arrayResult = OListResult3;
	result_size = sizeof(OListResult3) / sizeof(OListResult3[0]);
	if (!Compare(arrayINT, arrayResult, list_size, result_size)) test++;

	OList->del(6);
	OList->del(1);
	OList->del(7);

	list_size = OList->size();
	int OListResult4[2] = { 5,1 };
	arrayINT = OList->get_all();
	arrayResult = OListResult4;
	result_size = sizeof(OListResult4) / sizeof(OListResult4[0]);
	if (!Compare(arrayINT, arrayResult, list_size, result_size)) test++;

	node = OList->find(1);
	value = node->value;
	if (value != 1) test++;

	node = OList->find(5);
	value = node->value;
	if (value != 5) test++;
 */

 /*	OrderedList<string>* St_OList = new OrderedList<string>(true);
	St_OList->add("ABE");
	St_OList->add("A");
	St_OList->add(" A B");
     St_OList->add("ABC");

	string* list1 = St_OList->get_all();
	int count2 = St_OList->size();
	count2 = St_OList->size();
     string s1[4] = {"A", " A B", "ABC", "ABE"};

	for (int i = 0; i < count2; i++)
	{
		if(list1[i] != s1[i])
               test++;
	}
	St_OList->del("A");
	St_OList->del("ABE");

     string* list12 = St_OList->get_all();
     count2 = St_OList->size();
     string s12[2] = {" A B", "ABC"};
	for (int i = 0; i < count2; i++)
	{
		if(list12[i] != s12[i])
               test++;
	}

	St_OList->clear(false);
	St_OList->add("A");
	St_OList->add("AB");
	St_OList->add("A B");
	St_OList->add(" ABCB");
	St_OList->del("A B");
	St_OList->add(" ABE");

	string* list2 = St_OList->get_all();
	count2 = St_OList->size();
     string s2[4] = {" ABE"," ABCB","AB","A"};

	for (int i = 0; i < count2; i++)
	{
		if(list2[i] != s2[i])
               test++;
	}
	// delete OList;  */
     //delete St_OList;
	return test;
}
