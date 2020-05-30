#include<iostream>
#include<list>
#include<unordered_map>
using namespace std;

class LRU
{
    list<int> ll;
    unordered_map<int,int> map;
    int defaultsize=0;
    void set(int key,int val)
    { 
        if(map.find(key)==map.end())
        {
            if(ll.size() == defaultsize)
            {
                int lastkey=ll.back();
                ll.pop_back();
                map.erase(lastkey);
            }
        ll.push_front(key);
        map[key]=val;
        }
        else
        {
            ll.remove(key);
            ll.push_front(key);
            map[key]=val;
        }
    }
    int get(int key)
    {
       if(map.find(key)!=map.end())
       {
           return map[key];
       }
       else
       {
           return -1;
       }
       
    }
};
class linkedlist{
    public :
        class Node 
        {
            public :
               int data=0;
               Node *next=nullptr;

               Node(int data)
               {
                   this->data=data;
               }
        };
    private:
         Node *head=nullptr;
         Node *tail=nullptr;
         int size=0;

//basic========================================================================================================
    public :
        linkedlist()
        {
            Node *temp=head;
            while(head != nullptr)
            {
                head=head->next;
                delete temp;
                temp=head;
            }
        }  
       int addfirst(int data)
        {
            Node *node=new Node(data);
            if(head== nullptr)
            {
                head=node;
                tail=node;
            }
            else
            {
                node->next=head;
                head=node;
            }
            size++;
        }
        void addlast(int data)
        {
            Node *node=new Node(data);
            if(tail==nullptr)
            {
                head=node;
                tail=node;
            }
            else
            {
                tail->next=node;
                tail=node;
            }
            size++;
        }
        int removefirst()
        {
            Node *rn=nullptr;
            if(head !=nullptr)
            {
                if(size==1)
                {
                    tail=nullptr;
                }
                rn=head;
                head=head->next;
            }
            int data= rn!=nullptr ? rn->data : -1;
            size--;
             delete rn;
            return data;
        }
        Node *getnodeat(int idx)
        {
            if(idx==0)
            {
                return head;
            }
            Node *temp=head;
            while(idx !=0)
            {
                temp=temp->next;
                idx--;
            }
            return temp;
        }
        void addat(int idx,int data)
        {
            if(idx>size || idx <0 )
            {
                return;
            }
            if(idx ==0 )
            {
                addfirst(data);
            }
            else if(idx==size)
            {
                addlast(data);
            }
            else
            {
                Node *prev=getnodeat(idx-1);
                Node *next=prev->next;

                Node *node=new Node(data);
                prev->next=node;
                node->next=next;
                size++;
            }
        }
        int removelast()
        {
            Node *rn=nullptr;
            if(size==1)
            {
                rn=tail;
                head=nullptr;
                tail==nullptr;
            }
            else
            {
                Node *temp=getnodeat(size-2);
                rn=tail;
                temp->next=nullptr;
                tail=temp;
            }
            int data=rn!=nullptr ? rn->data : -1;
            delete rn;
            return data;
        }
        void removeat(int idx)
        {
            if(idx>=size || idx<0)
            {
                return;
            }
            if(idx==0)
            {
                removefirst();
            }
            else if(idx== size-1)
            {
                removelast();
            }
            else
            {
                Node *prev=getnodeat(idx-1);
                Node *forward=prev->next;
                prev->next=forward->next;
                size--;
                delete forward;
            }
        }
        Node *mid(Node *head)
        {
            Node *slow=head;
            Node *fast=head;

            while(fast != nullptr && fast->next!=nullptr && fast->next->next !=nullptr)
            {
                fast=fast->next->next;
                slow=slow->next;
            }
            return slow;
        }
        void display()
        {
            Node *curr=head;
            while(curr!= nullptr)
            {
                cout<<curr->data<<" ";
                curr=curr->next;
            }
            cout<<endl;
        }
//reverse==================================================================================
        class pairrev
        {
            public :
              Node *prevnode=NULL;
        };
        
        void reversedatarec_(Node *node,pairrev *prev,int level)
        {
             if(node == nullptr)
              return;
             reversedatarec_(node->next,prev,level+1);
             if(level > size/2)
             {
                  int temp= prev->prevnode->data;
                  prev->prevnode->data=node->data;
                  node->data=temp;

                  prev->prevnode=prev->prevnode->next;
             }
        }
    public:
        void reversedatarec()
        {
            pairrev *prev=new pairrev();
            prev->prevnode=head;

            reversedatarec_(head,prev,0);
        } 
    private:
        Node *reverselist_(Node *node)
        {
             Node *prev=nullptr;
             Node *curr=node;

             while(curr!=nullptr)
             {
                 Node *forw=curr->next;
                 curr->next=prev;
                 prev=curr;
                 curr=forw;
             }
             return prev;
        }
    public:
        void reverselist()
        {
          Node *prev=reverselist_(head);

          tail=head;
          head=prev;
        }
        bool ispalindrome()
        {
            Node *midnode=mid(head);
            Node *nhead=midnode->next;
            midnode->next=nullptr;

            Node *prev=reverselist_(nhead);
            
            Node *list1=head;
            Node *list2=prev;
            bool flag=true;
            while(list1 !=nullptr && list2 != nullptr)
            {
                if(list1->data != list2->data)
                {
                    flag=false;
                }
                list1=list1->next;
                list2=list2->next;
            }
            prev= reverselist_(prev);
            midnode->next=nhead;
            return flag;
        }
        Node *fold()
        {
            Node *midnode=mid(head);
            Node *nhead=midnode->next;
            midnode->next=nullptr;
            Node *prev=reverselist_(nhead);
           
            Node *curr1=head;
            Node *curr2=prev;
            
            while(curr2!=nullptr)
            {
                Node *cn1=curr1->next;
                Node *cn2=curr2->next;

                curr1->next=curr2;
                curr2->next=cn1;

                curr1=cn1;
                curr2=cn2;
            }

            if(curr1 !=nullptr)
             tail=curr1;
            else
            {
                tail=nhead;
            }
            return head;
        }
        Node *unfold()
        {
            linkedlist nll1,nll2;
            while(head != nullptr)
            {
            int first=removefirst();
            nll1.addfirst(first);
            int second=removefirst();
            nll2.addlast(second);
            }
            nll1.head->next=nll2.head;
            return nll1.head;
        }
        Node *detectcycle()
        {
            Node *slow=head;
            Node *fast=head;

            while(fast !=nullptr && fast->next !=nullptr )
            {
                slow=slow->next;
                fast=fast->next->next;

                if(slow==fast)
                break;
            }
            if(slow==fast)
            {
                fast=head;
                while(slow!=fast)
                {
                    slow=slow->next;
                    fast=fast->next;
                }
            }
            return fast;
        }
        
};

      void solve()
      {
          linkedlist ll;
          for(int i=1;i<=10;i++)
          {
             ll.addfirst(i*10);
          }
          ll.addlast(70);
          for (int i = 10; i >= 1; i--)
          {
         //     ll.addfirst(i * 10);
          }
          //ll.removelast();
        // ll.display();
         // ll.reversedatarec();
        //  ll.reverselist();
        
         // cout<<ll.ispalindrome() << endl;
         // ll.fold();
         // ll.display();
           //ll.unfold();
         // ll.display();
         // cout<<ll.detectcycle()->data;
      }

    int main()
    {
        solve();
        return 0;
    }