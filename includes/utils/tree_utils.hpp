#ifndef TREE_UTILS_HPP
#define TREE_UTILS_HPP

namespace ft {
template <class node_pointer>
inline bool tree_is_left_child(node_pointer node) throw()
{
    return node == node->parent->left;
}

template <class node_pointer>
inline node_pointer tree_min(node_pointer node, node_pointer nil) throw()
{
    while (node->left != nil)
        node = node->left;
    return node;
}

template <class node_pointer>
inline node_pointer tree_max(node_pointer node, node_pointer nil) throw()
{
    while (node->right != nil)
        node = node->right;
    return node;
}

template <class node_pointer>
inline node_pointer tree_next(node_pointer node, node_pointer nil) throw()
{
    if (node->right != nil)
    {
        return tree_min(node->right, nil);
    }
    while (!tree_is_left_child(node))
    {
        node = node->parent;
    }
    return node->parent;
}

template <class node_pointer>
inline node_pointer tree_prev(node_pointer node, node_pointer nil) throw()
{
    if (node->left != nil)
    {
        return tree_max(node->left, nil);
    }
    while (tree_is_left_child(node))
        node = node->parent;
    return node->parent;
}
} // namespace ft

#endif
