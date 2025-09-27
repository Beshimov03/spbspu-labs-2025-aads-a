#include "list.hpp"

void testListPush()
{
  beshimow::List<int> l;
  l.pushBack(1);
  l.pushBack(2);
  l.pushFront(0);
}
