#include "parser.hpp"
#include <cstring>
using namespace output;

//usable registers nums (R_low,...,R_high)
#define LOW_REG 8
#define HIGH_REG 26

//saves the framePointer
void saveFramePointer(){
	CodeBuffer::instance().emit("move $fp,$sp");
	CodeBuffer::instance().emit("subu $fp,$fp,4");
}

//init all the registers that we can use into the stack
void registersInit(stack<Register>& registerStack){
	for(int i=LOW_REG;i<HIGH_REG;i++){
		registerStack.push(Register(string("$" + to_string(i)), i));
	}
}

void saveUsedRegs(stack<Register> unUsedRegs){
	bool used[HIGH_REG] ;
	for(int i=LOW_REG;i<HIGH_REG;i++){	//marks all as used for start
		used[i] = true;
	}
	while(!unUsedRegs.empty()){		//while there are unused regs do:
		Register reg = unUsedRegs.top();
		used[reg.regNum] = false; //mark as unused
		unUsedRegs.pop();
	}
	for(int i=LOW_REG;i<HIGH_REG;i++){
		if(used[i]){	//for each used reg
			CodeBuffer::instance().emit("subu $sp,$sp,4");
			CodeBuffer::instance().emit("sw $" + to_string(i) + ",0($sp)");
		}
	}
	CodeBuffer::instance().emit("subu $sp,$sp,4");
	CodeBuffer::instance().emit("sw $fp,0($sp)");	//save the FramePointer
	CodeBuffer::instance().emit("subu $sp,$sp,4");
	CodeBuffer::instance().emit("sw $ra,0($sp)"); //save the return address in stack
}

//the opposite of saveUsedRegs
void restoreUsedRegs(stack<Register> unUsedRegs){
	CodeBuffer::instance().emit("lw $ra,0($sp)"); //restore the return address
	CodeBuffer::instance().emit("addu $sp,$sp,4");
	CodeBuffer::instance().emit("lw $fp,0($sp)");	//restore the return FramePointer
	CodeBuffer::instance().emit("addu $sp,$sp,4");
	bool used[HIGH_REG] ;
	for(int i=LOW_REG;i<HIGH_REG;i++){
		used[i] = true;
	}
	while(!unUsedRegs.empty()){	
		Register reg = unUsedRegs.top();
		used[reg.regNum] = false; //mark as unused
		unUsedRegs.pop();
	}
	for(int i=HIGH_REG-1; i>=LOW_REG; i++){ //loading from the opposite direction now
		if(used[i]){
			CodeBuffer::instance().emit("lw $" + to_string(i) + ",0($sp)"); //restore reg from stack
			CodeBuffer::instance().emit("addu $sp,$sp,4");
		}
	}
}

void StacksInit(stack<SymbolTable>& StackTable, stack<int>& OffsetStack) {
	SymbolTable global;
	StackTable.push(global);
	OffsetStack.push(0);
	
	std::vector<string> PrintTypes;
	std::vector<string> PrintITypes;

	PrintTypes.push_back("STRING");
	PrintITypes.push_back("INT");

	string s1=(makeFunctionType("VOID", PrintTypes));
	string s2=(makeFunctionType("VOID", PrintITypes));
	string ret1= "VOID";

	Symbol sym1("print", s1, OffsetStack.top(), PrintTypes, ret1);		//maybe need to send a & ?
	Symbol sym2("printi", s2, OffsetStack.top(), PrintITypes, ret1);
	
	CodeBuffer::instance().emit("print:");
  	CodeBuffer::instance().emit("lw $a0,0($sp)\nli $v0,4\nsyscall\njr $ra");
	StackTable.top().push_back(sym1);
	CodeBuffer::instance().emit("printi:");
    CodeBuffer::instance().emit("lw $a0,0($sp)\nli $v0,1\nsyscall\njr $ra");
	StackTable.top().push_back(sym2);

	//Div by Zero new label for error!
	string zeroExc = "divByZero";
	CodeBuffer::instance().emitData(zeroExc + ": " + ".asciiz \"Error division by zero\\n\"");
	CodeBuffer::instance().emit("divException:");
	CodeBuffer::instance().emit("la $a0,divByZero\nli $v0,4\nsyscall\n");
	CodeBuffer::instance().emit("li $v0,10\nsyscall\n"); //terminate the prog
	string indexExc = "outOfBounds";
	CodeBuffer::instance().emitData(indexExc + ": " + ".asciiz \"Error index out of bounds\\n\"");
	CodeBuffer::instance().emit("indexException:");
	CodeBuffer::instance().emit("la $a0,outOfBounds\nli $v0,4\nsyscall\n");
	CodeBuffer::instance().emit("li $v0,10\nsyscall\n"); //terminate the prog

}


