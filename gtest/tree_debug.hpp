#ifndef TREE_DEBUG_HPP
#define TREE_DEBUG_HPP

#include <cstddef>

namespace ft {

// print_tree
template <class node_pointer>
void print_tree(node_pointer __nd, node_pointer nil, std::size_t __level)
{
    if (__nd == nil)
    {
        return;
    }
    print_tree(__nd->right, nil, __level + 1);
    for (size_t i = 0; i < __level; i++)
    {
        std::cout << "  ";
    }
    if (__nd->color == kRed)
    {
        std::cout << RED;
    }
    std::cout << __nd->value.first << " " << END << std::endl;
    print_tree(__nd->left, nil, __level + 1);
}

template <class __node_pointer>
void print_tree_node(__node_pointer __nd, __node_pointer nil)
{
    std::cout << "==========================" << std::endl;
    print_tree(__nd, nil, 0);
}

template <class node_pointer>
void print_node_value(node_pointer x, node_pointer nil)
{
    if (x == nil)
        std::cout << "nil" << std::endl;
    else
        std::cout << x->value.first << std::endl;
}

template <class node_pointer>
void node_info(node_pointer x, node_pointer nil)
{
    // x
    std::cout << "x: " << std::flush;
    print_node_value(x, nil);
    // x->parent
    std::cout << "x's parent: " << std::flush;
    print_node_value(x->parent, nil);
    // x->left
    std::cout << "x's left: " << std::flush;
    print_node_value(x->left, nil);
    // x->right
    std::cout << "x's right: " << std::flush;
    print_node_value(x->right, nil);
}
}; // namespace ft

#endif