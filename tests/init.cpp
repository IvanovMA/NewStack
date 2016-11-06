#include <stack.hpp>
#include <catch.hpp>
#include <iostream>
using namespace std;

SCENARIO("count", "[count]"){
  stack<int> s;
  s.push(1);
  REQUIRE(s.count()==1);
}

SCENARIO("pop", "[pop]"){
  stack<int> s;
  s.push(1);
  s.pop();
  REQUIRE(s.count()==0);
}

