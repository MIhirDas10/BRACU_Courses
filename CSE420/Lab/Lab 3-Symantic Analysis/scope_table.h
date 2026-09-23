#ifndef SCOPE_TABLE_H
#define SCOPE_TABLE_H

#include "symbol_info.h"

class scope_table
{
private:
    int bucket_count;
    int unique_id;
    scope_table *parent_scope;
    vector<list<symbol_info*> > table;

    int hash_function(string name)
    {
        int hash = 0;
        for(int i=0; i<(int)name.length(); i++)
        {
            hash += name[i];
        }
        return hash % bucket_count;
    }

public:
    scope_table(int bucket_count, int unique_id, scope_table *parent_scope)
    {
        this->bucket_count = bucket_count;
        this->unique_id = unique_id;
        this->parent_scope = parent_scope;
        this->table.resize(bucket_count);
    }

    scope_table *get_parent_scope()
    {
        return parent_scope;
    }

    int get_unique_id()
    {
        return unique_id;
    }

    symbol_info *lookup_in_scope(symbol_info *symbol)
    {
        if(symbol == NULL) return NULL;

        int index = hash_function(symbol->getname());
        for(symbol_info *s : table[index])
        {
            if(s->getname() == symbol->getname())
            {
                return s;
            }
        }
        return NULL;
    }

    symbol_info *lookup_in_scope(string name)
    {
        symbol_info temp(name, "ID");
        return lookup_in_scope(&temp);
    }

    bool insert_in_scope(symbol_info *symbol)
    {
        if(symbol == NULL) return false;
        if(lookup_in_scope(symbol) != NULL) return false;

        int index = hash_function(symbol->getname());
        table[index].push_back(symbol);
        return true;
    }

    bool delete_from_scope(symbol_info *symbol)
    {
        if(symbol == NULL) return false;

        int index = hash_function(symbol->getname());
        for(list<symbol_info*>::iterator it = table[index].begin(); it != table[index].end(); it++)
        {
            if((*it)->getname() == symbol->getname())
            {
                delete *it;
                table[index].erase(it);
                return true;
            }
        }
        return false;
    }

    bool delete_from_scope(string name)
    {
        symbol_info temp(name, "ID");
        return delete_from_scope(&temp);
    }

    void print_scope_table(ofstream &outlog)
    {
        outlog<<"ScopeTable # "<<unique_id<<endl;

        for(int i=0; i<bucket_count; i++)
        {
            if(table[i].empty()) continue;

            outlog<<i<<" --> "<<endl;
            for(symbol_info *s : table[i])
            {
                outlog<<"< "<<s->getname()<<" : "<<s->gettype()<<" >"<<endl;

                if(s->getidtype() == "var" || s->getidtype() == "variable")
                {
                    outlog<<"Variable"<<endl;
                    outlog<<"Type: "<<s->getvartype()<<endl;
                }
                else if(s->getidtype() == "array")
                {
                    outlog<<"Array"<<endl;
                    outlog<<"Type: "<<s->getvartype()<<endl;
                    outlog<<"Size: "<<s->getarraysize()<<endl;
                }
                else if(s->getidtype() == "function" || s->getidtype() == "func")
                {
                    outlog<<"Function Definition"<<endl;
                    outlog<<"Return Type: "<<s->getreturntype()<<endl;
                    outlog<<"Number of Parameters: "<<s->getparamcount()<<endl;
                    outlog<<"Parameter Details: "<<s->getparamdetails()<<endl;
                }
            }

            symbol_info *last_symbol = table[i].back();
            bool has_next_bucket = false;
            for(int j=i+1; j<bucket_count; j++)
            {
                if(!table[j].empty())
                {
                    has_next_bucket = true;
                    break;
                }
            }

            if(!(last_symbol->getidtype() == "function" && last_symbol->getparamdetails() == "" && has_next_bucket))
            {
                outlog<<endl;
            }
        }
    }

    ~scope_table()
    {
        for(int i=0; i<bucket_count; i++)
        {
            for(symbol_info *s : table[i])
            {
                delete s;
            }
        }
    }
};

#endif
