#pragma once
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

template <typename T> struct LinkNode {
  using value_type = T;
  using LinkNodePtr = LinkNode *;
  T value;
  LinkNode *next;
  LinkNode(const T &value = {}, LinkNode *next = nullptr)
      : value(value), next(next) {}
  LinkNode(T &&value, LinkNode *next = nullptr) noexcept
      : value(std::move(value)), next(next) {}
  //!(LinkNode对象)写法可判断节点是否为尾节点
  explicit operator bool() { return next == nullptr; }
};
template <typename T> class LinkList {
public:
  using LinkNodePtr = LinkNode<T> *;
  using LinkNodeReference = LinkNode<T> &;
  using value_type = T;

protected:
  LinkNodePtr head;

public:
  //创建空链表
  LinkList(LinkNodePtr headLocation = new LinkNode<T>()) : head(headLocation) {}
  //拷贝构造链表
  LinkList(const LinkList<T> &another) : LinkList() {
    LinkNodePtr anotherListCur = (another.head)->next;
    while (anotherListCur) {
      addNode(anotherListCur->value);
      anotherListCur = anotherListCur->next;
    }
  }
  LinkList(LinkList<T> &&another) noexcept : head(another.head) {
    another.head = nullptr;
  }
  //用花括号包围的初始化列表初始化链表
  LinkList(std::initializer_list<T> datas) : LinkList() {
    for (const auto &x : datas) {
      addNode(x);
    }
  }
  LinkList &operator=(LinkList<T> another) {
    if (this->head != another.head) {
      auto tmp = this->head;
      this->head = another.head;
      another.head = tmp;
    }
    return *this;
  }
  //返回链表首个有效元素的指针
  LinkNodePtr operator*() { return head->next; }
  const LinkNodePtr operator*() const { return head->next; }
  LinkNodePtr getHead() { return head; }
  const LinkNodePtr getHead() const { return head; }
  ~LinkList() {
    LinkNodePtr tmp;
    while (head) {
      tmp = head->next;
      delete head;
      head = tmp;
    }
  }
  //打印整个链表的值
  friend std::ostream &operator<<(std::ostream &os, const LinkList &list) {
    auto cur = *list;
    os << "linklist{ ";
    while (cur) {
      os << cur->value << ' ';
      cur = cur->next;
    }
    return os << '}';
  }
  //通过控制台等输入值动态添加元素
  friend std::istream &operator>>(std::istream &is, LinkList &list) {
    T value;
    is >> value;
    if (!is) {
      //输入数据类型不匹配,不进行任何操作,重置流为有效状态退出
      is.clear();
    } else {
      list.addNode(value);
    }
    return is;
  }
  //遍历链表元素,接受以节点类型引用为参数的可调用对象
  void visit(const std::function<void(LinkNodeReference)> &visitWay =
                 [](const LinkNodeReference node) {
                   std::cout << node->value << ' ';
                 }) {
    auto cur = head->next;
    while (cur) {
      visitWay(*cur);
      cur = cur->next;
    }
  }
  void visit(const std::function<void(const LinkNodeReference)> &visitWay =
                 [](const LinkNodeReference node) {
                   std::cout << node->value << ' ';
                 }) const {
    //使常量复用非常量函数,只要不改变它的值即可,visitWay参数为const引用保证它不被修改
    const_cast<LinkList *>(this)->visit(visitWay);
  }
  bool isEmpty() const { return !head->next; }
  void addNode(const T &value) {
    LinkNodePtr newNode = new LinkNode<T>(value, head->next);
    newNode->next = head->next;
    head->next = newNode;
  }
  LinkNodePtr searchNode(const T &value) {
    LinkNodePtr cur = head->next;
    while (cur) {
      if (cur->value == value) {
        return cur;
      }
      cur = cur->next;
    }
    return nullptr;
  }
  const LinkNodePtr searchNode(const T &value) const {
    return const_cast<LinkList *>(this)->searchNode(value);
  }
  bool contains(const T &value) const { return searchNode(value) != nullptr; }
  //删除与给定值相等的节点
  bool deleteNode(const T &value) {
    LinkNodePtr cur = head->next, pre = head;
    while (cur && cur->value != value) {
      cur = cur->next;
      pre = pre->next;
    }
    if (!cur) {
      return false;
    }
    pre->next = cur->next;
    delete cur;
    return true;
  }
  //算法接受被删除元素之前节点的指针
  void deleteNodeAfter(LinkNodePtr prePtr) {
    if (!prePtr || !prePtr->next) {
      return;
    }
    auto tmp = prePtr->next;
    prePtr->next = tmp->next;
    delete tmp;
  }
  bool modifyNode(const T &oldValue, const T &newValue) {
    LinkNodePtr pos = searchNode(oldValue);
    if (!pos) {
      return false;
    }
    pos->value = newValue;
    return true;
  }
  size_t size() const {
    size_t size = 0;
    visit([&size](const LinkNodeReference) { size++; });
    return size;
  }
  //插入排序,可传入可调用对象指定排序规则,默认递增排序
  void sort(const std::function<bool(const T &, const T &)> &rule =
                [](const T &x1, const T &x2) { return x1 < x2; }) {
    if (!head || !head->next) {
      return;
    }
    LinkNodePtr head1 = head->next, head2, current, p, q;
    head2 = head1->next;
    head1->next = nullptr;
    while (head2) {
      current = head2;
      head2 = head2->next;
      for (p = nullptr, q = head1; q && rule(q->value, current->value);
           p = q, q = q->next)
        ;
      if (q == head1) {
        head1 = current;
      } else {
        p->next = current;
      }
      current->next = q;
    }
    head->next = head1;
  }
};