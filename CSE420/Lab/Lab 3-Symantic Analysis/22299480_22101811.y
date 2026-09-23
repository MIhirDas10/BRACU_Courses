%{

#include "symbol_table.h"

#define YYSTYPE symbol_info*

extern FILE *yyin;
int yyparse(void);
int yylex(void);
extern YYSTYPE yylval;

symbol_table *st;

int lines = 1;

ofstream outlog;
ofstream outerror;
int error_count = 0;

/*
	Semantic-analysis working lists:
	- decl_list holds all variables/arrays from one declaration until the
	  declared type is known in variable_decl.
	- paramtype/paramname collect the current function header parameters.
	- pending_paramtype/pending_paramname keep those parameters temporarily
	  until the function-body scope is created by compound_statement.
	- add_params_to_next_scope tells the next compound statement that it is a
	  function body, so parameters must be inserted as local variables there.
	By doing this, declarations, parameters, and function scopes are connected
	to the symbol table instead of only being printed in the grammar log.
*/
vector<symbol_info*> decl_list;
vector<string> paramtype;
vector<string> paramname;
vector<string> pending_paramtype;
vector<string> pending_paramname;
bool add_params_to_next_scope = false;

void yyerror(char *s)
{
	outlog<<"At line "<<lines<<" "<<s<<endl<<endl;
}

%}

%token IF ELSE FOR WHILE DO BREAK INT CHAR FLOAT DOUBLE VOID RETURN SWITCH CASE DEFAULT CONTINUE PRINTLN ADDOP MULOP INCOP DECOP RELOP ASSIGNOP LOGICOP NOT LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON CONST_INT CONST_FLOAT ID

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

start : program
	{
		outlog<<"At line no: "<<lines<<" start : program "<<endl<<endl;
		outlog<<"Symbol Table"<<endl<<endl;
		
		st->print_all_scopes(outlog);
	}
	;

program : program unit
	{
		outlog<<"At line no: "<<lines<<" program : program unit "<<endl<<endl;
		outlog<<$1->getname()+"\n"+$2->getname()<<endl<<endl;
		
		$$ = new symbol_info($1->getname()+"\n"+$2->getname(),"program");
	}
	| unit
	{
		outlog<<"At line no: "<<lines<<" program : unit "<<endl<<endl;
		outlog<<$1->getname()<<endl<<endl;
		
		$$ = new symbol_info($1->getname(),"program");
	}
	;

unit : variable_decl
	 {
		outlog<<"At line no: "<<lines<<" unit : variable_decl "<<endl<<endl;
		outlog<<$1->getname()<<endl<<endl;
		
		$$ = new symbol_info($1->getname(),"unit");
	 }
     | func_definition
     {
		outlog<<"At line no: "<<lines<<" unit : func_definition "<<endl<<endl;
		outlog<<$1->getname()<<endl<<endl;
		
		$$ = new symbol_info($1->getname(),"unit");
	 }
     ;

func_definition : type_specifier ID LPAREN param_list RPAREN
		{
			/*
				Function with parameters:
				First check whether the same parameter name appears more than
				once in this function header. Empty parameter names are skipped
				because a rule like "int, float" stores only types.
				If duplicate names exist, an error is written to both output
				files and error_count is increased.
			*/
			for(int i=0; i<(int)paramname.size(); i++)
			{
				if(paramname[i] == "") continue;
				for(int j=0; j<i; j++)
				{
					if(paramname[i] == paramname[j])
					{
						outlog<<"At line no: "<<lines<<" Multiple declaration of variable "<<paramname[i]<<" in parameter of "<<$2->getname()<<endl<<endl;
						outerror<<"At line no: "<<lines<<" Multiple declaration of variable "<<paramname[i]<<" in parameter of "<<$2->getname()<<endl<<endl;
						error_count++;
						break;
					}
				}
			}

			/*
				Now create the function symbol before parsing its body.
				The symbol stores:
				- category/id type: function
				- return type: the type_specifier before the function name
				- parameter types and names: collected from param_list
				Inserting here lets later function calls look up this function
				and validate argument count/type.
			*/
			symbol_info *s = new symbol_info($2->getname(), "ID");
			s->setidtype("function");
			s->setreturntype($1->getname());
			s->set_parameters(paramtype, paramname);
			if(!st->insert(s))
			{
				outlog<<"At line no: "<<lines<<" Multiple declaration of function "<<$2->getname()<<endl<<endl;
				outerror<<"At line no: "<<lines<<" Multiple declaration of function "<<$2->getname()<<endl<<endl;
				error_count++;
				delete s;
			}

			/*
				The compound_statement has not opened its scope yet.
				So parameters are copied into pending_* lists and inserted when
				the next LCURL creates the function body's local scope.
				This prevents parameters from being inserted into global scope.
			*/
			pending_paramtype = paramtype;
			pending_paramname = paramname;
			paramtype.clear();
			paramname.clear();
			add_params_to_next_scope = true;
		}
		compound_statement
		{	
			outlog<<"At line no: "<<lines<<" func_definition : type_specifier ID LPAREN param_list RPAREN compound_statement "<<endl<<endl;
			outlog<<$1->getname()<<" "<<$2->getname()<<"("+$4->getname()+")\n"<<$7->getname()<<endl<<endl;
			
			$$ = new symbol_info($1->getname()+" "+$2->getname()+"("+$4->getname()+")\n"+$7->getname(),"func_def");	
		}
		| type_specifier ID LPAREN RPAREN
		{
			/*
				Function with no parameters:
				Clear parameter lists, insert the function symbol with an empty
				parameter signature, then mark the next compound scope as the
				function body. This keeps zero-argument functions consistent with
				parameterized functions.
			*/
			paramtype.clear();
			paramname.clear();

			symbol_info *s = new symbol_info($2->getname(), "ID");
			s->setidtype("function");
			s->setreturntype($1->getname());
			s->set_parameters(paramtype, paramname);
			if(!st->insert(s))
			{
				outlog<<"At line no: "<<lines<<" Multiple declaration of function "<<$2->getname()<<endl<<endl;
				outerror<<"At line no: "<<lines<<" Multiple declaration of function "<<$2->getname()<<endl<<endl;
				error_count++;
				delete s;
			}

			pending_paramtype.clear();
			pending_paramname.clear();
			add_params_to_next_scope = true;
		}
		compound_statement
		{
			
			outlog<<"At line no: "<<lines<<" func_definition : type_specifier ID LPAREN RPAREN compound_statement "<<endl<<endl;
			outlog<<$1->getname()<<" "<<$2->getname()<<"()\n"<<$6->getname()<<endl<<endl;
			
			$$ = new symbol_info($1->getname()+" "+$2->getname()+"()\n"+$6->getname(),"func_def");	
		}
 		;

