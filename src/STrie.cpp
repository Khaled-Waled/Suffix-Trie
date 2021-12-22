#include <iostream>
using namespace std;

class Node
{
public:
    char c;
    Node* next;
    Node* child;
    int index;
    Node(char a)
    {
        this->c = a;
        this->next=0;
        this->child=0;
        this->index=-1;
    }

};
class SuffixTrie
{
public:
    Node* root;
    int suffSize;
    char* suff;
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
                if(ptr->child==0)
                {
                    ptr->child = new Node(suff[i]);
                    ptr=ptr->child;
                    if(suff[i]=='$')
                    {
                        ptr->index=j;
                    }
                    continue;
                }
                else
                {
                    ptr=ptr->child;
                    while(ptr->c != suff[i])
                    {
                        if (ptr->next)
                        {
                            ptr= ptr->next;
                        }
                        else
                        {
                            ptr->next = new Node(suff[i]);
                            ptr=ptr->next;
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
            ptr = ptr->child;
            while(ptr-> next)
            {
                if(ptr->c != word[i])
                {
                    ptr = ptr->next;
                }
                else
                {
                    break;
                }
            }
            //in the case of ptr = last element in the list, ie. ptr didnt find the element in the middle
            if(!ptr->next && ptr->c != word[i])
            {
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
    }

    void printAll(Node* curr)
    {
        if(curr->index!=-1)
        {
            cout<<curr->index << " ";
            return;
        }
        Node* temp = curr->child;
        while(temp)
        {
            printAll(temp);
            temp = temp->next;
        }

    }
};

int main()
{
    SuffixTrie t("bananabanaba$");
    t.Search("ana"); // Prints: 1 3 7
    t.Search("naba"); // Prints: 4 8
}
