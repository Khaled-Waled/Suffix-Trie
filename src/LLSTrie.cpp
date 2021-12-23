#include <iostream>
using namespace std;
template<class T>
struct ListNode
{
public:
    T* child;
    T* next;
};
template<class T>
class List
{
public:
    ListNode<T>* begin;
    List()
    {
        begin = new ListNode<T>;
    }
};

class Node
{
public:
    char c;
    List<Node> list;
    int index;
    Node(char a)
    {
        this->c = a;
        this->list.begin->next = 0;
        this->list.begin->child = 0;
        //this->child=0;
        this->index=-1;
    }

};
class SuffixTrie
{
private:
    Node* root;
    int suffSize;
    char* suff;
public:
    SuffixTrie(char word[])
    {
        suffSize=1;
        while(word[suffSize-1]!='$')
        {
            suffSize++;
        }
        this->root = new Node('&');
        suff = new char[suffSize];
        this->suff = word;
        buildTrie();
    }
    void buildTrie()
    {
        Node* ptr = root;
        for(int j=0; j<suffSize; j++)
        {
            ptr = root;
            for (int i=j; i<suffSize; i++)
            {
                if(ptr->list.begin->child == 0)
                {
                    ptr->list.begin->child = new Node(suff[i]);
                    ptr=ptr->list.begin->child;
                    if(suff[i]=='$')
                    {
                        ptr->index=j;
                    }
                    continue;
                }
                else
                {
                    ptr=ptr->list.begin->child;
                    while(ptr->c != suff[i])
                    {
                        if (ptr->list.begin->next)
                        {
                            ptr= ptr->list.begin->next;
                        }
                        else
                        {
                            ptr->list.begin->next = new Node(suff[i]);
                            ptr=ptr->list.begin->next;
                            if(suff[i]=='$')
                            {
                                ptr->index=j;
                            }
                            continue;
                        }
                    }
                }
            }
        }
    }

    void Search(char word[])
    {
        int s=0;
        bool found = false;
        while(word[s] != '\0')
        {
            s++;
        }
        //move the pointer to the root of the occurences sub-tree
        Node* ptr = root;
        for(int i=0; i<s; i++)
        {
            ptr = ptr->list.begin->child; // ???????
            while(ptr->list.begin->next)
            {
                if(ptr->c != word[i])
                {
                    ptr = ptr->list.begin->next;
                }
                else
                {
                    break;
                }
            }
            //in the case of ptr = last element in the list, ie. ptr didnt find the element in the middle
            if(!ptr->list.begin->next && ptr->c != word[i])
            {
                found = false;
                break;
            }
            else
            {

                found=true;
            }
        }

        //print all the indicies child in the sub-tree
        if (found)
        {
            printAll(ptr);
            cout << endl;
        }
        else
        {
            cout << "Not Found"<<endl;
        }
    }

private:
    void printAll(Node* curr)
    {
        if(curr->index!=-1)
        {
            cout<<curr->index << " ";
            return;
        }
        Node* temp = curr->list.begin->child;
        while(temp)
        {
            printAll(temp);
            temp = temp->list.begin->next;
        }

    }
};
/*
int main()
{
    SuffixTrie t("bananabanaba$");
    t.Search("ana");
    t.Search("a");
    t.Search("naba");
    t.Search("$");
}
*/