param_list : param_list COMMA type_specifier ID
		{
			outlog<<"At line no: "<<lines<<" param_list : param_list COMMA type_specifier ID "<<endl<<endl;
			outlog<<$1->getname()<<","<<$3->getname()<<" "<<$4->getname()<<endl<<endl;
					
			/*
				Append a named parameter.
				The type is used for function-call type matching, and the name is
				used for duplicate-parameter checks and insertion into the
				function-body scope.
			*/
			paramtype.push_back($3->getname());
			paramname.push_back($4->getname());
			$$ = new symbol_info($1->getname()+","+$3->getname()+" "+$4->getname(),"param_list");
		}
		| param_list COMMA type_specifier
		{
			outlog<<"At line no: "<<lines<<" param_list : param_list COMMA type_specifier "<<endl<<endl;
			outlog<<$1->getname()<<","<<$3->getname()<<endl<<endl;
			
			/*
				Append an unnamed parameter.
				It contributes to the function signature, but it is not inserted
				as a local variable because there is no parameter name.
			*/
			paramtype.push_back($3->getname());
			paramname.push_back("");
			$$ = new symbol_info($1->getname()+","+$3->getname(),"param_list");
		}
 		| type_specifier ID
 		{
			outlog<<"At line no: "<<lines<<" param_list : type_specifier ID "<<endl<<endl;
			outlog<<$1->getname()<<" "<<$2->getname()<<endl<<endl;
			
			/*
				Start a new parameter list with one named parameter.
				Clearing first is important because param_list is global
				temporary state reused across function definitions.
			*/
			paramtype.clear();
			paramname.clear();
			paramtype.push_back($1->getname());
			paramname.push_back($2->getname());
			$$ = new symbol_info($1->getname()+" "+$2->getname(),"param_list");
		}
		| type_specifier
		{
			outlog<<"At line no: "<<lines<<" param_list : type_specifier "<<endl<<endl;
			outlog<<$1->getname()<<endl<<endl;
			
			/*
				Start a new parameter list with one unnamed parameter.
				The empty name preserves the parameter count/type but prevents
				accidental local-variable insertion later.
			*/
			paramtype.clear();
			paramname.clear();
			paramtype.push_back($1->getname());
			paramname.push_back("");
			$$ = new symbol_info($1->getname(),"param_list");
		}
 		;

compound_statement : LCURL
			{
				/*
					Every compound statement creates a new scope.
					If this block is the body immediately after a function header,
					add_params_to_next_scope is true, so pending parameters are
					inserted into this new local scope as variables.
				*/
				st->enter_scope(outlog);

				if(add_params_to_next_scope)
				{
					for(int i=0; i<(int)pending_paramtype.size(); i++)
					{
						if(i >= (int)pending_paramname.size() || pending_paramname[i] == "") continue;

						symbol_info *s = new symbol_info(pending_paramname[i], "ID");
						s->setidtype("var");
						s->setvartype(pending_paramtype[i]);
						if(!st->insert(s)) delete s;
					}

					pending_paramtype.clear();
					pending_paramname.clear();
					add_params_to_next_scope = false;
				}
			}
			statements RCURL
			{ 
 		    	outlog<<"At line no: "<<lines<<" compound_statement : LCURL statements RCURL "<<endl<<endl;
				outlog<<"{\n"+$3->getname()+"\n}"<<endl<<endl;
				
				$$ = new symbol_info("{\n"+$3->getname()+"\n}","comp_stmnt");
				/*
					Print the active scopes before removing the current one.
					This shows the variables/parameters declared inside the block
					in the log before they go out of scope.
				*/
				st->print_all_scopes(outlog);
				st->exit_scope(outlog);
 		    }
 		    | LCURL
			{
				/*
					Empty compound statements still create scopes.
					This duplicate setup handles cases like an empty function body:
					int f(int x) { }
					The parameter x still needs to be inserted and printed before
					the scope is removed.
				*/
				st->enter_scope(outlog);

				if(add_params_to_next_scope)
				{
					for(int i=0; i<(int)pending_paramtype.size(); i++)
					{
						if(i >= (int)pending_paramname.size() || pending_paramname[i] == "") continue;

						symbol_info *s = new symbol_info(pending_paramname[i], "ID");
						s->setidtype("var");
						s->setvartype(pending_paramtype[i]);
						if(!st->insert(s)) delete s;
					}

					pending_paramtype.clear();
					pending_paramname.clear();
					add_params_to_next_scope = false;
				}
			}
			RCURL
 		    { 
 		    	outlog<<"At line no: "<<lines<<" compound_statement : LCURL RCURL "<<endl<<endl;
				outlog<<"{\n}"<<endl<<endl;
				
				$$ = new symbol_info("{\n}","comp_stmnt");
				st->print_all_scopes(outlog);
				st->exit_scope(outlog);
 		    }
 		    ;
 		    
