#ifndef H_PARSER
#define H_PARSER


#include <sstream>
#include <iterator>
#include <string>
#include <vector>
#include <stack>
#include <stdlib.h>
#include <iostream>
#include "output.hpp"
#include "bp.hpp"


using namespace std;
static int stringNum = 0;
class Symbol;
typedef vector<Symbol> SymbolTable;
extern stack<SymbolTable> TableStack; 
extern stack<int> OffsetStack;
class Register;
extern stack<Register> registerStack; //a stack for saving all the *Unused* Available registers
//extern bool isArgument;


extern int yylineno;		//extern var from lexer - keeps the current line number

#define YYSTYPE Node*

class Register {
	public:
	string regName;
	int regNum;

	Register() : regName("$0"), regNum(0) {}
	Register(string name, int num) : regName(name) , regNum(num) {}

	Register(const Register& reg){
    this->regName = reg.regName;
    this->regNum = reg.regNum;
  }

	Register& operator=(const Register& reg){
    this->regName = reg.regName;
    this->regNum = reg.regNum;
    return *this;
  }

};

class BackPatchLists{
	public:
	string quad;
	vector<int> trueList;
	vector<int> falseList;
	vector<int> nextList;  
	vector<int> breakList;

	BackPatchLists(){}
};
//----------------------------------------------------------------------------------------------

class Symbol{
    public:
    string name;
    string type;											
    int offset;
    bool isFunc;
    vector<string> args;
    string ret;											
    
	Symbol(): name(""), type(""), offset(0), isFunc(false){}
	Symbol(const Symbol& sym) : name(sym.name), type(sym.type), offset(sym.offset),
		isFunc(sym.isFunc), ret(sym.ret), args(sym.args) {}
    Symbol(string name, string type ,int offset) : name(name), type(type),
		offset(offset), isFunc(false) {}
	Symbol(string name, string type ,int offset,vector<string>& args,string ret ) : 		
		name(name), type(type), offset(offset),args(args),ret(ret), isFunc(true) {}
};

class Node {
	public:
	int lineNum;

	Node(): lineNum(yylineno){}
	virtual ~Node() {}
};

class Int : public Node {
	public:
	string type;						
  
	Int() : type("INT") {}
};

class Byte : public Node {
	public:
	string type;						

	Byte() : type("BYTE") {}
};

class Bool : public Node {
	public:
	string type;					

	Bool() : type("BOOL") {}
	
};

class Void : public Node {
	public:
	string type;

	Void() : type("VOID"){}
};

class Type : public Node {
	public:
	string type;													
	
	Type(): type(""){}
	Type(string t): type(t){}			
	Type(const Type& Ctype) : type(Ctype.type){}		//Copy cons

};

class String : public Node {
    public:
    string type;								
    string value;
	Register reg;			//temp reg to hold the string
	string label;			//the label that will hold the string
	
    String(const char* yytext) ;
};

class Return : public Node{};

class Relop : public Node{
	public:
		string op;
		Relop(string yytext) : op(yytext) {}
};

class Num : public Node {
    public:
    string type;								
    int value;
	Register reg;	//temp reg to hold the num
	
    Num(char* yytext) : type("INT"), value(atoi(yytext)) {
		reg = registerStack.top();
		registerStack.pop();
		CodeBuffer::instance().emit("li " + reg.regName + "," + string(yytext));	//saving num in a register
	}
};

class Exp;
class ExpList : public Node {
	public:
	vector<string> types;	//vector of type classes
	vector<Register> registers;		//vector of registers that hold every exp in the expList	
	vector<string> ids;			

	ExpList() : types( vector<string>() ), registers(vector<Register>()) , ids(vector<string>()) {}
	ExpList(Exp* exp);
	ExpList(Exp* exp, ExpList* expList);
};

class Id : public Node {
    public:
    string name;
	Register reg;			//temp reg to hold the id
	
    Id(char* yytext) : name(string(yytext)) {}
	Id(string yytext) : name(yytext) {}
    virtual ~Id() {}
	
};

class Call : public Node {
	public:
	string id;

	Call(){}
	Call(Id* id);
	Call(Id* id, ExpList* expList);
};

