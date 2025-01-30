#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "expr.h"

TEST_CASE("test interp") {
    // Test numeric values
    CHECK((new NumExpr(5))->interp() == 5);
    
    // Test multiplication
    CHECK((new MultExpr(new NumExpr(3), new NumExpr(2)))->interp() == 6);
    
    // Test nested addition
    CHECK((new AddExpr(new AddExpr(new NumExpr(10), new NumExpr(15)),
                      new AddExpr(new NumExpr(20), new NumExpr(20))))->interp() == 65);
    
    // Test variable interpretation throws error
    CHECK_THROWS_WITH((new VarExpr("x"))->interp(), "no value for variable");
}

TEST_CASE("test has_variable") {
    // Test addition with variable
    CHECK((new AddExpr(new VarExpr("x"), new NumExpr(1)))->has_variable() == true);
    
    // Test multiplication without variable
    CHECK((new MultExpr(new NumExpr(2), new NumExpr(1)))->has_variable() == false);
}

TEST_CASE("test subst") {
    // Test variable substitution in addition
    CHECK((new AddExpr(new VarExpr("x"), new NumExpr(7)))
          ->subst("x", new VarExpr("y"))
          ->equals(new AddExpr(new VarExpr("y"), new NumExpr(7))));
    
    // Test complex substitution
    CHECK((new VarExpr("x"))
          ->subst("x", new AddExpr(new VarExpr("y"), new NumExpr(7)))
          ->equals(new AddExpr(new VarExpr("y"), new NumExpr(7))));
}
