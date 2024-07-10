#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Complex.hpp"
#include "node.hpp"
#include "tree.hpp"
#include <string>

TEST_CASE("Iterators Testing")
{
    Node<double> root_node = Node<double>(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double> n1 = Node<double>(1.2);
    Node<double> n2 = Node<double>(1.3);
    Node<double> n3 = Node<double>(1.4);
    Node<double> n4 = Node<double>(1.5);
    Node<double> n5 = Node<double>(1.6);
    Node<double> n6 = Node<double>(1.7);
    Node<double> n7 = Node<double>(1.8);
    Node<double> n8 = Node<double>(1.9);

    CHECK_NOTHROW(tree.add_sub_node(root_node, n1));
    CHECK_NOTHROW(tree.add_sub_node(root_node, n2));
    CHECK_THROWS(tree.add_sub_node(root_node, n3)); // root already has 2 children
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n2, n5);
    tree.add_sub_node(n2, n6);
    tree.add_sub_node(n3, n7);
    tree.add_sub_node(n3, n8);

    vector<Node<double>> nodes = {root_node, n1, n4, n3, n7, n8, n2, n5, n6};

    // check pre order iterator
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        Node<double> expected = nodes.front();
        CHECK(*node == expected);
        nodes.erase(nodes.begin());
    }

    // check post order iterator
    nodes = {n4, n7, n8, n3, n1, n5, n6, n2, root_node};

    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        Node<double> expected = nodes.front();
        CHECK(*node == expected);
        nodes.erase(nodes.begin());
    }

    // check in order iterator
    nodes = {n4, n1, n7, n3, n8, root_node, n5, n2, n6};

    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        Node<double> expected = nodes.front();
        CHECK(*node == expected);
        nodes.erase(nodes.begin());
    }

    // check BFS iterator
    nodes = {root_node, n1, n2, n4, n3, n5, n6, n7, n8};

    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        Node<double> expected = nodes.front();
        CHECK(*node == expected);
        nodes.erase(nodes.begin());
    }

    // check DFS iterator

    nodes = {root_node, n1, n4, n3, n7, n8, n2, n5, n6};

    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        Node<double> expected = nodes.front();
        CHECK(*node == expected);
        nodes.erase(nodes.begin());
    }
}