variable_decl : type_specifier declaration_list SEMICOLON
		 {
			outlog<<"At line no: "<<lines<<" variable_decl : type_specifier declaration_list SEMICOLON "<<endl<<endl;
			outlog<<$1->getname()<<" "<<$2->getname()<<";"<<endl<<endl;
			
			/*
				After declaration_list finishes, decl_list contains all declared
				names from the statement. Here the final type_specifier is applied
				to each symbol, then each symbol is inserted into the current
				scope. Duplicate insertion means the same name already exists in
				this scope.
			*/
			for(int i=0; i<(int)decl_list.size(); i++)
			{
				if($1->getname() == "void")
				{
					outlog<<"At line no: "<<lines<<" variable type can not be void "<<endl<<endl;
					outerror<<"At line no: "<<lines<<" variable type can not be void "<<endl<<endl;
					error_count++;
					decl_list[i]->setvartype("error");
				}
				else
				{
					decl_list[i]->setvartype($1->getname());
				}

				if(!st->insert(decl_list[i]))
				{
					outlog<<"At line no: "<<lines<<" Multiple declaration of variable "<<decl_list[i]->getname()<<endl<<endl;
					outerror<<"At line no: "<<lines<<" Multiple declaration of variable "<<decl_list[i]->getname()<<endl<<endl;
					error_count++;
					delete decl_list[i];
				}
			}
			decl_list.clear();

			$$ = new symbol_info($1->getname()+" "+$2->getname()+";","var_dec");
		 }
 		 ;

type_specifier : INT
		{
			outlog<<"At line no: "<<lines<<" type_specifier : INT "<<endl<<endl;
			outlog<<"int"<<endl<<endl;
			
			$$ = new symbol_info("int","type");
	    }
 		| FLOAT
 		{
			outlog<<"At line no: "<<lines<<" type_specifier : FLOAT "<<endl<<endl;
			outlog<<"float"<<endl<<endl;
			
			$$ = new symbol_info("float","type");
	    }
 		| VOID
 		{
			outlog<<"At line no: "<<lines<<" type_specifier : VOID "<<endl<<endl;
			outlog<<"void"<<endl<<endl;
			
			$$ = new symbol_info("void","type");
	    }
		| CHAR
 		{
			outlog<<"At line no: "<<lines<<" type_specifier : CHAR "<<endl<<endl;
			outlog<<"char"<<endl<<endl;
			
			$$ = new symbol_info("char","type");
	    }
 		;

declaration_list : declaration_list COMMA ID
		  {
 		  	outlog<<"At line no: "<<lines<<" declaration_list : declaration_list COMMA ID "<<endl<<endl;
 		  	outlog<<$1->getname()+","<<$3->getname()<<endl<<endl;

			/*
				Store this scalar variable temporarily.
				Its actual type is not set here because the shared
				type_specifier is handled in variable_decl.
			*/
			symbol_info *s = new symbol_info($3->getname(), "ID");
			s->setidtype("var");
            decl_list.push_back(s);
			$$ = new symbol_info($1->getname()+","+$3->getname(),"decl_list");
 		  }
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
 		  {
 		  	outlog<<"At line no: "<<lines<<" declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD "<<endl<<endl;
 		  	outlog<<$1->getname()+","<<$3->getname()<<"["<<$5->getname()<<"]"<<endl<<endl;

			/*
				Store this array temporarily with its size.
				The array category lets later semantic checks reject scalar/array
				misuse, such as using an array without an index.
			*/
			symbol_info *s = new symbol_info($3->getname(), "ID");
			s->setidtype("array");
			s->setarraysize(atoi($5->getname().c_str()));
            decl_list.push_back(s);
			$$ = new symbol_info($1->getname()+","+$3->getname()+"["+$5->getname()+"]","decl_list");
 		  }
 		  |ID
 		  {
 		  	outlog<<"At line no: "<<lines<<" declaration_list : ID "<<endl<<endl;
			outlog<<$1->getname()<<endl<<endl;

            /*
            	This is the first name in a new declaration_list, so clear any
            	previous declaration state before storing the scalar variable.
            */
            decl_list.clear();
			symbol_info *s = new symbol_info($1->getname(), "ID");
			s->setidtype("var");
			decl_list.push_back(s);
			$$ = new symbol_info($1->getname(),"decl_list");
 		  }
 		  | ID LTHIRD CONST_INT RTHIRD
 		  {
 		  	outlog<<"At line no: "<<lines<<" declaration_list : ID LTHIRD CONST_INT RTHIRD "<<endl<<endl;
			outlog<<$1->getname()<<"["<<$3->getname()<<"]"<<endl<<endl;

            /*
            	First item in a declaration_list can also be an array.
            	The size is saved immediately; the element type is applied later
            	in variable_decl.
            */
            decl_list.clear();
			symbol_info *s = new symbol_info($1->getname(), "ID");
			s->setidtype("array");
			s->setarraysize(atoi($3->getname().c_str()));
			decl_list.push_back(s);
			$$ = new symbol_info($1->getname()+"["+$3->getname()+"]","decl_list");
 		  }
 		  ;
 		  

