#include <generated/Parent.hpp>
#include <generated/Child.hpp>
#include <iostream>

void print_child(Child &c) {
  using namespace std;
  cout << endl;
  cout << "Child" << endl;
  cout << "  member1: " << c.member1() << endl; // getter
  cout << "  member2: " << c.member2() << endl;
}

void print_parent(Parent &p) {
  using namespace std;
  cout << endl;
  cout << "Parent" << endl;
  
  // Subfields can be accessed like struct members
  cout << "  child1" << endl;
  cout << "    member1: " << p.child1.member1() << endl;
  cout << "    member2: " << p.child1.member2() << endl;

  // Note that using parentheses on the intermediate fields also works
  cout << "  child2" << endl;
  cout << "    member1: " << p.child2().member1() << endl;
  cout << "    member2: " << p.child2().member2() << endl;
}

int main()
{
  using namespace std;

  cout << "sizeof(Child): " << sizeof(Child) << " bytes" << endl;
  cout << "sizeof(Parent): " << sizeof(Parent) << " bytes" << endl;
  
  Child c;
  c.member1(1) // setter
   .member2(2);
  print_child(c);
  
  Parent p;
  p.child1.member1(3)   // setter for subfield
          .member2(4)
          .member2(44)  // reassignment is ok
          .member1(33); // any order is fine
  p.child2.member1(5)
          .member2(6);
  print_parent(p);
  
  p.child2(c); // call setter using another instance of the type
  print_parent(p);
  
  // The assignment operator can also be used
  p.child2 = p.child1;   // This works
  print_parent(p);

  p.child2.member2 = 7;
  p.child2 = p.child1(); // So does this
  p.child1 = c;
  p.child2.member1 = 5;
  print_parent(p);  
  
  c = p.child2;
  print_child(c);  

  Child c2;
  print_child(c2); 

  c2.member1 = c.member1;
  c2.member2(c.member2);
  print_child(c2);
  
  c2 = c;
  print_child(c2);
  
  Child c3(c);
  print_child(c3);
  
  Parent p2;
  print_parent(p2);
  
  p2 = p;
  print_parent(p2);

  Parent p3(p);
  print_parent(p3);

  p3.child1 = p.child1;
  p3.child2 = p.child1;
  print_parent(p3);
  
  Child c4(p.child2);
  print_child(c4);
  
  return 0;
}
