#include "fakeleaf.hpp"
#include <cassert>
#include <string>

void testFakeLeaf()
{
  beshimow::FakeLeafTree<std::string> tree;
  tree.addNode("root", false);
  tree.addNode("a", true);
  tree.addNode("b", false);
  tree.addNode("c", true);

  auto it = tree.begin();
  assert(*it == "a");
  ++it;
  assert(*it == "c");
  ++it;
  assert(it == tree.end());
}
