%{
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "symbol_table.h"

using namespace std;

#define YYSTYPE symbol_info*

extern FILE *yyin;
int yyparse(void);
int yylex(void);
extern YYSTYPE yylval;

symbol_table *st;
int errors = 0;
int lines = 1;

string current_type;
vector<symbol_info*> parameters;
vector<symbol_info*> declaration_list_vars;
vector<symbol_info*> arguments_list;

string current_func_name = "";

ofstream outlog;
ofstream outerr;

void yyerror(char *s)
{
	outerr<<"At line no: "<<lines<<" "<<s<<"\n\n";
	errors++;
}

void printError(string error_msg) {
    if (error_msg.find("Warning:") == 0) {
        outerr << "At line no: " << lines << " " << error_msg << "\n\n";
    } else {
        outerr << "At line no: " << lines << " " << error_msg << "\n\n";
    }
    errors++;
}

%}

%token IF ELSE FOR WHILE DO BREAK INT CHAR FLOAT DOUBLE VOID RETURN SWITCH CASE DEFAULT CONTINUE PRINTLN ADDOP MULOP INCOP DECOP RELOP ASSIGNOP LOGICOP NOT LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON CONST_INT CONST_FLOAT ID LOWER_THAN_ELSE

%left LOGICOP
%left RELOP
%left ADDOP
%left MULOP

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
start : program
{
	outlog<<"At line no: "<<lines<<" start : program \n\n";
	outlog<<"Symbol Table\n\n";
	st->print_all_scopes(outlog);
}
;

program : program unit
{
	outlog<<"At line no: "<<lines<<" program : program unit \n\n";
	outlog<<$1->get_name()<<"\n"<<$2->get_name()<<"\n\n";
	$$ = new symbol_info($1->get_name()+"\n"+$2->get_name(),"program");
}
| unit
{
	outlog<<"At line no: "<<lines<<" program : unit \n\n";
	outlog<<$1->get_name()<<"\n\n";
	$$ = new symbol_info($1->get_name(),"program");
}
;

unit : var_declaration
{
    outlog<<"At line no: "<<lines<<" unit : var_declaration \n\n";
	outlog<<$1->get_name()<<"\n\n";
	$$ = new symbol_info($1->get_name(),"unit");
}
| func_definition
{
    outlog<<"At line no: "<<lines<<" unit : func_definition \n\n";
	outlog<<$1->get_name()<<"\n\n";
	$$ = new symbol_info($1->get_name(),"unit");
}
;

func_definition : type_specifier ID LPAREN
{
    current_func_name = $2->get_name();
} 
parameter_list RPAREN 
{
    symbol_info* f = new symbol_info($2->get_name(), "ID");
    f->set_category("FUNCTION");
    f->set_data_type($1->get_name());
    for(size_t i=0; i<parameters.size(); ++i) {
        f->add_parameter(parameters[i]->get_data_type(), parameters[i]->get_name());
    }
    bool inserted = st->insert(f);
    if(!inserted) {
        printError("Multiple declaration of function " + $2->get_name());
    }
}
compound_statement
{
    outlog<<"At line no: "<<lines<<" func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement \n\n";
	string str = $1->get_name() + " " + $2->get_name() + "(" + $5->get_name() + ")\n" + $8->get_name();
	outlog<<str<<"\n\n";
	$$ = new symbol_info(str, "func_definition");
}
| type_specifier ID LPAREN RPAREN 
{
    current_func_name = $2->get_name();
    symbol_info* f = new symbol_info($2->get_name(), "ID");
    f->set_category("FUNCTION");
    f->set_data_type($1->get_name());
    bool inserted = st->insert(f);
    if(!inserted) {
        printError("Multiple declaration of function " + $2->get_name());
    }
}
compound_statement
{
    outlog<<"At line no: "<<lines<<" func_definition : type_specifier ID LPAREN RPAREN compound_statement \n\n";
	string str = $1->get_name() + " " + $2->get_name() + "()\n" + $6->get_name();
	outlog<<str<<"\n\n";
	$$ = new symbol_info(str, "func_definition");
}
;

