/*
 * FileDefModel.cpp
 *
 *  Created on: 14.10.2016
 *      Author: ProgSys
 */

#include <fileManager/FileDefModel.h>
#include <QDataStream>
#include <QDebug>
#include <QFileInfo>
#include <QIntValidator>

QString toString(token::TokenClass type){
	/*

	 Bigger_Equal_Then, Smaller_Then, Smaller_Equal_Then, Not,
			//Math
			Plus, Plus_Equal, Minus, Minus_Equal, Multiply, Multiply_Equal, Divide, Divide_Equal
			*/
	switch (type) {
		case token::NONE: return "NONE"; break;
		case token::Whitespace: return "Whitespace"; break;
		case token::Identifer: return "Identifer"; break;
		case token::String: return "String"; break;
		case token::Integer: return "Integer"; break;
		case token::Keyword: return "Keyword"; break;
		case token::VarType: return "VarType"; break;
		case token::Left_Parenthesis: return "Left_Parenthesis"; break;
		case token::Right_Parenthesis: return "Right_Parenthesis"; break;
		case token::Left_Curly_Bracket: return "Left_Curly_Bracket"; break;
		case token::Right_Curly_Bracket: return "Right_Curly_Bracket"; break;
		case token::Equals_Sign: return "Equals_Sign"; break;
		case token::Comma: return "Comma"; break;
		case token::Semicolon: return "Semicolon"; break;
		case token::Equal: return "Equal"; break;
		case token::Not_Equal: return "Not_Equal"; break;
		case token::Bigger_Then: return "Bigger_Then"; break;
		case token::Bigger_Equal_Then: return "Bigger_Equal_Then"; break;
		case token::Smaller_Then: return "Smaller_Then"; break;
		case token::Smaller_Equal_Then: return "Smaller_Equal_Then"; break;
		case token::Not: return "Not"; break;
		case token::Plus: return "Plus"; break;
		case token::Plus_Equal: return "Plus_Equal"; break;
		case token::Minus: return "Minus"; break;
		case token::Minus_Equal: return "Minus_Equal"; break;
		case token::Multiply: return "Multiply"; break;
		case token::Multiply_Equal: return "Multiply_Equal"; break;
		case token::Divide: return "Divide"; break;
		case token::Divide_Equal: return "Divide_Equal"; break;
		case token::Increase: return "Increase"; break;
		case token::Decrease: return "Decrease"; break;
	}

	return "NONE";
}

token validate(token& t){
	if(t.lexeme.isEmpty()){
		t.type = token::Whitespace;

	}else if(t.lexeme == "{"){
		t.type = token::Left_Curly_Bracket;
	}else if(t.lexeme == "}"){
		t.type = token::Right_Curly_Bracket;
	}else if(t.lexeme == "("){
		t.type = token::Left_Parenthesis;
	}else if(t.lexeme == ")"){
		t.type = token::Right_Parenthesis;
	}else if(t.lexeme == ";"){
		t.type = token::Semicolon;
	}else if(t.lexeme == ","){
		t.type = token::Comma;
	}else if(t.lexeme == "!"){
		t.type = token::Not;

	}else if(t.lexeme == "+"){
		t.type = token::Plus;
	}else if(t.lexeme == "-"){
		t.type = token::Minus;
	}else if(t.lexeme == "*"){
		t.type = token::Multiply;
	}else if(t.lexeme == "/"){
		t.type = token::Divide;

	}else if(t.lexeme == "="){
		t.type = token::Equals_Sign;
	}else if(t.lexeme == "!="){
		t.type = token::Not_Equal;
	}else if(t.lexeme == "+="){
		t.type = token::Plus_Equal;
	}else if(t.lexeme == "-="){
		t.type = token::Minus_Equal;
	}else if(t.lexeme == "*="){
		t.type = token::Multiply_Equal;
	}else if(t.lexeme == "/="){
		t.type = token::Divide_Equal;
	}else if(t.lexeme == "++"){
		t.type = token::Increase;
	}else if(t.lexeme == "--"){
		t.type = token::Decrease;

	}else if(t.lexeme == "=="){
		t.type = token::Equal;
	}else if(t.lexeme == "!="){
		t.type = token::Not_Equal;
	}else if(t.lexeme == ">"){
		t.type = token::Bigger_Then;
	}else if(t.lexeme == ">="){
		t.type = token::Bigger_Equal_Then;
	}else if(t.lexeme == "<"){
		t.type = token::Smaller_Then;
	}else if(t.lexeme == "<="){
		t.type = token::Smaller_Equal_Then;

	}else if(t.lexeme == "if" || t.lexeme == "for" || t.lexeme == "while"){
		t.type = token::Keyword;

	}else if(t.lexeme == "uint64" || t.lexeme == "ulong" ||
			t.lexeme == "uint32" || t.lexeme == "uint" ||
			t.lexeme == "uint16" || t.lexeme == "short"  ||
			t.lexeme == "uint8" || t.lexeme == "byte" ||
			t.lexeme == "int64" || t.lexeme == "long" ||
			t.lexeme == "int32" || t.lexeme == "int" ||
			t.lexeme == "int16" || t.lexeme == "short" ||
			t.lexeme == "int8" || t.lexeme == "char"
	){
		t.type = token::VarType;
	}else if(t.lexeme.size() > 3 && t.lexeme[0] == '\''  && t.lexeme[t.lexeme.size()-1] == '\''){
		t.type = token::String;
	}else if(!t.lexeme.isEmpty() && (t.lexeme[0] == '"' || t.lexeme[0] == '\'' || t.lexeme[0] == '!' || t.lexeme[0] == '=' || t.lexeme[0] == '+' || t.lexeme[0] == '-' || t.lexeme[0] == '*' || t.lexeme[0] == '/' )){
		t.type = token::NONE;
	}else{
		bool ok;
		t.lexeme.toInt(&ok);
		if(ok){
			t.type = token::Integer;
		}else
			t.type = token::Identifer;
	}

	return t;
}

