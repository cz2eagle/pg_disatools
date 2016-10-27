/*
 * FileDefModel.h
 *
 *  Created on: 14.10.2016
 *      Author: ProgSys
 */

#ifndef INCLUDE_FILEMANAGER_FILEDEFMODEL_H_
#define INCLUDE_FILEMANAGER_FILEDEFMODEL_H_


#include <util/AbstractTreeListModel.h>
#include <QString>
#include <QList>
#include <QTextStream>
#include <QVariant>

#define QDEBUG(x) qDebug()<<__LINE__<<": "<<x

struct token{
	enum TokenClass{
		NONE,
		Whitespace,
		Identifer, String, Integer, Boolean, Keyword,

		VarType,

		Left_Parenthesis, Right_Parenthesis, Left_Curly_Bracket, Right_Curly_Bracket,
		Equals_Sign,
		Semicolon, Comma,
		//logic
		Equal, Not_Equal, Bigger_Then, Bigger_Equal_Then, Smaller_Then, Smaller_Equal_Then, Not,
		//Math
		Plus, Plus_Equal, Minus, Minus_Equal, Multiply, Multiply_Equal, Divide, Divide_Equal, Increase, Decrease
	} type = NONE;
	QString lexeme;
};

QString toString(token::TokenClass type);
void tokenize(QTextStream& in, QList<token>& tokensOut, bool whitespace = false);


struct variable{
	enum varTypes{
		Void, String, Boolean, Number, Array
	};

	varTypes returnType = Void;

	varTypes getType() const { return returnType; }

	QString name;
	QVariant value;
};

/*
 * OPERATION:
 * VARTYPE: VarType
 * Assign: VARTYPE Identifer Equal OPERATION Semicolon
 */
class Programm{
public:
	//enum ProgrammClass{
		//NONE, Atom, Logic, Math, Assign, AssignNew, If, IfElse, For, While, Function, Block
	//};

	Programm();
	virtual ~Programm();

	virtual bool run(QVariant& out, QList<variable>& variables) = 0;
	virtual variable::varTypes getType() const;
};

variable::varTypes getVarType(const token& t);

class Atom: public Programm{
public:
	Atom(token atomIn);
	virtual ~Atom();

	virtual bool run(QVariant& out, QList<variable>& variables);
	bool runRef(QVariant*& out, QList<variable>& variables);

	virtual variable::varTypes getType() const;

	token atom;
	variable::varTypes type = variable::Void;
};

class Operation: public Programm{
public:
	Operation(token& leftIn, token::TokenClass operatorTypeIn, token& rightIn);
	Operation(token& leftIn, token::TokenClass operatorTypeIn, const QList<token>& rightIn);
	Operation(Programm* leftIn, token::TokenClass operatorTypeIn, Programm* rightIn);
	virtual ~Operation();

	virtual bool run(QVariant& out, QList<variable>& variables);

	virtual variable::varTypes getType() const;

	Programm* left;
	token::TokenClass operatorType;
	Programm* right;

	variable::varTypes type = variable::Void;
};

class OperationSingle: public Programm{
public:
	OperationSingle(token& leftIn, token::TokenClass operatorTypeIn);
	virtual ~OperationSingle();

	virtual bool run(QVariant& out, QList<variable>& variables);

	virtual variable::varTypes getType() const;

	Atom* left;
	token::TokenClass operatorType;

	variable::varTypes type = variable::Void;
};

class AssignNew: public Programm{
public:
	AssignNew(const QString& targetTypeLeximeIn, const QString& identiferLeximeIn, const QList<token>& operation);
	virtual ~AssignNew();

	virtual bool run(QVariant& out, QList<variable>& variables);

	variable::varTypes targetType;
	QString name;
	Programm* operation = nullptr;
};

class Block: public Programm{
public:
	Block();
	virtual ~Block();

	virtual bool run(QVariant& out, QList<variable>& variables);
	void push_back(Programm* p);
	bool isEmpty() const;
	int size() const;

	QList<Programm*> programms;
};

Programm* parse( const QList<token>& tokensIn);

class FileDefModel: public AbstractTreeListModel {
	Q_OBJECT
public:
	FileDefModel(QObject *parent = 0);
	virtual ~FileDefModel();
};

#endif /* INCLUDE_FILEMANAGER_FILEDEFMODEL_H_ */