SymbolTable::iterator getItToId(SymbolTable& scope, string id) {
  for (SymbolTable::iterator it = scope.begin(); it != scope.end(); it++) {
	if (it->name == id) 
		return it;
  }
  return scope.end();
}


bool checkSymDec(stack<SymbolTable>& StackTable, Id* id) {
	stack<SymbolTable> stackCopy = StackTable;
	SymbolTable currentScope;
	string idName= id->name;
	while ( stackCopy.size() ) {
		currentScope = stackCopy.top();
		if (getItToId(currentScope, idName) != currentScope.end()) 
			return true;
		stackCopy.pop();
	}
	return false;
}


void addNewScope(stack<SymbolTable>& StackTable, stack<int>& OffsetStack) {
	SymbolTable newScope;
	OffsetStack.push(OffsetStack.top());
	StackTable.push(newScope);
}

void scopePrint(SymbolTable& scope){
  endScope();
  for (SymbolTable::iterator it = scope.begin(); it != scope.end(); it++)
    	printID(it->name, it->offset, it->type);
}

void finishScope(stack<SymbolTable>& StackTable, stack<int>& OffsetStack){
	scopePrint(TableStack.top());
    OffsetStack.pop();
    TableStack.pop();
}

int getArraySize(string type){
	int pos1=type.find("[");
	int pos2=type.find("]");
	if(pos1 == -1 || pos2 == -1){
		return 1;					//not an array type = offset will be 1
	}
	const char* temp=type.substr(pos1+1,pos2-pos1-1).c_str();
	return atoi(temp);
}

//need TODO
void addFuncSymScope(stack<SymbolTable>& StackTable, stack<int>& OffsetStack,
                       Formals* formals, int lineno) {
  int offset = 0;
  for (vector<FormalDecl*>::reverse_iterator it = formals->formals.rbegin();
       it != formals->formals.rend(); it++) {

		Id id( (*it)->id );
		if (checkSymDec(StackTable, &id)) {
			errorDef(lineno, id.name);
			exit(0);
		}
		offset-=getArraySize((*it)->type);
		Symbol sym( (*it)->id, (*it)->type, offset);	
		StackTable.top().push_back(sym);
  }
}

bool isArray(string name){
	int pos1=name.find("[");
	return (pos1 != -1);
}


Type getTypeById(stack<SymbolTable>& StackTable, Id* id) {
  
	stack<SymbolTable> stackCopy = StackTable;
	string name = id->name;
	SymbolTable::iterator it;
	while ( stackCopy.size() ) {
		it = getItToId(stackCopy.top(), name);
		if (it != stackCopy.top().end()) 
			return it->type;
		stackCopy.pop();
	}

	return Type();
}

void addFuncToScope(stack<SymbolTable>& StackTable, stack<int>& OffsetStack,
                   RetType* ret, Id* id, Formals* formals, int lineno) {

	if (checkSymDec(StackTable, id)) {  //func is already declared
		errorDef(lineno, id->name);
		exit(0);
	}
	std::vector<string> types;
	for (vector<FormalDecl*>::reverse_iterator it = formals->formals.rbegin();
	   it != formals->formals.rend(); it++) {
			types.push_back((*it)->type);
	}
	string funcType=makeFunctionType(ret->type,types);
	Symbol sym(id->name, funcType, OffsetStack.top(),types, ret->type);
	StackTable.top().push_back(sym);
	CodeBuffer::instance().emit(id->name + ":"); //add a new func label
}

Symbol getSymbolById(stack<SymbolTable>& StackTable, string id) {

	stack<SymbolTable> stackCopy = StackTable;
	SymbolTable::iterator it;
	while ( stackCopy.size() ) {
		it = getItToId(stackCopy.top(), id);
		if (it != stackCopy.top().end()) 
			return *it;
		stackCopy.pop();
	}
	return Symbol();
}

void newVarScope(stack<SymbolTable>& StackTable, stack<int>& OffsetStack,
                        string type, Id* id, int lineno,int currentOff) {
 
	if (checkSymDec(StackTable, id)) {
		errorDef(lineno, id->name);
		exit(0);
	}
	int newOffset;
	Symbol sym(id->name, type, OffsetStack.top());    
	StackTable.top().push_back(sym);
	newOffset = OffsetStack.top() + currentOff;
	OffsetStack.pop();
	OffsetStack.push(newOffset);
}

