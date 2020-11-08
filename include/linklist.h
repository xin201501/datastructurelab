#pragma once
#include<utility>
#include<vector>
#include<functional>
#include<iostream>
template<typename T>
struct LinkNode {
    using value_type = T;
    using LinkNodePtr = LinkNode<T>*;
    T value;
    LinkNode* next;
    LinkNode(const T& value = 0, LinkNode* next = nullptr) :value(value), next(next) {}
    LinkNode(T&& value) :LinkNode(std::move(value)) {}
    explicit operator bool() {
        return next == nullptr;
    }
};
template<typename T>
class LinkList {
public:
    using LinkNodePtr = LinkNode<T>*;
    using LinkNodeReference = LinkNode<T>&;
    using value_type = T;
private:
    LinkNodePtr head;
public:
    LinkList() :head(new LinkNode<T>()) {}
    LinkList(const LinkList<T>& another) :LinkList() {
        LinkNodePtr anotherListCur = (another.head)->next;
        while (anotherListCur) {
            addNode(anotherListCur->value);
            anotherListCur = anotherListCur->next;
        }
    }
    LinkList(LinkList<T>&& another) :head(another.head) {
        another.head = nullptr;
    }
    LinkList(std::initializer_list<T>datas) :LinkList() {
        for (const auto& x : datas) {
            addNode(x);
        }
    }
    LinkList& operator=(LinkList<T> another) {
        if (this->head != another.head) {
            auto tmp = this->head;
            this->head = another.head;
            another.head = tmp;
        }
        return *this;
    }
    LinkNodePtr operator*() {
        return head->next;
    }
    const LinkNodePtr operator*()const {
        return head->next;
    }
    LinkNodePtr getHead() {
        return head;
    }
    const LinkNodePtr getHead()const {
        return head;
    }
    ~LinkList() {
        LinkNodePtr tmp;
        while (head) {
            tmp = head->next;
            delete head;
            head = tmp;
        }
    }
    friend std::ostream& operator<<(std::ostream& out, const LinkList<T>& list) {
        auto cur = *list;
        out << "linklist{ ";
        while (cur) {
            out << cur->value << ' ';
            cur = cur->next;
        }
        return out << '}';
    }
    void visit(const std::function<void(LinkNodeReference)>& visitWay = [](const LinkNodeReference node) {
        std::cout << node->value << ' ';
        }) {
        auto cur = head->next;
        while (cur) {
            visitWay(*cur);
            cur = cur->next;
        }
    }
    void visit(const std::function<void(const LinkNodeReference)>& visitWay = [](const LinkNodeReference node) {
        std::cout << node->value << ' ';
        })const {
        //使常量复用非常量函数，只要不改变它的值即可，visitWay参数为const引用保证它不被修改
        const_cast<LinkList<T>*>(this)->visit(visitWay);
    }
    void addNode(const T& value) {
        LinkNodePtr newNode = new LinkNode(value, head->next);
        newNode->next = head->next;
        head->next = newNode;
    }
    LinkNodePtr searchNode(const T& value) {
        LinkNodePtr cur = head->next;
        while (cur) {
            if (cur->value == value) {
                return cur;
            }
        }
        return nullptr;
    }
    //删除与给定值相等的节点
    bool deleteNode(const T& value) {
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
        auto tmp = prePtr->next;
        prePtr->next = tmp->next;
        delete tmp;
    }
    bool modifyNode(const T& oldValue, const T& newValue) {
        LinkNodePtr pos = searchNode(oldValue);
        if (!pos) {
            return false;
        }
        pos->value = newValue;
        return true;
    }
    size_t size()const {
        size_t size = 0;
        visit([&size](const LinkNodeReference) {
            size++;
            });
        return size;
    }
    //算法默认从小到大排序，可传入函数对象指定
    void sort(const std::function<bool(const T&, const T&)>& rule = [](const T& x1, const T& x2) {
        return x1 < x2;
        }) {
        if (!head || !head->next) {
            return;
        }
        LinkNodePtr head1 = head->next, head2, current, p, q;
        head2 = head1->next;
        head1->next = nullptr;
        while (head2) {
            current = head2;
            head2 = head2->next;
            for (p = nullptr, q = head1;q && rule(q->value, current->value);p = q, q = q->next)
                ;
            if (q == head1) {
                head1 = current;
            }
            else {
                p->next = current;
            }
            current->next = q;
        }
        head->next = head1;
    }
};