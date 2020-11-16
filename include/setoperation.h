#pragma once
#include"linklist.h"
//算法假定链表已按一定规则递增排序
template<typename T>
LinkList<T> retainAll(const LinkList<T>& one, const LinkList<T>& theOther) {
    LinkList<T>result;
    auto thisCur = *one, anotherCur = *theOther;
    while (thisCur && anotherCur) {
        if (thisCur->value == anotherCur->value) {
            result.addNode(thisCur->value);
            thisCur = thisCur->next;
            anotherCur = anotherCur->next;
        }
        else if (thisCur->value < anotherCur->value) {
            thisCur = thisCur->next;
        }
        else {
            anotherCur = anotherCur->next;
        }
    }
    return result;
}
//算法假定链表已按一定规则递增排序,求两集合的交集
template<typename T>
void addAll(LinkList<T>& one, const LinkList<T>& theOther) {
    one = addAllCopy(one, theOther);
}
//不改变源对象返回新集合的版本
template<typename T>
LinkList<T> addAllCopy(const LinkList<T>& one, const LinkList<T>& theOther) {
    LinkList<T>result;
    auto thisCur = *one, anotherCur = *theOther;
    while (thisCur && anotherCur) {
        if (thisCur->value == anotherCur->value) {
            result.addNode(thisCur->value);
            thisCur = thisCur->next;
            anotherCur = anotherCur->next;
        }
        else if (thisCur->value < anotherCur->value) {
            result.addNode(thisCur->value);
            thisCur = thisCur->next;
        }
        else {
            result.addNode(anotherCur->value);
            anotherCur = anotherCur->next;
        }
    }
    while (thisCur) {
        result.addNode(anotherCur->value);
        thisCur = thisCur->next;
    }
    while (anotherCur) {
        result.addNode(anotherCur->value);
        anotherCur = anotherCur->next;
    }
    return result;
}
//算法假定链表已按一定规则递增排序,将source中与selectSet相同的元素删除
template<typename T>
void removeAll(LinkList<T>& source, const LinkList<T>& selectSet) {
    auto sourceCur = *source, selectCur = *selectSet, pre = source.getHead();
    while (selectCur)
    {
        while (sourceCur) {
            if (sourceCur->value == selectCur->value) {
                source.deleteNodeAfter(pre);
                sourceCur = pre->next;
            }
            else {
                pre = sourceCur;
                sourceCur = sourceCur->next;
            }
        }
        pre = source.getHead();
        sourceCur = *source;
        selectCur = selectCur->next;
    }

}
//不改变源对象返回新集合的版本
template<typename T>
LinkList<T> removeAllCopy(const LinkList<T>& source, const LinkList<T>& selectSet) {
    auto result = source;
    removeAll(result, selectSet);
    return result;
}
//求集合的补集
template<typename T>
LinkList<T> calculateComplement(const LinkList<T>& source, const LinkList<T>& selectSet) {
    LinkList<T> result = selectSet;
    removeAll(result, source);
    return result;
}