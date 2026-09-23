/*
    CHANGE OVERVIEW FOR LAB 3 SEMANTIC ANALYSIS
    File created for explanation only.

    This file is not intended to replace 22299480_22101811.y.
    It is a commented overview that explains where the semantic-analysis
    changes are in the current project, why they were added, and what they do.

    Reference files:
      - Parser/grammar: 22299480_22101811.y
      - Lexer:          22299480_22101811.l
      - Symbol info:    symbol_info.h
      - Scope table:    scope_table.h
      - Symbol table:   symbol_table.h

    Baseline used for comparison:
      - lab2 from git/Lab02.y
      - lab2 from git/Lab02.l
      - lab2 from git/*.h

    Note:
      The explanations below use "line" or "lines" to point to the current
      files listed above. The original parser remains unchanged.
*/

/*
===============================================================================
SECTION 1: GLOBAL SEMANTIC STATE
===============================================================================

22299480_22101811.y, line 17:
    Change:
      Added outerror.
    Why:
      Lab 3 needs a separate error file, not just parser logs.
    Rationale:
      Semantic errors should be easy to check without reading the full derivation
      log.
    Result:
      Errors are written to 22299480_error.txt.

22299480_22101811.y, line 18:
    Change:
      Added error_count.
    Why:
      The assignment output needs total semantic/syntax error count.
    Rationale:
      Every semantic error branch increments one shared counter.
    Result:
      The parser prints "Total errors" at the end of both log and error files.

22299480_22101811.y, line 20:
    Change:
      Added decl_list.
    Why:
      A declaration like "int a, b[5];" is parsed before the type is applied to
      every declared name.
    Rationale:
      Store all declared symbols temporarily, then apply the type after the full
      declaration is reduced.
    Result:
      Multiple variables and arrays in one declaration are inserted correctly.

22299480_22101811.y, lines 21-22:
    Change:
      Added paramtype and paramname.
    Why:
      Function definitions and function calls need parameter type/name tracking.
    Rationale:
      Store types and names separately so duplicate-name checks and argument
      matching are straightforward.
    Result:
      Functions remember return type, parameter count, parameter types, and
      parameter names.

22299480_22101811.y, lines 23-25:
    Change:
      Added pending_paramtype, pending_paramname, and add_params_to_next_scope.
    Why:
      Function parameters must be inserted into the function body's local scope,
      but that scope is created only when the compound statement begins.
    Rationale:
      Save parameters after parsing the function header, then insert them as soon
      as the next "{" creates the function-body scope.
    Result:
      Parameters are visible inside the function body and are not inserted into
      the global scope.
*/

/*
===============================================================================
SECTION 2: FUNCTION DEFINITIONS AND PARAMETER HANDLING
===============================================================================

22299480_22101811.y, lines 82-123:
    Change:
      Split function definition with parameters into header action +
      compound_statement action.
    Why:
      The function symbol must be inserted before entering the function body, and
      the parameters must be prepared for the upcoming body scope.
    Rationale:
      Bison mid-rule action lets semantic work happen immediately after the
      function header is known.
    Result:
      The function is stored in the current/global scope before parsing its body.

22299480_22101811.y, lines 84-97:
    Change:
      Added duplicate parameter-name checking.
    Why:
      Function parameters are variables in the same local scope, so the same name
      cannot appear twice in one parameter list.
    Rationale:
      Compare every named parameter with earlier named parameters. Empty names
      are skipped because prototypes like "int, float" have no parameter names.
    Result:
      "int f(int a, float a)" reports a multiple declaration error.

22299480_22101811.y, lines 99-109:
    Change:
      Added function symbol construction and insertion.
    Why:
      Later function calls need to know that an identifier is a function and what
      its return/parameter types are.
    Rationale:
      Store function metadata in symbol_info, then insert it into the active
      scope. If insertion fails, the function name was already declared.
    Result:
      Duplicate functions are detected, and valid functions can be checked during
      calls.

22299480_22101811.y, lines 111-115:
    Change:
      Moved parameter vectors into pending vectors and cleared active vectors.
    Why:
      The current parameter list has finished, but the body scope has not opened
      yet.
    Rationale:
      Keep a short-lived pending copy so parameters can be inserted exactly when
      "{" opens the function scope.
    Result:
      Parameter storage is reset safely before parsing later declarations.

22299480_22101811.y, lines 124-152:
    Change:
      Added the same function insertion path for functions with no parameters.
    Why:
      "int main()" also needs a function symbol and return type.
    Rationale:
      Empty parameter vectors represent zero-argument functions.
    Result:
      Zero-argument functions are stored and checked consistently.

22299480_22101811.y, lines 155-195:
    Change:
      Reworked parameter list actions to store type/name information.
    Why:
      Lab 2 only printed grammar reductions; Lab 3 must use parameter metadata
      for scope insertion and call checking.
    Rationale:
      Each grammar branch appends or initializes parameter type/name vectors.
    Result:
      Parameter details are available for duplicate checking, symbol-table
      printing, and function-call validation.
*/

