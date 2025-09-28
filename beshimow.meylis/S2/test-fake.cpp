#include "fake.hpp"
#include <cassert>
#include <string>

void testFake()
{
  beshimow::FakeContainer<int> cont;
  cont.pushBack(1);
  cont.pushBack(2);
  cont.pushBack(3);

  auto it = cont.begin();
  assert(*it == 1);
  ++it;
  assert(*it == 2);
  ++it;
  assert(*it == 3);
  ++it;
  assert(it == cont.end());
}
