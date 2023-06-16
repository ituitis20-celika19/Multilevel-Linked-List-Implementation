#include <iostream>
#include <string>
#include "../include/MultiList.h"

using namespace std;

MultiList::MultiList()
{
    head=NULL;
    tail=NULL;
}

MultiList::~MultiList()
{
    DateNode* p1 = head;
    DateNode* n1 = head;
    TSiteNode* p2 = NULL;
    TSiteNode* n2 = NULL;

    while(n1!=NULL){
        n2 = n1->get_up();
        p2 = n2->get_up();
        while(n2!=NULL)
        {
            n2 = p2->get_up();
            delete p2;
            p2 = n2;
        }
        n1=p1->get_next();
        delete p1;
        p1=n1;
    }
}


void MultiList::add_node(string date,string time,string site_name)
{
    DateNode *new_date = new DateNode(date);
    TSiteNode *new_site = new TSiteNode(time,site_name);

    if(head == NULL)
    {
        new_date->set_up(new_site);
        head = new_date;
        tail = new_date;
    }
    else
    {
        DateNode *finder = head;
        while (finder != NULL)
        {
            if(new_date->get_date() < head->get_date())
            {
                insert_Begin(&head,new_date);
                new_date->set_up(new_site);
                break;
            }
            
            else if(finder->get_date() == new_date->get_date())
            {
                TSiteNode *finder_site = finder->get_up();
                while (finder_site != NULL)
                {
                    if(new_site->get_time() < finder_site->get_time())
                    {
                        new_site->set_up(finder_site);
                        finder->set_up(new_site);
                        break;
                    }

                    else if(new_site->get_time() > finder_site->get_time() && finder_site->get_up() != NULL && new_site->get_time() < finder_site->get_up()->get_time())
                    {
                        new_site->set_up(finder_site->get_up());
                        finder_site->set_up(new_site);
                        break;                    
                    }

                    else if(new_site->get_time() > finder_site->get_time() && finder_site->get_up() == NULL)
                    {
                        finder_site->set_up(new_site);
                        break;
                    }
                    finder_site = finder_site->get_up();
                }
                
            }

            else if(new_date->get_date() > finder->get_date() && finder->get_next() != NULL && new_date->get_date() < finder->get_next()->get_date())
            {
                insert_Between(&finder,new_date);
                new_date->set_up(new_site);
                break;
            }

            else if(new_date->get_date() > tail->get_date())
            {
                insert_End(&tail,new_date);
                new_date->set_up(new_site);
                break;
            }
            finder = finder->get_next();

        }
        
        
    }
}
    

void MultiList::remove_node(string date,string time)
{

    DateNode *date_finder = head;
    
        while (date_finder != NULL)
        {

            if(date_finder->get_date() == date)
            {
                TSiteNode *time_finder = date_finder->get_up();
                TSiteNode *prev_time = NULL;
                while (time_finder != NULL)
                {
                    
                    if(time_finder->get_time() == time)
                    {
                        if(time_finder->get_time() == date_finder->get_up()->get_time())
                        {
                            date_finder->set_up(time_finder->get_up());
                            delete time_finder;
                            return;

                        }
                        else
                        {
                            prev_time->set_up(time_finder->get_up());
                            delete time_finder;
                            return;                                     
                        }
                    }
                    else
                    {
                        while (time_finder != NULL && time_finder->get_time() != time)
                            {
                                prev_time = time_finder;
                                time_finder = time_finder->get_up();
                            }
                        
                    }
                }  
            }
            else
            {
                date_finder = date_finder->get_next();
            }
            
            
            
        }
        

}

void MultiList::print_list()
{
    DateNode* p_hor=head;
    TSiteNode* p_ver;
    
    while(p_hor)
    {
        cout<<p_hor->get_date()<<":"<<endl;
        p_ver=p_hor->get_up();
        while(p_ver)
        {
            cout<<p_ver->get_time()<<"->"<<p_ver->get_site_name()<<endl;
            p_ver=p_ver->get_up();
        }
        p_hor=p_hor->get_next();
    }

}

void MultiList::insert_Begin(DateNode** head_ref,DateNode* new_date)
{
   new_date->set_next((*head_ref));
   (*head_ref)->set_prev(new_date);
   *head_ref = new_date; 
}

void MultiList::insert_End(DateNode** tail_ref,DateNode* new_date)
{
    (*tail_ref)->set_next(new_date);
    new_date->set_prev((*tail_ref));
    *tail_ref = new_date;
}

void MultiList::insert_Between(DateNode** head_ref,DateNode* new_date)
{
    DateNode* temp = *head_ref;
    DateNode* temp2 = temp->get_next();
    temp->set_next(new_date);
    temp2->set_prev(new_date);
    new_date->set_next(temp2);
    new_date->set_prev(temp);

}
