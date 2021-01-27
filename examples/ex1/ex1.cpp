#include <generated/Parent.hpp>
#include <generated/Child.hpp>
#include <iostream>

int main()
{
  using namespace std;
  
  Child c;
  cout << sizeof(c) << endl;
  c.member1(1)
   .member2(2);
  cout << c.member1() << " " << c.member2() << endl;
  
  Parent p;
  p.child1.member1(3)
          .member2(4)
          .member2(44)
          .member1(33);
  p.child2.member1(5)
          .member2(6);
  p.child2(c);
  
  cout << p.child1().member1() << " " << p.child1().member2() << endl;
  cout << p.child2().member1() << " " << p.child2().member2() << endl;

  p.child1 = c;
  p.child2.member1 = 5;
  
  // This form works also
  cout << p.child1.member1() << " " << p.child1.member2() << endl;
  cout << p.child2.member1() << " " << p.child2.member2() << endl;

  return 0;
}
