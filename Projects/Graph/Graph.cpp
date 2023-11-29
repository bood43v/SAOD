#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
    Graph<int>* g1 = new Graph<int>();

    g1->InsertVertex(2);
    g1->InsertVertex(4);

    cout << g1->NumberOfEdges();

}

