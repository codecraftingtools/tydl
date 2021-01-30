#include <generated/Parent.hpp>
#include <generated/Child.hpp>
#include <iostream>

int main()
{
  using namespace std;
  
  Child c;
  c.member1(1)
   .member2(2);
  
  cout << "Child" << endl;
  cout << "  size: " << sizeof(c) << " bytes" << endl;
  cout << "  member1: " << c.member1() << endl;
  cout << "  member2: " << c.member2() << endl;
  
  Parent p;
  p.child1.member1(3)
          .member2(4)
          .member2(44)  // reassign
          .member1(33); // reassign
  p.child2.member1(5)
          .member2(6);

  cout << endl;
  cout << "Parent" << endl;
  cout << "  size: " << sizeof(p) << " bytes" << endl;
  cout << "  child1" << endl;
  cout << "    member1: " << p.child1.member1() << endl;
  cout << "    member2: " << p.child1.member2() << endl;
  cout << "  child2" << endl;
  cout << "    member1: " << p.child2.member1() << endl;
  cout << "    member2: " << p.child2.member2() << endl;

  p.child2(c); // call setter using another instance of the type

  // Note that parentheses on the child accessor also works
  cout << endl;
  cout << "Parent" << endl;
  cout << "  child1" << endl;
  cout << "    member1: " << p.child1().member1() << endl;
  cout << "    member2: " << p.child1().member2() << endl;
  cout << "  child2" << endl;
  cout << "    member1: " << p.child2().member1() << endl;
  cout << "    member2: " << p.child2().member2() << endl;

  // Use assignment operator
  p.child2 = p.child1;   // This works
  p.child2 = p.child1(); // So does this
  p.child1 = c;
  p.child2.member1 = 5;
  
  cout << endl;
  cout << "Parent" << endl;
  cout << "  child1" << endl;
  cout << "    member1: " << p.child1.member1() << endl;
  cout << "    member2: " << p.child1.member2() << endl;
  cout << "  child2" << endl;
  cout << "    member1: " << p.child2.member1() << endl;
  cout << "    member2: " << p.child2.member2() << endl;

  return 0;
}
