#ifndef DLIST_H
#define DLIST_H

#include <iostream>
#include <cstdlib>
#include "dnode.h"

//더블리 링크드 리스트 클래스
template <typename T>
class dlist{
public:
    //디폴트 생성자
    dlist():count(0){
        //헤드와 테일을 생성하고 서로가 서로를 가리키게 함
        head = new dnode<T>;
        tail = new dnode<T>;
        head->set_next_node(tail);
        tail->set_prev_node(head);
    }

    //복사 생성자
    dlist(const dlist<T>& source);

    //소멸자
    ~dlist(){list_clear();}

    //리스트의 길이를 리턴
    int list_length()const {return count;}

    //리스트의 제일 앞에 데이터 추가
    void list_head_insert(const T& data);
    //리스트의 제일 뒤에 데이터 추가
    void list_tail_insert(const T& data);
    //리스트 중간에 데이터 추가, prev_node 앞에 추가
    void list_insert(dnode<T>* prev_node, const T& data);

    //data에 해당하는 가장 앞 노드 리턴, data가 리스트에 없으면 nullptr 리턴
    dnode<T>* list_search(const T& data)const;
    //해당 위치에 있는 노드 리턴
    //prefix: 0<=position<=count
    dnode<T>* list_locate(int position)const;
    //리스트를 카피하는 함수
    dlist<T>& list_copy(const dlist<T>& source);
    // 대입 연산자 오버로드
    dlist<T>& operator=(const dlist<T>& source);

    //리스트 가장 앞 노드 제거
    void list_head_remove();
    //리스트 가장 뒤 노드 제거
    void list_tail_remove();
    //리스트 중간에 있는 노드 제거, prev_node 앞 노드 제거
    void list_remove(dnode<T>* prev_node);
    //리스트의 모든 노드 제거
    void list_clear();

    //리스트가 비어있으면 true, 아니면 false 리턴
    bool is_empty(){return count == 0;}

    //getter
    dnode<T>* get_head_ptr(){return head;}    
    dnode<T>* get_tail_ptr(){return tail;}

private:
    //number of node
    int count;
    //헤드 노드, 실제로 데이터를 가지고 있지 않고 헤드의 역할만 함
    dnode<T>* head;
    //테일 노드, 실제로 데이터를 가지고 있지 않고 테일의 역할만 함
    dnode<T>* tail;
};

template <typename T>
dlist<T>::dlist(const dlist<T>& source){
    //헤드와 테일 노드를 만든 후 헤드와 테일이 서로를 가리키게 설정
    head = new dnode<T>;
    tail = new dnode<T>;
    head->set_next_node=tail;
    tail->set_prev_node=head;
   
    //커서가 source의 첫 번째 노드를 가리키게 함
    dnode<T>* source_cursor = source.head->get_next_node_ptr();
    
    //source의 첫 번째 노드를 생성하는 노드의 첫 번째로 노드로 추가
    this->list_head_insert(source_cursor->get_data());
    
    //prev_cursor를 생성해서 현재 노드의 첫번째 노드를 가리키게 함
    dnode<T>* prev_cursor = this->head->get_next_node_ptr();
    //source_cursor는 다음 노드를 가리킴
    source_cursor = source_cursor -> get_next_node_ptr();

    //source_cursor가 테일 노드를 가리킬 때까지 복사 반복
    while(source_cursor!=source.tail){
        this->list_insert(prev_cursor, source_cursor->get_data());
        prev_cursor = prev_cursor->get_next_node_ptr();
        source_cursor = source_cursor->get_next_node_ptr();
    }

    this->count = source.count;
}

template <typename T>
void dlist<T>::list_head_insert(const T& data){
    //인자로 받은 data를 데이터로 가지는 노드 생성
    dnode<T>* insert_node = new dnode<T>(data);
    //이 포인터는 리스트의 첫 번째 노드를 가리킴
    dnode<T>* insert_next_node = head->get_next_node_ptr();

    //삽입되는 노드의 이전 노드와 다음 노드 설정
    insert_node->set_next_node(insert_next_node);
    insert_node->set_prev_node(head);

    //삽입되는 노드를 가리키는 노드 설정
    head->set_next_node(insert_node);
    insert_next_node->set_prev_node(insert_node);

    count++;
}

template <typename T>
void dlist<T>::list_tail_insert(const T& data){
    //인자로 받은 data를 데이터로 가지는 노드 생성
    dnode<T>* insert_node = new dnode<T>(data);
    //이 포인터는 리스트의 첫 번째 노드를 가리킴
    dnode<T>* insert_prev_node = tail->get_prev_node_ptr();

    //삽입되는 노드의 이전 노드와 다음 노드 설정
    insert_node->set_next_node(tail);
    insert_node->set_prev_node(insert_prev_node);

    //삽입되는 노드를 가리키는 노드 설정
    tail->set_prev_node(insert_node);
    insert_prev_node->set_next_node(insert_node);

    count++;
}

template <typename T>
void dlist<T>::list_insert(dnode<T>* prev_node, const T& data){
    //인자로 받은 data를 데이터로 가지는 노드 생성
    dnode<T>* insert_node = new dnode<T>(data);
    //이 포인터는 삽입되는 노드의 다음 노드가 될 노드를 가리킴
    dnode<T>* next_node = prev_node->get_next_node_ptr();

    //삽입되는 노드의 이전 노드와 다음 노드 설정
    insert_node->set_next_node(next_node);
    insert_node->set_prev_node(prev_node);

    //삽입되는 노드를 가리키는 노드 설정
    prev_node->set_next_node(insert_node);
    next_node->set_prev_node(insert_node);    

    count++;
}

