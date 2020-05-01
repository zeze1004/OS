#include <iostream>
#include <stdio.h>
#include <atomic>
#include <thread>
#include <vector>
#include <string>

using namespace std;

struct Node {
public:

    int data;   //데이터 저장 공간
    Node* next; //다음 노드의 연결을 위한 포인터(주소값 저장)
};

class LinkedList {
private:
    //Node* head = NULL;
    std::atomic <Node*> head;
    Node* tail;
    int size = 0;           //링크의 길이
public:
    LinkedList() : head(nullptr), tail(nullptr) {}
    ~LinkedList() {} //소멸자

public:
    int headReturn() {
        if (head == nullptr)
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }

    void push(Node* pNewNode) {
        //Node* next;
        Node* t = head; //t = next

        while (!head.compare_exchange_weak(t, pNewNode)) //head가 pNewNode가 되면 탈출
            pNewNode->next = t;
        //head가 t와 같으면 pNewNode로 바뀐다
        size++;

    }

    Node* pop()
    {
        Node* current = head;
        while (current) {
            if (!head.compare_exchange_weak(current, current->next)) { //current->next

                return current;
            }

            current = head;
        }return NULL;
    }
    void display() {
        Node* ptr;
        if (head == NULL) {
            cout << "stack is empty";
        }
        else {
            ptr = head;
            cout << "stack element : ";
            while (ptr != NULL) {
                cout << ptr->data << " ";
                ptr = ptr->next;
            }
        }
        cout << endl;
    }
    void FUNCfreeList(Node* head)
    {
        for (int i = 0; i < 100; i++)
        {
            Node* node = new Node;      //노드라는 구조체를 선언한 것
            node->data = i;
            node->next = nullptr;

            if (head == nullptr) //만약 머리가 없을경우 
            {
                head = node;
                tail = node;
            }

            else // 만약 머리가 있을경우 뒤에 연결 
            {
                tail->next = node;
                tail = tail->next;
            }
        }
    }

};

LinkedList freeList;    //링크드리스트 객체 freeList 선언
LinkedList headList;

//static void           //(std::atomic<int>& i)
static void ThreadBody1(std::atomic<int>& i)
{
   
    //freeList->head = head;
    //Node* freeList;
    int i = 0;
    while (i < 10000)
    {
        for(int j=0;j<100;j++)
            if (freeList.headReturn() == 1)
            {
                //Node *headList;
                freeList.push(headList);
            }
        for (int j = 0; j < 100; j++)
        {
            if (head != nullptr)
            {
                Node* freeList;
                headList.pop();
                headList.push(freeList * head);
            }
        }
        
        i++;
    }
}
/*
void ThreadBody()
{
    cout << ThreadBody1 << endl;
}
*/

//void ThreadBody();
//std::thread thread1(ThreadBody1);


int main() {
    //void ThreadBody();
  
    //LinkedList<int> List;
    
    thread thread1(ThreadBody1);
    
    /*
    LinkedList(display);
    LinkedList(pop);
    freeeList.display();
    headList.pop();
    */
    std::atomic<int> i = 0;


//    void FUNCfreeList();


//    freeList.display();



    thread1.join();
    


    return 0;
}