parameter_list : parameter_list COMMA type_specifier ID
{
    outlog<<"At line no: "<<lines<<" parameter_list : parameter_list COMMA type_specifier ID \n\n";
    string str = $1->get_name() + "," + $3->get_name() + " " + $4->get_name();
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "parameter_list");
    
    symbol_info* p = new symbol_info($4->get_name(), "ID");
    p->set_data_type($3->get_name()); // "int", "float", "void"
    
    // check for duplicate
    bool duplicate = false;
    for(size_t i=0; i<parameters.size(); ++i) {
        if(parameters[i]->get_name() == p->get_name()) {
            duplicate = true;
            break;
        }
    }
    if(duplicate) {
        printError("Multiple declaration of variable "+p->get_name()+" in parameter of "+current_func_name);
    } else {
        parameters.push_back(p);
    }
}
| parameter_list COMMA type_specifier
{
    outlog<<"At line no: "<<lines<<" parameter_list : parameter_list COMMA type_specifier \n\n";
    string str = $1->get_name() + "," + $3->get_name();
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "parameter_list");
}
| type_specifier ID
{
    outlog<<"At line no: "<<lines<<" parameter_list : type_specifier ID \n\n";
    string str = $1->get_name() + " " + $2->get_name();
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "parameter_list");
    
    // parameters.clear();
    symbol_info* p = new symbol_info($2->get_name(), "ID");
    p->set_data_type($1->get_name());
    parameters.push_back(p);
}
| type_specifier
{
    outlog<<"At line no: "<<lines<<" parameter_list : type_specifier \n\n";
    outlog<<$1->get_name()<<"\n\n";
    $$ = new symbol_info($1->get_name(), "parameter_list");
    // parameters.clear();
}
;

compound_statement : LCURL_SCOPE statements RCURL_SCOPE
{
    outlog<<"At line no: "<<lines<<" compound_statement : LCURL statements RCURL \n\n";
    string str = "{\n" + $2->get_name() + "\n}";
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "compound_statement");
}
| LCURL_SCOPE RCURL_SCOPE
{
    outlog<<"At line no: "<<lines<<" compound_statement : LCURL RCURL \n\n";
    string str = "{}\n";
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "compound_statement");
}
;

LCURL_SCOPE : LCURL
{
    st->enter_scope();
    outlog << "New ScopeTable with ID " << st->get_current_scope_id() << " created\n\n";
    for(size_t i=0; i<parameters.size(); ++i) {
        symbol_info* p = new symbol_info(parameters[i]->get_name(), "ID");
        p->set_category("VAR");
        p->set_data_type(parameters[i]->get_data_type());
        bool inserted = st->insert(p);
        if(!inserted) {
            // Already handled
        }
    }
    parameters.clear();
}
;

RCURL_SCOPE : RCURL
{
    st->print_current_scope(outlog);
    outlog << "Scopetable with ID " << st->get_current_scope_id() << " removed\n\n";
    st->exit_scope();
}
;

var_declaration : type_specifier declaration_list SEMICOLON
{
    outlog<<"At line no: "<<lines<<" var_declaration : type_specifier declaration_list SEMICOLON \n\n";
    string str = $1->get_name() + " " + $2->get_name() + ";";
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "var_declaration");
    
    if($1->get_name() == "void") {
        printError("variable type can not be void");
    } else {
        for(size_t i=0; i<declaration_list_vars.size(); ++i) {
            declaration_list_vars[i]->set_data_type($1->get_name());
            symbol_info* insert_sym = new symbol_info(declaration_list_vars[i]->get_name(), "ID");
            insert_sym->set_data_type($1->get_name());
            insert_sym->set_category(declaration_list_vars[i]->get_category());
            insert_sym->set_array_size(declaration_list_vars[i]->get_array_size());
            
            bool inserted = st->insert(insert_sym);
            if(!inserted) {
                printError("Multiple declaration of variable " + declaration_list_vars[i]->get_name());
            }
        }
    }
    declaration_list_vars.clear();
}
;

