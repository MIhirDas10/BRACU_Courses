#ifndef SYMBOL_INFO_H
#define SYMBOL_INFO_H

#include<bits/stdc++.h>
using namespace std;

class symbol_info
{
private:
    string name;
    string type;
    string category;
    string data_type;
    int array_size;
    vector<string> parameter_types;
    vector<string> parameter_names;

public:
    symbol_info()
    {
        this->name = "";
        this->type = "";
        this->category = "";
        this->data_type = "";
        this->array_size = 0;
    }

    symbol_info(string name, string type)
    {
        this->name = name;
        this->type = type;
        this->category = "";
        this->data_type = "";
        this->array_size = 0;
    }

    string get_name()
    {
        return name;
    }

    string getname()
    {
        return name;
    }

    string get_type()
    {
        return type;
    }

    string gettype()
    {
        return type;
    }

    string get_category()
    {
        return category;
    }

    string getidtype()
    {
        return category;
    }

    string get_data_type()
    {
        return data_type;
    }

    string getvartype()
    {
        return data_type;
    }

    string getreturntype()
    {
        return data_type;
    }

    int get_array_size()
    {
        return array_size;
    }

    int getarraysize()
    {
        return array_size;
    }

    vector<string> get_parameter_types()
    {
        return parameter_types;
    }

    vector<string> getparamtype()
    {
        return parameter_types;
    }

    vector<string> get_parameter_names()
    {
        return parameter_names;
    }

    vector<string> getparamname()
    {
        return parameter_names;
    }

    void set_name(string name)
    {
        this->name = name;
    }

    void setname(string name)
    {
        this->name = name;
    }

    void set_type(string type)
    {
        this->type = type;
    }

    void settype(string type)
    {
        this->type = type;
    }

    void set_category(string category)
    {
        this->category = category;
    }

    void setidtype(string category)
    {
        this->category = category;
    }

    void set_data_type(string data_type)
    {
        this->data_type = data_type;
    }

    void setvartype(string data_type)
    {
        this->data_type = data_type;
    }

    void setreturntype(string return_type)
    {
        this->data_type = return_type;
    }

    void set_array_size(int array_size)
    {
        this->array_size = array_size;
    }

    void setarraysize(int array_size)
    {
        this->array_size = array_size;
    }

    void set_parameters(vector<string> types, vector<string> names)
    {
        this->parameter_types = types;
        this->parameter_names = names;
    }

    void add_parameter(string type, string name)
    {
        parameter_types.push_back(type);
        parameter_names.push_back(name);
    }

    int getparamcount()
    {
        return (int)parameter_types.size();
    }

    string getparamdetails()
    {
        string details = "";
        for(int i=0; i<(int)parameter_types.size(); i++)
        {
            if(i > 0) details += ", ";

            details += parameter_types[i];
            if(i < (int)parameter_names.size() && parameter_names[i] != "")
            {
                details += " " + parameter_names[i];
            }
        }
        return details;
    }

    ~symbol_info()
    {
    }
};

#endif
