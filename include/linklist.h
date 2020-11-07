#pragma once
#include<utility>
#include<vector>
#include<functional>
#include<iostream>
template<typename T>
struct LinkNode {
    using value_type = T;
    using linknodePtr = T*;
    T value;
    LinkNode* next;
    LinkNode(const T& value = 0, LinkNode* next = nullptr) :value(value), next(next) {}
    LinkNode(T&& value) :LinkNode(std::move(value)) {}
    explicit operator bool() {
        return next == nullptr;
    }
};
template<typename T>
class LinkList
{
    using NodePtr = LinkNode<T>*;
    using value_type = T;
private:
    NodePtr head;
public:
    LinkList() :head(new LinkNode<T>()) {}
    LinkList(const LinkList<T>& another) :LinkList() {
        NodePtr anotherListCur = (another.head)->next;
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
    friend std::ostream& operator<<(std::ostream& out, const LinkList<T>& list) {
        auto cur = *list;
        while (cur) {
            out << cur->value << ' ';
            cur = cur->next;
        }
        return out;
    }
    void visit(const std::function<void(const LinkNode<T>&)>& visitWay = [](const LinkNode<T>& node) {
        std::cout << node->value << ' ';
        }) {
        auto cur = head->next;
        while (cur) {
            visitWay(*cur);
            cur = cur->next;
        }
    }
    void addNode(const T& value) {
        NodePtr newNode = new LinkNode(value, head->next);
        newNode->next = head->next;
        head->next = newNode;
    }
    NodePtr searchNode(const T& value) {
        NodePtr cur = head->next;
        while (cur) {
            if (cur->value == value) {
                return cur;
            }
        }
        return nullptr;
    }
    //删除与给定值相等的节点
    bool deleteNode(const T& value) {
        NodePtr cur = head->next, pre = head;
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
    void deleteNodeAfter(LinkNode<T>* nodePtr) {
        auto tmp = nodePtr->next;
        nodePtr->next = tmp->next;
        delete tmp;
    }
    bool modifyNode(const T& oldValue, const T& newValue) {
        NodePtr pos = searchNode(oldValue);
        if (!pos) {}
        return false;
        pos->value = newValue;
        return true;
    }
    ~LinkList() {
        NodePtr tmp;
        while (head) {
            tmp = head->next;
            delete head;
            head = tmp;
        }
    }
    NodePtr operator*() {
        return head->next;
    }
    const NodePtr operator*()const {
        return head->next;
    }
    void sortUsingHelpArray() {
        std::vector<T> help;
        auto cur = head->next;
        while (cur) {
            help.push_back(cur->val);
            cur = cur->next;
        }
    }
    void sort(const std::function<bool(const T&, const T&)>& rule = [](const T& x1, const T& x2) {
        return x1 < x2;
        }) {
        if (!head || !head->next) {
            return;
        }
        NodePtr head1 = head->next, head2, current, p, q;
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