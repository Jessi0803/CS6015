#ifndef EXPR_H
#define EXPR_H

#include <string>
#include <stdexcept>

// Base expression class
class Expr {
public:
    virtual bool equals(Expr* e) = 0;
    virtual int interp() = 0;  // Method to evaluate expression
    virtual bool has_variable() = 0;  // Check if contains variables
    virtual Expr* subst(std::string var, Expr* replacement) = 0;  // Variable substitution
    //VarExpr 如果名稱匹配 var，則回傳 replacement，否則回傳自己。
    virtual ~Expr() {}  // Virtual destructor
};
//Expr 類別的解構函數 ~Expr() 被宣告為虛擬 (virtual)，確保當我們刪除 (delete) 一個 Expr* 指標時，會呼叫子類別的解構函數，而不只是 Expr 本身的解構函數。

// Numeric expression
class NumExpr : public Expr {
public:
    int val;
    NumExpr(int val);
    bool equals(Expr* e);
    int interp();  // Returns the numeric value
    bool has_variable();  // Always returns false
    Expr* subst(std::string var, Expr* replacement);  // Returns copy of itself
};

// Variable expression
class VarExpr : public Expr {
public:
    std::string name;
    VarExpr(std::string name);
    bool equals(Expr* e);
    int interp();  // Throws exception
    bool has_variable();  // Always returns true
    Expr* subst(std::string var, Expr* replacement);  // Handles substitution
};

// Addition expression
class AddExpr : public Expr {
public:
    Expr* lhs;
    Expr* rhs;
    AddExpr(Expr* lhs, Expr* rhs);
    bool equals(Expr* e);
    int interp();  // Adds subexpression values
    bool has_variable();  // Checks both sides
    Expr* subst(std::string var, Expr* replacement);  // Substitutes both sides
};

// Multiplication expression
class MultExpr : public Expr {
public:
    Expr* lhs;
    Expr* rhs;
    MultExpr(Expr* lhs, Expr* rhs);
    bool equals(Expr* e);
    int interp();  // Multiplies subexpression values
    bool has_variable();  // Checks both sides
    Expr* subst(std::string var, Expr* replacement);  // Substitutes both sides
};

#endif




//定義了一個抽象基類 Expr 和三個子類別：NumExpr（數字表達式）、VarExpr（變數表達式）、AddExpr（加法表達式），用於表示數學表達式的結構。每個子類別實作了 equals 方法，用於比較表達式是否相等