/*
===============================================================================
SECTION 3: SCOPE CREATION AND PARAMETER INSERTION
===============================================================================

22299480_22101811.y, lines 197-226:
    Change:
      Added explicit scope creation before parsing non-empty compound statements.
    Why:
      Variables declared inside "{ ... }" need a separate nested scope.
    Rationale:
      Enter the scope immediately after LCURL, before statements are parsed.
    Result:
      Local variables are stored in the correct scope and disappear after RCURL.

22299480_22101811.y, lines 201-216:
    Change:
      Insert pending function parameters into the newly created scope.
    Why:
      Parameters behave like local variables inside the function body.
    Rationale:
      Use the pending vectors only once, then clear them and reset the flag.
    Result:
      Function parameters can be used inside the body without undeclared-variable
      errors.

22299480_22101811.y, lines 224-225:
    Change:
      Print all scopes, then exit the current scope.
    Why:
      Lab output needs scope-table snapshots before a scope is destroyed.
    Rationale:
      Print before exit so the closing scope is still visible.
    Result:
      The log shows nested scopes and then records scope removal.

22299480_22101811.y, lines 227-256:
    Change:
      Added the same scope handling for empty compound statements.
    Why:
      Empty blocks still create scopes, and empty function bodies may still have
      parameters.
    Rationale:
      Duplicate the LCURL setup logic for the LCURL RCURL grammar branch.
    Result:
      Empty function bodies are scoped correctly.
*/

/*
===============================================================================
SECTION 4: VARIABLE AND ARRAY DECLARATION SEMANTICS
===============================================================================

22299480_22101811.y, lines 259-290:
    Change:
      Replaced simple declaration logging with semantic insertion and error
      checking.
    Why:
      Declared variables must be stored in the current scope and duplicate names
      must be rejected.
    Rationale:
      The declaration_list builds symbols first; this rule applies the final
      type and inserts each symbol.
    Result:
      Variables/arrays are available to later expressions, and duplicate local
      declarations are reported.

22299480_22101811.y, lines 266-272:
    Change:
      Added "void variable" error handling.
    Why:
      Variables cannot have type void.
    Rationale:
      Mark the symbol type as error so later expressions do not treat it as a
      valid typed value.
    Result:
      "void x;" produces "variable type can not be void".

22299480_22101811.y, lines 278-284:
    Change:
      Added duplicate declaration detection.
    Why:
      The same variable name cannot be declared twice in the same scope.
    Rationale:
      scope_table::insert_in_scope returns false when the current scope already
      has the name.
    Result:
      Duplicate variables generate an error and the duplicate symbol object is
      deleted.

22299480_22101811.y, lines 313-319:
    Change:
      Added CHAR as a type_specifier branch.
    Why:
      The lexer already recognizes char, and Lab 3 semantic checks should carry
      that type through the grammar.
    Rationale:
      Treat char as another declared type alongside int, float, and void.
    Result:
      "char c;" can be parsed and assigned a symbol type.

22299480_22101811.y, lines 322-366:
    Change:
      declaration_list now builds symbol_info records for variables and arrays.
    Why:
      The symbol table needs category and array-size information, not just text.
    Rationale:
      Each grammar branch creates a symbol_info, sets id type to var/array, and
      pushes it into decl_list.
    Result:
      Later lookups can distinguish scalar variables from arrays.

22299480_22101811.y, lines 337-340 and 360-363:
    Change:
      Array declarations store array category and size.
    Why:
      Array usage checks need to know whether a symbol is an array.
    Rationale:
      Save CONST_INT as array_size when the declaration is parsed.
    Result:
      Symbol-table output can show array size, and array/non-array misuse can be
      detected.
*/