type_specifier : INT
{
    outlog<<"At line no: "<<lines<<" type_specifier : INT \n\n";
    outlog<<"int\n\n";
    $$ = new symbol_info("int", "type_specifier");
    current_type = "int";
}
| FLOAT
{
    outlog<<"At line no: "<<lines<<" type_specifier : FLOAT \n\n";
    outlog<<"float\n\n";
    $$ = new symbol_info("float", "type_specifier");
    current_type = "float";
}
| VOID
{
    outlog<<"At line no: "<<lines<<" type_specifier : VOID \n\n";
    outlog<<"void\n\n";
    $$ = new symbol_info("void", "type_specifier");
    current_type = "void";
}
;

declaration_list : declaration_list COMMA ID
{
    outlog<<"At line no: "<<lines<<" declaration_list : declaration_list COMMA ID \n\n";
    string str = $1->get_name() + "," + $3->get_name();
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "declaration_list");
    
    symbol_info* s = new symbol_info($3->get_name(), "ID");
    s->set_category("VAR");
    declaration_list_vars.push_back(s);
}
| declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
{
    outlog<<"At line no: "<<lines<<" declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD \n\n";
    string str = $1->get_name() + "," + $3->get_name() + "[" + $5->get_name() + "]";
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "declaration_list");
    
    symbol_info* s = new symbol_info($3->get_name(), "ID");
    s->set_category("ARRAY");
    s->set_array_size(stoi($5->get_name()));
    declaration_list_vars.push_back(s);
}
| ID
{
    outlog<<"At line no: "<<lines<<" declaration_list : ID \n\n";
    outlog<<$1->get_name()<<"\n\n";
    $$ = new symbol_info($1->get_name(), "declaration_list");
    
    declaration_list_vars.clear(); // just to be safe
    symbol_info* s = new symbol_info($1->get_name(), "ID");
    s->set_category("VAR");
    declaration_list_vars.push_back(s);
    
    current_func_name = $1->get_name(); 
}
| ID LTHIRD CONST_INT RTHIRD
{
    outlog<<"At line no: "<<lines<<" declaration_list : ID LTHIRD CONST_INT RTHIRD \n\n";
    string str = $1->get_name() + "[" + $3->get_name() + "]";
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "declaration_list");
    
    declaration_list_vars.clear();
    symbol_info* s = new symbol_info($1->get_name(), "ID");
    s->set_category("ARRAY");
    s->set_array_size(stoi($3->get_name()));
    declaration_list_vars.push_back(s);
}
;

statements : statement
{
    outlog<<"At line no: "<<lines<<" statements : statement \n\n";
    outlog<<$1->get_name()<<"\n\n";
    $$ = new symbol_info($1->get_name(), "statements");
}
| statements statement
{
    outlog<<"At line no: "<<lines<<" statements : statements statement \n\n";
    string str = $1->get_name() + "\n" + $2->get_name();
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "statements");
}
;

statement : var_declaration
{
    outlog<<"At line no: "<<lines<<" statement : var_declaration \n\n";
    outlog<<$1->get_name()<<"\n\n";
    $$ = new symbol_info($1->get_name(), "statement");
}
| func_definition
{
    outlog<<"At line no: "<<lines<<" statement : func_definition \n\n";
    outlog<<$1->get_name()<<"\n\n";
    $$ = new symbol_info($1->get_name(), "statement");
}
| expression_statement
{
    outlog<<"At line no: "<<lines<<" statement : expression_statement \n\n";
    outlog<<$1->get_name()<<"\n\n";
    $$ = new symbol_info($1->get_name(), "statement");
}
| compound_statement
{
    outlog<<"At line no: "<<lines<<" statement : compound_statement \n\n";
    outlog<<$1->get_name()<<"\n\n";
    $$ = new symbol_info($1->get_name(), "statement");
}
| FOR LPAREN expression_statement expression_statement expression RPAREN statement
{
    outlog<<"At line no: "<<lines<<" statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement \n\n";
    string str = "for(" + $3->get_name() + $4->get_name() + $5->get_name() + ")" + $7->get_name();
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "statement");
}
| IF LPAREN expression RPAREN statement
{
    outlog<<"At line no: "<<lines<<" statement : IF LPAREN expression RPAREN statement \n\n";
    string str = "if(" + $3->get_name() + ")" + $5->get_name();
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "statement");
}
| IF LPAREN expression RPAREN statement ELSE statement
{
    outlog<<"At line no: "<<lines<<" statement : IF LPAREN expression RPAREN statement ELSE statement \n\n";
    string str = "if(" + $3->get_name() + ")" + $5->get_name() + "else " + $7->get_name();
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "statement");
}
| WHILE LPAREN expression RPAREN statement
{
    outlog<<"At line no: "<<lines<<" statement : WHILE LPAREN expression RPAREN statement \n\n";
    string str = "while(" + $3->get_name() + ")" + $5->get_name();
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "statement");
}
| PRINTLN LPAREN ID RPAREN SEMICOLON
{
    outlog<<"At line no: "<<lines<<" statement : PRINTLN LPAREN ID RPAREN SEMICOLON \n\n";
    string str = "printf(" + $3->get_name() + ");";
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "statement");
    
    symbol_info* existing = st->lookup($3);
    if(existing == NULL) {
        printError("Undeclared variable " + $3->get_name());
    }
}
| RETURN expression SEMICOLON
{
    outlog<<"At line no: "<<lines<<" statement : RETURN expression SEMICOLON \n\n";
    string str = "return " + $2->get_name() + ";";
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "statement");
}
;