statements : statement
	   {
	    	outlog<<"At line no: "<<lines<<" statements : statement "<<endl<<endl;
			outlog<<$1->getname()<<endl<<endl;
			
			$$ = new symbol_info($1->getname(),"stmnts");
	   }
	   | statements statement
	   {
	    	outlog<<"At line no: "<<lines<<" statements : statements statement "<<endl<<endl;
			outlog<<$1->getname()<<"\n"<<$2->getname()<<endl<<endl;
			
			$$ = new symbol_info($1->getname()+"\n"+$2->getname(),"stmnts");
	   }
	   ;
	   
statement : variable_decl
	  {
	    	outlog<<"At line no: "<<lines<<" statement : variable_decl "<<endl<<endl;
			outlog<<$1->getname()<<endl<<endl;
			
			$$ = new symbol_info($1->getname(),"stmnt");
	  }
	  | func_definition
	  {
	  		outlog<<"At line no: "<<lines<<" statement : func_definition "<<endl<<endl;
            outlog<<$1->getname()<<endl<<endl;

            $$ = new symbol_info($1->getname(),"stmnt");
	  		
	  }
	  | expression_statement
	  {
	    	outlog<<"At line no: "<<lines<<" statement : expression_statement "<<endl<<endl;
			outlog<<$1->getname()<<endl<<endl;
			
			$$ = new symbol_info($1->getname(),"stmnt");
	  }
	  | compound_statement
	  {
	    	outlog<<"At line no: "<<lines<<" statement : compound_statement "<<endl<<endl;
			outlog<<$1->getname()<<endl<<endl;
			
			$$ = new symbol_info($1->getname(),"stmnt");
	  }
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement
	  {
	    	outlog<<"At line no: "<<lines<<" statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement "<<endl<<endl;
			outlog<<"for("<<$3->getname()<<$4->getname()<<$5->getname()<<")\n"<<$7->getname()<<endl<<endl;
			
			$$ = new symbol_info("for("+$3->getname()+$4->getname()+$5->getname()+")\n"+$7->getname(),"stmnt");
	  }
	  | IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE
	  {
	    	outlog<<"At line no: "<<lines<<" statement : IF LPAREN expression RPAREN statement "<<endl<<endl;
			outlog<<"if("<<$3->getname()<<")\n"<<$5->getname()<<endl<<endl;
			
			$$ = new symbol_info("if("+$3->getname()+")\n"+$5->getname(),"stmnt");
	  }
	  | IF LPAREN expression RPAREN statement ELSE statement
	  {
	    	outlog<<"At line no: "<<lines<<" statement : IF LPAREN expression RPAREN statement ELSE statement "<<endl<<endl;
			outlog<<"if("<<$3->getname()<<")\n"<<$5->getname()<<"\nelse\n"<<$7->getname()<<endl<<endl;
			
			$$ = new symbol_info("if("+$3->getname()+")\n"+$5->getname()+"\nelse\n"+$7->getname(),"stmnt");
	  }
	  | WHILE LPAREN expression RPAREN statement
	  {
	    	outlog<<"At line no: "<<lines<<" statement : WHILE LPAREN expression RPAREN statement "<<endl<<endl;
			outlog<<"while("<<$3->getname()<<")\n"<<$5->getname()<<endl<<endl;
			
			$$ = new symbol_info("while("+$3->getname()+")\n"+$5->getname(),"stmnt");
	  }
	  | PRINTLN LPAREN ID RPAREN SEMICOLON
	  {
	    	outlog<<"At line no: "<<lines<<" statement : PRINTLN LPAREN ID RPAREN SEMICOLON "<<endl<<endl;
			outlog<<"printf("<<$3->getname()<<");"<<endl<<endl; 
			/*
				printf/println receives an ID directly in this grammar.
				Look it up so printing an undeclared variable becomes a semantic
				error instead of silently passing.
			*/
			symbol_info *found = st->lookup($3->getname());
			if(found == NULL)
			{
				outlog<<"At line no: "<<lines<<" Undeclared variable "<<$3->getname()<<endl<<endl;
				outerror<<"At line no: "<<lines<<" Undeclared variable "<<$3->getname()<<endl<<endl;
				error_count++;
			}
			
			$$ = new symbol_info("printf("+$3->getname()+");","stmnt");
	  }
	  | RETURN expression SEMICOLON
	  {
	    	outlog<<"At line no: "<<lines<<" statement : RETURN expression SEMICOLON "<<endl<<endl;
			outlog<<"return "<<$2->getname()<<";"<<endl<<endl;
			
			$$ = new symbol_info("return "+$2->getname()+";","stmnt");
	  }
	  ;
	  
expression_statement : SEMICOLON
			{
				outlog<<"At line no: "<<lines<<" expression_statement : SEMICOLON "<<endl<<endl;
				outlog<<";"<<endl<<endl;
				
				$$ = new symbol_info(";","expr_stmt");
	        }			
			| expression SEMICOLON 
			{
				outlog<<"At line no: "<<lines<<" expression_statement : expression SEMICOLON "<<endl<<endl;
				outlog<<$1->getname()<<";"<<endl<<endl;
				
				$$ = new symbol_info($1->getname()+";","expr_stmt");
	        }
			;
	  