/*
===============================================================================
SECTION 5: STATEMENT-LEVEL SEMANTIC CHECKS
===============================================================================

22299480_22101811.y, lines 442-455:
    Change:
      Added lookup check for printf/println identifier.
    Why:
      Printing an undeclared variable should be reported as a semantic error.
    Rationale:
      The grammar only receives an ID here, so symbol_table lookup is enough.
    Result:
      "printf(x);" reports undeclared variable if x was not declared.
*/

/*
===============================================================================
SECTION 6: VARIABLE USE AND ARRAY USE CHECKS
===============================================================================

22299480_22101811.y, lines 481-507:
    Change:
      Added semantic validation for scalar variable usage.
    Why:
      Expressions need to know whether an identifier exists and what type it has.
    Rationale:
      Lookup the ID; if missing, mark expression type as error. If the ID is an
      array but used without indexing, report array misuse.
    Result:
      Undeclared variables and using an array as a scalar are caught.

22299480_22101811.y, lines 508-545:
    Change:
      Added semantic validation for array indexing.
    Why:
      "a[i]" is valid only when a is declared as an array and i is an int.
    Rationale:
      Check symbol existence, check category, then check index expression type.
    Result:
      Non-array indexing and non-integer array index errors are reported.

22299480_22101811.y, lines 536-542:
    Change:
      Added array index type check.
    Why:
      C-like array indexing requires integer index expressions.
    Rationale:
      Ignore empty/error types to avoid cascading duplicate errors.
    Result:
      "arr[2.5]" reports "array index is not of integer type".
*/

/*
===============================================================================
SECTION 7: EXPRESSION TYPE PROPAGATION AND ASSIGNMENT CHECKS
===============================================================================

22299480_22101811.y, lines 547-554:
    Change:
      Propagated logic_expression type into expression.
    Why:
      Parent grammar rules need expression result type.
    Rationale:
      Every expression node carries vartype in symbol_info.
    Result:
      Nested expressions can be checked by later semantic rules.

22299480_22101811.y, lines 555-582:
    Change:
      Added assignment type checking.
    Why:
      Assignments should reject void values and warn when assigning float to int.
    Rationale:
      Compare left-hand variable type and right-hand expression type after both
      sides are reduced.
    Result:
      Invalid assignments are reported, and valid assignments keep the left-side
      variable type as the expression type.

22299480_22101811.y, lines 561-567:
    Change:
      Added operation-on-void check for assignment RHS.
    Why:
      A void expression has no assignable value.
    Rationale:
      Treat assigning void as an error and stop normal type propagation.
    Result:
      Assigning a void function result reports an error.

22299480_22101811.y, lines 570-575:
    Change:
      Added warning/error count for assigning float into int.
    Why:
      This loses precision in a C-like language.
    Rationale:
      The assignment is still represented, but a warning is emitted through the
      same error-reporting files.
    Result:
      "int a; a = 1.5;" produces the float-to-int warning.
*/

/*
===============================================================================
SECTION 8: LOGICAL, RELATIONAL, ADDITIVE, AND MULTIPLICATIVE OPERATORS
===============================================================================

22299480_22101811.y, lines 585-615:
    Change:
      Added type propagation and validation for LOGICOP expressions.
    Why:
      Logical expressions produce integer truth values and cannot operate on
      void expressions.
    Rationale:
      If either side is invalid/void, preserve error; otherwise result type is
      int.
    Result:
      "a && b" has type int, and void operands are rejected.

22299480_22101811.y, lines 617-647:
    Change:
      Added type propagation and validation for RELOP expressions.
    Why:
      Relational expressions produce integer truth values.
    Rationale:
      Same pattern as logical operators: reject void/error, otherwise result int.
    Result:
      "a < b" has type int.

22299480_22101811.y, lines 649-684:
    Change:
      Added type propagation for addition/subtraction.
    Why:
      Arithmetic expressions need to know whether the result is int or float.
    Rationale:
      If either operand is float, result is float; if both are int, result is int;
      void/error remains error.
    Result:
      Mixed int/float arithmetic produces float and invalid operands are caught.

22299480_22101811.y, lines 686-760:
    Change:
      Added type propagation and special checks for *, /, and %.
    Why:
      Multiplicative operations have special semantic rules, especially modulus
      and division by zero.
    Rationale:
      Split modulus from other MULOP cases because % requires integer operands.
    Result:
      Multiplication/division result types are computed; bad modulus operands,
      modulus by zero, division by zero, and void operands are reported.

22299480_22101811.y, lines 701-724:
    Change:
      Added modulus-specific checks.
    Why:
      The % operator is only valid for integers and cannot use zero divisor.
    Rationale:
      Check operand types first, then literal zero on the right operand.
    Result:
      "5 % 2.5" and "5 % 0" produce semantic errors.

22299480_22101811.y, lines 728-734:
    Change:
      Added division-by-zero check for literal zero divisor.
    Why:
      Division by zero is a semantic/runtime-danger condition expected by the lab.
    Rationale:
      Detect direct literal zero forms available from the grammar text.
    Result:
      "x / 0" reports "Division by 0".
*/