expression_statement : SEMICOLON
{
    outlog<<"At line no: "<<lines<<" expression_statement : SEMICOLON \n\n";
    outlog<<";\n\n";
    $$ = new symbol_info(";", "expression_statement");
}
| expression SEMICOLON
{
    outlog<<"At line no: "<<lines<<" expression_statement : expression SEMICOLON \n\n";
    string str = $1->get_name() + ";";
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "expression_statement");
}
;

variable : ID
{
    outlog<<"At line no: "<<lines<<" variable : ID \n\n";
    outlog<<$1->get_name()<<"\n\n";
    $$ = new symbol_info($1->get_name(), "variable");
    
    symbol_info* existing = st->lookup($1);
    if(existing == NULL) {
        printError("Undeclared variable " + $1->get_name());
        $$->set_data_type("error"); 
    } else {
        if(existing->get_category() == "ARRAY") {
            printError("variable is of array type : " + $1->get_name());
            $$->set_data_type("error");
        } else {
            $$->set_data_type(existing->get_data_type());
        }
    }
}
| ID LTHIRD expression RTHIRD
{
    outlog<<"At line no: "<<lines<<" variable : ID LTHIRD expression RTHIRD \n\n";
    string str = $1->get_name() + "[" + $3->get_name() + "]";
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "variable");
    
    symbol_info* existing = st->lookup($1);
    bool valid = true;
    if(existing == NULL) {
        printError("Undeclared variable " + $1->get_name());
        valid = false;
    } else {
        if(existing->get_category() != "ARRAY") {
            printError("variable is not of array type : " + $1->get_name());
            valid = false;
        }
    }
    
    if(!valid) {
        $$->set_data_type("error"); 
    } else {
        $$->set_data_type(existing->get_data_type());
    }
    
    if($3->get_data_type() != "int" && $3->get_data_type() != "error") {
        printError("array index is not of integer type : " + $1->get_name());
    }
}
;

expression : logic_expression
{
    outlog<<"At line no: "<<lines<<" expression : logic_expression \n\n";
    outlog<<$1->get_name()<<"\n\n";
    $$ = new symbol_info($1->get_name(), "expression");
    $$->set_data_type($1->get_data_type());
}
| variable ASSIGNOP logic_expression
{
    outlog<<"At line no: "<<lines<<" expression : variable ASSIGNOP logic_expression \n\n";
    string str = $1->get_name() + "=" + $3->get_name();
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "expression");
    $$->set_data_type($1->get_data_type());
    
    if($3->get_data_type() == "void" || $1->get_data_type() == "void") {
        printError("operation on void type "); // added trailing space as in error1.txt if any
    } else if($1->get_data_type() == "int" && $3->get_data_type() == "float") {
        // According to error files, warning appears here
        printError("Warning: Assignment of float value into variable of integer type ");
    }
}
;

