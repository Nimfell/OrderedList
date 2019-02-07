                

#include <typeinfo.h>  // for 'typeid' to work
#include <stdio.h>
#include <string>

using namespace std;


class Node
{
public:
	int value;
	Node* next;
	Node* prev;

	Node(int valueNode)
	{
		value = valueNode;
		next = NULL;
		prev = NULL;
	}
};


class OrderedList
{

private:
	bool _ascending;

public:
	Node* head;
	Node* tail;

	OrderedList(bool asc)
	{
		head = NULL;
		tail = NULL;
		_ascending = asc;
	}

	int compare(int v1, int v2)
	{
	        if (v1 < v2)  return -1;						// universal comparison
	        if (v1 == v2) return  0;
	        if (v1 > v2)  return  1;
	}


	void add(int value)
	{
		Node* node = head;
		Node* new_node = new Node(value);

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

	Node* find(int val)
	{
		Node* node = head;

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

	void del(int val)
	{
		Node* node = head;
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
		Node* node = head;
		while (node != NULL)
		{
			Node* node_del = node;
			node = node->next;
			delete node_del;
		}
		head = NULL;
		tail = NULL;
	}

	int size()
	{
		int count = 0;
		Node* node = head;
		while (node != NULL)
		{
			count++;
			node = node->next;
		}
		return count;
	}

	int* get_all()     // give the filing of ordered list as array
	{
		int count = size();
		Node* node = head;
		int* list = new int[count];

		for (int i = 0; node != NULL; i++)
		{
			list[i] = node->value;
			node = node->next;
		}
		return list;
	}

protected:  //----------------------------------------------
	void insert_after(Node* nodeAfter, Node* nodeToInsert)
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

	void add_in_tail(Node* item)
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

	OrderedList* OList = new OrderedList(true);

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

	Node* node = OList->find(1);
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
        delete OList;

	return test;
}