/*
===============================================================================
SECTION 9: UNARY AND FACTOR TYPE HANDLING
===============================================================================

22299480_22101811.y, lines 762-769:
    Change:
      Unary plus/minus now propagates operand type.
    Why:
      "-x" should have the same type as x.
    Rationale:
      No new type is introduced by unary + or -.
    Result:
      Later parent expressions receive the correct type.

22299480_22101811.y, lines 770-791:
    Change:
      Added NOT operator validation and result type.
    Why:
      Logical NOT produces int but cannot operate on void.
    Rationale:
      Invalid operand stays error; valid operand returns int.
    Result:
      "!x" has type int when x is valid.

22299480_22101811.y, lines 792-808:
    Change:
      Added factor_info wrapper.
    Why:
      The grammar separates factor type propagation from unary_expression.
    Rationale:
      This wrapper carries factor vartype upward in one place.
    Result:
      factor types reliably reach unary_expression.

22299480_22101811.y, lines 809-816:
    Change:
      factor : variable now propagates variable type.
    Why:
      A variable used as an expression has the variable's type.
    Rationale:
      Use the type already checked in the variable rule.
    Result:
      Arithmetic and assignment rules can inspect variable expression type.

22299480_22101811.y, lines 817-862:
    Change:
      Added function-call semantic checking.
    Why:
      Calls must verify that the identifier exists, is a function, has correct
      argument count, and receives matching argument types.
    Rationale:
      Lookup function metadata from symbol table and compare against argument
      list types collected by arguments rules.
    Result:
      Undeclared functions, calling variables as functions, wrong argument
      count, and argument type mismatches are reported.

22299480_22101811.y, lines 840-860:
    Change:
      Added parameter type comparison for calls.
    Why:
      A function declared as "int f(int)" should reject "f(1.5)".
    Rationale:
      Compare expected vector from function symbol with actual vector from
      argument_list.
    Result:
      Function calls are semantically validated before their return type is used.

22299480_22101811.y, lines 863-870:
    Change:
      Parenthesized expression now propagates inner expression type.
    Why:
      "(x + y)" has the same type as "x + y".
    Rationale:
      Parentheses group syntax but do not alter semantic type.
    Result:
      Outer expressions receive the inner type.

22299480_22101811.y, lines 871-886:
    Change:
      Constants now receive concrete types.
    Why:
      Arithmetic checks need int/float information from literals.
    Rationale:
      CONST_INT maps to int; CONST_FLOAT maps to float.
    Result:
      "1 + 2.5" correctly becomes float.

22299480_22101811.y, lines 887-902:
    Change:
      Increment/decrement factors propagate variable type.
    Why:
      "x++" and "x--" are expressions based on x.
    Rationale:
      Reuse the already validated variable type.
    Result:
      Parent expressions can still type-check increment/decrement usage.
*/

/*
===============================================================================
SECTION 10: ARGUMENT LIST TYPE COLLECTION
===============================================================================

22299480_22101811.y, lines 905-921:
    Change:
      argument_list now stores collected argument types.
    Why:
      Function-call checking needs actual argument types.
    Rationale:
      Reuse symbol_info parameter vectors as a convenient type list holder.
    Result:
      Empty calls produce an empty type vector; non-empty calls carry argument
      types upward.

22299480_22101811.y, lines 923-943:
    Change:
      arguments now appends each logic_expression type.
    Why:
      Each function argument is an expression whose type matters.
    Rationale:
      Copy previous argument type vector, append current expression type, and
      pass it upward.
    Result:
      Calls like "f(a, b + 1, 2.5)" produce a three-item actual type list.
*/

