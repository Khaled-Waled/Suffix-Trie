#include <iostream>
using namespace std;
class Node
{
public:
    char c;
    int idx;
    int r1;
    int r2;

    Node()
    {

    }
    Node(char ch, int i)
    {
        this->c = ch;
        this->idx= i;
        this->r1=-1;
        this->r2=-1;
    }
};

class SuffixArray
{
public:
    int n;
    Node* arr;

    SuffixArray(char word[])
    {
        n=1;
        while(word[n-1] !='$')
        {
            n++;
        }
        this->arr = new Node[n];
        for (int i=0; i<n;i++)
        {
            arr[i] = Node(word [i],i);
        }
    }

    void ConstructUsingPrefixDoubling()
    {
        
    }
    

    void Print()
    {
        for(int i=0; i<n; i++)
        {
            cout<<arr[i].c<<" ";
        }
    }
};

int main()
{
    SuffixArray t("ACGACTACGATAAC$");

    t.ConstructUsingPrefixDoubling();

    t.Print(); // Prints:  14 11 12  0  6  3  9 13  1  7  4  2  8 10  5

    return 0;
}
