#ifndef DNODE_H
#define DNODE_H

#include <cstdlib>

//더블리 노드 클래스
template <typename T>
class dnode{
public:
    //기초 생성자
    dnode()
        :prev_node_ptr(nullptr), next_node_ptr(nullptr){}
    
    //데이터, 이전 노드, 다음 노드를 지정해서 생성할 수 있는 생성자
    dnode(T the_data, dnode* prev = nullptr, dnode* next = nullptr)
        :data(the_data), prev_node_ptr(prev), next_node_ptr(next){}
    
    //setter
    void set_data(T new_data){data = new_data;}
    void set_prev_node(dnode* new_prev){prev_node_ptr = new_prev;}
    void set_next_node(dnode* new_next){next_node_ptr = new_next;}

    //getter
    T get_data()const{return data;}
    dnode* get_prev_node_ptr()const{return prev_node_ptr;}
    dnode* get_next_node_ptr()const{return next_node_ptr;}

private:
    //노드가 가지고 있는 데이터
    T data;
    //이전 노드 주소
    dnode* prev_node_ptr;
    //다음 노드 주소
    dnode* next_node_ptr;
};


#endif