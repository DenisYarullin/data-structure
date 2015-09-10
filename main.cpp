#include <iostream>
//#include "linked_list.h"
#include "doubly_linked_list.h"


using namespace std;


int main()
{
	DoublyLinkedList<int> list;
	list.Add(3);
	list.AddFirst(100);
	list.Add(4);
	list.AddLast(200);
	list.Add(5);

	//cout << list.Count() << endl;
	//cout << list.Contains(4) << endl;
	
	list.Remove(4);
	list.RemoveFirst();
	list.Remove(5);
	list.RemoveLast();
	list.Remove(3);

	//cout << list.Count() << endl;
	//cout << list.Contains(4) << endl;

	list.Add(3);
	list.AddFirst(100);
	list.Add(4);
	list.AddLast(200);
	list.Add(5);

	//list.Clear();

	cin.get();

	return 0;
}