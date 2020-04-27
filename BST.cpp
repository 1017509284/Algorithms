#include <iostream>
#include <functional>
#include <stack>
#include <queue>
using namespace  std;

class BSTree
{
public:
    BSTree():root(nullptr){}
    ~BSTree(){}
    void insert(const int &val)
    {
        if(root==nullptr)
        {
            root=new Node(val);
            return ;
        }
        Node *cur=root;
        Node *parent=nullptr;
        while(cur!= nullptr)
        {
            if(cur->data > val)
            {
                parent=cur;
                cur=cur->left;
            }
            else if(cur->data < val)
            {
                parent=cur;
                cur=cur->right;
            }
            else
            {
                return;
            }
        }
        if(val < parent->data)
        {
            parent->left=new Node(val);
        }
        else
        {
            parent->right=new Node(val);
        }
    }
    void remove(const int &val)
    {
        if(root== nullptr)
        {
            return ;
        }
        Node *cur=root;
        Node *parent=nullptr;
        while(cur!= nullptr)
        {
            if(val < cur->data)
            {
                parent=cur;
                cur=cur->left;
            }
            else if(val > cur->data)
            {
                parent=cur;
                cur=cur->right;
            }
            else
            {
                break;
            }
        }

        if(cur==nullptr)
        {
            return;
        }

        if(cur->left!= nullptr && cur->right!= nullptr)
        {
            parent=cur;
            Node *pre=cur->left;
            while(pre->right!= nullptr)
            {
                parent=pre;
                pre=pre->right;
            }
            cur->data = pre->data;
            cur = pre;
        }

        Node * child = cur->left;
        if (child == nullptr)
        {
            child = cur->right;
        }

        if(parent==nullptr)
        {
            root=child;
        }
        else
        {
            if(cur->left==cur)
            {
                parent->left=child;
            }
            else
            {
                parent->right=child;
            }
        }
        delete cur;
    }
    bool query(const int &val)
    {
        Node *cur=root;
        while(cur!= nullptr)
        {
            if(cur->data == val)
            {
                return true;
            }
            else if(val < cur->data)
            {
                cur=cur->left;
            }
            else
            {
                cur=cur->right;
            }
        }
        return false;
    }
    void preOrder()
    {
        stack<Command> stack;
        stack.push(Command("go",root));
        while(!stack.empty())
        {
            Command command=stack.top();
            stack.pop();
            if(command.s=="print")
            {
                cout<<command.node->data<<" ";
            }
            else
            {
                if(command.node->right)
                {
                    stack.push(Command("go",command.node->right));
                }
                if(command.node->left)
                {
                    stack.push(Command("go",command.node->left));
                }
                stack.push(Command("print",command.node));
            }
        }
        cout<<endl;
    }
    void levelOrder()
    {
        queue<Node *> q;
        q.push(root);
        while(!q.empty())
        {
            Node *cur=q.front();
            q.pop();
            cout<<cur->data<<" ";
            if(cur->left)
                q.push(cur->left);
            if(cur->right)
                q.push(cur->right);
        }
        cout<<endl;
    }
    void findValues(int i,int j)
    {
        findValues(root,i,j);
    }
private:
    struct Node
    {
        Node(int val=int()):data(val),left(nullptr),right(nullptr){}
        int data;
        Node *left;
        Node *right;
    };
    struct Command
    {
        string s;
        Node *node;
        Command(string s,Node *node):s(s),node(node){}
    };
    Node *root;
    void findValues(Node *node,int i,int j)
    {
        if(node!= nullptr)
        {
            if(node->data > i)
                findValues(node->left,i,j);
            if(node->data>=i && node->data<=j)
            {
                cout<<node->data<<" ";
            }
            if(node->data < j)
                findValues(node->right,i,j);
        }
    }
};
int main()
{
    int arr[]={58,24,67,0,34,62,69,5,41,78};
    BSTree bst;
    for(int v:arr)
    {
        bst.insert(v);
    }


    bst.preOrder();
    bst.levelOrder();
    bst.findValues(10,60);
    return 0;
}
