#pragma once
#include "linklist.h"
#include <initializer_list>
template <typename T> class Stack : protected LinkList<T> {
public:
  using LinkNodePtr = typename LinkList<T>::LinkNodePtr;
  using LinkNodeReference = typename LinkList<T>::LinkNodeReference;
  using value_type = typename LinkList<T>::value_type;
  Stack() = default;
  Stack(const Stack &another) {
    LinkNodePtr anotherListCur = (another.head)->next;
    while (anotherListCur) {
      addNode(anotherListCur->value);
      anotherListCur = anotherListCur->next;
    }
  }
  Stack(Stack &&another) noexcept : LinkList<T>(another.head) {
    another.head = nullptr;
  }
  Stack(std::initializer_list<T> datas) {
    for (const auto &x : datas) {
      push(x);
    }
  }
  friend std::ostream &operator<<(std::ostream &os, const Stack &stack) {
    auto cur = *stack;
    os << "Stack(top->bottom){ ";
    while (cur) {
      os << cur->value << ' ';
      cur = cur->next;
    }
    return os << '}';
  }
  //通过控制台等输入值动态添加元素
  friend std::istream &operator>>(std::istream &is, Stack &stack) {
    T value;
    is >> value;
    if (!is) {
      //输入数据类型不匹配,不进行任何操作,重置流为有效状态退出
      is.clear();
    } else {
      stack.addNode(value);
    }
    return is;
  }
  void push(const T &value) { this->addNode(value); }
  void pop() { this->deleteNodeAfter(this->head); }
  T &top() { return this->head->next->value; }
  //常量版本重用了非常量函数的代码,代码内部逻辑保证了其不会被修改
  const T &top() const { return const_cast<Stack *>(*this)->top(); }
  bool isEmpty() const { return LinkList<T>::isEmpty(); }
  bool contains(const T &value) const { return LinkList<T>::contains(value); }
};