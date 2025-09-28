#include <iostream>
#include <string>
#include "fake.hpp"

namespace beshimow
{
  int run()
  {
    FakeContainer<std::string> cont;
    std::string word;

    while (std::cin >> word)
    {
      cont.pushBack(word);
    }

    if (cont.empty())
    {
      std::cout << "Empty" << std::endl;
      return 0;
    }

    for (auto it = cont.begin(); it != cont.end(); ++it)
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