/*
===============================================================================
SECTION 11: MAIN FUNCTION OUTPUT AND LIFETIME CHANGES
===============================================================================

22299480_22101811.y, lines 956-957:
    Change:
      Output files changed to 22299480_log.txt and 22299480_error.txt.
    Why:
      Assignment outputs usually require student-ID-specific filenames and a
      separate semantic error file.
    Rationale:
      Use ios::trunc so every run starts with clean output files.
    Result:
      Running the parser rewrites fresh log and error files.

22299480_22101811.y, lines 965-966:
    Change:
      Symbol table created with bucket size 10 and initial scope creation logged.
    Why:
      Lab output format expects the first scope creation to be visible.
    Rationale:
      symbol_table constructor creates the global scope; the log line documents
      that creation.
    Result:
      Log begins with "New ScopeTable with ID 1 created".

22299480_22101811.y, lines 970-972:
    Change:
      Total line and error summaries added.
    Why:
      Final output should show total processed lines and total errors.
    Rationale:
      Use shared lines and error_count globals.
    Result:
      Both successful and error-containing parses end with a summary.

22299480_22101811.y, lines 974-976:
    Change:
      Added symbol table deletion and error file close.
    Why:
      Dynamically allocated scopes/symbols and open files should be cleaned up.
    Rationale:
      Delete symbol_table after parsing and close both output streams.
    Result:
      Memory and file handles are released cleanly.
*/

/*
===============================================================================
SECTION 12: LEXER CHANGES
===============================================================================

22299480_22101811.l, line 2:
    Change:
      Added COMMENT start condition.
    Why:
      Multi-line comments need a separate lexer state until closing "*/".
    Rationale:
      Flex start conditions are cleaner than trying to match multi-line comments
      with one fragile pattern.
    Result:
      Comment bodies are ignored safely while line numbers are still counted.

22299480_22101811.l, lines 34-38:
    Change:
      Added single-line and multi-line comment skipping.
    Why:
      Comments should not generate parser tokens.
    Rationale:
      Ignore "//..." directly; enter COMMENT state for "/* ... */"; increment
      lines on newlines inside comments.
    Result:
      Source comments do not break parsing and error line numbers stay accurate.

22299480_22101811.l, line 109:
    Change:
      Added catch-all rule for unknown characters.
    Why:
      The lexer should not crash or return accidental tokens for unsupported
      characters.
    Rationale:
      Ignore unmatched characters as a fallback.
    Result:
      Unexpected characters are skipped instead of stopping tokenization.
*/

/*
===============================================================================
SECTION 13: symbol_info.h CHANGES
===============================================================================

symbol_info.h, lines 1-2 and 205:
    Change:
      Added include guard.
    Why:
      Header files can be included more than once through parser/lexer/table
      dependencies.
    Rationale:
      Standard C++ include guards prevent duplicate class definitions.
    Result:
      The project compiles more reliably.

symbol_info.h, lines 12-16:
    Change:
      Added semantic fields: category, data_type, array_size, parameter_types,
      and parameter_names.
    Why:
      A symbol must store whether it is a variable, array, or function, plus its
      type metadata.
    Rationale:
      Keep all semantic information attached to the symbol itself.
    Result:
      Parser checks can retrieve type/category/parameter information from the
      symbol table.

symbol_info.h, lines 19-35:
    Change:
      Added default constructor and initialized semantic fields.
    Why:
      Temporary symbols and helper lookups need safe default values.
    Rationale:
      Empty strings and zero array size avoid undefined values.
    Result:
      Lookup helper objects can be created safely.

symbol_info.h, lines 42-80, 87-109, 117-155, and 162-171:
    Change:
      Added Lab 3 helper names like getname, getidtype, getvartype,
      getreturntype, getparamtype, setvartype, setreturntype, and set_parameters.
    Why:
      The current parser uses these shorter method names.
    Rationale:
      Keep compatibility with both Lab 2-style names and the current grammar.
    Result:
      Parser, symbol table, and scope table can share one symbol_info class.

symbol_info.h, lines 179-198:
    Change:
      Added getparamcount and getparamdetails.
    Why:
      Symbol-table printing needs function parameter count and readable details.
    Rationale:
      Build the formatted parameter string from stored type/name vectors.
    Result:
      Function symbols print return type, number of parameters, and parameter
      details.
*/

