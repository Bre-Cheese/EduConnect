#ifndef SSLIST_H
#define SSLIST_H

#include <iostream>

using namespace std;

template <typename T>
class SLList;

template <typename T>
class SLLNode
{
private:
    T info;
    SLLNode<T>* next;
    friend class SLList<T>;
public:
    SLLNode()
    {
    }
    SLLNode(T info, SLLNode<T>* next)
    {
       this->info = info;
       this->next = next;
    }
    SLLNode(T info)
    {
       this->info = info;
       this->next = nullptr;
    }
    ~SLLNode()
    {
    }

    T getInfo() const
    {
        return info;
    }
    SLLNode<T>* getNext() const
    {
        return next;
    }
};



template <typename T>
class SLList
{
private:
    SLLNode<T>* head = nullptr;
    SLLNode<T>* tail = nullptr;
public:
    SLLNode<T>* getHead() const
    {
       return head;
    }

    SLLNode<T>* getTail() const
    {
       return tail;
    }

    void addToHead(const T info)
    {
       head = new SLLNode<T>(info, head);
       if(head->next == nullptr)
       {
          tail = head;
       }
    }
    void addToTail(const T info)
    {
       SLLNode<T>* temp = new SLLNode<T>(info);
       if(head == nullptr)
       {
          head = temp;
          tail = temp;
       }
       tail->next = nullptr;
       tail = temp;
    }

    T deleteFromHead()
    {
       if (head == nullptr)
       {
          cout << "\n\nFailed to delete from head: no elements in list\n\n";
          return -1;
       }
       SLLNode<T>* oldHead = head;
       T tempInfo = oldHead->info;
       
       if (head == tail)
       {
          head = nullptr;
          tail = nullptr;
       }
       else
       {
          head = oldHead->next;
          oldHead->~SLLNode<T>();
       }
       
       return tempInfo;
       
    }
    T deleteFromTail()
    {
       if (head == nullptr)
       {
          cout << "\n\nFailed to delete from tail: no elements in list\n\n";
          return -1;
       }
       
       T tempInfo = tail->info;

       SLLNode<T>* beforeTail = head;
       if (head == tail)
       {
          head = nullptr;
          tail = nullptr;
       }
       else
       {
          //find node just before tail
          while(beforeTail->next != tail)
          {
             beforeTail = beforeTail->next;
          }
          tail->~SLLNode<T>();
          tail = beforeTail;
          tail->next = nullptr;
       }

       return tempInfo;
    }

    T deleteNode(const int index)
    {
       if (index == 0)
       {
          deleteFromHead();
       }
       else
       {
          SLLNode<T>* toPop = head;
          SLLNode<T>* beforeToPop = toPop;
          for(int i = 0; i < index; i++)
          {
             if(toPop == tail)
             {
                cout << "\n\nFailed to delete node at " << index << ": index out of bounds\n\n";
                return -1;
             }
             else
             {
                beforeToPop = toPop;
                toPop = head->next;
             }
          }
          if (toPop == tail)
          {
             deleteFromTail();
          }
          else
          {
             beforeToPop->next = toPop->next;
             toPop->~SLLNode<T>();
          }
       }
       return 0;
    }

   SLLNode<T>* search(const T compare) const
    {
       SLLNode<T>* searchPoint = head;
       while(searchPoint != nullptr)
       {
          if(searchPoint->info == compare)
          {
             return searchPoint;
          }
          searchPoint = searchPoint->next;
       }
       return nullptr;
    }

    bool isEqualTo(const SLList<T> compareTo) const
    {
        SLLNode<T>* tempCompare = head;
        SLLNode<T>* tempCompareTo = compareTo.getHead();

        if(tempCompare->info != tempCompareTo->info)
        {
            return false;
        }
        while(tempCompare->next != nullptr)
        {
            if(tempCompareTo->next == nullptr)
            {
                return false;
            }

            tempCompare = tempCompare->next;
            tempCompareTo = tempCompareTo->next;

            if(tempCompare->info != tempCompareTo->info)
            {
                return false;
            }
        }
        
        if (tempCompareTo->next != nullptr)
        {
            return false;
        }
        
        return true;
    }

    void disp() const
    {
       SLLNode<T>* temp = head;
       while(temp != nullptr)
       {
          cout << temp->info << " ";
          temp = temp->next;
       }
    }
};

#endif

