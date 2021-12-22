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
    SuffixTrie(string word)
    {
        this->root = new Node('&');
        suff = new char[word.length()];
        this->suff = word;
        this->suffSize = word.length();
        buildTrie();
    }

    void buildTrie()
    {
        Node* ptr = root;
        for (int i=0; i<suffSize; i++)
        {
            if(ptr->down==0)
            {
                ptr->down = new Node(suff[i]);
                ptr=ptr->down;
                if(suff[i]=='$')
                {
                    ptr->index=i;
                    indices[suffSize-i] = ptr;
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
                            indices[suffSize-i] = ptr;
                        }
                        continue;
                    }
                }
            }
        }
    }
    Node* indices[];
};

int main()
{
    //char word[] = {'b','a','n','a','n','a','$'};
    SuffixTrie t("bananabanana$");  
}
