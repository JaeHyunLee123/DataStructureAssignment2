#ifndef DEQUE_H
#define DEQUE_H

#include "dlist.h"
#include "dnode.h"

//더블리 큐 클래스
template <typename T>
class deque{
public:
    //디폴트 생성자
    deque();
    
    //큐의 가장 앞에 데이터 추가
    void push_front(const T& data);
    //큐의 가장 뒤에 데이터 추가
    void push_back(const T& data);

    //큐의 가장 앞 노드 제거
    void pop_front();
    //큐의 가장 뒤 노드 제거
    void pop_back();

    //큐의 크기 리턴
    int size(){return list->list_length();}
    //큐가 비어 있으면 true, 아니면 false 리턴
    bool is_empty(){return list->is_empty();}

    //큐의 가장 앞 데이터 리턴
    T front();
    //큐의 가장 뒤 데이터 리턴
    T back();

private:
    //더블리 링크드 리스트를 멤버 변수로 가짐
    dlist<T>* list;
};

template <typename T>
deque<T>::deque(){
    //새로운 더블리 링크드 리스트 생성
    list = new dlist<T>;
}

template <typename T>
void deque<T>::push_front(const T& data){
    //더블리 링크드 리스트의 list_head_insert 함수 호출
    list->list_head_insert(data);
}

template <typename T>
void deque<T>::push_back(const T& data){
    //더블리 링크드 리스트의 list_tail_insert 함수 호출
    list->list_tail_insert(data);
}

template <typename T>
void deque<T>::pop_front(){
    //더블리 링크드 리스트의 list_head_remove 함수 호출
    list->list_head_remove();
}

template <typename T>
void deque<T>::pop_back(){
    //더블리 링크드 리스트의 list_tail_remove 함수 호출
    list->list_tail_remove();
}

template <typename T>
T deque<T>::front(){
    //더블리 링크드 리스트의 첫번째 노드가 가지고 있는 데이터 값 리턴
    return list->get_head_ptr()->get_next_node_ptr()->get_data();
}

template <typename T>
T deque<T>::back(){
    //더블리 링크드 리스트의 마지막 노드가 가지고 있는 데이터 값 리턴
    return list->get_tail_ptr()->get_prev_node_ptr()->get_data();
}
#endif