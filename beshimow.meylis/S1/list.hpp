#ifndef BESHIMOW_LIST_HPP
#define BESHIMOW_LIST_HPP

#include <cstddef>
#include <iterator>
#include <utility>

namespace beshimow
{
  template <typename T>
  class List
  {
  private:
    struct Node
    {
      T value;
      Node* next;
      Node* prev;
      Node(const T& v, Node* p, Node* n) : value(v), next(n), prev(p) {}
    };

    Node* head_;
    Node* tail_;
    std::size_t size_;

  public:
    class Iterator
    {
    public:
      using iterator_category = std::bidirectional_iterator_tag;
      using value_type = T;
      using difference_type = std::ptrdiff_t;
      using pointer = T*;
      using reference = T&;

      explicit Iterator(Node* ptr) : node_(ptr) {}

      reference operator*() const { return node_->value; }
      pointer operator->() const { return &node_->value; }

      Iterator& operator++()
      {
        node_ = node_->next;
        return *this;
      }

      Iterator operator++(int)
      {
        Iterator tmp = *this;
        node_ = node_->next;
        return tmp;
      }

      Iterator& operator--()
      {
        node_ = node_->prev;
        return *this;
      }

      Iterator operator--(int)
      {
        Iterator tmp = *this;
        node_ = node_->prev;
        return tmp;
      }

      bool operator==(const Iterator& other) const { return node_ == other.node_; }
      bool operator!=(const Iterator& other) const { return node_ != other.node_; }

    private:
      Node* node_;
      friend class List<T>;
    };

    List() : head_(nullptr), tail_(nullptr), size_(0) {}

    ~List()
    {
      Node* cur = head_;
      while (cur)
      {
        Node* tmp = cur->next;
        delete cur;
        cur = tmp;
      }
    }

    List(const List&) = delete;
    List& operator=(const List&) = delete;

    List(List&& other) noexcept
      : head_(other.head_), tail_(other.tail_), size_(other.size_)
    {
      other.head_ = nullptr;
      other.tail_ = nullptr;
      other.size_ = 0;
    }

    List& operator=(List&& other) noexcept
    {
      if (this != &other)
      {
        Node* cur = head_;
        while (cur)
        {
          Node* tmp = cur->next;
          delete cur;
          cur = tmp;
        }

        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;

        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
      }
      return *this;
    }

    void pushBack(const T& value)
    {
      Node* node = new Node(value, tail_, nullptr);
      if (!head_)
      {
        head_ = tail_ = node;
      }
      else
      {
        tail_->next = node;
        tail_ = node;
      }
      ++size_;
    }

    void pushFront(const T& value)
    {
      Node* node = new Node(value, nullptr, head_);
      if (!head_)
      {
        head_ = tail_ = node;
      }
      else
      {
        head_->prev = node;
        head_ = node;
      }
      ++size_;
    }

    bool empty() const { return size_ == 0; }
    std::size_t size() const { return size_; }

    Iterator begin() const { return Iterator(head_); }
    Iterator end() const { return Iterator(nullptr); }

    Iterator rbegin() const { return Iterator(tail_); }
    Iterator rend() const { return Iterator(nullptr); }
  };
}

#endif