//TODO
bool checkMatchingTypes(vector<string>& types1,vector<string>& types2){
	 if( types1.size() != types2.size() ){
		return false;
	 }
	for(int i=0; i < types1.size(); i++){
		if(types1[i] != types2[i]){
			if(types1[i] == "INT" && types2[i] == "BYTE")
				continue;
			//array case
			int pos1 = types1[i].find("INT");
			int pos2=types2[i].find("BYTE");
			if(pos1 == -1 || pos2 == -1){
				return false;
			}
			pos1=types1[i].find("[");
			pos2=types2[i].find("[");
			if(pos1 == -1 || pos2 == -1){
				return false;
			}
			string temp1=types1[i].substr(pos1);
			string temp2=types2[i].substr(pos2);
			if(temp1 != temp2){
				return false;
			}
		}
	}
	return true;
}

void checkMain(){
	CodeBuffer::instance().printDataBuffer();  //prints data Buffer
	//cout<<".globl main"<<endl; ????????????????????????????????????????????
	CodeBuffer::instance().printCodeBuffer(); //prints code Buffer

	Symbol mainSym = getSymbolById(TableStack,"main");
	if(mainSym.ret !="VOID" ||mainSym.name!="main" || !(mainSym.args.empty())){
		errorMainMissing();
		exit(0);
	}
}


Funcs::Funcs() : funcsList( vector<Func*>() ){}  // for epsilon rule

Funcs::Funcs(Funcs* list, Func* func) : funcsList( vector<Func*>(list->funcsList) ){
	this->funcsList.push_back(func);
}

Func::Func(RetType* ret, Id* id, Formals* formals, Statements* statements,stack<int>& OffsetStack) :
id(id->name), funcRet(ret->type), formals(formals) {
	int offset = OffsetStack.top();
	if(offset > 0){
		CodeBuffer::instance().emit("addu $sp,$sp," + to_string(offset*4)); //saving space for func args in stack
	}
	CodeBuffer::instance().emit("jr $ra"); //jump into return address
}


RetType::RetType(Void* vNode) : type("VOID"){}


RetType::RetType(Type* t) : type(t->type){}


Formals::Formals(FormalsList* formalsList) : formals(formalsList->formalsVec){}


FormalsList::FormalsList(FormalDecl* formalDecl) : formalsVec(vector<FormalDecl*>()){
	this->formalsVec.push_back(formalDecl);
}

FormalsList::FormalsList(FormalsList* formalsList, FormalDecl* formalsDecl) :
formalsVec(vector<FormalDecl*>(formalsList->formalsVec)) {
  
	this->formalsVec.push_back(formalsDecl);
}


FormalDecl::FormalDecl(Type* t, Id* id) : type(t->type), id(id->name){}

FormalDecl::FormalDecl(Type* t, Id* id,Num* num) {
	if(num->value <1 || num->value >255){
		errorInvalidArraySize(yylineno,id->name);
		exit(0);
	}
	this->type = makeArrayType(t->type,num->value);
	this->id = id->name;
}

FormalDecl::FormalDecl(Type* t, Id* id,Num* num, b* byte ){
	if(num->value == 0){
		errorInvalidArraySize(yylineno,id->name);
		exit(0);
	}
	checkByteToLarge(num->value);
	this->type = makeArrayType(t->type,num->value);
	this->id = id->name;
}

Statements::Statements(Statement* statement) {
	this->bp.quad = CodeBuffer::instance().genLabel(); 
	CodeBuffer::instance().bpatch(statement->bp.nextList,this->bp.quad);
	this->bp.breakList = statement->bp.breakList;
}

Statements::Statements(Statements* statements, Statement* statement) {
	this->bp.quad = CodeBuffer::instance().genLabel();
	CodeBuffer::instance().bpatch(statement->bp.nextList,this->bp.quad);
	this->bp.breakList = CodeBuffer::instance().merge(statements->bp.breakList,statement->bp.breakList);

}

Statement::Statement(Statements* statements) {
	this->bp.nextList = statements->bp.nextList;
	this->bp.trueList = statements->bp.trueList;
	this->bp.falseList = statements->bp.falseList;
	this->bp.breakList = statements->bp.breakList;
}

Statement::Statement(Exp* exp) {}

Statement::Statement(Call* call) {}

