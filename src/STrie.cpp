#include <iostream>
using namespace std;

class Node
{
public:
    char c;
    Node* right;
    Node* down;
    int index;
    Node(char a, Node* r, Node* d)
    {
        this->c = a;
        this->right=r;
        this->down=d;
        this->index=-1;
    }
    Node(char a)
    {
        this->c = a;
        this->right=0;
        this->down=0;
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
            for (int i=j; i<suffSize; i++)
            {
                if(ptr->down==0)
                {
                    ptr->down = new Node(suff[i]);
                    ptr=ptr->down;
                    if(suff[i]=='$')
                    {
                        ptr->index=i;
                    }
                    continue;
                }
                else
                {
                    ptr=ptr->down;
                    while(ptr->c != suff[i])
                    {
                        if (ptr->right)
                        {
                            ptr= ptr->right;
                        }
                        else
                        {
                            ptr->right = new Node(suff[i]);
                            ptr=ptr->right;
                            if(suff[i]=='$')
                            {
                                ptr->index=i;
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
        int s=1;
        bool found = false;
        while(word[s-1]!='$')
        {
            s++;   
        }
        //move the pointer to the root of the occurences sub-tree
        Node* ptr = root;
        for(int i=0; i<s; i++)
        {
            ptr = ptr->down;
            while(ptr-> right)
            {
                if(ptr->c != word[i])
                {
                    ptr = ptr->right;
                }
                else
                {
                    break;
                } 
            }
            //in the case of ptr = last element in the list, ie. ptr didnt find the element in the middle
            if(!ptr->right && ptr->c != word[i])
            {
                break;
            }
            else
            {
                found=true;
            }
        }

        //print all the indicies down in the sub-tree
        //TODO
    }
};

int main()
{
    SuffixTrie t("bananabanana$");  
}
