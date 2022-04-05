#ifndef TREE_UTILS_HPP
#define TREE_UTILS_HPP

namespace ft {

enum r_b_color { kRed = false, kBlack = true };

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
                   ○100                  ○100
                  /                        /
             ○20(x)                   ○10(y)
             /   \         ->          /   \
         ○10(y)  ○25            ○15    ○20(x)
         /   \                            /    \
      ○5     ○15                      ○15    ○25

        x が right_child の時
            ○0                    ○0
              \                      \
             ○20(x)                  ○10(y)
             /   \         ->          /   \
         ○10(y)  ○25            ○15    ○20(x)
         /   \                            /    \
      ○5     ○15                      ○15    ○25
    */
    node_pointer y = x->left;
    x->left        = y->right;
    if (x->left != nil)
        x->left->set_parent(x);
    y->parent = x->parent;
    if (tree_is_left_child(x))
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
    // node_pointer tmp = x;
    if (x == root)
        x->color = kBlack;
    else
        x->color = kRed;

    // ○黒色、●赤色

    // x はルートではない && 親は赤色でループ
    while (x != root && x->parent->color == kRed)
    {
        // 親が left_child
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
                    ●16 を左挿入時、叔父(○70)が黒色の場合
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
                tree_right_rotate(x, nil);
                break;
            }
        }
        else
        {
            node_pointer y = x->parent->parent->left;
            if (y != nil && y->color == kRed)
            {
                x        = x->parent;
                x->color = kBlack;
                x        = x->parent;
                if (x == root)
                    x->color = kBlack;
                else
                    x->color = kRed;
                y->color = kBlack;
            }
            else
            {
                if (tree_is_left_child(x))
                {
                    x = x->parent;
                    tree_right_rotate(x, nil);
                }
                x        = x->parent;
                x->color = kBlack;
                x        = x->parent;
                x->color = kRed;
                tree_left_rotate(x, nil);
                break;
            }
        }
    }
}

template <class node_pointer>
bool has_two_children(node_pointer x, node_pointer nil)
{
    if (x->left != nil && x->right != nil)
        return true;
    return false;
}

template <class node_pointer>
void tree_remove(node_pointer root, node_pointer z, node_pointer nil)
{
    // z は消去予定ノード
    // y は z もしくは z が2つ子要素を２つ持つ場合は tree_next(z)のノードを持つ
    // y は 多くて1つの子要素を持つ
    // y は tree の最初の穴
    node_pointer y = has_two_children(z, nil) ? tree_next(z, nil) : z;
    // x は y のただ一つのnilになりうる子要素
    node_pointer x = y->left != nil ? y->left : y->right;
    // w は nilになりうるxの叔父ノード(w は最終的に x の兄弟になる)
    node_pointer w = nil;
    // x と y の親をリンクし、w を見つけます
    if (x != nil)
        x->parent = y->parent; // xの親を祖父にする
    if (tree_is_left_child(y))
    {
        y->parent->left = x; // 祖父の子要素を xにする
        if (y != root)
            w = y->parent->right; // w を x の兄弟にする
        else
            root = x; // w == nil
    }
    else // y 自信が右の子要素
    {
        y->parent->right = x;
        // y は自身が右の子要素の場合は root にはなり得ない
        w = y->parent->left;
    }
    bool removed_black = y->color;
    // z を削除していない場合は、y を z に継ぎ足し、z の色をコピーする
    // これは x や w には影響しない
    if (y != z)
    {
        y->parent = z->parent;
        if (tree_is_left_child(z))
            y->parent->left = y;
        else
            y->parent->right = y;
        y->left = z->left;
        y->left->set_parent(y);
        y->right = z->right;
        if (y->right != nil)
            y->right->set_parent(y);
        y->color = z->color;
        if (root == z)
            root = y;
    }
    // 赤色もしくは最後のノードを削除した場合はリバランスは必要ない
    if (removed_black == kBlack && root != nil)
    {
        if (x != nil)
            x->color = kBlack;
        else
        {
            while (true)
            {
                // print_tree(root, nil, 10);
                // node_info(w, nil);
                if (!tree_is_left_child(w)) // if x is left child
                {
                    if (w->color == kRed)
                    {
                        w->color         = kBlack;
                        w->parent->color = kRed;
                        tree_left_rotate(w->parent, nil);
                        // x is still valid
                        // reset root only if necessary
                        if (root == w->left)
                            root = w;
                        // reset sibling, and it still can't be null
                        w = w->left->right;
                    }
                    // w->color is Black, w may have null children
                    if ((w->left == nil || w->left->color == kBlack) &&
                        (w->right == nil || w->right->color == kBlack))
                    {
                        w->color = kRed;
                        x        = w->parent;
                        // x can no longer be nil
                        if (x == root || x->color == kRed)
                        {
                            x->color = kBlack;
                            break;
                        }
                        // reset sibling, and it still can't be nil
                        w = tree_is_left_child(x) ? x->parent->right
                                                  : x->parent->left;
                        // continue;
                    }
                    else // w has a red child
                    {
                        if (w->right == nil || w->right->color == kBlack)
                        {
                            // w left child is non-nil and red
                            w->left->color = kBlack;
                            w->color       = kRed;
                            tree_right_rotate(w, nil);
                            // w is known not to be root, so root hasn't changed
                            // reset sibling, and it still can't be nill
                            w = w->parent;
                        }
                        // w has a right red child, left child may be nil
                        w->color         = w->parent->color;
                        w->parent->color = kBlack;
                        w->right->color  = kBlack;
                        tree_left_rotate(w->parent, nil);
                        break;
                    }
                }
                else // if x is right child
                {
                    if (x->color == kRed)
                    {
                        w->color         = kBlack;
                        w->parent->color = kRed;
                        tree_right_rotate(w->parent, nil);
                        // x is still valid
                        // reset root only if necessary
                        if (root == w->right)
                            root = w;
                        // reset sibling, and it still can't be nil
                        w = w->right->left;
                    }
                    // w->color is Black, w may have nil children
                    if ((w->left == nil || w->left->color == kBlack) &&
                        (w->right == nil || w->right->color == kBlack))
                    {
                        w->color = kRed;
                        x        = w->parent;
                        // x can no longer be nil
                        if (x->color == kRed || x == root)
                        {
                            x->color = kBlack;
                            break;
                        }
                        // reset sibling, and it still can't be nil
                        w = tree_is_left_child(x) ? x->parent->right
                                                  : x->parent->left;
                        // continue;
                    }
                    else // w has a red child
                    {
                        if (w->left == nil || w->left->color == kBlack)
                        {
                            // w right child is non-nil and red
                            w->right->color = kBlack;
                            w->color        = kRed;
                            tree_left_rotate(w, nil);
                            // w is known not to be root, so root hasn't changed
                            // reset sibling, and it still can't be nil
                            w = w->parent;
                        }
                        // w has a left red child, right child may be nil
                        w->color         = w->parent->color;
                        w->parent->color = kBlack;
                        w->left->color   = kBlack;
                        tree_right_rotate(w->parent, nil);
                        break;
                    }
                }
            }
        }
    }
}

} // namespace ft

#endif
