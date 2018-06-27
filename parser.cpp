#include "parser.hpp"
#include <cstring>
using namespace output;

//usable registers nums (R_low,...,R_high)
#define LOW_REG 8
#define HIGH_REG 26



string toString ( int num ){
   std::ostringstream ss;
   ss << num;
   return ss.str();
}

//saves the framePointer
void saveFramePointer(){
	CodeBuffer::instance().emit("move $fp,$sp");
	CodeBuffer::instance().emit("subu $fp,$fp,4");
}

//init all the registers that we can use into the stack
void RegistersInit(stack<Register>& registerStack){
	for(int i=LOW_REG;i<HIGH_REG;i++){
		registerStack.push(Register(string("$" + toString(i)), i));
	}
}

void saveUsedRegs(stack<Register> unUsedRegs){
	//CodeBuffer::instance().emit("#**********SAVING REGS IN ******"); //--------------------------------------------------
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
			CodeBuffer::instance().emit("sw $" + toString(i) + ",0($sp)");
		}
	}
	CodeBuffer::instance().emit("subu $sp,$sp,4");
	CodeBuffer::instance().emit("sw $fp,0($sp)");	//save the FramePointer
	CodeBuffer::instance().emit("subu $sp,$sp,4");
	CodeBuffer::instance().emit("sw $ra,0($sp)"); //save the return address in stack
	//CodeBuffer::instance().emit("#**********SAVING REGS OUT ******"); //--------------------------------------------------
}

//the opposite of saveUsedRegs
void restoreUsedRegs(stack<Register> unUsedRegs){
	//CodeBuffer::instance().emit("#**********RESTORING REGS IN ******"); //--------------------------------------------------
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
		//std::cout << "reg num is " << reg.regNum << std::endl;
		used[reg.regNum] = false; //mark as unused
		unUsedRegs.pop();
	}
	for(int i=HIGH_REG-1; i>=LOW_REG; i--){ //loading from the opposite direction now
		if(used[i]){
			CodeBuffer::instance().emit("lw $" + toString(i) + ",0($sp)"); //restore reg from stack
			CodeBuffer::instance().emit("addu $sp,$sp,4");
		}
	}
		//CodeBuffer::instance().emit("#**********RESTORING REGS OUT ******"); //--------------------------------------------------

}