template <typename T>
dnode<T>* dlist<T>::list_search(const T& data)const{
    //노드를 가리키는 포인터 생성
    dnode<T>* cursor;
    //커서가 첫번째 노드부터 차례로 인자로 받은 데이터와 커서가 가리키는 데이터 비교
    for(cursor = head->get_next_node_ptr(); cursor!=tail; cursor=cursor->get_next_node_ptr()){
        //데이터 비교후 같으면 해당 노드 포인터 리턴
        if(cursor->get_data() == data) return cursor;
    }
    //같은 데이터가 없으면 널 포인터 리턴
    return nullptr;
}

template <typename T>
dnode<T>* dlist<T>::list_locate(int position)const{
    //인자로 받은 숫자보다 노드의 개수가 작으면 예외 처리
    if(position>count){
        std::cout<<"Out of bound!"<<std::endl;
        std::cout<<"This list have only "<<count<<" node(s)."<<std::endl; 
        return nullptr;
    }

    //인자가 0이면 첫 번째 노드 리턴
    if(position == 0) return head->get_next_node_ptr();

    //인자로 받은 숫자 만큼 커서를 옮기고 해당 커서 리턴
    dnode<T>* cursor = head->get_next_node_ptr();
    for(int i=0; i<position; i++){
        cursor = cursor->get_next_node_ptr();
    }
    return cursor;
} 

template <typename T>
dlist<T>& dlist<T>::list_copy(const dlist<T>& source){
    //자기 자신을 복사하려는 경우 예외처리
    if(source=this){
        std::cout<<"Self copy"<<std::endl;
        return *this;
    }

    //this 리스트 비우기
    this->list_clear();
    
    //source가 비어 있으면 비운 this 그대로 리턴
    if(source.is_empty()) return *this;

    //밑에 구조는 복사 생성자에 적은 구조와 동일
    dnode<T>* source_cursor = source.head->get_next_node_ptr();
    

    this->list_head_insert(source_cursor->get_data());
    
    dnode<T>* prev_cursor = this->head->get_next_node_ptr();
    source_cursor = source_cursor -> get_next_node_ptr();

    while(source_cursor!=source.tail){
        this->list_insert(prev_cursor, source_cursor->get_data());
        prev_cursor = prev_cursor->get_next_node_ptr();
        source_cursor = source_cursor->get_next_node_ptr();
    }

    this->count = source.count;

    return *this;
}

template <typename T>
dlist<T>& dlist<T>::operator=(const dlist<T>& source){
    //list_copy 함수와 구조 동일
    if(source=this){
        std::cout<<"Self assignment"<<std::endl;
        return *this;
    }

    this->list_clear();
    
    if(source.is_empty()) return *this;

    dnode<T>* source_cursor = source.head->get_next_node_ptr();
    

    this->list_head_insert(source_cursor->get_data());
    
    dnode<T>* prev_cursor = this->head->get_next_node_ptr();
    source_cursor = source_cursor -> get_next_node_ptr();

    while(source_cursor!=source.tail){
        this->list_insert(prev_cursor, source_cursor->get_data());
        prev_cursor = prev_cursor->get_next_node_ptr();
        source_cursor = source_cursor->get_next_node_ptr();
    }

    this->count = source.count;

    return *this;
}

template <typename T>
void dlist<T>::list_head_remove(){
    //리스트가 비어 있는 경우 예외 처리
    if(is_empty()){
        std::cout<<"This list is empty!"<<std::endl;
        return;
    }

    //지우려는 노드는 첫 번째 노드
    dnode<T>* remove_node = head->get_next_node_ptr();
    //이 포인터는 2 번째 노드를 가리킴
    dnode<T>* next_node = remove_node->get_next_node_ptr();

    //헤드 노드와 2번째 노드가 서로를 가리키게 만듬
    head->set_next_node(next_node);
    next_node->set_prev_node(head);

    //지우려는 노드 delete
    delete remove_node;

    count--;
}

template <typename T>
void dlist<T>::list_tail_remove(){
    //리스트가 비어있는 경우 예외 처리
    if(is_empty()){
        std::cout<<"This list is empty!"<<std::endl;
        return;
    }

    //지우려는 노드는 마지막 노드
    dnode<T>* remove_node = tail->get_prev_node_ptr();
    //이 포인터는 마지막에서 2번째 노드를 가리킴
    dnode<T>* prev_node = remove_node->get_prev_node_ptr();

    //테일 노드와 마지막에서 2번째 노드를 서로 가리키게 만듬
    tail->set_prev_node(prev_node);
    prev_node->set_next_node(tail);

    //지우려는 노드 delete
    delete remove_node;

    count--;
}

template <typename T>
void dlist<T>::list_remove(dnode<T>* prev_node){
    //리스트가 비어 있는 경우 예외 처리
    if(is_empty()){
        std::cout<<"This list is empty!"<<std::endl;
        return;
    }

    //지우려는 노드는 인자로 받은 노드의 다음 노드
    dnode<T>* remove_node = prev_node->get_next_node_ptr();
    //이 포인터는 지우려는 노드의 다음 노드를 가리킴
    dnode<T>* next_node = remove_node->get_next_node_ptr();

    //지우려는 노드의 이전 노드와 다음 노드가 서로를 가리키게 만듬
    prev_node->set_next_node(next_node);
    next_node->set_prev_node(prev_node);

    //지우려는 노드 delete
    delete remove_node;

    count--;
}

template <typename T>
void dlist<T>::list_clear(){
    //리스트가 가진 노드의 개수 만큼 list_head_remove 함수 실행
    for(int i=0; i<count; i++){
        list_head_remove();
    }
    count = 0;
}

#endif