Statement::Statement(Type* type, Id* id) {

	if (checkSymDec(TableStack, id)) {			//maybe export into outer func
		errorDef(yylineno, id->name);
		exit(0);
	}
}

//array
Statement::Statement(Type* type, Id* id, Num* num){
	if(num->value <1 || num->value >255){
		errorInvalidArraySize(yylineno,id->name);
		exit(0);
	}
	if (checkSymDec(TableStack, id)) {			//maybe export into outer func
		errorDef(yylineno, id->name);
		exit(0);
	}
}

Statement::Statement(Type* type, Id* id, Num* num,b* b1){

	if(num->value == 0){
		errorInvalidArraySize(yylineno,id->name);
		exit(0);
	}
	checkByteToLarge(num->value);

	if (checkSymDec(TableStack, id)) {			//maybe export into outer func
		errorDef(yylineno, id->name);
		exit(0);
	}
}

void checkByteToLarge(int numVal){
	if(numVal <1 || numVal >255){
		stringstream s;
		s << numVal;
		errorByteTooLarge(yylineno,string(s.str()));
		exit(0);
	}
}

//for array var
Statement::Statement(Id* id, Exp* exp) {

	if (!checkSymDec(TableStack, id)) {			//check a[0] if a func given a[5]
		errorUndef(yylineno, id->name);
		exit(0);
	}

	Symbol sym =getSymbolById(TableStack,id->name);
	if(sym.isFunc){
		errorUndef(yylineno, id->name);
		exit(0);
	}
	string idType = getTypeById(TableStack, id).type;	
	if ( idType != exp->type ) {
		if ( idType == "INT" && exp->type == "BYTE") {
		} 
		else {
			errorMismatch(yylineno);
			exit(0);
		}
	}
}

//assign exp2 into id[exp1]
Statement::Statement(Id* id, Exp* exp1,Exp* exp2){
	if (!checkSymDec(TableStack, id)) {
		errorUndef(yylineno, id->name);
		exit(0);
	}
	string idType = getTypeById(TableStack, id).type;	//is array!
	size_t pos=idType.find("[");
	if(pos == -1){
		errorMismatch(yylineno);
		exit(0);
	}
	string idTemp= idType.substr(0,pos);
	if ( idTemp != exp2->type ) {
	
		if ( idTemp == "INT" && exp2->type == "BYTE") {
		} 
		else {
			errorMismatch(yylineno);
			exit(0);
		}
	}
}


Statement::Statement(Exp* exp, Statement* statement) {}

Statement::Statement(Type* type, Id* id, Exp* exp) {
	
	if (checkSymDec(TableStack, id)) {
		errorDef(yylineno, id->name);
		exit(0);
	}
	if (type->type != exp->type) {
		if (type->type == "INT" && exp->type == "BYTE") {
		} 
		else {
			errorMismatch(yylineno);
			exit(0);
		}
	}
}


Statement::Statement(Exp* exp, Statement* ifStatment,
                     Statement* elseStatement) {}


ExpList::ExpList(Exp* exp) {

	this->types = vector<string>();
  	this->types.push_back(exp->type);
}


ExpList::ExpList(Exp* exp, ExpList* expList){
  
	this->types = vector<string>();
	this->types.push_back(exp->type);
	for(int i=0; i<expList->types.size(); i++)
		this->types.push_back(expList->types[i]);
}


Call::Call(Id* id) {
	stack<Register> regs = registerStack;
  	saveUsedRegs(regs);

	if (!checkSymDec(TableStack, id)) {
		errorUndefFunc(yylineno, id->name);
		exit(0);
	}
	Symbol sym = getSymbolById(TableStack, id->name);
	if (!(sym.isFunc)) {
		errorUndefFunc(yylineno, id->name);
		exit(0);
	} 
	else if (!sym.args.empty()) { //func without parameters
		errorPrototypeMismatch(yylineno, id->name, sym.args);
		exit(0);
	}
	this->id = id->name;
	int funArgs = sym.args.size(); //num of args of the func called
	CodeBuffer::instance().emit("jal " + id->name); //jump to func + stores ra
  	CodeBuffer::instance().emit("addu $sp,$sp,"+to_string(funArgs*4)); //saves space for all the fun arguments???
  	restoreUsedRegs(regs);
}