void StacksInit(stack<SymbolTable>& StackTable, stack<int>& OffsetStack) {
	SymbolTable global;
	StackTable.push(global);
	OffsetStack.push(0);
	
	vector<string> PrintTypes;
	vector<string> PrintITypes;

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

void finishScope(stack<SymbolTable>& StackTable, stack<int>& OffsetStack,bool progEnd){
	//scopePrint(TableStack.top());
	if(progEnd == false){
		stack<int> tempStack = OffsetStack;
		int currentOff = tempStack.top();
		tempStack.pop();
		int prevOff = tempStack.top();
		int localOffset = currentOff - prevOff;
		if(localOffset > 0){
			CodeBuffer::instance().emit("addu $sp,$sp," + toString(localOffset*4)); //deleting local var in sp on exit
		}
	}
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

//adding func arguments to the scope
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

//adding func symbol to scope
void addFuncToScope(stack<SymbolTable>& StackTable, stack<int>& OffsetStack,
                   RetType* ret, Id* id, Formals* formals, int lineno) {

	if (checkSymDec(StackTable, id)) {  //func is already declared
		errorDef(lineno, id->name);
		exit(0);
	}
	vector<string> types;
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

	Symbol mainSym = getSymbolById(TableStack,"main");
	if(mainSym.ret !="VOID" ||mainSym.name!="main" || !(mainSym.args.empty())){
		errorMainMissing();
		exit(0);
	}

	CodeBuffer::instance().printDataBuffer();  //prints data Buffer
	//cout<<".globl main"<<endl; // marks where the main starts..
	CodeBuffer::instance().printCodeBuffer(); //prints code Buffer

	
}

Funcs::Funcs() : funcsList( vector<Func*>() ){}  // for epsilon rule

Funcs::Funcs(Funcs* list, Func* func) : funcsList( vector<Func*>(list->funcsList) ){
	this->funcsList.push_back(func);
}

Func::Func(RetType* ret, Id* id, Formals* formals, Statements* statements) :
id(id->name), funcRet(ret->type), formals(formals) {
	stack<int> tempStack = OffsetStack;
	int currentOff = tempStack.top();
	tempStack.pop();
	int prevOff = tempStack.top();
	int localOffset = currentOff - prevOff;
	if(localOffset > 0){
		CodeBuffer::instance().emit("addu $sp,$sp," + toString(localOffset*4)); //deleting func args before return
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
	CodeBuffer::instance().bpatch(statement->bp.nextList,this->bp.quad); //pointing next to next line
	this->bp.breakList = statement->bp.breakList;	//pointing break to next line
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

Statement::Statement(Return* ret){
	stack<int> tempStack = OffsetStack;
	int currentOff = tempStack.top();
	tempStack.pop();
	int prevOff = tempStack.top();
	int localOffset = currentOff - prevOff;
	//CodeBuffer::instance().emit("##1###"); //saving space for func args in stack
	if(localOffset > 0){
		CodeBuffer::instance().emit("addu $sp,$sp," + toString(localOffset*4)); //saving space for func args in stack
	}
	//CodeBuffer::instance().emit("##2###"); //saving space for func args in stack
	CodeBuffer::instance().emit("jr $ra"); ///-----------------------------TODO
}

Statement::Statement(Return* ret,Exp* expression) { 
  this->bp.quad = CodeBuffer::instance().genLabel();
  	stack<int> tempStack = OffsetStack;
	int currentOff = tempStack.top();
	tempStack.pop();
	int prevOff = tempStack.top();
	int localOffset = currentOff - prevOff;
	if(localOffset > 0){
		CodeBuffer::instance().emit("addu $sp,$sp," + toString(localOffset*4)); //saving space for func args in stack
	}
  if(expression->type == "BOOL"){
    string trueLabel = CodeBuffer::instance().genLabel();
    CodeBuffer::instance().emit("li $v0,1");
    vector<int> nexts = CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j "));
    string falseLabel = CodeBuffer::instance().genLabel();
    CodeBuffer::instance().emit("li $v0,0");
    nexts = CodeBuffer::instance().merge(nexts,CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j ")));
    string next = CodeBuffer::instance().genLabel();
    CodeBuffer::instance().bpatch(nexts,next);
    CodeBuffer::instance().bpatch(expression->bp.trueList,trueLabel);
    CodeBuffer::instance().bpatch(expression->bp.falseList,falseLabel);
  }else{
    CodeBuffer::instance().emit("move $v0," + expression->reg.regName);
	registerStack.push(expression->reg);
  }
  CodeBuffer::instance().emit("jr $ra");
}

Statement::Statement(Call* call) {}

Statement::Statement(Type* type, Id* id) {

	if (checkSymDec(TableStack, id)) {			//maybe export into outer func
		errorDef(yylineno, id->name);
		exit(0);
	}
	//assignning place for local var in stack
  	Register reg = registerStack.top();
	registerStack.pop(); 
	CodeBuffer::instance().emit("li " +reg.regName +",0"); //default value to var!
	CodeBuffer::instance().emit("subu $sp,$sp,4");		//add place for local variable in the stack.
	CodeBuffer::instance().emit("sw "+reg.regName +",0($sp)");//push to the stack.
	//adding local variable to stack:
	registerStack.push(reg);
}

//array - int a[4]
Statement::Statement(Type* type, Id* id, Num* num){
	if(num->value <1 || num->value >255){
		errorInvalidArraySize(yylineno,id->name);
		exit(0);
	}
	if (checkSymDec(TableStack, id)) {			//maybe export into outer func
		errorDef(yylineno, id->name);
		exit(0);
	}
	//assignning place for local var in stack
  	Register reg = registerStack.top();
	registerStack.pop(); 
	CodeBuffer::instance().emit("li " +reg.regName +",0"); //default value to array!
	for(int i=0;i<num->value;i++){
		CodeBuffer::instance().emit("subu $sp,$sp,4");		//add place for local variable in the stack.
		CodeBuffer::instance().emit("sw "+reg.regName +",0($sp)");//push to the stack.
	}
	//adding local variable to stack:
	registerStack.push(num->reg);
	registerStack.push(reg);
}

//array - int a[4b]
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
	//assignning place for local var in stack
  	Register reg = registerStack.top();
	registerStack.pop(); 
	CodeBuffer::instance().emit("li " +reg.regName +",0"); //default value to array!
	for(int i=0;i<num->value;i++){
		CodeBuffer::instance().emit("subu $sp,$sp,4");		//add place for local variable in the stack.
		CodeBuffer::instance().emit("sw "+reg.regName +",0($sp)");//push to the stack.
	}
	//adding local variable to stack:
	registerStack.push(num->reg);
	registerStack.push(reg);
}

void checkByteToLarge(int numVal){
	if(numVal <1 || numVal >255){
		stringstream s;
		s << numVal;
		errorByteTooLarge(yylineno,string(s.str()));
		exit(0);
	}
}

// int getLocalOffset(int local){
// 	stack<int> tempStack = OffsetStack;
// 	CodeBuffer::instance().emit("LOCAL OFFSET IS "+ toString(local));
// 	if(local < 0){
// 		return local; //func argument
// 	}
// 	tempStack.pop();
// 	int prevOff = tempStack.top();
// 	CodeBuffer::instance().emit("PREV OFFSET IS "+ toString(prevOff));
// 	return (local - prevOff);
// }

//assign to var a=5; / a=b; //can be array to array as well
Statement::Statement(Id* id, Exp* exp) {

	if (!checkSymDec(TableStack, id)) {			
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
	int offset = sym.offset;//getLocalOffset(sym.offset);//----------------------------------
	//storing result in a temp register:

	if(idType == "BOOL"){
		exp->reg = registerStack.top();
		registerStack.pop();
		string trueLabel = CodeBuffer::instance().genLabel();
		CodeBuffer::instance().emit("li " +exp->reg.regName+",1");
		vector<int> nexts = CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j "));
		string falseLabel = CodeBuffer::instance().genLabel();
		CodeBuffer::instance().emit("li " +exp->reg.regName+",0");
		nexts = CodeBuffer::instance().merge(nexts,CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j ")));
		string next = CodeBuffer::instance().genLabel();
		CodeBuffer::instance().bpatch(nexts,next);
		CodeBuffer::instance().bpatch(exp->bp.trueList,trueLabel);
		CodeBuffer::instance().bpatch(exp->bp.falseList,falseLabel);
	}
	if(exp->arrayID == ""){	
		CodeBuffer::instance().emit("sw "+exp->reg.regName+","+toString((-offset)*4)+"($fp)");	//push to the stack.
	}else{ //both are arrays
		Symbol expSym = getSymbolById(TableStack, exp->arrayID);
			int expOffset = expSym.offset; //getLocalOffset(sym.offset);
			int size = getArraySize(expSym.type); //both are the same size
			for(int k=0;k<size; k++){
				CodeBuffer::instance().emit("lw " + exp->reg.regName + "," + toString(-expOffset*4)+ "($fp)");
				CodeBuffer::instance().emit("sw "+exp->reg.regName+","+toString((-offset)*4)+"($fp)"); //push registers to the stack.
				expOffset++;
				offset++;
	}
	//adding local variable to stack:
	}
	registerStack.push(exp->reg); //free the exp reg
}

//id[exp1] = exp2
Statement::Statement(Id* id, Exp* exp1,Exp* exp2){
	if (!checkSymDec(TableStack, id)) {
		errorUndef(yylineno, id->name);
		exit(0);
	}
	string idType = getTypeById(TableStack, id).type;	//is array!
	size_t pos1=idType.find("[");
	if(pos1 == -1){
		errorMismatch(yylineno);
		exit(0);
	}
	string idTemp= idType.substr(0,pos1);
	if ( idTemp != exp2->type ) {
	
		if ( idTemp == "INT" && exp2->type == "BYTE") {
		} 
		else {
			errorMismatch(yylineno);
			exit(0);
		}
	}
	Symbol arraySym = getSymbolById(TableStack,id->name);
	
	int pos2=idType.find("]");
	string temp = idType.substr(pos1+1,pos2-pos1-1);

	if(idTemp == "BOOL"){
		exp2->reg = registerStack.top();
		registerStack.pop();
		string trueLabel = CodeBuffer::instance().genLabel();
		CodeBuffer::instance().emit("li " +exp2->reg.regName+",1");
		vector<int> nexts = CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j "));
		string falseLabel = CodeBuffer::instance().genLabel();
		CodeBuffer::instance().emit("li " +exp2->reg.regName+",0");
		nexts = CodeBuffer::instance().merge(nexts,CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j ")));
		string next = CodeBuffer::instance().genLabel();
		CodeBuffer::instance().bpatch(nexts,next);
		CodeBuffer::instance().bpatch(exp2->bp.trueList,trueLabel);
		CodeBuffer::instance().bpatch(exp2->bp.falseList,falseLabel);
	}

	CodeBuffer::instance().emit("bge " + exp1->reg.regName + "," + temp +",indexException");
	CodeBuffer::instance().emit("blt " + exp1->reg.regName + ",0,indexException");

	int arrayOffset = arraySym.offset;//getLocalOffset(arraySym.offset);
	CodeBuffer::instance().emit("addu " + exp1->reg.regName + "," + exp1->reg.regName + ","
								+ toString(arrayOffset));	//num of words from fp
	CodeBuffer::instance().emit("mul " + exp1->reg.regName + "," + exp1->reg.regName + ","
								+ toString(-4));	//num of bytes from fp						
	CodeBuffer::instance().emit("addu " + exp1->reg.regName + "," + 
								exp1->reg.regName + "," + "$fp"); //absolute address
	CodeBuffer::instance().emit("sw " + exp2->reg.regName + "," + 
								"(" + exp1->reg.regName + ")"); // writing exp2 to id[exp1]
	registerStack.push(exp1->reg); //free the exp reg
	registerStack.push(exp2->reg); //free the exp reg							
}

//While and if )without else) statement	- when do we restore the exp reg??!11111111111111111111
Statement::Statement(Exp* exp, Statement* statement,bool isWhile) {
	CodeBuffer::instance().bpatch(exp->bp.trueList,statement->bp.quad);
	this->bp.falseList=CodeBuffer::instance().merge(exp->bp.falseList,statement->bp.nextList);
	//this->bp.breakList= statement->bp.breakList;
	if(isWhile){
		CodeBuffer::instance().emit("j "+ exp->bp.quad);
	}
	string label = CodeBuffer::instance().genLabel();
	CodeBuffer::instance().bpatch(this->bp.falseList,label); 
	CodeBuffer::instance().bpatch(statement->bp.breakList,label); 
}

// int a=exp;
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

	if(type->type == "BOOL"){
		exp->reg = registerStack.top();
		registerStack.pop();
		string trueLabel = CodeBuffer::instance().genLabel();
		CodeBuffer::instance().emit("li " + exp->reg.regName +",1");
		vector<int> nexts = CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j "));
		string falseLabel = CodeBuffer::instance().genLabel(); 
		CodeBuffer::instance().emit("li " + exp->reg.regName +",0");
		nexts = CodeBuffer::instance().merge(nexts,CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j ")));
		string next = CodeBuffer::instance().genLabel();
		CodeBuffer::instance().bpatch(nexts,next);
		CodeBuffer::instance().bpatch(exp->bp.trueList,trueLabel);
		CodeBuffer::instance().bpatch(exp->bp.falseList,falseLabel);
	}
	CodeBuffer::instance().emit("subu $sp,$sp,4");			//add place for local variable in the stack.
	CodeBuffer::instance().emit("sw "+ exp->reg.regName +",0($sp)");//push to the stack.
	//adding local variable to stack:
	registerStack.push(exp->reg);
}


Statement::Statement(Exp* exp, Statement* ifStatment,Statement* N, Statement* elseStatement) {
	CodeBuffer::instance().bpatch(exp->bp.trueList,ifStatment->bp.quad);
	CodeBuffer::instance().bpatch(exp->bp.falseList,elseStatement->bp.quad);
	this->bp.nextList=CodeBuffer::instance().merge(
	CodeBuffer::instance().merge(ifStatment->bp.nextList,elseStatement->bp.nextList),
	N->bp.nextList);
	this->bp.breakList = CodeBuffer::instance().merge(ifStatment->bp.breakList,elseStatement->bp.breakList);
}


ExpList::ExpList(Exp* exp) {
	this->types = vector<string>();
  	this->types.push_back(exp->type);
	this->ids.push_back(exp->arrayID);

	
	if(exp->type=="BOOL" ){
			exp->reg = registerStack.top();
			registerStack.pop();
			string trueLabel = CodeBuffer::instance().genLabel();
			CodeBuffer::instance().emit("li "+ exp->reg.regName +",1");
			vector<int> nexts = CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j "));
			string falseLabel = CodeBuffer::instance().genLabel();
			CodeBuffer::instance().emit("li "+ exp->reg.regName +",0");
			nexts = CodeBuffer::instance().merge(nexts,CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j ")));
			string next = CodeBuffer::instance().genLabel();
			CodeBuffer::instance().bpatch(nexts,next);
			CodeBuffer::instance().bpatch(exp->bp.trueList,trueLabel);
			CodeBuffer::instance().bpatch(exp->bp.falseList,falseLabel);
  	}
	this->registers = vector<Register>();
 	this->registers.push_back(exp->reg);
}


ExpList::ExpList(Exp* exp, ExpList* expList){
  
	this->types = vector<string>();
	this->types.push_back(exp->type);
	this->ids.push_back(exp->arrayID);
	for(int i=0; i<expList->types.size(); i++){
		this->types.push_back(expList->types[i]);
		this->ids.push_back(expList->ids[i]);
	}
	// if(exp->type=="BOOL"){
	// 	exp->reg = registerStack.top();
	// 	registerStack.pop();
	// 	string trueLabel = CodeBuffer::instance().genLabel();
	// 	CodeBuffer::instance().emit("li "+ exp->reg.regName+",1");
	// 	vector<int> nexts = CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j "));
	// 	string falseLabel = CodeBuffer::instance().genLabel();
	// 	CodeBuffer::instance().emit("li "+exp->reg.regName+",0");
	// 	nexts = CodeBuffer::instance().merge(nexts,CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j ")));
	// 	string next = CodeBuffer::instance().genLabel();
	// 	CodeBuffer::instance().bpatch(nexts,next);
	// 	CodeBuffer::instance().bpatch(exp->bp.trueList,trueLabel);
	// 	CodeBuffer::instance().bpatch(exp->bp.falseList,falseLabel);
  	// }
  this->registers = vector<Register>();
  this->registers.push_back(exp->reg);
  for(int i=0; i<expList->registers.size(); i++){
    this->registers.push_back(expList->registers[i]);
  }
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
	CodeBuffer::instance().emit("jal " + id->name); //jump to func + stores ra
  	restoreUsedRegs(regs);
}


Call::Call(Id* id, ExpList* expList) {
	stack<Register> regs = registerStack;
  	saveUsedRegs(regs);
	int funArgs;
	int argsSize=0;
	Id* newId;

	if (!checkSymDec(TableStack, id)) {
		errorUndefFunc(yylineno, id->name);
		exit(0);
	}
	Symbol sym = getSymbolById(TableStack, id->name);
	if (!(sym.isFunc)) {								//make outer func
		errorUndefFunc(yylineno, id->name);
		exit(0);
	}
	if (!checkMatchingTypes(sym.args,expList->types)) {
		errorPrototypeMismatch(yylineno, id->name, sym.args);
		exit(0);
	}

	funArgs = sym.args.size(); //num of args of the func called - can be arrays as well!
	for(int i=0;i<funArgs;i++){
		argsSize += getArraySize(sym.args[i]);		//update args size 
	}

	this->id = id->name;
	int j = expList->ids.size()-1;
	for(vector<Register>::reverse_iterator i=expList->registers.rbegin(); i!=expList->registers.rend(); i++){
		if(expList->ids[j] == ""){ //not an array
			CodeBuffer::instance().emit("subu $sp,$sp,4");
			CodeBuffer::instance().emit("sw " + (*i).regName + ",0($sp)"); //push registers to the stack.
			registerStack.push((*i)); //mark reg as unUsed!//-------------------------------------------------------------------TODO
		}else{ //is an array
			Symbol sym = getSymbolById(TableStack, expList->ids[j]);
			int offset = sym.offset; //getLocalOffset(sym.offset);
			int size = getArraySize(sym.type);
			for(int k=0;k<size; k++){
				CodeBuffer::instance().emit("lw " + (*i).regName + "," + toString(-offset*4)+ "($fp)");
				CodeBuffer::instance().emit("subu $sp,$sp,4");
				CodeBuffer::instance().emit("sw " + (*i).regName + ",0($sp)"); //push registers to the stack.
				offset++;
			}
			registerStack.push((*i)); //mark reg as unUsed!//--------------------------------------------------TODO
		}
		j--;
	}
	CodeBuffer::instance().emit("jal " + id->name);
  	CodeBuffer::instance().emit("addu $sp,$sp," + toString(argsSize*4)); //saves space for all the fun arguments, clearing parameters
  	restoreUsedRegs(regs);	//update the regStack accord.
}

String::String(const char* yytext) {
	this->type = "STRING";
	this->value = yytext; 
  label = "lbl" + toString(++stringNum); //updating the stringNum val to make a DIFFERENT label for diff msgs.
  CodeBuffer::instance().emitData(label + ": " + ".asciiz " + string(yytext));
  reg = registerStack.top();
  registerStack.pop();
  CodeBuffer::instance().emit("la " + reg.regName + "," + label);
}

///---------------------------------------add reg val to exp funcs
Exp::Exp(): type(""), arrayID("") {}

// id[exp]
Exp::Exp(Id* id,Exp* exp){
	
	if (!checkSymDec(TableStack, id)) {
		errorUndef(yylineno, id->name);
		exit(0);
	}
	
	string t=getTypeById(TableStack,id).type;
	int currOffset = getSymbolById(TableStack, id->name).offset;
	int pos1=t.find("[");
	if(pos1 == -1){				//not an array
		errorMismatch(yylineno);													//TODO
		exit(0);
	}
	this->type = t.substr(0,pos1);
	this->reg = exp->reg;
	//this->needEval = false;
	
	
	int pos2=t.find("]");
	string temp = t.substr(pos1+1,pos2-pos1-1);
	//SymbolTable currScope = TableStack.top();
	//int firstOffset = currScope[0].offset;
	//std::cout << "#POINT 8 \n" << std::endl;
	int localOffset = currOffset; // - firstOffset ;// findActualOffset();
	this->arrayID="";
	
	this->bp.quad = CodeBuffer::instance().emit("bge " + exp->reg.regName + "," + temp +",indexException");
	CodeBuffer::instance().emit("blt " + exp->reg.regName + ",0,indexException");
	CodeBuffer::instance().emit("addu " + this->reg.regName + "," + this->reg.regName + ","
								+ toString(localOffset));	//num of words from fp
	CodeBuffer::instance().emit("mul " + this->reg.regName + "," + this->reg.regName + ","
								+ toString(-4));	//num of bytes from fp						
	CodeBuffer::instance().emit("addu " + this->reg.regName + "," + 
								this->reg.regName + "," + "$fp"); //absolute address
	CodeBuffer::instance().emit("lw " + this->reg.regName + "," + 
								"(" + this->reg.regName + ")"); // loading id[exp]
	
	if(this-> type =="BOOL" ){
		this->bp.trueList = CodeBuffer::instance().makelist(CodeBuffer::instance().emit("beq "+ this->reg.regName +",1,"));
		this->bp.falseList = CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j "));
		//if(isArgument == false){
			registerStack.push(exp->reg);
		//}
	}
}


Exp::Exp(String* exp,bool isAprintFunc,bool isAprintiFunc) { //help please
	
	if (!isAprintFunc && !isAprintiFunc) {
		errorMismatch(yylineno);
		exit(0);
	}
	this->type = "STRING";
	this->arrayID="";
	this->reg = exp->reg;
	//this->needEval = false;
}


Exp::Exp(Num* exp) : type("INT"), reg(exp->reg) , arrayID("") {} //exp uses the same reg as num

// exp = (exp)
Exp::Exp(Exp* exp) : type(exp->type), reg(exp->reg) , arrayID("") {
	this->bp.trueList=exp->bp.trueList;
  	this->bp.falseList=exp->bp.falseList;
	this->bp.breakList=exp->bp.breakList;
	this->bp.nextList=exp->bp.nextList;
	this->bp.quad=exp->bp.quad;
	//this->needEval = exp->needEval;

} //exp uses the same reg as exp

Exp::Exp(Id* id) {
  
	if (!checkSymDec(TableStack, id)) {
		errorUndef(yylineno, id->name);
		exit(0);
	}
	this->type = getTypeById(TableStack, id).type;
	if(isArray(this->type)){
		this->arrayID = id->name;
	}else{
		this->arrayID = "";
	}
	//this->needEval = false;
	//if(registerStack.empty())	std::cout << "STACK EMPTY!!! "  << std::endl; ///////////////////////-----------------------------------------------
	this->reg = registerStack.top();
	registerStack.pop();
	
	int localOffset =getSymbolById(TableStack,id->name).offset; //getLocalOffset(getSymbolById(TableStack,id->name).offset);
	//CodeBuffer::instance().emit("##############OFFSET IS" + toString(localOffset));
	this->bp.quad = CodeBuffer::instance().emit("lw " + this->reg.regName + "," + toString((-localOffset)*4)+"($fp)");// loading id	
	if(this-> type =="BOOL" ){
		this->bp.trueList = CodeBuffer::instance().makelist(CodeBuffer::instance().emit("beq "+ this->reg.regName +",1,"));
		this->bp.falseList = CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j "));
		// string trueLabel = CodeBuffer::instance().genLabel();
		// CodeBuffer::instance().emit("li "+ this->reg.regName+",1");
		// vector<int> nexts = CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j "));
		// string falseLabel = CodeBuffer::instance().genLabel();
		// CodeBuffer::instance().emit("li "+this->reg.regName+",0");
		// nexts = CodeBuffer::instance().merge(nexts,CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j ")));
		// string next = CodeBuffer::instance().genLabel();
		// CodeBuffer::instance().bpatch(nexts,next);
		//if(isArgument == false){
			registerStack.push(this->reg);		//relase reg for bool exp  ------------------------Level 3 added here
		//}
  	}
	//else keep the reg

}

Exp::Exp(Call* call) { //TODO: X=CALL F() -> SHOULD EXP.REG GET RETURN VALUE?
	this->arrayID="";
	this->type = getSymbolById(TableStack, call->id).ret;
	this->reg = registerStack.top();
	//this->needEval = false;
	registerStack.pop();
	CodeBuffer::instance().emit("move " + reg.regName + ",$v0");
	if(this->type == "BOOL"){
		this->bp.trueList = CodeBuffer::instance().makelist(CodeBuffer::instance().emit("beq "+ this->reg.regName +",1,"));
		this->bp.falseList = CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j "));
		//if(isArgument == false){
		registerStack.push(this->reg);
	}
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
	
	this->reg = num->reg;
	this->arrayID = "";
	//this->needEval = false;
}

//for TRUE or FALSE vals
Exp::Exp(string flag) {
	this->type="BOOL";
	this->arrayID = "";
	//this->needEval = true;
	if(flag == "TRUE" ){
		this->bp.trueList = CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j "));
	}else{
		this->bp.falseList = CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j "));
	}
}

Exp::Exp(string operand, Exp* exp) {		//not
	
	if(operand == "NOT"){
		if ((exp->type != "BOOL")) {
			errorMismatch(yylineno);
			exit(0);
		}
		this->arrayID="";
		this->type="BOOL";
		this->bp.trueList=exp->bp.falseList;
  		this->bp.falseList=exp->bp.trueList;
		//this->needEval = true;
	}

	
}

Exp::Exp(Exp* exp1, Exp* exp2, string opType,string opVal) { // TODO: check for bool back patching
	
		if(opType == "LOGOP"){ //AND \ OR
		if ((exp1->type != "BOOL") || (exp2->type != "BOOL")) {
			errorMismatch(yylineno);
			exit(0);
		}
		this->type = "BOOL";
		//this->needEval = true;
		if(opVal == "AND"){
			CodeBuffer::instance().bpatch(exp1->bp.trueList,exp2->bp.quad);
			this->bp.trueList=exp2->bp.trueList;	
			this->bp.falseList=CodeBuffer::instance().merge(exp1->bp.falseList,exp2->bp.falseList);
		}else if(opVal == "OR"){ 	//OR	
			CodeBuffer::instance().bpatch(exp1->bp.falseList,exp2->bp.quad);
			this->bp.falseList=exp2->bp.falseList;
			this->bp.trueList=CodeBuffer::instance().merge(exp1->bp.trueList,exp2->bp.trueList);
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
		
		this->reg = exp1->reg; //using exp1 reg
		//this->needEval = false;
		string opCmd;
		string optmp = string(opVal);

		if(optmp == "+"){
			opCmd = "addu ";
		}else if(optmp == "-"){
			opCmd = "subu ";
		}else if(optmp == "*"){
			opCmd = "mul ";
		}else if(optmp == "/"){
			opCmd = "div ";
			CodeBuffer::instance().emit("beq " + exp2->reg.regName + ",0,divException");
		}
		CodeBuffer::instance().emit(opCmd + this->reg.regName + "," + 
					exp1->reg.regName + "," + exp2->reg.regName);
		
		if(this->type == "BYTE"){
			CodeBuffer::instance().emit("andi " +this->reg.regName+", " + this->reg.regName + ", 0x000000ff");
		}
		
		registerStack.push(exp2->reg); //we no longer need the reg2
	}
	this->arrayID="";
}

Exp::Exp(Exp* exp1,Exp* exp2,Relop* op){	

	if ((exp1->type != "INT" && exp1->type != "BYTE") ||
			(exp2->type != "INT" && exp2->type != "BYTE")) {
		errorMismatch(yylineno);
		exit(0);
	}
	
	this->type = "BOOL";
	//this->needEval = true;
	
	string opCmd;
	string opVal=op->op;

	if(opVal == "=="){
		opCmd = "beq";
	}else if(opVal == "!="){
		opCmd = "bne";
	}else if(opVal == "<"){
		opCmd = "blt";
	}else if(opVal == ">"){
		opCmd = "bgt";
	}else if(opVal == "<="){
		opCmd = "ble";
	}else if(opVal == ">="){
		opCmd = "bge";
	}

	this->bp.trueList = CodeBuffer::instance().makelist(CodeBuffer::instance().emit(
		opCmd +" "+ exp1->reg.regName+","+ exp2->reg.regName+","));
	this->bp.falseList = CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j "));
	this->arrayID="";

	registerStack.push(exp1->reg);
	registerStack.push(exp2->reg);
}



