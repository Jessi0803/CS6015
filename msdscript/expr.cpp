#include "expr.h"

// Implementation of numeric expression
NumExpr::NumExpr(int val) {
    this->val = val;
}

bool NumExpr::equals(Expr* e) {
    NumExpr* n = dynamic_cast<NumExpr*>(e);
    if(n == nullptr) {
        return false;
    }
    return this->val == n->val;
}

int NumExpr::interp() {
    return val;  // Return the numeric value
}

bool NumExpr::has_variable() {
    return false;  // Numbers don't contain variables
}

Expr* NumExpr::subst(std::string var, Expr* replacement) {
    return new NumExpr(val);  // Numbers remain unchanged
}

// Implementation of variable expression
VarExpr::VarExpr(std::string name) {
    this->name = name;
}

bool VarExpr::equals(Expr* e) {
    VarExpr* v = dynamic_cast<VarExpr*>(e);
    if(v == nullptr) {
        return false;
    }
    return this->name == v->name;
}

int VarExpr::interp() {
    throw std::runtime_error("no value for variable");  // Variables can't be evaluated
}

bool VarExpr::has_variable() {
    return true;  // Variables are variables
}

Expr* VarExpr::subst(std::string var, Expr* replacement) {
    if (this->name == var) {
        return replacement;  // Replace if names match
    }
    return new VarExpr(this->name);  // Otherwise return copy
} //負責變數替換

// Implementation of addition expression
AddExpr::AddExpr(Expr* lhs, Expr* rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool AddExpr::equals(Expr* e) {
    AddExpr* a = dynamic_cast<AddExpr*>(e);
    if(a == nullptr) {
        return false;
    }
    return this->lhs->equals(a->lhs) && this->rhs->equals(a->rhs);
}

int AddExpr::interp() {
    return lhs->interp() + rhs->interp();  // Add the values
} //需要遞迴，因為它要計算所有子表達式的值。

bool AddExpr::has_variable() {
    return lhs->has_variable() || rhs->has_variable();  // Check both sides
}

Expr* AddExpr::subst(std::string var, Expr* replacement) {
    return new AddExpr(
        lhs->subst(var, replacement),
        rhs->subst(var, replacement)
    );  // Substitute in both subexpressions
}
//如果 lhs 或 rhs 包含 var，那麼它會將 var 替換成 replacement。
//如果 lhs 或 rhs 不包含 var，則 subst() 會回傳原本的子表達式，不做變更。

// Implementation of multiplication expression
MultExpr::MultExpr(Expr* lhs, Expr* rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool MultExpr::equals(Expr* e) {
    MultExpr* m = dynamic_cast<MultExpr*>(e);
    if(m == nullptr) {
        return false;
    }
    return this->lhs->equals(m->lhs) && this->rhs->equals(m->rhs);
}

int MultExpr::interp() {
    return lhs->interp() * rhs->interp();  // Multiply the values
}

bool MultExpr::has_variable() {
    return lhs->has_variable() || rhs->has_variable();  // Check both sides
}

Expr* MultExpr::subst(std::string var, Expr* replacement) {
    return new MultExpr(
        lhs->subst(var, replacement),
        rhs->subst(var, replacement)
    );  // Substitute in both subexpressions
}


//subst(var, replacement)
//負責變數替換，例如把 x 替換成 5。
//它遞迴處理整個數學表達式，確保所有變數都被替換。
//interp()
//負責計算數學表達式的值。
//如果 expr 內部有變數，interp() 可能會失敗（因為變數沒有數值）。
//但如果先執行 subst()，變數就變成了數值，interp() 就可以正常運算。
