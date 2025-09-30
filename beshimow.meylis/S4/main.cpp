#include <iostream>
#include <string>
#include "fakeleaf.hpp"

namespace beshimow
{
  int run()
  {
    FakeLeafTree<std::string> tree;

    std::string name;
    while (std::cin >> name)
    {
      bool isLeaf;
      std::cin >> isLeaf;
      tree.addNode(name, isLeaf);
    }

    for (auto it = tree.begin(); it != tree.end(); ++it)
    {
      std::cout << *it << std::endl;
    }

    return 0;
  }
}

int main()
{
  try
  {
    return beshimow::run();
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
