#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include "list.hpp"

namespace beshimow
{
  using IntList = List<int>;

  int run()
  {
    std::map<std::string, IntList> data;
    std::vector<std::string> order;
    std::string name;

    while (std::cin >> name)
    {
      std::string token;
      std::getline(std::cin, token);
      std::istringstream iss(token);

      if (data.find(name) == data.end())
      {
        order.push_back(name);
      }

      IntList& list = data[name];

      int value;
      while (iss >> value)
      {
        list.pushBack(value);
      }
    }

    if (data.empty())
    {
      std::cout << 0 << std::endl;
      return 0;
    }

    for (std::size_t i = 0; i < order.size(); ++i)
    {
      if (i) std::cout << ' ';
      std::cout << order[i];
    }
    std::cout << std::endl;

    std::vector<std::vector<int>> levels;
    std::size_t idx = 0;

    while (true)
    {
      bool hasAtLevel = false;
      std::vector<int> row;
      for (const auto& n : order)
      {
        const IntList& lst = data.at(n);
        auto it = lst.begin();
        std::size_t i = 0;
        while (i < idx && it != lst.end())
        {
          ++it;
          ++i;
        }
        if (it != lst.end())
        {
          row.push_back(*it);
          hasAtLevel = true;
        }
      }

      if (!hasAtLevel) break;

      for (std::size_t j = 0; j < row.size(); ++j)
      {
        if (j) std::cout << ' ';
        std::cout << row[j];
      }
      std::cout << std::endl;
      levels.push_back(std::move(row));
      ++idx;
    }

    if (levels.empty())
    {
      std::cerr << "Cannot calculate sums" << std::endl;
      return 1;
    }

    for (std::size_t j = 0; j < levels.size(); ++j)
    {
      long long sum = 0;
      for (int v : levels[j]) sum += v;
      if (j) std::cout << ' ';
      std::cout << sum;
    }
    std::cout << std::endl;

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