variable : ID 	
      {
	    outlog<<"At line no: "<<lines<<" variable : ID "<<endl<<endl;
		outlog<<$1->getname()<<endl<<endl;
			
		$$ = new symbol_info($1->getname(),"varbl");
		/*
			Scalar variable use:
			- missing symbol means undeclared variable
			- array symbol used without [] means array used like scalar
			- valid scalar copies its declared type into this expression node
		*/
		symbol_info *found = st->lookup($1->getname());
		if(found == NULL)
		{
			outlog<<"At line no: "<<lines<<" Undeclared variable "<<$1->getname()<<endl<<endl;
			outerror<<"At line no: "<<lines<<" Undeclared variable "<<$1->getname()<<endl<<endl;
			error_count++;
			$$->setvartype("error");
		}
		else if(found->getidtype() == "array")
		{
			outlog<<"At line no: "<<lines<<" variable is of array type : "<<$1->getname()<<endl<<endl;
			outerror<<"At line no: "<<lines<<" variable is of array type : "<<$1->getname()<<endl<<endl;
			error_count++;
			$$->setvartype("error");
		}
		else
		{
			$$->setvartype(found->getvartype());
		}
		
	 }	
	 | ID LTHIRD expression RTHIRD 
	 {
	 	outlog<<"At line no: "<<lines<<" variable : ID LTHIRD expression RTHIRD "<<endl<<endl;
		outlog<<$1->getname()<<"["<<$3->getname()<<"]"<<endl<<endl;
		
		$$ = new symbol_info($1->getname()+"["+$3->getname()+"]","varbl");
		/*
			Array variable use:
			First confirm the symbol exists and is actually an array.
			Then check that the index expression type is int. Empty/error index
			types are ignored here to avoid repeating earlier errors.
		*/
		symbol_info *found = st->lookup($1->getname());
		if(found == NULL)
		{
			outlog<<"At line no: "<<lines<<" Undeclared variable "<<$1->getname()<<endl<<endl;
			outerror<<"At line no: "<<lines<<" Undeclared variable "<<$1->getname()<<endl<<endl;
			error_count++;
			$$->setvartype("error");
		}
		else
		{
			if(found->getidtype() != "array")
			{
				outlog<<"At line no: "<<lines<<" variable is not of array type : "<<$1->getname()<<endl<<endl;
				outerror<<"At line no: "<<lines<<" variable is not of array type : "<<$1->getname()<<endl<<endl;
				error_count++;
				$$->setvartype("error");
			}
			else
			{
				$$->setvartype(found->getvartype());
			}

			if($3->getvartype() != "int" && $3->getvartype() != "" && $3->getvartype() != "error")
			{
				outlog<<"At line no: "<<lines<<" array index is not of integer type : "<<$1->getname()<<endl<<endl;
				outerror<<"At line no: "<<lines<<" array index is not of integer type : "<<$1->getname()<<endl<<endl;
				error_count++;
				$$->setvartype("error");
			}
		}
	 }
	 ;
	 
expression : logic_expression
	   {
	    	outlog<<"At line no: "<<lines<<" expression : logic_expression "<<endl<<endl;
			outlog<<$1->getname()<<endl<<endl;
			
			$$ = new symbol_info($1->getname(),"expr");
			/*
				Plain expression keeps the type computed by logic_expression.
				This propagation is what lets parent rules type-check nested
				expressions.
			*/
			$$->setvartype($1->getvartype());
	   }
	   | variable ASSIGNOP logic_expression 	
	   {
	    	outlog<<"At line no: "<<lines<<" expression : variable ASSIGNOP logic_expression "<<endl<<endl;
			outlog<<$1->getname()<<"="<<$3->getname()<<endl<<endl;

			$$ = new symbol_info($1->getname()+"="+$3->getname(),"expr");
			/*
				Assignment check:
				- assigning a void expression is invalid
				- assigning float into int is reported as a warning/error
				- otherwise the assignment expression takes the left variable type
				- prior errors are preserved as "error" to avoid false success
			*/
			if($3->getvartype() == "void")
			{
				outlog<<"At line no: "<<lines<<" operation on void type "<<endl<<endl;
				outerror<<"At line no: "<<lines<<" operation on void type "<<endl<<endl;
				error_count++;
				$$->setvartype("error");
			}
			else if($1->getvartype() != "" && $1->getvartype() != "error" && $3->getvartype() != "" && $3->getvartype() != "error")
			{
				if($1->getvartype() == "int" && $3->getvartype() == "float")
				{
					outlog<<"At line no: "<<lines<<" Warning: Assignment of float value into variable of integer type "<<endl<<endl;
					outerror<<"At line no: "<<lines<<" Warning: Assignment of float value into variable of integer type "<<endl<<endl;
					error_count++;
				}
				$$->setvartype($1->getvartype());
			}
			else
			{
				$$->setvartype("error");
			}
	   }
	   ;
			
