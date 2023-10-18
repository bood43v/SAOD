
#include "LinkedList.h"
#include <iostream>

using namespace std;
int main()
{
    LinkedList<int>* list1 = new LinkedList<int>();
 
    list1->InsertAtHead(2);
    list1->InsertAtHead(1);

    list1->InsertAfter(1, 10);

    int* arr = list1->ToListArray();;
    for (int i = 0; i < list1->getSize(); i++)
    {
        cout << arr[i] << endl;
    }
}