logic_expression : rel_expression
{
    outlog<<"At line no: "<<lines<<" logic_expression : rel_expression \n\n";
    outlog<<$1->get_name()<<"\n\n";
    $$ = new symbol_info($1->get_name(), "logic_expression");
    $$->set_data_type($1->get_data_type());
}
| rel_expression LOGICOP rel_expression
{
    outlog<<"At line no: "<<lines<<" logic_expression : rel_expression LOGICOP rel_expression \n\n";
    string str = $1->get_name() + $2->get_name() + $3->get_name();
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "logic_expression");
    $$->set_data_type("int");
}
;

rel_expression : simple_expression
{
    outlog<<"At line no: "<<lines<<" rel_expression : simple_expression \n\n";
    outlog<<$1->get_name()<<"\n\n";
    $$ = new symbol_info($1->get_name(), "rel_expression");
    $$->set_data_type($1->get_data_type());
}
| simple_expression RELOP simple_expression
{
    outlog<<"At line no: "<<lines<<" rel_expression : simple_expression RELOP simple_expression \n\n";
    string str = $1->get_name() + $2->get_name() + $3->get_name();
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "rel_expression");
    $$->set_data_type("int");
    if($1->get_data_type() == "void" || $3->get_data_type() == "void") {
        printError("operation on void type ");
    }
}
;

simple_expression : term
{
    outlog<<"At line no: "<<lines<<" simple_expression : term \n\n";
    outlog<<$1->get_name()<<"\n\n";
    $$ = new symbol_info($1->get_name(), "simple_expression");
    $$->set_data_type($1->get_data_type());
}
| simple_expression ADDOP term
{
    outlog<<"At line no: "<<lines<<" simple_expression : simple_expression ADDOP term \n\n";
    string str = $1->get_name() + $2->get_name() + $3->get_name();
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "simple_expression");
    
    if($1->get_data_type() == "void" || $3->get_data_type() == "void") {
        printError("operation on void type ");
    }
    
    if($1->get_data_type() == "float" || $3->get_data_type() == "float") {
        $$->set_data_type("float");
    } else {
        $$->set_data_type("int");
    }
}
;

term : unary_expression
{
    outlog<<"At line no: "<<lines<<" term : unary_expression \n\n";
    outlog<<$1->get_name()<<"\n\n";
    $$ = new symbol_info($1->get_name(), "term");
    $$->set_data_type($1->get_data_type());
}
| term MULOP unary_expression
{
    outlog<<"At line no: "<<lines<<" term : term MULOP unary_expression \n\n";
    string str = $1->get_name() + $2->get_name() + $3->get_name();
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "term");
    
    if($1->get_data_type() == "void" || $3->get_data_type() == "void") {
        printError("operation on void type ");
    }
    
    if($2->get_name() == "%") {
        if($1->get_data_type() != "int" || $3->get_data_type() != "int") {
            printError("Modulus operator on non integer type ");
        }
        if($3->get_name() == "0") {
            printError("Modulus by 0 ");
        }
        $$->set_data_type("int");
    } else if($2->get_name() == "/") {
        if($3->get_name() == "0") {
            printError("Division by 0 ");
        }
    }
    
    if($2->get_name() != "%") {
         if($1->get_data_type() == "float" || $3->get_data_type() == "float") {
            $$->set_data_type("float");
        } else {
            $$->set_data_type("int");
        }
    }
}
;

unary_expression : ADDOP unary_expression
{
    outlog<<"At line no: "<<lines<<" unary_expression : ADDOP unary_expression \n\n";
    string str = $1->get_name() + $2->get_name();
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "unary_expression");
    $$->set_data_type($2->get_data_type());
}
| NOT unary_expression
{
    outlog<<"At line no: "<<lines<<" unary_expression : NOT unary_expression \n\n";
    string str = "!" + $2->get_name();
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "unary_expression");
    $$->set_data_type("int");
}
| factor
{
    outlog<<"At line no: "<<lines<<" unary_expression : factor \n\n";
    outlog<<$1->get_name()<<"\n\n";
    $$ = new symbol_info($1->get_name(), "unary_expression");
    $$->set_data_type($1->get_data_type());
}
;

