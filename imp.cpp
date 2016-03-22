#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>
#include "imp.h"

using namespace std;

  // the constructor for node links the node to its children,
  // and stores the character representation of the operator.
operator_node::operator_node(exp_node *L, exp_node *R) {
    left    = L;
    right   = R;
}
  
number_node::number_node(float value) {
    num = value;
}
  
void number_node:: print() {
    cout << num;
}

float number_node::evaluate() {
    return num;
}

id_node::id_node(string value) : id(value) {}

void id_node:: print() {
    cout << id;
}

float id_node::evaluate() {
    return idTable[id];
}

// plus_node inherits the characteristics of node and adds its own evaluate function
// plus_node's constructor just uses node's constructor
plus_node::plus_node(exp_node *L, exp_node *R) : operator_node(L,R) { }

void plus_node:: print() {
    cout << "(";
    left->print();
    cout << " + ";
    right->print();
    cout << ")";
}

float plus_node::evaluate() {
    float left_num, right_num;

    left_num  = left->evaluate();
    right_num = right->evaluate();
    
    return left_num + right_num;
}


// minus_node inherits the characteristics of node and adds its own evaluate function
minus_node::minus_node(exp_node *L, exp_node *R) : operator_node(L,R) { }

void minus_node:: print() {
    cout << "(";
    left->print();
    cout << " - ";
    right->print();
    cout << ")";
}

float minus_node::evaluate() {
    float left_num, right_num;

    left_num  = left->evaluate();
    right_num = right->evaluate();

    return  left_num - right_num;
}

// times_node inherits the characteristics of node and adds its own evaluate function
times_node::times_node(exp_node *L, exp_node *R) : operator_node(L,R) { }

void times_node:: print() {
    cout << "(";
    left->print();
    cout << " * ";
    right->print();
    cout << ")";
}

float times_node::evaluate() {
    float left_num, right_num;

    left_num = left->evaluate();
    right_num = right->evaluate();

    return left_num * right_num;
}

// divide_node inherits the characteristics of node and adds its own evaluate function
divide_node::divide_node(exp_node *L, exp_node *R) : operator_node(L,R) { }

void divide_node:: print() {
    cout << "(";
    left->print();
    cout << " / ";
    right->print();
    cout << ")";
}

float divide_node::evaluate() {
    float left_num, right_num;

    left_num = left->evaluate();
    right_num = right->evaluate();

    if(right_num) {
        return  left_num / right_num;
    }
    else {
	    cout << "division by zero -> " << left_num << " / " << 0 << endl;
	    //  include stdlib.h for exit
	    exit(1);
    }
}

unary_minus_node::unary_minus_node(exp_node *L) : exp(L) {}

void unary_minus_node:: print() {
    cout << "- ( ";
    exp->print();
    cout << " )";
}

float unary_minus_node::evaluate() {
    float expValue = exp->evaluate();
    return  -expValue;
}

assignment_stmt::assignment_stmt(string name, exp_node *expression) : id(name), exp(expression) { }

void assignment_stmt::print() {
    cout << id << " = ";
    exp->print();
}

void assignment_stmt::evaluate() {
    float result = exp->evaluate();

    idTable[id] = result;
}

print_stmt::print_stmt (exp_node *myexp) : exp(myexp) {}

void print_stmt::print() {
    cout <<  "print ";
    exp->print();
}


void print_stmt::evaluate() {
    cout << "output: " << exp->evaluate() << endl << endl;
}

skip_stmt::skip_stmt ()  {}

void skip_stmt::evaluate() {}
void skip_stmt::print() {}

sequence_stmt::sequence_stmt(statement* mystmt1, statement* mystmt2): stmt1(mystmt1), stmt2(mystmt2) { }

void sequence_stmt::print() {
    stmt1->print();  cout << " ;" << endl;
    stmt2->print();
}



//-----------Input-------------------------

input_node::input_node(float value) {
    num = value;
}

void input_node:: print() {
    cout << "input";
}

float input_node:: evaluate() {
    cout << "input: ";
    cin >> num;
    cout << endl;
    return num;
}


//-----------Boolean-Expressions-----------

//Duplicate of operator_node, handles expressions with 2 variables
boolean_operator_node::boolean_operator_node(bexp_node *L, bexp_node *R) {
    left    = L;
    right   = R;
}

//Handles true values
true_node::true_node() { }

void true_node:: print() {
    cout << " True ";
}

bool true_node::evaluate() {
    return true;
}

//Handles false values
false_node::false_node() { }

void false_node:: print() {
    cout << " False ";
}

bool false_node::evaluate() {
    return false;
}

//Boolean type for ID's, used to correct for ambiguous grammar (var = 10, var = true would be ambiguous)
//IDs are assigned to boolean values when $= sign is used
boolean_id_node::boolean_id_node(string value) : id(value) {}