logic_expression : rel_expression
	     {
	    	outlog<<"At line no: "<<lines<<" logic_expression : rel_expression "<<endl<<endl;
			outlog<<$1->getname()<<endl<<endl;
			
			$$ = new symbol_info($1->getname(),"lgc_expr");
			/* Single relational expression keeps its existing type. */
			$$->setvartype($1->getvartype());
	     }	
		 | rel_expression LOGICOP rel_expression 
		 {
	    	outlog<<"At line no: "<<lines<<" logic_expression : rel_expression LOGICOP rel_expression "<<endl<<endl;
			outlog<<$1->getname()<<$2->getname()<<$3->getname()<<endl<<endl;
			
			$$ = new symbol_info($1->getname()+$2->getname()+$3->getname(),"lgc_expr");
			/*
				Logical operators produce int when both operands are valid.
				Void operands are invalid because void has no usable value.
			*/
			if($1->getvartype() == "void" || $3->getvartype() == "void")
			{
				outlog<<"At line no: "<<lines<<" operation on void type "<<endl<<endl;
				outerror<<"At line no: "<<lines<<" operation on void type "<<endl<<endl;
				error_count++;
				$$->setvartype("error");
			}
			else if($1->getvartype() == "" || $1->getvartype() == "error" || $3->getvartype() == "" || $3->getvartype() == "error")
			{
				$$->setvartype("error");
			}
			else
			{
				$$->setvartype("int");
			}
	     }	
		 ;
			
rel_expression	: simple_expression
		{
	    	outlog<<"At line no: "<<lines<<" rel_expression : simple_expression "<<endl<<endl;
			outlog<<$1->getname()<<endl<<endl;
			
			$$ = new symbol_info($1->getname(),"rel_expr");
			$$->setvartype($1->getvartype());
	    }
		| simple_expression RELOP simple_expression
		{
	    	outlog<<"At line no: "<<lines<<" rel_expression : simple_expression RELOP simple_expression "<<endl<<endl;
			outlog<<$1->getname()<<$2->getname()<<$3->getname()<<endl<<endl;
			
			$$ = new symbol_info($1->getname()+$2->getname()+$3->getname(),"rel_expr");
			/*
				Relational operators also produce int truth values.
				Invalid or void operands make the result invalid.
			*/
			if($1->getvartype() == "void" || $3->getvartype() == "void")
			{
				outlog<<"At line no: "<<lines<<" operation on void type "<<endl<<endl;
				outerror<<"At line no: "<<lines<<" operation on void type "<<endl<<endl;
				error_count++;
				$$->setvartype("error");
			}
			else if($1->getvartype() == "" || $1->getvartype() == "error" || $3->getvartype() == "" || $3->getvartype() == "error")
			{
				$$->setvartype("error");
			}
			else
			{
				$$->setvartype("int");
			}
	    }
		;
				
simple_expression : term
          {
	    	outlog<<"At line no: "<<lines<<" simple_expression : term "<<endl<<endl;
			outlog<<$1->getname()<<endl<<endl;
			
			$$ = new symbol_info($1->getname(),"simp_expr");
			$$->setvartype($1->getvartype());
			
	      }
		  | simple_expression ADDOP term 
		  {
	    	outlog<<"At line no: "<<lines<<" simple_expression : simple_expression ADDOP term "<<endl<<endl;
			outlog<<$1->getname()<<$2->getname()<<$3->getname()<<endl<<endl;
			
			$$ = new symbol_info($1->getname()+$2->getname()+$3->getname(),"simp_expr");
			/*
				Add/subtract type rule:
				- any previous error keeps result as error
				- void operand is invalid
				- if either side is float, result is float
				- otherwise both sides are int, so result is int
			*/
			if($1->getvartype() == "" || $1->getvartype() == "error" || $3->getvartype() == "" || $3->getvartype() == "error")
			{
				$$->setvartype("error");
			}
			else if($1->getvartype() == "void" || $3->getvartype() == "void")
			{
				outlog<<"At line no: "<<lines<<" operation on void type "<<endl<<endl;
				outerror<<"At line no: "<<lines<<" operation on void type "<<endl<<endl;
				error_count++;
				$$->setvartype("error");
			}
			else if($1->getvartype() == "float" || $3->getvartype() == "float")
			{
				$$->setvartype("float");
			}
			else
			{
				$$->setvartype("int");
			}
	      }
		  ;
					
term :	unary_expression
     {
	    	outlog<<"At line no: "<<lines<<" term : unary_expression "<<endl<<endl;
			outlog<<$1->getname()<<endl<<endl;
			
			$$ = new symbol_info($1->getname(),"term");
			$$->setvartype($1->getvartype());
			
	 }
     |  term MULOP unary_expression
     {
	    	outlog<<"At line no: "<<lines<<" term : term MULOP unary_expression "<<endl<<endl;
			outlog<<$1->getname()<<$2->getname()<<$3->getname()<<endl<<endl;
			
			$$ = new symbol_info($1->getname()+$2->getname()+$3->getname(),"term");
			string op = $2->getname();
			/*
				Multiplication/division/modulus type rule:
				Modulus is handled separately because % requires integer
				operands. Division additionally checks literal zero divisors.
				For * and /, float dominates int unless an operand is void/error.
			*/
			if(op == "%")
			{
				if($1->getvartype() != "int" || $3->getvartype() != "int")
				{
					if($1->getvartype() != "" && $1->getvartype() != "error" && $3->getvartype() != "" && $3->getvartype() != "error")
					{
						outlog<<"At line no: "<<lines<<" Modulus operator on non integer type "<<endl<<endl;
						outerror<<"At line no: "<<lines<<" Modulus operator on non integer type "<<endl<<endl;
						error_count++;
					}
					$$->setvartype("error");
				}
				else if($3->getname() == "0" || $3->getname() == "0.0" || $3->getname() == "0.00")
				{
					outlog<<"At line no: "<<lines<<" Modulus by 0 "<<endl<<endl;
					outerror<<"At line no: "<<lines<<" Modulus by 0 "<<endl<<endl;
					error_count++;
					$$->setvartype("error");
				}
				else
				{
					$$->setvartype("int");
				}
			}
			else
			{
				if(op == "/" && ($3->getname() == "0" || $3->getname() == "0.0" || $3->getname() == "0.00"))
				{
					outlog<<"At line no: "<<lines<<" Division by 0 "<<endl<<endl;
					outerror<<"At line no: "<<lines<<" Division by 0 "<<endl<<endl;
					error_count++;
					$$->setvartype("error");
				}
				else
				{
					if($1->getvartype() == "" || $1->getvartype() == "error" || $3->getvartype() == "" || $3->getvartype() == "error")
					{
						$$->setvartype("error");
					}
					else if($1->getvartype() == "void" || $3->getvartype() == "void")
					{
						outlog<<"At line no: "<<lines<<" operation on void type "<<endl<<endl;
						outerror<<"At line no: "<<lines<<" operation on void type "<<endl<<endl;
						error_count++;
						$$->setvartype("error");
					}
					else if($1->getvartype() == "float" || $3->getvartype() == "float")
					{
						$$->setvartype("float");
					}
					else
					{
						$$->setvartype("int");
					}
				}
			}
			
	 }
     ;

