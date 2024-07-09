/**
 * Demo app for Ex4
 */
#include <iostream>
#include <string>
using namespace std;

#include "Complex.hpp"
#include "node.hpp"
#include "tree.hpp"

int main()
{

    Node<double> root_node = Node<double>(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double> n1 = Node<double>(1.2);
    Node<double> n2 = Node<double>(1.3);
    Node<double> n3 = Node<double>(1.4);
    Node<double> n4 = Node<double>(1.5);
    Node<double> n5 = Node<double>(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */

    cout << "Pre order:" << endl;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << " ";
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl;

    cout << "Post order:" << endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << node->get_value() << " ";
    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1
    cout << endl;

    cout << "In order:" << endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << node->get_value() << " ";
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3
    cout << endl;

    cout << "BFS:" << endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        cout << node->get_value() << " ";
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;

    // DFS iterator
    cout << "DFS:" << endl;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        cout << node->get_value() << " ";
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl;

    cout << tree; // Should print the graph using GUI.

    // Heap iterator
    cout << "Heap:" << endl;
    Tree<double> heap_tree = tree.myHeap();

    cout << heap_tree; // Should print the graph using GUI.
    for (auto node = heap_tree.begin_bfs_scan(); node != heap_tree.end_bfs_scan(); ++node)
    {
        cout << node->get_value() << " ";
    } // prints: 1.6, 1.5, 1.3, 1.4, 1.2, 1.1

    cout << endl;

    

    cout << "For range loop:" << endl;
    for (auto node : tree)
    {
        cout << node.get_value() << " ";
    } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;
    // cout << tree; // Should print the graph using GUI.

    Tree<double, 3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    cout << three_ary_tree; // Should print the graph using GUI.
    cout << endl
         << "Three ary tree:" << endl;
    for (auto node = three_ary_tree.begin_pre_order(); node != three_ary_tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << endl;
    } // should print 1.1, 1.2, 1.5, 1.3, 1.6, 1.4
    // The tree should look like:
    /**
     *       root = 1.1
     *     /      |     \
     *    1.2    1.3    1.4
     *   /        |
     *  1.5      1.6
     */

    Node<Complex> root_node_complex = Node<Complex>(Complex(1, 1));
    Tree<Complex, 4> complex_tree; // Tree that contains complex numbers.
    complex_tree.add_root(root_node_complex);

    Node<Complex> n1_complex = Node<Complex>(Complex(2, 2));
    Node<Complex> n2_complex = Node<Complex>(Complex(3, 3));
    Node<Complex> n3_complex = Node<Complex>(Complex(4, 4));
    Node<Complex> n4_complex = Node<Complex>(Complex(5, 5));
    Node<Complex> n5_complex = Node<Complex>(Complex(6, 6));
    Node<Complex> n6_complex = Node<Complex>(Complex(7, 7));
    Node<Complex> n7_complex = Node<Complex>(Complex(8, 8));
    Node<Complex> n8_complex = Node<Complex>(Complex(9, 9));
    Node<Complex> n9_complex = Node<Complex>(Complex(10, 10));

    complex_tree.add_sub_node(root_node_complex, n1_complex);
    complex_tree.add_sub_node(root_node_complex, n7_complex);
    complex_tree.add_sub_node(n1_complex, n2_complex);
    complex_tree.add_sub_node(n1_complex, n3_complex);
    complex_tree.add_sub_node(root_node_complex, n4_complex);
    complex_tree.add_sub_node(n4_complex, n5_complex);
    complex_tree.add_sub_node(n4_complex, n6_complex);
    complex_tree.add_sub_node(n4_complex, n8_complex);
    complex_tree.add_sub_node(n4_complex, n9_complex);

    cout << complex_tree; // Should print the graph using GUI.
    cout << endl
         << "Complex tree:" << endl;
    cout << "Pre order:" << endl;
    for (auto node = complex_tree.begin_pre_order(); node != complex_tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << " ";
    } // should print 1+1i, 2+2i, 3+3i, 4+4i 8+8i, 5+5i, 6+6i, 7+7i, 9+9i, 10+10i
    cout << endl;

    cout << "Post order:" << endl;
    for (auto node = complex_tree.begin_post_order(); node != complex_tree.end_post_order(); ++node)
    {
        cout << node->get_value() << " ";
    } // should print 2+2i, 3+3i, 1+1i, 5+5i, 6+6i, 8+8i, 9+9i, 10+10i, 4+4i, 7+7i
    cout << endl;

    cout << "In order:" << endl;
    for (auto node = complex_tree.begin_in_order(); node != complex_tree.end_in_order(); ++node)
    {
        cout << node->get_value() << " ";
    } // should print 2+2i, 1+1i, 3+3i, 5+5i, 4+4i, 6+6i, 7+7i, 8+8i, 9+9i, 10+10i

    cout << endl
         << "BFS:" << endl;

    for (auto node = complex_tree.begin_bfs_scan(); node != complex_tree.end_bfs_scan(); ++node)
    {
        cout << node->get_value() << " ";
    } // should print 1+1i, 2+2i, 7+7i, 3+3i, 4+4i, 5+5i, 6+6i, 8+8i, 9+9i, 10+10i

    cout << endl
         << "DFS:" << endl;

    for (auto node = complex_tree.begin_dfs_scan(); node != complex_tree.end_dfs_scan(); ++node)
    {
        cout << node->get_value() << " ";
    } // should print 1+1i, 2+2i, 3+3i, 4+4i, 5+5i, 6+6i, 7+7i, 8+8i, 9+9i, 10+10i

    cout << endl;

    cout << "For range loop:" << endl;

    for (auto node : complex_tree)
    {
        cout << node.get_value() << " ";
    } // should print 1+1i, 2+2i, 7+7i, 3+3i, 4+4i, 5+5i, 6+6i, 8+8i, 9+9i, 10+10i

    cout << endl;

    
    // a big tree with 50 nodes
    Tree<int, 5> big_tree;
    vector<Node<int>> nodes;
    for (int i = 0; i <= 30; i++)
    {
        Node<int> n = Node<int>(i);
        nodes.push_back(n);
    }
    big_tree.add_root(nodes[0]);
    big_tree.add_sub_node(nodes[0], nodes[1]);
    big_tree.add_sub_node(nodes[0], nodes[2]);
    big_tree.add_sub_node(nodes[0], nodes[3]);
    big_tree.add_sub_node(nodes[0], nodes[4]);
    big_tree.add_sub_node(nodes[1], nodes[5]);
    big_tree.add_sub_node(nodes[1], nodes[6]);
    big_tree.add_sub_node(nodes[2], nodes[7]);
    big_tree.add_sub_node(nodes[2], nodes[8]);
    big_tree.add_sub_node(nodes[3], nodes[9]);
    big_tree.add_sub_node(nodes[3], nodes[10]);
    big_tree.add_sub_node(nodes[4], nodes[11]);
    big_tree.add_sub_node(nodes[4], nodes[12]);
    big_tree.add_sub_node(nodes[4], nodes[13]);
    big_tree.add_sub_node(nodes[4], nodes[14]);
    big_tree.add_sub_node(nodes[5], nodes[15]);
    big_tree.add_sub_node(nodes[5], nodes[16]);
    big_tree.add_sub_node(nodes[6], nodes[17]);
    big_tree.add_sub_node(nodes[6], nodes[18]);
    big_tree.add_sub_node(nodes[7], nodes[19]);
    big_tree.add_sub_node(nodes[7], nodes[20]);
    big_tree.add_sub_node(nodes[7], nodes[21]);
    big_tree.add_sub_node(nodes[7], nodes[22]);
    big_tree.add_sub_node(nodes[8], nodes[23]);
    big_tree.add_sub_node(nodes[9], nodes[24]);
    big_tree.add_sub_node(nodes[9], nodes[25]);
    big_tree.add_sub_node(nodes[10], nodes[26]);
    big_tree.add_sub_node(nodes[10], nodes[28]);
    big_tree.add_sub_node(nodes[11], nodes[30]);
    big_tree.add_sub_node(nodes[26], nodes[29]);
    big_tree.add_sub_node(nodes[29], nodes[27]);

    cout << big_tree; // Should print the graph using GUI.

    return 0;
}
