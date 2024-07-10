#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <iostream>
using namespace std;
template <typename T>
class Node
{
public:
    Node(T value) : value(value) {};
    Node(T value, vector<Node<T> *> children) : value(value), children(children) {};
    T get_value() const { return value; };
    vector<Node<T> *> &get_children() { return children; };
    void add_child(Node<T> &child) { children.push_back(&child); };
    bool operator==(const Node<T> &other) const { return value == other.value; };

private:
    T value;
    vector<Node<T> *> children;
};

#endif // NODE_HPP
