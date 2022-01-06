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
private:
    class LLNode
    {
    public:
        Node* data;
        LLNode* next;

        LLNode()
        {
            this->next= nullptr;
        }
    };
public:
    int n;
    Node* arr;
    int* alpha;
    int alphaSize=1;

    SuffixArray(char word[])
    {
        this->alpha = new int[27];
        alpha[0]='$';
        n=1;
        while(word[n-1] !='$')
        {
            //add to alphabet if not already there
            bool flg=true;
            for (int i=1; i<alphaSize; i++)
            {
                if (word[n-1] == alpha[i])
                {
                    flg=false;
                    break;
                }
            }
            if(flg) //add it at the end
            {
                alpha[alphaSize++] = word[n-1];
            }

            //increase the size
            n++;
        
        }
       

        //fill arr with characters
        this->arr = new Node[n];
        for (int i=0; i<n;i++)
        {
            arr[i] = Node(word [i],i);
        }
    }

    void ConstructUsingPrefixDoubling()
    {
        int k=0;
        //First iteration*****************************
        //set r1
        arr[n-1].r1=0; //set $ data
        for (int i=0; i<n-1; i++)
        {
            arr[i].r1= getOrderInAlpha(arr[i].c);
        }
        
        //set r2
        arr[n-1].r2=0; //set $ data
        int counter=1;

        //Second iteration*****************************
        quickSort(arr,0,n);

        

    }
    

    void Print()
    {
        cout<<"|| ";
        for(int i=0; i<n; i++)
        {
            cout<<arr[i].c<<" || ";
        }
        cout<<endl;

        cout<<"|| ";
        for(int i=0; i<n; i++)
        {
            cout<<arr[i].idx<<" || ";
        }
        cout<<endl;

        cout<<"|| ";
        for(int i=0; i<n; i++)
        {
            cout<<arr[i].r1<<" || ";
        }
        cout<<endl;

        cout<<"|| ";
        for(int i=0; i<n; i++)
        {
            cout<<arr[i].r2<<" || ";
        }


    }

    int getOrderInAlpha(char ch)
    {
        for (int i=0; i<=alphaSize; i++)
        {
            if (ch == (char) alpha[i])
            {
                return i;
            }
        }
        return -9;
    }

    Node* sortArr1()
    {
        LLNode* head = new LLNode();
        head->data= &arr[0];

        
        for(int i=1; i<n; i++)
        {
            LLNode llNode = LLNode();
            llNode.data = &arr[i];
            llNode.next = 0;

            LLNode* ptr = head;            
            while (ptr->next != 0)
            {
                if(llNode.data->r1 > ptr->data->r1)
                {
                    ptr = ptr->next;
                }
                else
                {
                    llNode.next = ptr->next;
                    break;
                }
            }
            ptr->next = &llNode;
        }
    }


    int middlePartition(Node nodeArray[], int start, int pivot, int End){
        while(start <= End){
            while(nodeArray[start].r1 < pivot){
                start+=1;
            }
            while(nodeArray[End].r1 > pivot){
                End-=1;
            }
            if(start <= End){
                swap(nodeArray[start], nodeArray[End]);
                start+=1;
                End-=1;
            }
        }
        return start;
    }

    void middledlePivot(Node nodeArray[], int start, int End){
    if(start < End){
        int pivot = nodeArray[(start + End) / 2].r1;

        int pivotRightIndex = middlePartition(nodeArray, start, pivot, End);

        middledlePivot(nodeArray, start, pivotRightIndex - 1);
        middledlePivot(nodeArray, pivotRightIndex, End);

    }
}

    Node* quickSort(Node nodeArray[], int length)
    {
        middledlePivot(nodeArray, 0, length - 1);
        cout << "Quick Sort: ";
    }




void Swap(Node* a, Node* b)
    {
        Node t = *a;
        *a = *b;
        *b = t;
    }

    int partition (Node arr[], int low, int high)
    {
        int pivot = arr[high].r1; // pivot 
        int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

        for (int j = low; j <= high - 1; j++)
        {
            // If current element is smaller than the pivot 
            if (arr[j].r1 < pivot)
            {
                i++; // increment index of smaller element 
                Swap(&arr[i], &arr[j]);
            }
        }
        Swap(&arr[i + 1], &arr[high]);
        return (i + 1);
    }


    void quickSort(Node arr[], int low, int high)
    {
        if (low < high)
        {
            /* pi is partitioning index, arr[p] is now 
            at right place */
            int pi = partition(arr, low, high);

            // Separately sort elements before 
            // partition and after partition 
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
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