Call::Call(Id* id, ExpList* expList) {
	stack<Register> regs = registerStack;
  	saveUsedRegs(regs);
	int funArgs;

	if (!checkSymDec(TableStack, id)) {
		errorUndefFunc(yylineno, id->name);
		exit(0);
	}else{
		Symbol sym = getSymbolById(TableStack, id->name);
		funArgs = sym.args.size(); //num of args of the func called
		if (!(sym.isFunc)) {								//make outer func
			errorUndefFunc(yylineno, id->name);
			exit(0);
		} 
		if (!checkMatchingTypes(sym.args,expList->types)) {
			errorPrototypeMismatch(yylineno, id->name, sym.args);
			exit(0);
		}
	}
	this->id = id->name;
	for(vector<Register>::reverse_iterator i=expList->registers.rbegin(); i!=expList->registers.rend(); i++){
		CodeBuffer::instance().emit("subu $sp,$sp,4");
		CodeBuffer::instance().emit("sw " + (*i).regName + ",0($sp)"); //push registers to the stack.
		registerStack.push((*i)); //mark reg as unUsed!
  	}
	CodeBuffer::instance().emit("jal " + id->name);
  	CodeBuffer::instance().emit("addu $sp,$sp," + to_string(funArgs*4)); //saves space for all the fun arguments
  	restoreUsedRegs(regs);	//update the regStack accord.
}

String::String(const char* yytext) {
  label = "msg" + to_string(++stringNum); //updating the stringNum val to make a DIFFERENT label for diff msgs.
  CodeBuffer::instance().emitData(label + ": " + ".asciiz " + string(yytext));
  reg = registerStack.top();
  registerStack.pop();
  CodeBuffer::instance().emit("la " + reg.regName + "," + label);
}

///---------------------------------------add reg val to exp funcs
Exp::Exp(): type("") {}


Exp::Exp(Id* id,Exp* exp){
	if (!checkSymDec(TableStack, id)) {
		errorUndef(yylineno, id->name);
		exit(0);
	}
	string t=getTypeById(TableStack,id).type;
	int pos=t.find("[");
	if(pos == -1){				//not an array
		errorMismatch(yylineno);													//TODO
		exit(0);
	}
	this->type=t.substr(0,pos);
}


Exp::Exp(String* exp,bool isAprintFunc,bool isAprintiFunc) {
	
	if (!isAprintFunc && !isAprintiFunc) {
		errorMismatch(yylineno);
		exit(0);
	}
	this->type = "STRING";
}


Exp::Exp(Num* exp) : type("INT"){}

Exp::Exp(Exp* exp) : type(exp->type){}

Exp::Exp(Id* id) {
  
	if (!checkSymDec(TableStack, id)) {
		errorUndef(yylineno, id->name);
		exit(0);
	}
	this->type = getTypeById(TableStack, id).type;
}


Exp::Exp(Call* call) {
	
	this->type = getSymbolById(TableStack, call->id).ret;
}


Exp::Exp(Num* num, b* byte) {
	
	this->type = "BYTE";
	int numVal = num->value;
	
	if(numVal>255){
		stringstream s;
		s << numVal;
		errorByteTooLarge(yylineno,string(s.str()));
		exit(0);
	}
}

Exp::Exp(string flag) {
	if(flag == "TRUE" || flag == "FALSE"){
		this->type="BOOL";
	}
}

Exp::Exp(string operand, Exp* exp) {		//not
	if(operand == "NOT"){
		if ((exp->type != "BOOL")) {
			errorMismatch(yylineno);
			exit(0);
		}
		this->type="BOOL";
	}
}

//-----------------------------------------------------------------to change a bit
Exp::Exp(Exp* exp1, Exp* exp2, string opType,char* opVal) : type("BOOL"){
	if(opType == "OR" || opType == "AND"){
		if ((exp1->type != "BOOL") || (exp2->type != "BOOL")) {
			errorMismatch(yylineno);
			exit(0);
		}
	}else if(opType == "RELOP"){//--------
		if ((exp1->type != "INT" && exp1->type != "BYTE") ||
	 		 (exp2->type != "INT" && exp2->type != "BYTE")) {
			errorMismatch(yylineno);
			exit(0);
		}
	}else if(opType == "BINOP"){//--------
		if ((exp1->type != "INT" && exp1->type != "BYTE") ||
	 		 (exp2->type != "INT" && exp2->type != "BYTE")) {
			errorMismatch(yylineno);
			exit(0);
		}
		if (exp1->type  == "INT"  || exp2->type =="INT" ) {
			this->type = "INT";
		} 
		else{
			this->type = "BYTE";
		}
	}
}



