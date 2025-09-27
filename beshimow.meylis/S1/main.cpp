#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <climits>
#include "list.hpp"

namespace beshimow
{
  using IntList = List<unsigned long long>;

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

      std::string num;
      while (iss >> num)
      {
        try
        {
          size_t pos = 0;
          unsigned long long value = std::stoull(num, &pos);
          if (pos != num.size())
          {
            throw std::invalid_argument("bad number");
          }

          if (value > static_cast<unsigned long long>(LLONG_MAX))
          {
            std::cerr << "overflow" << std::endl;
            return 1;
          }

          list.pushBack(value);
        }
        catch (...)
        {
          std::cerr << "overflow" << std::endl;
          return 1;
        }
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

    std::vector<std::vector<unsigned long long>> levels;
    std::size_t idx = 0;

    while (true)
    {
      bool hasAtLevel = false;
      std::vector<unsigned long long> row;
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
      std::cout << 0 << std::endl;
      return 0;
    }

    for (std::size_t j = 0; j < levels.size(); ++j)
    {
      unsigned long long sum = 0;
      for (auto v : levels[j]) sum += v;
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
