#include <queue>
#include <stack>
#include <algorithm>
#include <functional>
#include <iostream>
using namespace std;

#include "node.hpp"
#include "treeGUI.hpp"

enum class IterationOrder
{
    PreOrder,
    PostOrder,
    InOrder,
    BFS,
    DFS,
    Heap
};

template <typename T, size_t K = 2>
class Tree
{
public:
    class Iterator
    {
    private:
        Node<T> *current;
        stack<Node<T> *> s;
        queue<Node<T> *> q;
        IterationOrder order;

        void push_left(Node<T> *node)
        {
            while (node != nullptr)
            {
                s.push(node);
                node = node->get_children().size() > 0 ? node->get_children()[0] : nullptr;
            }
        }

        auto pre_order_next()
        {
            if (current->get_children().size() > 0)
            {
                for (int i = current->get_children().size() - 1; i >= 0; i--)
                {
                    s.push(current->get_children()[i]);
                }
            }
            if (s.empty())
            {
                current = nullptr;
            }
            else
            {
                current = s.top();
                s.pop();
            }
            return this;
        };

        auto init_post_order()
        {
            stack<Node<T> *> temp_stack;
            if (current != nullptr)
            {
                temp_stack.push(current);

                while (!temp_stack.empty())
                {
                    Node<T> *node = temp_stack.top();
                    temp_stack.pop();
                    s.push(node);

                    for (auto child : node->get_children())
                    {
                        temp_stack.push(child);
                    }
                }

                current = s.top();
                s.pop();
            }
        };

        auto post_order_next()
        {
            if (!s.empty())
            {
                current = s.top();
                s.pop();
            }
            else
            {
                current = nullptr;
            }
            return this;
        };

        auto init_in_order()
        {
            if (current != nullptr)
            {
                push_left(current);
                current = s.top();
                s.pop();
            }
        };

        auto in_order_next()
        {
            if (current->get_children().size() > 1)
            {
                push_left(current->get_children()[1]);
            }
            if (s.empty())
            {
                current = nullptr;
            }
            else
            {
                current = s.top();
                s.pop();
            }
            return this;
        };

        auto init_bfs_scan() {
            // no need to do anything actually
        };

        auto bfs_scan_next()
        {
            if (current != nullptr)
            {
                for (auto child : current->get_children())
                {
                    q.push(child);
                }
            }
            if (q.empty())
            {
                current = nullptr;
            }
            else
            {
                current = q.front();
                q.pop();
            }
            return this;
        };

        // DFS iterator
        auto init_dfs_scan() {
            // no need to do anything actually
        };

        auto dfs_scan_next()
        {
            if (current->get_children().size() > 0)
            {
                for (int i = current->get_children().size() - 1; i >= 0; i--)
                {
                    s.push(current->get_children()[i]);
                }
            }
            if (s.empty())
            {
                current = nullptr;
            }
            else
            {
                current = s.top();
                s.pop();
            }
            return this;
        };

        auto init_heap_scan()
        {
            if (current != nullptr)
            {
                min_heap.push(current);
                current = min_heap.top();
                min_heap.pop();
            }
        };

        auto heap_scan_next()
        {
            if (min_heap.empty())
            {
                current = nullptr;
            }
            else
            {
                current = min_heap.top();
                min_heap.pop();
                for (auto child : current->get_children())
                {
                    min_heap.push(child);
                }
            }
            return this;
        };
        

    public:
        Iterator(Node<T> *root, IterationOrder order) : current(root), order(order)
        {
            if (current != nullptr)
            {
                switch (order)
                {
                case IterationOrder::PreOrder:
                    if (K > 2)
                    {
                        this->order = IterationOrder::DFS;
                    }
                    break;
                case IterationOrder::PostOrder:
                    if (K <= 2)
                    {
                        init_post_order();
                    }
                    else
                    {
                        this->order = IterationOrder::DFS;
                    }
                    break;
                case IterationOrder::InOrder:
                    if (K <= 2)
                    {
                        init_in_order();
                    }
                    else
                    {
                        this->order = IterationOrder::DFS;
                    }
                    break;
                case IterationOrder::BFS:
                    break;
                case IterationOrder::DFS:
                    break;
                case IterationOrder::Heap:
                    init_heap_scan();
                    break;
                default:
                    break;
                }
            }
        }

