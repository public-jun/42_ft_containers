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

template <class node_pointer>
inline void tree_left_rotate(node_pointer x, node_pointer nil) throw()
{
    /*
        x が left_child の時
                ○100                     ○100
                /                           /
            ○10(x)                     ○20(y)
            /   \         ->            /   \
        ○5      ○20(y)             ○10(x)  ○25
                /   \                /    \
            ○15     ○25         ○5    ○15


        x が right_child の時
        ○0                          ○0
           \                            \
            ○10(x)                     ○20(y)
            /   \           ->           /   \
        ○5      ○20(y)              ○10(x)  ○25
                /   \                /    \
            ○15     ○25          ○5    ○15
    */
    node_pointer y = x->right;
    x->right       = y->left;
    if (x->right != nil)
        x->right->set_parent(x);
    y->parent = x->parent;
    if (tree_is_left_child(x))
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->set_parent(y);
}

template <class node_pointer>
inline void tree_right_rotate(node_pointer x, node_pointer nil)
{
    /*
        x が left_child の時
                ○100                     ○100
                /                           /
            ○10(x)                     ○20(y)
            /   \         ->            /   \
        ○5      ○20(y)             ○10(x)  ○25
                /   \                /    \
            ○15     ○25         ○5    ○15


        x が right_child の時
        ○0                          ○0
           \                            \
            ○10(x)                     ○20(y)
            /   \           ->           /   \
        ○5      ○20(y)              ○10(x)  ○25
                /   \                /    \
            ○15     ○25          ○5    ○15
    */
    node_pointer y = x->left;
    x->left        = y->right;
    if (x->left != nil)
        x->left->set_parent(x);
    y->parent = x->parent;
    if  (tree_is_left_child(x))
        x->parent->left = y;
    else
        x->parent->right = y;
    y->right = x;
    x->set_parent(y);
}

/*
赤黒木のルール
1.
2.
3.
*/

template <class node_pointer>
inline void tree_balance_after_insert(node_pointer root, node_pointer x,
                                      node_pointer nil) throw()
{
    if (x == root)
        x->color = kBlack;
    else
        x->color = kRed;

    // ○黒色、●赤色

    // x はルートではない && 親は赤色でループ
    while (x != root && x->parent->color == kRed)
    {
        // 親が left_child -> 自身は左挿入
        if (tree_is_left_child(x->parent))
        {
            // 叔父ノードを取得
            node_pointer y = x->parent->parent->right;
            // 叔父が nil ではない && 叔父は赤色
            if (y != nil && y->color == kRed)
            {
                /*
                    ●16 挿入時、叔父(○70)が赤色の場合
                                   /
                                 ○50
                                /   \
                            ●20     ●70
                            /   \   /   \
                        ●16     ○○     ○
                        /   \
                      ○     ○

                    親、祖父、叔父の色を変更
                    -> ●50より上を再帰的に調べる
                                   /
                                 ●50
                                /   \
                            ○20     ○70
                            /   \   /   \
                        ●16     ○○     ○
                        /   \
                      ○     ○
                */
                x        = x->parent;
                x->color = kBlack;
                x        = x->parent;
                if (x == root)
                    x->color = kBlack;
                else
                    x->color = kRed;
                y->color = kBlack;
            }
            // 叔父が nil || 叔父が黒色
            else
            {
                if (!tree_is_left_child(x))
                {
                    x = x->parent;
                    /*
                        ●16 を右挿入時、叔父(○70)が赤色の場合
                                         /
                                      ○50
                                    /       \
                                ●12       ○70
                               /     \     /   \
                            ○10    ●16  ○     ○
                                    /   \
                                  ○14  ○18

                          ●12で左回転(rotateL)

                          1. 自分(●16)を親の位置へ
                          2. 親(●12)を兄弟の位置へ
                          3. 子(○14)を親(●12)の子へ
                                         /
                                      ○50
                                    /       \
                                ●16       ○70
                               /     \     /   \
                            ●12    ○18  ○     ○
                           /    \
                         ○10   ○14
                    */
                    tree_left_rotate(x, nil);
                }
                /*
                    ●16 を左挿入時、叔父(○70)が赤色の場合
                                   /
                                 ○50
                                /   \
                            ●20     ○70
                            /   \   /   \
                        ●16     ○○     ○
                        /   \
                      ○     ○

                    1. 親(●20)を黒色に変更
                    2. 祖父(○50)を赤色に変更
                                   /
                                 ●50
                                /   \
                            ○20     ○70
                            /   \   /   \
                        ●16     ○○     ○
                        /   \
                      ○     ○
                */
                x        = x->parent;
                x->color = kBlack;
                x        = x->parent;
                x->color = kRed;
                /*

                      ●50で右回転(rotateR)

                      1. 自分(●16)を親の位置へ
                      2. 親(○20)を祖父の位置へ
                      3. 祖父(●50)を兄弟の位置へ
                                   /
                                 ○20
                                /   \
                            ●16     ●50
                            /   \   /   \
                         ○     ○○     ○70
                        /   \
                      ○     ○
                */
                tree_right_rotate(x);
                break;
            }
        }
    }
}
} // namespace ft

#endif
