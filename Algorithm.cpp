#include <iostream>
#include <stdlib.h>


#define N 100
#define INF (int)100000

using namespace std;

// Priority queue
bool isempty = true;

class Pair
{
public:
    int data;
    int node;
    Pair *previous;
    Pair *next;
    Pair(int datas, int nodes)
    {
        data = datas;
        node = nodes;
        previous = NULL;
        next = NULL;
    }
};
Pair *head = NULL;
Pair *tail = NULL;
void pqadd(int data, int node)
{
    Pair *temp = new Pair(data, node);
    if (head == NULL)
    {
        head = temp;
        tail = temp;
        isempty = false;
    }
    else
    {
        Pair *temp1 = head;
        while (temp1 != NULL && temp1->data <= data)
        {
            temp1 = temp1->next;
        }
        if (temp1 == NULL)
        {
            if (tail->previous == NULL)
            {
                temp->previous = head;
                head->next = temp;
            }
            else
            {
                (temp->previous) = tail;
                tail->next = temp;
            }
            tail = temp;
        }
        else
        {
            if (temp1->previous == NULL)
            {
                temp->next = head;
                head->previous = temp;
                head = temp;
            }
            else
            {
                temp->previous = temp1->previous;
                temp->next = temp1;
                (temp->previous)->next = temp;
                (temp->next)->previous = temp;
            }
        }
    }
}
Pair *poll()
{
    if (isempty)
        return NULL;
    if (head->next == NULL)
    {
        Pair *temp = head;
        head = NULL;
        tail = NULL;
        isempty = true;
        return temp;
    }
    else
    {
        Pair *temp = head;
        head = temp->next;
        head->previous = NULL;
        return temp;
    }
}

class node
{
public:
    int data, weight;
    node *next;

    node(int data, int weight)
    {
        this->data = data;
        this->weight = weight;
        this->next = NULL;
    }
};

// 2D array or vector
class vector
{
public:
    node *head, *curr;
    int sz;
};

vector v[N];

void insert(int a, int b, int w)
{
    node *newnode = new node(b, w);
    if (v[a].head == NULL)
    {
        v[a].head = newnode;
    }
    else
    {
        v[a].curr->next = newnode;
    }
    v[a].curr = newnode;
    v[a].sz++;
}

void dijkstra(int V)
{

    cout << "Enter source vertex" << endl;
    int src;
    cin >> src;

    int minDistance[V + 1];
    for (int i = 1; i <= V; i++)
    {
        minDistance[i] = INF;
    }

    minDistance[src] = 0;
    pqadd(0, src);

    while (!isempty)
    {
        Pair *par = poll();

        node *temp = v[par->node].head;
        while (temp != NULL)
        {
            if (temp->weight + par->data < minDistance[temp->data])
            {
                minDistance[temp->data] = temp->weight + par->data;
                pqadd(minDistance[temp->data], temp->data);
            }
            temp = temp->next;
        }
    }
    cout << "The shortest distance from source vertex " << src << " to all other vertex" << endl;
    for (int i = 1; i <= V; i++)
    {
        if (minDistance[i] == INF)
        {
            minDistance[i] = -1;
        }
        cout << "Minimum distance from " << src << " to " << i << " is :- " << minDistance[i] << " " << endl;
    }
    cout << endl;
}

int main()
{
    cout << "Enter the number of vertex and edges" << endl;
    int V, E;
    cin >> V >> E;

    cout << "Enter all edges and weight" << endl;
    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        insert(u, v, w);
        insert(v, u, w);
    }

    dijkstra(V);

    return 0;
}