unary_expression : ADDOP unary_expression
		 {
	    	outlog<<"At line no: "<<lines<<" unary_expression : ADDOP unary_expression "<<endl<<endl;
			outlog<<$1->getname()<<$2->getname()<<endl<<endl;
			
			$$ = new symbol_info($1->getname()+$2->getname(),"un_expr");
			$$->setvartype($2->getvartype());
	     }
		 | NOT unary_expression 
		 {
	    	outlog<<"At line no: "<<lines<<" unary_expression : NOT unary_expression "<<endl<<endl;
			outlog<<"!"<<$2->getname()<<endl<<endl;
			
			$$ = new symbol_info("!"+$2->getname(),"un_expr");
			/*
				Logical NOT produces int for valid operands.
				It rejects void because void expressions do not have a value to
				negate.
			*/
			if($2->getvartype() == "void")
			{
				outlog<<"At line no: "<<lines<<" operation on void type "<<endl<<endl;
				outerror<<"At line no: "<<lines<<" operation on void type "<<endl<<endl;
				error_count++;
				$$->setvartype("error");
			}
			else if($2->getvartype() == "" || $2->getvartype() == "error")
			{
				$$->setvartype("error");
			}
			else
			{
				$$->setvartype("int");
			}
	     }
		 | factor_info  
		 {
	    	outlog<<"At line no: "<<lines<<" unary_expression : factor_info "<<endl<<endl;
			outlog<<$1->getname()<<endl<<endl;
			
			$$ = new symbol_info($1->getname(),"un_expr");
			$$->setvartype($1->getvartype());
	     }
		 ;
factor_info : factor	{
	    outlog<<"At line no: "<<lines<<" factor_info : factor "<<endl<<endl;
		outlog<<$1->getname()<<endl<<endl;
			
		$$ = new symbol_info($1->getname(),"fctr_info");
		/*
			factor_info is a small wrapper used to carry the factor's computed
			type upward into unary_expression.
		*/
		$$->setvartype($1->getvartype());
	}	
	;