TEST_CASE("Template Testings") // Testing Template
{
    Node<Complex> root_node_complex = Node<Complex>(Complex(1, 1));
    Tree<Complex, 4> complex_tree; // Tree that contains complex numbers.
    complex_tree.add_root(root_node_complex);
    int value = 2;

    Node<Complex> n1_complex = Node<Complex>(Complex(value, value));
    value++;
    Node<Complex> n2_complex = Node<Complex>(Complex(value, value));value++;
    Node<Complex> n3_complex = Node<Complex>(Complex(value, value));value++;
    Node<Complex> n4_complex = Node<Complex>(Complex(value, value));value++;
    Node<Complex> n5_complex = Node<Complex>(Complex(value, value));value++;
    Node<Complex> n6_complex = Node<Complex>(Complex(value, value));value++;
    Node<Complex> n7_complex = Node<Complex>(Complex(value, value));value++;
    Node<Complex> n8_complex = Node<Complex>(Complex(value, value));value++;
    Node<Complex> n9_complex = Node<Complex>(Complex(value, value));value++;
    Node<Complex> n10_complex = Node<Complex>(Complex(value, value));value++;
    Node<Complex> n11_complex = Node<Complex>(Complex(value, value));value++;

    complex_tree.add_sub_node(root_node_complex, n1_complex);
    complex_tree.add_sub_node(root_node_complex, n7_complex);
    complex_tree.add_sub_node(n1_complex, n2_complex);
    complex_tree.add_sub_node(n1_complex, n3_complex);
    complex_tree.add_sub_node(root_node_complex, n4_complex);
    complex_tree.add_sub_node(n4_complex, n5_complex);
    complex_tree.add_sub_node(n4_complex, n6_complex);
    complex_tree.add_sub_node(n4_complex, n8_complex);
    complex_tree.add_sub_node(n4_complex, n9_complex);

    CHECK_THROWS(complex_tree.add_sub_node(n10_complex, n11_complex)); // n10_complex is not in the tree

    // preorder iterator for K larger than 2 should be the same as DFS

    vector<Node<Complex>> nodes = {root_node_complex, n1_complex, n2_complex, n3_complex, n7_complex, n4_complex, n5_complex, n6_complex, n8_complex, n9_complex};
    // check pre order iterator
    for (auto node = complex_tree.begin_pre_order(); node != complex_tree.end_pre_order(); ++node)
    {

        Node<Complex> expected = nodes.front();
        CHECK(*node == expected);
        nodes.erase(nodes.begin());
    }

    // check post order iterator
    nodes = {root_node_complex, n1_complex, n2_complex, n3_complex, n7_complex, n4_complex, n5_complex, n6_complex, n8_complex, n9_complex};

    for (auto node = complex_tree.begin_post_order(); node != complex_tree.end_post_order(); ++node)
    {
        Node<Complex> expected = nodes.front();
        CHECK(*node == expected);
        nodes.erase(nodes.begin());
    }

    Tree<string, 2> string_tree; // Binary tree that contains strings.
    Node<string> root_node_string = Node<string>("root");
    string_tree.add_root(root_node_string);
    Node<string> n1_string = Node<string>("n1");
    Node<string> n2_string = Node<string>("n2");
    Node<string> n3_string = Node<string>("n3");
    Node<string> n4_string = Node<string>("n4");
    Node<string> n5_string = Node<string>("n5");
    Node<string> n6_string = Node<string>("n6");
    Node<string> n7_string = Node<string>("n7");
    Node<string> n8_string = Node<string>("n8");

    string_tree.add_sub_node(root_node_string, n1_string);
    string_tree.add_sub_node(root_node_string, n2_string);
    string_tree.add_sub_node(n1_string, n3_string);
    string_tree.add_sub_node(n2_string, n4_string);
    string_tree.add_sub_node(n2_string, n5_string);
    string_tree.add_sub_node(n4_string, n6_string);
    string_tree.add_sub_node(n4_string, n7_string);
    string_tree.add_sub_node(n7_string, n8_string);

    vector<Node<string>> nodes_string = {root_node_string, n1_string, n3_string, n2_string, n4_string, n6_string, n7_string, n8_string, n5_string};

    // check pre order iterator
    for (auto node = string_tree.begin_pre_order(); node != string_tree.end_pre_order(); ++node)
    {
        Node<string> expected = nodes_string.front();
        CHECK(*node == expected);
        nodes_string.erase(nodes_string.begin());
    }
}

TEST_CASE("One Child tree nodes")
{
    Tree<int, 1> tree;

    Node<int> root = Node<int>(1);
    tree.add_root(root);
    Node<int> n1 = Node<int>(2);
    Node<int> n2 = Node<int>(3);
    Node<int> n3 = Node<int>(4);
    Node<int> n4 = Node<int>(5);
    Node<int> n5 = Node<int>(6);

    tree.add_sub_node(root, n1);
    tree.add_sub_node(n1, n2);
    tree.add_sub_node(n2, n3);
    tree.add_sub_node(n3, n4);
    tree.add_sub_node(n4, n5);

    vector<Node<int>> nodes = {root, n1, n2, n3, n4, n5};

    // check pre order iterator
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        Node<int> expected = nodes.front();
        CHECK(*node == expected);
        nodes.erase(nodes.begin());
    }

    // check post order iterator
    nodes = {n5, n4, n3, n2, n1, root};

    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        Node<int> expected = nodes.front();
        CHECK(*node == expected);
        nodes.erase(nodes.begin());
    }

    // check in order iterator
    nodes = {n5, n4, n3, n2, n1, root};

    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        Node<int> expected = nodes.front();
        CHECK(*node == expected);
        nodes.erase(nodes.begin());
    }

    cout << tree << endl;
}