class b : public Node {};

class Exp : public Node {
	public:
	string type;
	Register reg;		//temp reg to hold the Exp
	BackPatchLists bp;			
	string arrayID; //for array name
	//bool needEval;		

	Exp();
	Exp(String* s,bool isAPrintFunc,bool isAPrintiFunc);
	Exp(Exp* exp);
	Exp(Id* id,Exp* exp);											
	Exp(Id* id);
	Exp(Call* call);
	Exp(Num* num);
	Exp(Num* num, b* byte);
	Exp(string flag);
	Exp(string operand, Exp* exp);
	Exp(Exp* exp1,Exp* exp2,Relop* op);
	Exp(Exp* exp1,Exp* exp2,string opType,string opVal);
};

class Statements;
class Statement : public Node {
	public:
	BackPatchLists bp;
	
	Statement(){}
	Statement(Call* call);
	Statement(Statements* statements);
	Statement(Type* t, Id* id);
	Statement(Type* t, Id* id, Exp* exp);
	Statement(Type* t, Id* id, Num* num);					
	Statement(Type* t, Id* id, Num* num, b* byte); 
	Statement(Id* id, Exp* exp);
	Statement(Id* id, Exp* exp1,Exp* exp2);		
	Statement(Exp* exp, Statement* statement,bool isWhile);
	Statement(Exp* exp, Statement* statement1, Statement* statement2, Statement* statement3);	//for if + else func
	//new cons:
	Statement(Return* ret);
  	Statement(Return* ret,Exp* expression);
};

class Statements : public Node {
	public:
	BackPatchLists bp;

	Statements(){}
	Statements(Statement* statement);
	Statements(Statements* statements, Statement* statement); //recursion

};

class FormalDecl : public Node {
	public:
	string type;											
	string id;

	FormalDecl(){}
	FormalDecl(Type* t, Id* id);
	FormalDecl(Type* t, Id* id,Num* num);						//cons for array : bool a[5]; 5 is num 
	FormalDecl(Type* t, Id* id,Num* num, b* byte );				//cons for array : bool a[5]; 5 is numB
};

class FormalsList : public Node {
	public:
	vector<FormalDecl*> formalsVec;
	
	FormalsList(){}
	FormalsList(FormalsList* formalsList, FormalDecl* formalsDecl); //recursion
	FormalsList(FormalDecl* formalDecl);
};

class Formals : public Node {
	public:
	vector<FormalDecl*> formals;

	Formals(){}
	Formals(FormalsList* formalsList);
};

class RetType : public Node {
	public:
	string type;							

	RetType(){}
	RetType(Type* t);
	RetType(Void* vNode);
};

class Func : public Node {
	public:
	string id;
	string funcRet;						
	Formals* formals;
	
	Func(){}
	Func(RetType* ret, Id* id, Formals* formals, Statements* statements);
};

class Funcs : public Node {
	public:
	vector<Func*> funcsList;
	
	Funcs();
	Funcs(Funcs* list, Func* func);  //recursion
	virtual ~Funcs() {
	}
};

//Auxiliry functions

void checkMain();
void saveFramePointer();
void checkByteToLarge(int numVal);
void StacksInit(stack<SymbolTable>& StackTable, stack<int>& OffsetStack) ;
void foldLocals(stack<SymbolTable>& StackTable, stack<int>& OffsetStack);
void RegistersInit(stack<Register>& registerStack);
void addNewScope(stack<SymbolTable>& StackTable, stack<int>& OffsetStack) ;
void scopePrint(SymbolTable& scope);
void finishScope(stack<SymbolTable>& StackTable, stack<int>& OffsetStack,bool progEnd);
void addFuncSymScope(stack<SymbolTable>& StackTable, stack<int>& OffsetStack,Formals* formals, int lineno); 				   
void newVarScope(stack<SymbolTable>& StackTable, stack<int>& OffsetStack,string type, Id* id, int lineno,int currentOff) ;
void addFuncToScope(stack<SymbolTable>& StackTable, stack<int>& OffsetStack,RetType* ret, Id* id, Formals* formals, int lineno);

#endif