factor	: variable
    {
	    outlog<<"At line no: "<<lines<<" factor : variable "<<endl<<endl;
		outlog<<$1->getname()<<endl<<endl;
			
		$$ = new symbol_info($1->getname(),"fctr");
		/* A variable factor has the same type computed by variable. */
		$$->setvartype($1->getvartype());
	}
	| ID LPAREN argument_list RPAREN
	{
		outlog<<"At line no: "<<lines<<" factor : ID LPAREN argument_list RPAREN "<<endl<<endl;
		outlog<<$1->getname()<<"("<<$3->getname()<<")"<<endl<<endl;

		$$ = new symbol_info($1->getname()+"("+$3->getname()+")","fctr");
		/*
			Function-call check:
			- function name must be declared
			- declared symbol must actually be a function
			- actual argument count must match expected parameter count
			- actual argument types must match expected parameter types
			The call expression receives the function return type if the function
			symbol is valid.
		*/
		symbol_info *found = st->lookup($1->getname());
		if(found == NULL)
		{
			outlog<<"At line no: "<<lines<<" Undeclared function: "<<$1->getname()<<endl<<endl;
			outerror<<"At line no: "<<lines<<" Undeclared function: "<<$1->getname()<<endl<<endl;
			error_count++;
			$$->setvartype("error");
		}
		else if(found->getidtype() != "function" && found->getidtype() != "func")
		{
			outlog<<"At line no: "<<lines<<" "<<$1->getname()<<" is not a function"<<endl<<endl;
			outerror<<"At line no: "<<lines<<" "<<$1->getname()<<" is not a function"<<endl<<endl;
			error_count++;
			$$->setvartype("error");
		}
		else
		{
			vector<string> expected = found->getparamtype();
			vector<string> got = $3->getparamtype();
			if(expected.size() != got.size())
			{
				outlog<<"At line no: "<<lines<<" Inconsistencies in number of arguments in function call: "<<$1->getname()<<endl<<endl;
				outerror<<"At line no: "<<lines<<" Inconsistencies in number of arguments in function call: "<<$1->getname()<<endl<<endl;
				error_count++;
			}
			else
			{
				for(int i=0; i<(int)expected.size(); i++)
				{
					if(got[i] != "" && got[i] != "error" && expected[i] != got[i])
					{
						outlog<<"At line no: "<<lines<<" argument "<<to_string(i+1)<<" type mismatch in function call: "<<$1->getname()<<endl<<endl;
						outerror<<"At line no: "<<lines<<" argument "<<to_string(i+1)<<" type mismatch in function call: "<<$1->getname()<<endl<<endl;
						error_count++;
					}
				}
			}
			$$->setvartype(found->getreturntype());
		}
	}
	| LPAREN expression RPAREN
	{
	   	outlog<<"At line no: "<<lines<<" factor : LPAREN expression RPAREN "<<endl<<endl;
		outlog<<"("<<$2->getname()<<")"<<endl<<endl;
		
		$$ = new symbol_info("("+$2->getname()+")","fctr");
		/* Parentheses group an expression but do not change its type. */
		$$->setvartype($2->getvartype());
	}
	| CONST_INT 
	{
	    outlog<<"At line no: "<<lines<<" factor : CONST_INT "<<endl<<endl;
		outlog<<$1->getname()<<endl<<endl;
			
		$$ = new symbol_info($1->getname(),"fctr");
		/* Integer literal contributes int type to expression checking. */
		$$->setvartype("int");
	}
	| CONST_FLOAT
	{
	    outlog<<"At line no: "<<lines<<" factor : CONST_FLOAT "<<endl<<endl;
		outlog<<$1->getname()<<endl<<endl;
			
		$$ = new symbol_info($1->getname(),"fctr");
		/* Float literal contributes float type to expression checking. */
		$$->setvartype("float");
	}
	| variable INCOP 
	{
	    outlog<<"At line no: "<<lines<<" factor : variable INCOP "<<endl<<endl;
		outlog<<$1->getname()<<"++"<<endl<<endl;
			
		$$ = new symbol_info($1->getname()+"++","fctr");
		/* Post-increment keeps the variable's type for parent expressions. */
		$$->setvartype($1->getvartype());
	}
	| variable DECOP
	{
	    outlog<<"At line no: "<<lines<<" factor : variable DECOP "<<endl<<endl;
		outlog<<$1->getname()<<"--"<<endl<<endl;
			
		$$ = new symbol_info($1->getname()+"--","fctr");
		/* Post-decrement keeps the variable's type for parent expressions. */
		$$->setvartype($1->getvartype());
	}
	;
	
argument_list : arguments
			  {
					outlog<<"At line no: "<<lines<<" argument_list : arguments "<<endl<<endl;
					outlog<<$1->getname()<<endl<<endl;
						
					$$ = new symbol_info($1->getname(),"arg_list");
					/*
						argument_list passes the collected argument types upward
						so factor can compare them with function parameter types.
					*/
					$$->set_parameters($1->getparamtype(), vector<string>());
			  }
			  |
			  {
					outlog<<"At line no: "<<lines<<" argument_list :  "<<endl<<endl;
					outlog<<""<<endl<<endl;
						
					$$ = new symbol_info("","arg_list");
					/* Empty argument list means zero actual arguments. */
					$$->set_parameters(vector<string>(), vector<string>());
			  }
			  ;
	
arguments : arguments COMMA logic_expression
		  {
				outlog<<"At line no: "<<lines<<" arguments : arguments COMMA logic_expression "<<endl<<endl;
				outlog<<$1->getname()<<","<<$3->getname()<<endl<<endl;
						
				$$ = new symbol_info($1->getname()+","+$3->getname(),"arg");
				/*
					Append this argument expression's type to the existing
					actual-argument type list.
				*/
				vector<string> types = $1->getparamtype();
				types.push_back($3->getvartype());
				$$->set_parameters(types, vector<string>());
		  }
	      | logic_expression
	      {
				outlog<<"At line no: "<<lines<<" arguments : logic_expression "<<endl<<endl;
				outlog<<$1->getname()<<endl<<endl;
						
				$$ = new symbol_info($1->getname(),"arg");
				/* First argument starts the actual-argument type list. */
				vector<string> types;
				types.push_back($1->getvartype());
				$$->set_parameters(types, vector<string>());
		  }
	      ;
 

%%

int main(int argc, char *argv[])
{
	if(argc != 2) 
	{
		cout<<"Please input file name"<<endl;
		return 0;
	}
	yyin = fopen(argv[1], "r");
	/*
		Open separate output files:
		- log file keeps grammar reductions and symbol-table snapshots
		- error file keeps only semantic/syntax error summaries
		ios::trunc makes each run start with clean output.
	*/
	outlog.open("22299480_log.txt", ios::trunc);
	outerror.open("22299480_error.txt", ios::trunc);
	
	if(yyin == NULL)
	{
		cout<<"Couldn't open file"<<endl;
		return 0;
	}

	st = new symbol_table(10);
	/*
		The symbol_table constructor creates the global scope.
		This line records that first scope creation in the required log format.
	*/
	outlog<<"New ScopeTable with ID 1 created"<<endl<<endl;

	yyparse();
	
	outlog<<endl<<"Total lines: "<<lines<<endl<<endl;
	outlog<<"Total errors: "<<error_count<<endl<<endl;
	outerror<<"Total errors: "<<error_count<<endl;
	
	delete st;
	outlog.close();
	outerror.close();
	
	fclose(yyin);
	
	return 0;
}
