
#include "LinkedList.h"
#include <iostream>

using namespace std;
int main()
{
    LinkedList<int>* list1 = new LinkedList<int>();
 
    list1->InsertAtTail(5);///  5 10 20 30 40
    list1->InsertAtTail(10);
    list1->InsertAtTail(20);
    list1->InsertAtTail(30);
    list1->InsertAtTail(40);
    list1->InsertAfter(20, 15);
    /*list1->InsertAfter(1, 10);*/

    int* arr = new int[list1->Size()];
    arr = list1->ToListArray();
    for (int i = 0; i < list1->Size(); i++)
    {
        cout << arr[i] << endl;
    }

    ListNode<int>* newNode = new ListNode<int>(5555);
    cout << newNode->Data();
}

