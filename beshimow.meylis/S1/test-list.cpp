#include "list.hpp"

void testListPush()
{
  beshimow::List<unsigned long long> l;
  l.pushBack(1);
  l.pushBack(2);
  l.pushFront(0);

  auto it = l.begin();
  ++it;
  --it;
}
