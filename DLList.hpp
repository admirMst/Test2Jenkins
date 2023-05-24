#pragma once
#include <cstddef>
#include <iostream>
#include "node.hpp"

template <typename T>
class DLList {
  private:
  Node<T>* head;
  Node<T>* tail;
  size_t size_;

  public:
  DLList() : head{nullptr}, tail{nullptr}, size_{0} {}
  DLList(const DLList& o);
  DLList(DLList&& o);
  DLList& operator=(const DLList& o);
  DLList& operator=(DLList&& o);
  ~DLList();

  class iterator;
  iterator begin() const { return iterator{head}; }
  iterator end() const { return iterator{nullptr}; }

  void print() const;
  const T& front() const { return head->value; }
  const T& back() const { return tail->value; }

  void clear();

  void remove(iterator it);
  void remove(iterator from, iterator to);

  void insert(iterator it, const T& value);
  void insert(iterator it, T&& value);

  void push_back(const T& val);
  void push_front(const T& val);
  void push_back(T&& val);
  void push_front(T&& val);

  void pop_back();
  void pop_front();

  void removeN(iterator pos, size_t n);

  void swapp() {
    tail->nextN = head->nextN;
    head->prevN = tail->prevN;
    head->nextN->prevN = tail;
    head->nextN = nullptr;
    tail->prevN->nextN = head;
    tail->prevN = nullptr;
    auto tmp = head;
    head = tail;
    tail = tmp;
  }
  size_t size() const { return size_; }
};

template <typename T>
class DLList<T>::iterator
    : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
  Node<T>* Cnode = nullptr;

  public:
  friend class DLList<T>;
  iterator() = default;
  iterator(Node<T>* CN) : Cnode{CN} {}

  T& operator*() {
    if (Cnode == nullptr) {
      std::cout << "DEREFERENCING NULLPTR\n";
      exit(1);
    }
    return Cnode->value;
  }
  T& operator->() { return Cnode->value; }

  bool operator==(const iterator& o) const { return Cnode == o.Cnode; }

  bool operator!=(const iterator& o) const { return !operator==(o); }

  iterator& operator++() {
    if (Cnode) {
      Cnode = Cnode->nextN;
    } else
      std::cout << "ITERATOR OUT OF BOUNDS\n";
    return *this;
  }

  iterator operator++(int) {
    auto oldThis = *this;
    ++(*this);
    return oldThis;
  }

  iterator& operator--() {
    if (Cnode) {
      Cnode = Cnode->prevN;
    } else
      std::cout << "ITERATOR OUT OF BOUNDS\n";
    return *this;
  }

  iterator operator--(int) {
    auto oldThis = *this;
    --(*this);
    return oldThis;
  }

  iterator operator+(const int& a) {
    for (int i = 0; i < a; i++) {
      Cnode = Cnode->nextN;
      if (Cnode == nullptr) {
        std::cout << "ITERATOR OUT OF BOUNDS\n";
        exit(1);
      }
    }
    return *this;
  }
  iterator operator-(const int& a) {
    for (int i = 0; i < a; i++) {
      Cnode = Cnode->prevN;
      if (Cnode == nullptr) {
        std::cout << "ITERATOR OUT OF BOUNDS\n";
        exit(1);
      }
    }

    return *this;
  }
};

template <typename T>
void DLList<T>::print() const {
  auto temp = head;
  while (temp != nullptr) {
    std::cout << temp->value << " ";
    temp = temp->nextN;
  }
  std::cout << std::endl;
}

template <typename T>
void DLList<T>::clear() {
  if (size_ != 0) {
    auto temp = head;
    while (temp != nullptr) {
      // std::cout << "Deleting item: " << temp->value << std::endl;
      head = temp;
      temp = temp->nextN;
      delete head;
      size_--;
    }
  }
  head = tail = nullptr;
}

// KONSTRUKTORI, DESTRUKTOR I OPERATORI = //
template <typename T>
DLList<T>::~DLList() {
  clear();
}

template <typename T>
DLList<T>::DLList(DLList&& o) : head{o.head}, tail{o.tail}, size_{o.size_} {
  o.head = nullptr;
  o.tail = nullptr;
  o.size_ = 0;
}

template <typename T>
DLList<T>::DLList(const DLList<T>& o) : head{nullptr}, tail{nullptr}, size_{0} {
  head = o.head;
  tail = o.tail;
  auto tmp = o.head;
  while (tmp != nullptr) {
    push_back(tmp->value);
    tmp = tmp->nextN;
  }
}

template <typename T>
DLList<T>& DLList<T>::operator=(const DLList<T>& o) {
  if (this != &o) {
    clear();
    for (auto tmp = o.head; tmp != nullptr; tmp = tmp->nextN) {
      push_back(tmp->value);
    }
  }
}

template <typename T>
DLList<T>& DLList<T>::operator=(DLList<T>&& o) {
  if (this != &o) {
    clear();
    head = o.head;
    tail = o.tail;
    size_ = o.size_;
    o.head = nullptr;
    o.tail = nullptr;
    o.size_ = 0;
  }
}
//          //

template <typename T>
void DLList<T>::push_back(const T& val) {
  auto newN = new Node<T>(val);
  if (size_ == 0)
    head = tail = newN;
  else {
    newN->prevN = tail;
    tail->nextN = newN;
    tail = newN;
  }
  // std::cout << "CONST T& VAL\n";
  size_++;
}