void boolean_id_node:: print() {
    cout << id;
}

bool boolean_id_node::evaluate() {
    return idTable[id];
}

//Handles || expressions
or_node::or_node(bexp_node *L, bexp_node *R) : boolean_operator_node(L,R) {}

void or_node:: print() {
    cout << "(";
    left->print();
    cout << " || ";
    right->print();
    cout << ")";
}

bool or_node::evaluate() {
    bool left_num, right_num;

    left_num  = left->evaluate();
    right_num = right->evaluate();

    return left_num || right_num;
}

//Handles && expressions
and_node::and_node(bexp_node *L, bexp_node *R) : boolean_operator_node(L,R) {}

void and_node:: print() {
    cout << "(";
  	left->print();
  	cout << " && ";
  	right->print();
  	cout << ")";
}

bool and_node::evaluate() {
    bool left_num, right_num;

    left_num = left->evaluate();
    right_num = right->evaluate();

    return left_num && right_num;
}

//Handles == expressions
equals_equals_node::equals_equals_node(bexp_node *L, bexp_node *R) : boolean_operator_node(L,R) {}

void equals_equals_node:: print() {
  	cout << "(";
  	left->print();
  	cout << " == ";
  	right->print();
  	cout << ")";
}

bool equals_equals_node::evaluate() {
    bool left_num, right_num;

    left_num = left->evaluate();
    right_num = right->evaluate();

    return left_num == right_num;
}

////Handles > expressions
//greater_node::greater_node(exp_node *L, exp_node *R) : operator_node(L, R) {}
//
//void greater_node::print() {
//    cout << "( ";
//  	left->print();
//  	cout << " > ";
//  	right->print();
//  	cout << " )";
//}
//
//float greater_node::evaluate() {
//    float left_num, right_num;
//
//    left_num = left->evaluate();
//    right_num = right->evaluate();
//
//    if (left_num > right_num) {
//        return 1;
//    }
//    else {
//        return 0;
//    }
//}

//Handles ! expression
not_node::not_node(bexp_node *myexp) : bexp(myexp)  {}

void not_node:: print() {
    cout << "! ( ";
    bexp->print();
    cout << " )";
}

bool not_node::evaluate() {
    bool var = bexp->evaluate();
    return  !var;
}

//Boolean assignment, needs to be duplicated because not all bool functions work for numbers
// $= is the assignment operator
boolean_assignment_stmt::boolean_assignment_stmt(string name, bexp_node *expression) : id(name), bexp(expression) {}

void boolean_assignment_stmt::print() {
    cout << id << " $= ";
    bexp->print();
}

void boolean_assignment_stmt::evaluate() {
    bool result = bexp->evaluate();
    idTable[id] = result;
}

//Duplicated print stmt
boolean_print_stmt::boolean_print_stmt (bexp_node *myexp) : bexp(myexp) {}

void boolean_print_stmt::print() {
    cout <<  "print ";
    bexp->print();
}

void boolean_print_stmt::evaluate() {
    cout << "output: " << bexp->evaluate() << endl << endl;
}


//-----------If-Else Statement-------------
//if_than_stmt inherits the characteristic nodes and evalutates it works with imp.h file

//Constructor for all three conditions for if else statement. 
if_else_stmt::if_else_stmt(bexp_node *bexp, statement *stmtlist1, statement *stmtlist2)
{
	this->bexp = bexp;
	this->stmtlist1 = stmtlist1;
	this->stmtlist2 = stmtlist2;
}
//Prints out the if-else statement.
void if_else_stmt::print()
{
	cout << "if ( ";
	this->bexp->print();
	cout << " )" << endl;

	this->stmtlist1->print();
	cout << endl;

	cout << "else " << endl;
	this->stmtlist2->print();
	cout << endl;
}
//Evaluates the condition and statements through an if-else statement
void if_else_stmt::evaluate()
{
	if (this->bexp->evaluate())
	{
		this->stmtlist1->evaluate();
	}
	else
	{
		this->stmtlist2->evaluate();
	}

}
//-------------While Statement-------------------

//While statement constructor.
while_do_stmt::while_do_stmt(bexp_node *bexp, statement *stmtlist1)
{
	this->bexp = bexp;
	this->stmtlist1 = stmtlist1;
}
//Prints of out the while statement.
void while_do_stmt::print()
{
	cout << "while ( ";
	this->bexp->print();
	cout << " )" << endl;

	cout << "do: " << endl;
	this->stmtlist1->print();
	cout << endl;
}
//Evaluate the condition and the do statement in a while loop.
void while_do_stmt::evaluate()
{
	while (this->bexp->evaluate())
	{
		this->stmtlist1->evaluate();
	}
}

void sequence_stmt::evaluate() {
    stmt1->evaluate();
    stmt2->evaluate();
}

map<string, float> idTable;