factor : variable
{
    outlog<<"At line no: "<<lines<<" factor : variable \n\n";
    outlog<<$1->get_name()<<"\n\n";
    $$ = new symbol_info($1->get_name(), "factor");
    $$->set_data_type($1->get_data_type());
}
| ID LPAREN argument_list RPAREN
{
    outlog<<"At line no: "<<lines<<" factor : ID LPAREN argument_list RPAREN \n\n";
    string str = $1->get_name() + "(" + $3->get_name() + ")";
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "factor");
    
    symbol_info* existing = st->lookup($1);
    if(existing == NULL) {
        printError("Undeclared function: " + $1->get_name());
        $$->set_data_type("int");
    } else {
        if(existing->get_category() != "FUNCTION") {
            printError($1->get_name() + " is not a function");
        } else {
            $$->set_data_type(existing->get_data_type());
            
            // Check arguments
            vector<string> p_types = existing->get_parameter_types();
            if(p_types.size() != arguments_list.size()) {
                printError("Inconsistencies in number of arguments in function call: " + $1->get_name());
            } else {
                for(size_t i=0; i<arguments_list.size(); ++i) {
                    if(arguments_list[i]->get_data_type() != "error" && arguments_list[i]->get_data_type() != p_types[i]) {
                        printError("argument " + to_string(i+1) + " type mismatch in function call: " + $1->get_name());
                    }
                }
            }
        }
    }
    arguments_list.clear();
}
| LPAREN expression RPAREN
{
    outlog<<"At line no: "<<lines<<" factor : LPAREN expression RPAREN \n\n";
    string str = "(" + $2->get_name() + ")";
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "factor");
    $$->set_data_type($2->get_data_type());
}
| CONST_INT
{
    outlog<<"At line no: "<<lines<<" factor : CONST_INT \n\n";
    outlog<<$1->get_name()<<"\n\n";
    $$ = new symbol_info($1->get_name(), "factor");
    $$->set_data_type("int");
}
| CONST_FLOAT
{
    outlog<<"At line no: "<<lines<<" factor : CONST_FLOAT \n\n";
    outlog<<$1->get_name()<<"\n\n";
    $$ = new symbol_info($1->get_name(), "factor");
    $$->set_data_type("float");
}
| variable INCOP
{
    outlog<<"At line no: "<<lines<<" factor : variable INCOP \n\n";
    string str = $1->get_name() + "++";
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "factor");
    $$->set_data_type($1->get_data_type());
}
| variable DECOP
{
    outlog<<"At line no: "<<lines<<" factor : variable DECOP \n\n";
    string str = $1->get_name() + "--";
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "factor");
    $$->set_data_type($1->get_data_type());
}
;

argument_list : arguments
{
    outlog<<"At line no: "<<lines<<" argument_list : arguments \n\n";
    outlog<<$1->get_name()<<"\n\n";
    $$ = new symbol_info($1->get_name(), "argument_list");
}
| /* empty */
{
    $$ = new symbol_info("", "argument_list");
}
;

arguments : arguments COMMA logic_expression
{
    outlog<<"At line no: "<<lines<<" arguments : arguments COMMA logic_expression \n\n";
    string str = $1->get_name() + "," + $3->get_name();
    outlog<<str<<"\n\n";
    $$ = new symbol_info(str, "arguments");
    arguments_list.push_back($3);
}
| logic_expression
{
    outlog<<"At line no: "<<lines<<" arguments : logic_expression \n\n";
    outlog<<$1->get_name()<<"\n\n";
    $$ = new symbol_info($1->get_name(), "arguments");
    
    arguments_list.clear();
    arguments_list.push_back($1);
}
;

%%

int main(int argc, char *argv[])
{
	if(argc!=2){
		cout<<"Please input file name\n";
		return 0;
	}
	yyin = fopen(argv[1], "r");
	
	outlog.open("22101530_log.txt", ios::trunc);
	outerr.open("22101530_error.txt", ios::trunc);
	
	st = new symbol_table(11);
	
	yyparse();
	
	outlog<<"Total lines: "<<lines<<"\n";
	outlog<<"Total errors: "<<errors<<"\n";
	outerr<<"Total errors: "<<errors<<"\n";
	
	outlog.close();
	outerr.close();
	
	return 0;
}
