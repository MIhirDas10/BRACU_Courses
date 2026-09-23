#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "scope_table.h"

class symbol_table
{
private:
    scope_table *current_scope;
    int bucket_count;
    int current_scope_id;

public:
    symbol_table(int bucket_count)
    {
        this->bucket_count = bucket_count;
        this->current_scope = NULL;
        this->current_scope_id = 0;
        enter_scope();
    }

    ~symbol_table()
    {
        while(current_scope != NULL)
        {
            scope_table *temp = current_scope;
            current_scope = current_scope->get_parent_scope();
            delete temp;
        }
    }

    void enter_scope()
    {
        current_scope_id++;
        scope_table *new_scope = new scope_table(bucket_count, current_scope_id, current_scope);
        current_scope = new_scope;
    }

    void enter_scope(ofstream &outlog)
    {
        enter_scope();
        outlog<<"New ScopeTable with ID "<<current_scope->get_unique_id()<<" created"<<endl<<endl;
    }

    void exit_scope()
    {
        if(current_scope == NULL) return;

        scope_table *temp = current_scope;
        current_scope = current_scope->get_parent_scope();
        delete temp;
    }

    void exit_scope(ofstream &outlog)
    {
        if(current_scope == NULL) return;

        int id = current_scope->get_unique_id();
        exit_scope();
        outlog<<"Scopetable with ID "<<id<<" removed"<<endl<<endl;
    }

    bool insert(symbol_info *symbol)
    {
        if(current_scope == NULL) return false;
        return current_scope->insert_in_scope(symbol);
    }

    bool remove(symbol_info *symbol)
    {
        if(current_scope == NULL) return false;
        return current_scope->delete_from_scope(symbol);
    }

    symbol_info *lookup(symbol_info *symbol)
    {
        scope_table *temp = current_scope;
        while(temp != NULL)
        {
            symbol_info *found = temp->lookup_in_scope(symbol);
            if(found != NULL) return found;
            temp = temp->get_parent_scope();
        }
        return NULL;
    }

    symbol_info *lookup(string name)
    {
        symbol_info temp(name, "ID");
        return lookup(&temp);
    }

    void print_current_scope(ofstream &outlog)
    {
        if(current_scope != NULL)
        {
            current_scope->print_scope_table(outlog);
        }
    }

    void print_all_scopes(ofstream &outlog)
    {
        outlog<<"################################"<<endl<<endl;

        scope_table *temp = current_scope;
        while(temp != NULL)
        {
            temp->print_scope_table(outlog);
            temp = temp->get_parent_scope();
            if(temp != NULL) outlog<<endl;
        }

        outlog<<"################################"<<endl<<endl;
    }
};

#endif
