#pragma once

template <typename T>
class Node {
  public:
  T value;
  Node* prevN;
  Node* nextN;
  Node(const T& el)
      : value{el}, prevN{nullptr}, nextN{nullptr} {}
};