/*
===============================================================================
SECTION 14: scope_table.h CHANGES
===============================================================================

scope_table.h, lines 1-2 and 160:
    Change:
      Added include guard.
    Why:
      Avoid duplicate class definition problems.
    Result:
      Safer repeated header inclusion.

scope_table.h, lines 43-62:
    Change:
      Added null-safe lookup and string-name lookup overload.
    Why:
      Parser code often has only an identifier name string.
    Rationale:
      Build a temporary symbol_info for string lookup.
    Result:
      st->lookup("x") can be used directly.

scope_table.h, lines 64-72:
    Change:
      insert_in_scope now rejects null and duplicate symbols.
    Why:
      Duplicate declaration checking depends on insertion failure.
    Rationale:
      Current-scope lookup before insertion enforces same-scope uniqueness.
    Result:
      Parser can detect multiple declarations from a false return value.

scope_table.h, lines 74-95:
    Change:
      delete_from_scope now deletes symbol memory and has a string overload.
    Why:
      Removed symbols should not leak memory.
    Rationale:
      Delete the owned symbol pointer before erasing list entry.
    Result:
      Scope cleanup is more complete.

scope_table.h, lines 97-146:
    Change:
      Symbol-table printing now includes semantic details for variables, arrays,
      and functions.
    Why:
      Lab 3 output requires more than "< name : token >".
    Rationale:
      Print category-specific metadata from symbol_info.
    Result:
      Logs show variable type, array type/size, and function return/parameter
      details.
*/

/*
===============================================================================
SECTION 15: symbol_table.h CHANGES
===============================================================================

symbol_table.h, lines 1-2 and 117:
    Change:
      Added include guard.
    Why:
      Prevent duplicate definitions from repeated includes.
    Result:
      Cleaner compilation.

symbol_table.h, lines 39-43:
    Change:
      Added enter_scope(outlog).
    Why:
      Grammar actions need to both create scopes and log creation.
    Rationale:
      Wrap normal enter_scope with formatted output.
    Result:
      Parser code stays shorter and logs scope creation consistently.

symbol_table.h, lines 54-61:
    Change:
      Added exit_scope(outlog).
    Why:
      Grammar actions need to log which scope was removed.
    Rationale:
      Capture current scope id before deleting it.
    Result:
      Logs include "Scopetable with ID ... removed".

symbol_table.h, lines 69-73:
    Change:
      Added remove wrapper.
    Why:
      Exposes current-scope deletion through symbol_table.
    Result:
      Parser or future semantic logic can remove symbols without accessing
      scope_table directly.

symbol_table.h, lines 87-91:
    Change:
      Added lookup by string.
    Why:
      Semantic checks usually start from an ID name.
    Rationale:
      Build a temporary symbol_info and reuse the existing lookup flow.
    Result:
      Parser rules can call st->lookup($1->getname()).

symbol_table.h, lines 101-114:
    Change:
      print_all_scopes now adds boundary lines and prints parent scopes.
    Why:
      Lab output needs a complete visible symbol-table snapshot.
    Rationale:
      Walk from current scope to parents and format with separators.
    Result:
      The log shows all currently active scopes when requested.
*/

/*
===============================================================================
SECTION 16: OVERALL EFFECT
===============================================================================

What changed:
    The project moved from mostly syntax logging to actual semantic analysis.

Main semantic abilities now present:
    1. Insert functions, variables, arrays, and parameters into scoped symbol
       tables.
    2. Detect duplicate variable/function/parameter declarations.
    3. Detect undeclared variables and functions.
    4. Detect scalar-vs-array misuse.
    5. Detect non-integer array indexes.
    6. Propagate int/float/void/error types through expressions.
    7. Detect operation on void.
    8. Detect float-to-int assignment warning.
    9. Detect modulus type errors, modulus by zero, and division by zero.
   10. Validate function argument count and argument types.
   11. Write separate detailed log and error files.

What happened by doing this:
    The parser can now behave like a semantic analyzer. It still logs grammar
    reductions, but it also builds meaningful symbol-table entries and reports
    semantic mistakes with line numbers.
*/
