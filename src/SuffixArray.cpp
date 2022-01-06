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
    Node* temp;
    char* alpha;
    int alphaSize=1;

    SuffixArray(char const* word)
    {
        this->alpha = new char[27];
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
        insertionSort(alpha, alphaSize);



        //fill arr with characters
        this->arr = new Node[n];
        this->temp = new Node[n];
        for (int i=0; i<n;i++)
        {
            arr[i] = Node(word [i],i);
            temp[i] = Node(word [i],i);
        }


    }

    void ConstructUsingPrefixDoubling()
    {
        int k=1;
        //First iteration*****************************
        //set r1
        arr[n-1].r1=0;
        temp[n-1].r1=0;//set $ data
        for (int i=0; i<n-1; i++)
        {
            arr[i].r1= getOrderInAlpha(arr[i].c);
            temp[arr[i].idx].r1 = arr[i].r1;
        }

        //set r2
        arr[n-1].r2=0; //set $ data
        int counter=1;

        while(counter<n-1)
        {
            counter= 1;
            for (int i=0; i<n; i++)
            {
                if (arr[i].idx+k <= n-1) {
                    arr[i].r2 = temp[arr[i].idx+k].r1;
                }
            }

            //Nth iteration*****************************
            quickSort(arr,0,n-1);

            int _r1= arr[1].r1;
            int _r2= arr[1].r2;
            for (int i=1; i<n; i++)
            {
                if(arr[i].r1 == _r1)
                {
                    if(arr[i].r2 != _r2)
                    {
                        counter++;
                        _r2 = arr[i].r2;
                    }
                }
                else
                {
                    counter++;
                    _r1 = arr[i].r1;
                    _r2 = arr[i].r2;
                }
                arr[i].r2 = counter;
            }
            k *=2;
            r2r1();
            for (int i = 0; i < n; i++) {
                temp[arr[i].idx].r1 = arr[i].r1;
            }
        }

    }


    void Print()
    {
        for(int i=0; i<n; i++)
        {
            cout<<arr[i].idx<<" ";
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

    void insertionSort(char alpha[], int length){
        char key;
        for(int i = 1; i < length; i++)
        {
            key = alpha[i];
            int j = i;
            // For descending order switch the sign
            while(j >= 1 && alpha[j - 1] > key)
            {
                alpha[j] = alpha[j - 1];
                j--;
            }
            alpha[j] = key;
        }
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
        int ppivot = arr[high].r2;     //second pivot
        int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

        for (int j = low; j <= high - 1; j++)
        {
            // If current element is smaller than the pivot
            if (arr[j].r1 < pivot)
            {
                i++; // increment index of smaller element
                Swap(&arr[i], &arr[j]);
            }
            else if (arr[j].r1 == pivot)
            {
                if (arr[j].r2 < ppivot)
                {
                    i++; // increment index of smaller element
                    Swap(&arr[i], &arr[j]);
                }
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

    void r2r1 ()
    {
        for (int i=0; i<n; i++)
        {
            arr[i].r1=arr[i].r2;
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
