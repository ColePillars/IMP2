#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>

using namespace std;

class exp_node {
public:
    // print function for pretty printing an expression
    virtual void print() = 0;

    // evaluation function for a leaf, replaced for interior nodes
    virtual float evaluate() = 0;
};

class bexp_node {
public:

	//print function for Boolean expressions
	virtual void print() = 0;

	//evaluation function for Boolean expressions
	virtual bool evaluate() = 0;
};

class operator_node : public exp_node {
    public:
        exp_node *left;
        exp_node *right;

        // the constructor for node links the node to its children,
        // and stores the character representation of the operator.
        operator_node(exp_node *L, exp_node *R);
};

//Boolean Operator Constructor, duplicated from operator node, creates two variables which will be compared
class boolean_operator_node : public bexp_node {
    public:
        bexp_node *left;
        bexp_node *right;

        boolean_operator_node(bexp_node *L, bexp_node *R);
};

class number_node : public exp_node {
    private:
        float num;

    public:
        number_node(float value);
        void print();
        float evaluate();
};

//Boolean True Constructor
class true_node : public bexp_node {
    public:
        true_node();
        void print();
        bool evaluate();
};

//Boolean False Constructor
class false_node : public bexp_node {
    public:
        false_node();
        void print();
        bool evaluate();
};

//Input Constructor
class input_node : public exp_node {
    private:
        float num;

    public:
        input_node(float value);
        void print();
        float evaluate();
    };

class unary_minus_node : public exp_node {
    protected:
        exp_node *exp;
    public:
        unary_minus_node(exp_node *exp);
        void print();
        float evaluate();
};

//Boolean NOT Constructor
class not_node : public bexp_node {
    protected:
        bexp_node *bexp;
    public:
	    not_node(bexp_node *bexp);
	    void print();
	    bool evaluate();
};

class id_node : public exp_node {
    protected:
        string id;
    public:
        id_node(string value);
        void print();
        float evaluate();
};

//Boolean ID Constructor, duplicated from ID Node
class boolean_id_node : public bexp_node {
    protected:
        string id;
    public:
        boolean_id_node(string value);
        void print();
        bool evaluate();
};

// plus_node inherits the characteristics of node and adds its own evaluate function
class plus_node : public operator_node {
    public:
        // plus_node's constructor just uses node's constructor
        plus_node(exp_node *L, exp_node *R);
        void print();
        float evaluate();
};

//Boolean OR constructor
class or_node : public boolean_operator_node {
    public:
        or_node(bexp_node *L, bexp_node *R);
        void print();
        bool evaluate();
};



// minus_node inherits the characteristics of node and adds its own evaluate function
class minus_node : public operator_node {
    public:
        minus_node(exp_node *L, exp_node *R);
        void print();
        float evaluate();
};


// times_node inherits the characteristics of node and adds its own evaluate function
class times_node : public operator_node {
    public:
        times_node(exp_node *L, exp_node *R);
        void print();
        float evaluate();
};

//Boolean AND Constructor
class and_node : public boolean_operator_node {
    public:
	    and_node(bexp_node *L, bexp_node *R);
	    void print();
	    bool evaluate();
};

//Boolean EQUALS EQUALS Constructor
class equals_equals_node : public boolean_operator_node {
    public:
	    equals_equals_node(bexp_node *L, bexp_node *R);
	    void print();
	    bool evaluate();
};

//Boolean GREATER Constructor
class greater_node : public operator_node {
    public:
	    greater_node(exp_node *L, exp_node *R);
	    void print();
	    float evaluate();
};

//Equivalence for expressions (numbers)
class equivalent_node : public operator_node {
    public:
        equivalent_node(exp_node *L, exp_node *R);
        void print();
        float evaluate();
};

// divide_node inherits the characteristics of node and adds its own evaluate function
class divide_node : public operator_node {
    public:
        divide_node(exp_node *L, exp_node *R);
        void print();
        float evaluate();
};

class statement {
    public:
        virtual void print() {}
        virtual void evaluate() = 0;
};

//If-Else Statement inherits the characteristics of statements, evaluates, and prints. 
class if_else_stmt : public statement {
    protected:
	    exp_node *exp;
	    statement *stmtlist1, *stmtlist2;
    public:
	    if_else_stmt(exp_node *exp, statement *stmtlist1, statement *stmtlist2);
	    void print();
	    void evaluate();
};

//While statement inherits the characteristics of statements, evaluates, and prints. 
class while_do_stmt : public statement {
    protected:
	    exp_node *exp;
	    statement *stmtlist1;
    public:
	    while_do_stmt(exp_node *exp, statement *stmtlist1);
	    void print();
	    void evaluate();
};

//If-Else Statement inherits the characteristics of statements, evaluates, and prints. 
class if_else_stmt : public statement
{
protected:
	bexp_node *bexp;
	statement *stmtlist1, *stmtlist2;
public:
	if_else_stmt(bexp_node *bexp, statement *stmtlist1, statement *stmtlist2);
	void print();
	void evaluate();
};

//While statement inherits the characteristics of statements, evaluates, and prints. 
class while_do_stmt : public statement
{
protected:
	bexp_node *bexp;
	statement *stmtlist1;
public:
	while_do_stmt(bexp_node *bexp, statement *stmtlist1);
	void print();
	void evaluate();
};

class assignment_stmt : public statement {
    protected:
        string id;
        exp_node *exp;
    public:
        assignment_stmt(string name, exp_node *expression);
        void print();
        void evaluate();
};

//Boolean assignment stmt Constructor, duplicated from assignment stmt to prevent ambiguity
class boolean_assignment_stmt : public statement{
    protected:
	    string id;
	    bexp_node *bexp;
    public:
	    boolean_assignment_stmt(string name, bexp_node *expression);
	    void print();
	    void evaluate();
};

class print_stmt: public statement {
    protected:
        exp_node *exp;
    public:
        print_stmt(exp_node *myexp);
        void print();
        void evaluate();
};

//Boolean print stmt Constructor, duplicated from print stmt
class boolean_print_stmt: public statement {
    protected:
        bexp_node *bexp;
    public:
        boolean_print_stmt(bexp_node *myexp);
        void print();
        void evaluate();
};

class skip_stmt: public statement {
    public:
        skip_stmt();
        void print();
        void evaluate();
};


class sequence_stmt: public statement {
    protected:
        statement *stmt1, *stmt2;
    public:
        sequence_stmt(statement *mystmt1, statement *mystmt2);
        void print();
        void evaluate();
};

// the object at the base of our tree
extern map<string, float> idTable;

