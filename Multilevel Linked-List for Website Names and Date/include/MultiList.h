#pragma once
#include "../include/MultiNode.h"
#include <string>

using namespace std;

class MultiList{
    private:
        DateNode* head;
        DateNode* tail;

    public:
        MultiList();
        ~MultiList();
        void add_node(string,string,string);
        void remove_node(string,string);
        void print_list();
        //You can add any function.
        void insert_Begin(DateNode**,DateNode*);
        void insert_End(DateNode**,DateNode*);
        void insert_Between(DateNode**,DateNode*);

};