template <typename T>
void DLList<T>::push_front(const T& val) {
  auto newN = new Node<T>(val);
  if (size_ == 0)
    head = tail = newN;
  else {
    newN->nextN = head;
    head->prevN = newN;
    head = newN;
  }
  size_++;
}

template <typename T>
void DLList<T>::insert(iterator it, const T& value) {
  if (size_ == 0 || it == nullptr) {
    std::cout << "LIST IS EMPTY OR NULLPTR PASSED\n";
    return;
  }
  auto newN = new Node<T>(value);
  if (it.Cnode == head) {
    it.Cnode->prevN = newN;
    newN->nextN = it.Cnode;
    head = newN;
    std::cout << "CONST T& VAL\n";
    size_++;
    return;
  }
  newN->prevN = it.Cnode->prevN;
  newN->nextN = it.Cnode;
  it.Cnode->prevN->nextN = newN;
  it.Cnode->prevN = newN;
  size_++;
  std::cout << "CONST T& VAL\n";
}

// OVERLOADED METHODS
template <typename T>
void DLList<T>::insert(iterator it, T&& value) {
  if (size_ == 0 || it == nullptr) {
    std::cout << "LIST IS EMPTY OR NULLPTR PASSED\n";
    return;
  }
  auto newN = new Node<T>(std::move(value));
  if (it.Cnode == head) {
    head = newN;
    it.Cnode->prevN = newN;
    newN->nextN = it.Cnode;
    size_++;
    return;
  }
  newN->prevN = it.Cnode->prevN;
  newN->nextN = it.Cnode;
  it.Cnode->prevN->nextN = newN;
  it.Cnode->prevN = newN;
  size_++;
  std::cout << "T&& VAL\n";
}

template <typename T>
void DLList<T>::push_back(T&& val) {
  auto newN = new Node<T>(std::move(val));
  if (size_ == 0)
    head = tail = newN;
  else {
    newN->prevN = tail;
    tail->nextN = newN;
    tail = newN;
  }

  size_++;
}

template <typename T>
void DLList<T>::push_front(T&& val) {
  auto newN = new Node<T>(std::move(val));
  if (size_ == 0)
    head = tail = newN;
  else {
    newN->nextN = head;
    head->prevN = newN;
    head = newN;
  }
  size_++;
}
//

template <typename T>
void DLList<T>::pop_back() {
  if (size_ == 0) {
    std::cout << "LIST IS EMPTY\n";
    return;
  }
  if (size_ == 1) {
    delete tail;
    head = tail = nullptr;
    size_--;
    return;
  }
  tail = tail->prevN;
  tail->nextN->prevN = nullptr;
  delete tail->nextN;
  tail->nextN = nullptr;
  size_--;
}

template <typename T>
void DLList<T>::pop_front() {
  if (size_ == 0) {
    std::cout << "LIST IS EMPTY\n";
    return;
  }
  if (size_ == 1) {
    delete head;
    head = tail = nullptr;
    size_--;
    return;
  }
  head = head->nextN;
  delete head->prevN;
  head->prevN = nullptr;
  size_--;
}

template <typename T>
void DLList<T>::remove(iterator it) {
  if (size_ == 0 || it == nullptr) {
    std::cout << "LIST IS EMPTY OR NULLPTR PASSED\n";
    return;
  }
  if (it == begin()) {
    std::cout << "REMOVING: " << it.Cnode->value << std::endl;
    pop_front();
    return;
  }
  if (it == tail) {
    std::cout << "TAIL\n";
    std::cout << "REMOVING: " << it.Cnode->value << std::endl;
    pop_back();
    return;
  }

  std::cout << "REMOVING: " << it.Cnode->value << std::endl;
  it.Cnode->prevN->nextN = it.Cnode->nextN;
  it.Cnode->nextN->prevN = it.Cnode->prevN;
  it.Cnode->nextN = it.Cnode->prevN = nullptr;
  delete it.Cnode;
  size_--;
}

template <typename T>
void DLList<T>::remove(iterator from, iterator to) {
  if (from.Cnode == head) {
    while (from.Cnode != to.Cnode) {
      from++;
      pop_front();
    }
    return;
  }

  auto tmp = from.Cnode->prevN;
  tmp->nextN = to.Cnode;
  to.Cnode->prevN = tmp;
  while (from.Cnode->nextN != to.Cnode) {
    auto temp = from.Cnode;
    from.Cnode = from.Cnode->nextN;
    delete temp;
    size_--;
  }
}
template <typename T>
void DLList<T>::removeN(iterator pos, size_t n) {
  if (pos.Cnode == head) {
    for (int i = 1; i <= n; i++) pop_front();
    return;
  }

  auto temp = pos.Cnode->prevN;

  auto tmp1 = pos.Cnode;

  for (int i = 1; i <= n; i++) tmp1 = tmp1->nextN;
  std::cout << tmp1->value << std::endl;

  temp->nextN = tmp1;

  while (pos.Cnode != tmp1) {
    auto t2 = pos.Cnode;
    delete t2;
    pos.Cnode = pos.Cnode->nextN;
    size_--;
  }
}
