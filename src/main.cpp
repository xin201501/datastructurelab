#include<iostream>
#include"../include/calculatestudentscore.h"
#include"../include/setoperation.h"
using std::cin;
using std::endl;
using std::cout;
int main(int argc, char const* argv[]) {
    //实验一测试代码
    StudentScore scores = { 20,80,70,40,50,60,70 };
    cout << scores.getMaxGrade() << " " << scores.getMinGrade() << " " << scores.getAverage() << endl;
    scores.sort();
    scores.displayAllScores();
    cout << endl;
    //实验二测试代码
    LinkList<int> l1{ 20,42,10,14,25,36,50 };
    cout << l1 << endl;
    LinkList<int> l2{ 10,50,25,70 };
    cout << l2 << endl;
    l1.sort();
    l2.sort();
    cout << "l1" << l1 << endl << "l2" << l2 << endl;
    cout << removeAllCopy(l1, l2) << endl;
    // cout << l1 << endl;
    // l1.addNode(25);
    // cout << l1 << endl;
    // l1.deleteNode(25);
    // cout << l1 << endl;
    // cout << calculateComplement(l1, l2);
    addAll(l1, l2);
    cout << l1 << ' ' << l1.size() << endl;
    cin >> l1;
    cout << l1;
}