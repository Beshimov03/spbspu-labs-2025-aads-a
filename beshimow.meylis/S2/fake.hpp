#ifndef BESHIMOW_FAKE_HPP
#define BESHIMOW_FAKE_HPP

#include <cstddef>
#include <iterator>
#include <vector>

namespace beshimow
{
  template <typename T>
  class FakeContainer
  {
  public:
    class Iterator
    {
    public:
      using iterator_category = std::forward_iterator_tag;
      using value_type = T;
      using difference_type = std::ptrdiff_t;
      using pointer = T*;
      using reference = T&;

      Iterator(pointer ptr) : ptr_(ptr) {}

      reference operator*() const { return *ptr_; }
      pointer operator->() const { return ptr_; }

      Iterator& operator++()
      {
        ++ptr_;
        return *this;
      }

      Iterator operator++(int)
      {
        Iterator tmp = *this;
        ++ptr_;
        return tmp;
      }

      bool operator==(const Iterator& other) const { return ptr_ == other.ptr_; }
      bool operator!=(const Iterator& other) const { return ptr_ != other.ptr_; }

    private:
      pointer ptr_;
    };

    FakeContainer() = default;

    void pushBack(const T& value)
    {
      data_.push_back(value);
    }

    std::size_t size() const
    {
      return data_.size();
    }

    bool empty() const
    {
      return data_.empty();
    }

    Iterator begin()
    {
      return Iterator(data_.data());
    }

    Iterator end()
    {
      return Iterator(data_.data() + data_.size());
    }

  private:
    std::vector<T> data_;
  };
}

#endif