        Iterator &operator++()
        {
            switch (order)
            {
            case IterationOrder::PreOrder:
                pre_order_next();
                break;
            case IterationOrder::PostOrder:
                post_order_next();
                break;
            case IterationOrder::InOrder:
                in_order_next();
                break;
            case IterationOrder::BFS:
                bfs_scan_next();
                break;
            case IterationOrder::DFS:
                dfs_scan_next();
                break;
            case IterationOrder::Heap:
                heap_scan_next();
                break;
            default:
                break;
            }
            return *this;
        }

        Node<T> *operator->()
        {
            return current;
        }

        Node<T> &operator*()
        {
            return *current;
        }

        bool operator==(const Iterator &other)
        {
            return current == other.current;
        }

        bool operator!=(const Iterator &other)
        {
            return current != other.current;
        }

    private:
        priority_queue<Node<T> *, vector<Node<T> *>, function<bool(Node<T> *, Node<T> *)>> min_heap;
    };

private:
    Node<T> *root;
    Node<T> *find_node(Node<T> &node)
    {
        bool found = false;
        for (auto node_iter = begin_pre_order(); node_iter != end_pre_order(); ++node_iter)
        {
            if (node_iter->get_value() == node.get_value())
            {
                if (node_iter->get_children().size() >= K)
                {
                    found = true;
                    continue;
                }

                else
                {
                    return &(*node_iter);
                }
            }
        }

        if (found){
            throw std::invalid_argument("Node already has " + to_string(K) + " children");
        }

        return nullptr;
    }

public:
    Tree() : root(nullptr) {}
    ~Tree() {}

    void add_root(Node<T> &root_node)
    {
        if (root != nullptr)
        {
            throw std::invalid_argument("Tree already has a root");
        }
        root = new Node<T>(root_node);
    }

    void add_sub_node(Node<T> &parent, Node<T> &child)
    {
        Node<T> *parent_ptr = find_node(parent);

        if (parent_ptr == nullptr)
        {
            throw std::invalid_argument("Parent not found");
        }

        Node<T> *child_ptr = new Node<T>(child);
        parent_ptr->add_child(*child_ptr);
    }

    Iterator begin_pre_order() const
    {
        return Iterator(root, IterationOrder::PreOrder);
    }

    Iterator end_pre_order() const
    {
        return Iterator(nullptr, IterationOrder::PreOrder);
    }

    Iterator begin_post_order() const
    {
        return Iterator(root, IterationOrder::PostOrder);
    }

    Iterator end_post_order() const
    {
        return Iterator(nullptr, IterationOrder::PostOrder);
    }

    Iterator begin_in_order() const
    {
        return Iterator(root, IterationOrder::InOrder);
    }

    Iterator end_in_order() const
    {
        return Iterator(nullptr, IterationOrder::InOrder);
    }

    Iterator begin_bfs_scan() const
    {
        return Iterator(root, IterationOrder::BFS);
    }

    Iterator end_bfs_scan() const
    {
        return Iterator(nullptr, IterationOrder::BFS);
    }

    Iterator begin_dfs_scan() const
    {
        return Iterator(root, IterationOrder::DFS);
    }

    Iterator end_dfs_scan() const
    {
        return Iterator(nullptr, IterationOrder::DFS);
    }

    Iterator begin() const
    {
        return begin_bfs_scan();
    }

    Iterator end() const
    {
        return end_bfs_scan();
    }

    Tree<T, K> myHeap() const
    {
        if (K != 2)
        {
            throw std::invalid_argument("Heap iterator is only supported for binary trees");
        }

        
        Tree<T> heap;
        vector<Node<T> *> nodes;

        for (auto node = begin_bfs_scan(); node != end_bfs_scan(); ++node)
        {
            nodes.push_back(new Node<T>(*node)); // copy the nodes
            nodes.back()->get_children().clear(); // clear the children
        }

        sort(nodes.begin(), nodes.end(), [](Node<T> *a, Node<T> *b) {
            return a->get_value() < b->get_value();
        });

        // build the new min heap tree
        heap.add_root(*nodes[0]);

        int j = 0;
        for (size_t i = 1; i < nodes.size(); i++)
        {
            heap.add_sub_node(*nodes[j], *nodes[i]);
            i%2 == 0 ? j++ : j;
        }

        return heap;
    }

    template <typename T1, size_t K1>
    friend std::ostream &operator<<(std::ostream &os, const Tree<T1, K1> &tree);
};

template <typename T, size_t K>
std::ostream &operator<<(std::ostream &os, const Tree<T, K> &tree)
{
    TreeGUI<T> gui(tree.root);
    gui.draw();
    return os;
}