struct lexer{
	QTextStream& in;
	QChar currentChar;
	lexer(QTextStream& testStream): in(testStream){
		getNext();
	}

	operator bool() const
	{
	    return currentChar != '~';
	}

	QChar getNext(){
		if(in.atEnd()) {
			currentChar = '~';
			return '~';
		}
		in >> currentChar;
		return currentChar;
	}

	token getToken(){
		token t;
		bool comment = false;
		bool string = false;
		while(currentChar != '~'){
			if(comment){
				if(currentChar == '\n') comment = false;
			}else if(string){

				if(currentChar == '"' || currentChar == '\'') {
					string = false;
					t.lexeme += '\'';
				}else{
					t.lexeme += currentChar;
				}
			}else if(currentChar == '"' || currentChar == '\''){
				string = true;
				t.lexeme += '\'';
			}else if(currentChar == '#'){
				comment = true;
			}else if(currentChar == ' ' || currentChar == '\n' || currentChar == '\t' || currentChar == '\r'){
				if(!t.lexeme.isEmpty()) return validate(t);
				else t.type = token::Whitespace;
			}else if(currentChar == '{'){
				if(!t.lexeme.isEmpty() || t.type == token::Whitespace) return validate(t);
				t.type = token::Left_Curly_Bracket;
				t.lexeme = "{";
				break;
			}else if(currentChar == '}'){
				if(!t.lexeme.isEmpty() || t.type == token::Whitespace) return validate(t);
				t.type = token::Right_Curly_Bracket;
				t.lexeme = "}";
				break;
			}else if(currentChar == '('){
				if(!t.lexeme.isEmpty() || t.type == token::Whitespace) return validate(t);
				t.type = token::Right_Parenthesis;
				t.lexeme = "(";
				break;
			}else if(currentChar == ')'){
				if(!t.lexeme.isEmpty() || t.type == token::Whitespace) return validate(t);
				t.type = token::Left_Parenthesis;
				t.lexeme = ")";
				break;
			}else if(currentChar == ';'){
				if(!t.lexeme.isEmpty() || t.type == token::Whitespace) return validate(t);
				t.type = token::Semicolon;
				t.lexeme = ";";
				break;
			}else if(currentChar == ','){
				if(!t.lexeme.isEmpty() || t.type == token::Whitespace) return validate(t);
				t.type = token::Comma;
				t.lexeme = ",";
				break;
			}else if(t.lexeme.size() == 1){
				const QChar& c = t.lexeme[0];
				if(c == '!' || c == '=' || c == '+' || c == '-' || c == '*' || c == '/' || c == '>'  || c == '<'){
					if(currentChar == '=' || currentChar == '+' || currentChar == '-'){
						t.lexeme += currentChar;
						break;
					}else{
						return validate(t);
					}
				}
				if(currentChar == '!' || currentChar == '=' || currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/' || currentChar == '>'  || currentChar == '<')
					return validate(t);
				t.lexeme += currentChar.toLower();
			}else if(!t.lexeme.isEmpty() &&
					(currentChar == '!' || currentChar == '=' || currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/' || currentChar == '>'  || currentChar == '<')){
				return validate(t);

			}else{
				t.lexeme += currentChar.toLower();
			}
			getNext();
		}

		getNext();
		return validate(t);
	}
};

void tokenize(QTextStream& in, QList<token>& tokensOut, bool whitespace){
	lexer Lexer(in);
	while(Lexer) {
		token t = Lexer.getToken();
		if(whitespace)
			tokensOut.push_back(t);
		else if(t.type != token::Whitespace)
			tokensOut.push_back(t);

	}

}

Programm::Programm(){}

Programm::~Programm(){}

variable::varTypes Programm::getType() const{
	return variable::Void;
}

//ATOM

Atom::Atom(token atomIn): atom(atomIn){}
Atom::~Atom(){}

bool Atom::run(QVariant& out, QList<variable>& variables){
	if(atom.type == token::Integer){
		out = atom.lexeme.toInt();
		type = variable::Number;
	}else if(atom.type == token::String){
			out = atom.lexeme;
			type = variable::String;
	}else if(atom.type == token::Identifer){
		for(const variable& var: variables){
			if(var.name ==  atom.lexeme){
				out = var.value;
				type = var.getType();
			}
		}
		qDebug()<< "Unknown Identifier "<< atom.lexeme;
		return false;
	}
	return true;
}


variable::varTypes Atom::getType() const{
	return type;
}



Operation::Operation(Programm* leftIn, token::TokenClass operatorTypeIn, Programm* rightIn):
	left(leftIn), operatorType(operatorTypeIn), right(rightIn){}
Operation::~Operation(){
	delete left;
	delete right;
}

bool Operation::run(QVariant& out, QList<variable>& variables){
	QVariant a,b;
	if(!left->run(a,variables)) return false;
	if(!right->run(b,variables)) return false;

	if(operatorType == token::Plus){
		if(left->getType() == right->getType() ){
			if(left->getType() == variable::Number){
				out = a.toInt()+b.toInt();
				type = variable::Number;
			}else if(left->getType() == variable::String){
				out = a.toString()+b.toString();
				type = variable::String;
			}else{
				qDebug()<<"You can only ADD numbers or strings!";
				return false;
			}
		}else{
			qDebug()<<"Add operation with invalid types!";
			return false;
		}
	}else{
		qDebug()<<"Unknown operation!";
		return false;
	}

	return true;
}

variable::varTypes Operation::getType() const{
	return type;
}

AssignNew::AssignNew(variable::varTypes targetTypeIn, const QString& nameIn, Programm* operationIn):
		targetType(targetTypeIn), name(nameIn), operation(operationIn){}
AssignNew::~AssignNew(){
	delete operation;
}

bool AssignNew::run(QVariant& out, QList<variable>& variables){
	QVariant a;
	operation->run(a, variables);

	for(const variable& var: variables){
		if(var.name == name){
			qDebug()<<"Assign: Variable with the name: "<<name<<" already defined!";
			return false;
		}
	}

	variable v;

	if(operation->getType() == variable::Void){
		qDebug()<<"Assign: Type can't be void!";
		return false;
	}

	if(operation->getType() != targetType){
		qDebug()<<"Assign: Type isn't the target type! ("<<operation->getType()<<" != "<<targetType<<")";
		return false;
	}
	v.name = name;
	v.returnType = targetType;
	v.value = a;

	variables.push_back(v);
	return true;
}

//Void, String, Boolean, Number, Array
variable::varTypes getVarType(const token& t){
	if(t.type == token::VarType) {
		if(t.lexeme == "int") return variable::Number;
		if(t.lexeme == "uint") return variable::Number;
		return variable::Void;
	}
	if(t.type == token::Integer) return variable::Number;
	if(t.type == token::String) return variable::String;
	return variable::Void;
}

Programm* parse( const QList<token>& tokensIn){
	Programm* p =  new AssignNew(
			getVarType(tokensIn[0]),
			tokensIn[1].lexeme,
			new Operation(
					new Operation( new Atom(tokensIn[3]), tokensIn[4].type, new Atom(tokensIn[5]) ),
					tokensIn[6].type,
					new Atom(tokensIn[7])
					)
			);
	return p;
}

//////////////////////////
FileDefModel::FileDefModel(QObject *parent): AbstractTreeListModel(parent) {
	// TODO Auto-generated constructor stub

}

FileDefModel::~FileDefModel() {
	// TODO Auto-generated destructor stub
}

