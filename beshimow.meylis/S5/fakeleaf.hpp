#ifndef BESHIMOW_FAKELEAF_HPP
#define BESHIMOW_FAKELEAF_HPP

#include <vector>
#include <iterator>
#include <cstddef>

namespace beshimow
{
  template <typename T>
  class FakeLeafTree
  {
  public:
    struct Node
    {
      T value;
      bool isLeaf;
      Node(const T& v, bool leaf) : value(v), isLeaf(leaf) {}
    };

    class LeafIterator
    {
    public:
      using iterator_category = std::forward_iterator_tag;
      using value_type = T;
      using difference_type = std::ptrdiff_t;
      using pointer = T*;
      using reference = T&;

      LeafIterator(typename std::vector<Node>::iterator it,
                   typename std::vector<Node>::iterator end)
        : it_(it), end_(end)
      {
        skipToLeaf();
      }

      reference operator*() { return it_->value; }
      pointer operator->() { return &(it_->value); }

      LeafIterator& operator++()
      {
        ++it_;
        skipToLeaf();
        return *this;
      }

      LeafIterator operator++(int)
      {
        LeafIterator tmp = *this;
        ++(*this);
        return tmp;
      }

      bool operator==(const LeafIterator& other) const { return it_ == other.it_; }
      bool operator!=(const LeafIterator& other) const { return it_ != other.it_; }

    private:
      typename std::vector<Node>::iterator it_;
      typename std::vector<Node>::iterator end_;

      void skipToLeaf()
      {
        while (it_ != end_ && !it_->isLeaf)
        {
          ++it_;
        }
      }
    };

    void addNode(const T& value, bool isLeaf)
    {
      nodes_.emplace_back(value, isLeaf);
    }

    LeafIterator begin()
    {
      return LeafIterator(nodes_.begin(), nodes_.end());
    }

    LeafIterator end()
    {
      return LeafIterator(nodes_.end(), nodes_.end());
    }

  private:
    std::vector<Node> nodes_;
  };
}

#endif
