# Linked_List_Demo.cpp

```cpp
// Linked_List_Demo.cpp

#include<iostream>
using namespace std;

class node
{
public:
	int data;
	node *next;
};

class PointerList
{
public:
	PointerList()
	{
		top = NULL;
	}

	bool empty()
	{
		if (top == NULL)
			return true;
		else
			return false;
	}

	void insertAfterPosition(int position, int element)
	{
		node *newptr = new node;
		newptr->data = element;

		if (top == NULL)			//insert the very first element
			if (position == 0)
			{
				newptr->next = NULL;
				top = newptr;
			}
			else
				cout << "Location Error!!";
		else
			if (position == 0)		//insert on the first position when some elements existed
			{
				newptr->next = top;
				top = newptr;
			}
			else				//most cases belongs to this situation (as showed in the class slide)
			{
				node *preptr;
				preptr = top;

				for (int i = 0; i < position - 1; i++)
					preptr = preptr->next;

				newptr->next = preptr->next;
				preptr->next = newptr;
			}
	}

	void insertAfterValue(int value, int element)
	{
		node *newptr = new node;
		newptr->data = element;

		// if list is empty, insert value as first item in list regardless of value
		if (top == NULL)			//insert the very first element
		{
			newptr->next = NULL;
			top = newptr;
		}
		else
		{
			// find index of first occurance of matching element in list
			node *currentptr = top;
			bool found = false;
			while (currentptr != NULL)
			{
				if (value == currentptr->data) // we found a match
				{
					newptr->next = currentptr->next;
					currentptr->next = newptr;
					found = true;
					break; // we found it and we inserted it so we are finished while loop
				}
				currentptr = currentptr->next; // move on to next element in list
			}
			if (!found) // no found a match
			{
				cout << "error, no " << value << " existed in the linked list\n";
			}
		}
	}

	void removeAfterPosition(int position)
	{
		if (position == 0)			//delete the first element
		{
			node * ptr = top;
			top = ptr->next;
			delete(ptr);
		}
		else
		{
			node *preptr;
			preptr = top;
			for (int i = 0; i < position - 1; i++)
				preptr = preptr->next;

			node * ptr = preptr->next;
			preptr->next = ptr->next;
			delete(ptr);
		}
	}

	void removeAfterValue(int preptr_value)
	{
		// if list is empty, must display error because there could be no match
		if (top == NULL)
		{
			cout << "error, no " << preptr_value << " existed in the linked list\n";
		}
		else
		{
			// find index of first occurance of matching element in list
			node *currentptr = top;
			bool found = false;
			while (currentptr != NULL)
			{
				if (preptr_value == currentptr->data) // we found a match
				{
					// we want to delete the next element after the matching element (currentptr->next)
					node * ptrNext = currentptr->next; // ptrNext points to node to be deleted
					if (ptrNext->next != NULL)
					{
						ptrNext = currentptr->next;
						currentptr->next = ptrNext->next;
					}
					else
					{
						currentptr->next = NULL;
					}
					delete(ptrNext);
					found = true;
					break; // we found it and we inserted it so we are finished while loop
				}
				currentptr = currentptr->next; // move on to next element in list
			}
			if (!found) // no found a match
			{
				cout << "error, no " << preptr_value << " existed in the linked list\n";
			}
		}
	}

	void print()
	{
		node *temp;
		temp = top;
		while (temp != NULL)
		{
			cout << temp->data << ",";
			temp = temp->next;
		}
		cout << endl;
	}

private:
	node *top;
	int stackData;
};


int main()
{
	PointerList *pPointerList;
	
	cout << "Inserting and removing values after position\n";
	pPointerList = new PointerList();
	pPointerList->insertAfterPosition(0, 10);
	pPointerList->insertAfterPosition(1, 20);
	pPointerList->insertAfterPosition(2, 30);
	pPointerList->insertAfterPosition(3, 40);
	pPointerList->insertAfterPosition(0, 50);
	pPointerList->insertAfterPosition(3, 60);
	pPointerList->insertAfterPosition(5, 70);
	pPointerList->removeAfterPosition(2);
	pPointerList->print();

	cout << "---\n";

	cout << "Inserting and removing values after matching value\n";
	pPointerList = new PointerList();
	pPointerList->insertAfterValue(0, 10);  //current linked list: 10 (default status, when empty)   
	pPointerList->insertAfterValue(10, 20); //current linked list: 10->20
	pPointerList->insertAfterValue(20, 30); //current linked list: 10->20->30
	pPointerList->insertAfterValue(20, 40);	//current linked list: 10->20->40->30
	pPointerList->insertAfterValue(30, 50);	//current linked list: 10->20->40->30->50
	pPointerList->print();
	pPointerList->insertAfterValue(50, 60);	//current linked list: 10->20->40->30->50->60
	pPointerList->insertAfterValue(5, 70);	//error, no 5 existed in the linked list
	pPointerList->print();
	pPointerList->removeAfterValue(30); 	//current linked list: 10->20->40->30->60
	pPointerList->print();
	pPointerList->removeAfterValue(10);	    //current linked list: 10->40->30->60
	pPointerList->print();
	pPointerList->removeAfterValue(50);	    //error, no 50 existed in the linked list
	pPointerList->print();

	cout << "---\n";

	return 0;
}
```
# Output

```
Inserting and removing values after position
50,10,60,30,70,40,
---
Inserting and removing values after matching value
10,20,40,30,50,
error, no 5 existed in the linked list
10,20,40,30,50,60,
10,20,40,30,60,
10,40,30,60,
error, no 50 existed in the linked list
10,40,30,60,
---
```
