#include <generated/Struct2.hpp>
#include <iostream>

void print_struct1(const Struct1 &s) {
  using namespace std;
  cout << "Struct1" << endl;
  cout << "  member1: " << int(s.member1()) << endl;
  cout << "  member2: size=" << num_bytes_in(s.member2) << "/"
       << num_bytes_allocated_for(s.member2) << endl;
  for (int i=0; i<num_bytes_in(s.member2); i++) {
    cout << "    " << int(s.member2[i]) << endl;
  }
  cout << "  member3: " << int(s.member3()) << endl;
}

void print_struct2(const Struct2 &s) {
  using namespace std;
  cout << endl;
  print_struct1(s.child1());
  print_struct1(s.child2());
}

int main()
{
  using namespace std;

  cout << "sizeof(Struct2): " << sizeof(Struct2) << " bytes" << endl;
  cout << "sizeof(Struct1): " << sizeof(Struct1) << " bytes" << endl;
  
  Struct2 s;
  cout << "sizeof(Struct1.child1.member2): "
       << sizeof(s.child1.member2) << " bytes" << endl;
  cout << "num_bytes_allocated_for(Struct2.child1.member2): "
       << num_bytes_allocated_for(s.child1.member2)
       << " bytes" << endl;
  
  auto *s_bytes = reinterpret_cast<uint8_t*>(&s);
  for (int i=0; i<sizeof(s); i++) {
    s_bytes[i] = i;
  }
  
  s.child1.member1 = 0;
  s.child2.member1 = 0;
  print_struct2(s);

  s.child1.member1 = 1;
  print_struct2(s);

  s.child1.member1 = 2;
  print_struct2(s);

  s.child1.member1 = 3;
  print_struct2(s);

  s.child2.member1 = 4;
  print_struct2(s);

  const size_t v = tydl::num_bytes_allocated_for<Struct1>();
  
  return 0;
}
