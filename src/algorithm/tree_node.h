#ifndef _TREE_NODE_H_
#define _TREE_NODE_H_

#include "point.h"

/******************************************************************************
 * KDTree Node class
 * Tree Node contains:
 * key_:    key of tree node, which is the index of index of stored data points
 * level_:  level of tree node
 * left:    pointer to left child
 * right:   pointer to right child
 ******************************************************************************
 */
template <typename NodeType>
class TreeNode {
    
public:
    
    typedef std::unique_ptr<TreeNode<NodeType> >  TreeNodePtr;
    
    std::unique_ptr<TreeNode<NodeType> > left;
    std::unique_ptr<TreeNode<NodeType> > right;
    
    TreeNode() : left(nullptr), right(nullptr), key_(0), level_(0) {}
    TreeNode(const size_t& index) : left(nullptr), right(nullptr),
                                    key_(index), level_(0) {}
    TreeNode(const size_t& index, const size_t& level) : left(nullptr),
                                                         right(nullptr),
                                                         key_(index),
                                                         level_(level) {}
    TreeNode(const TreeNode<NodeType>& t)
    {
        key_ = t.key();
        level_ = t.level();
        if (nullptr != t.left)
            left = TreeNodePtr(new TreeNode<NodeType>(t.left));
        else
            left = nullptr;
        if (nullptr != t.right)
            right = TreeNodePtr(new TreeNode<NodeType>(t.right));
        else
            right = nullptr;
    }
    TreeNode(const TreeNodePtr t) {
        if (nullptr == t) {
            key_ = 0;
            level_ = 0;
            left = nullptr;
            right = nullptr;
        } else {
            key_ = t->key();
            level_ = t->level();
            if (nullptr != t->left) {
                left = TreeNodePtr(new TreeNode<NodeType>(t->left));
            }
            else
                left = nullptr;
            if (nullptr != t->right) {
                right = TreeNodePtr(new TreeNode<NodeType>(t->right));
            }
            else
                right = nullptr;
        }
    }
    TreeNode& operator=(const TreeNode<NodeType>& t)
    {
        if (this != &t) {
            key_ = t.key();
            level_ = t.level();
            if (nullptr != t->left) {
                left = TreeNodePtr(new TreeNode<NodeType>(t.left));
            }
            else
                left = nullptr;
            if (nullptr != t->right) {
                right = TreeNodePtr(new TreeNode<NodeType>(t.right));
            }
            else
                right = nullptr;
        }
        return  *this;
    }
    ~TreeNode() { }
    
    bool operator ==(const TreeNode<NodeType>& t) {
        return  key_ == t.key();
    }
    
    size_t  key() const  { return key_; }
    size_t  level() const    { return level_; }
    void    setKey(const size_t& k)    { key_ = k; }
    void    setLevel(const size_t& l)  { level_ = l; }
    
    friend std::ostream& operator << (std::ostream& ofs, const TreeNodePtr& node)
    {
        if (nullptr != node) {
            ofs << node->key() << "\t" << node->level() << "\t";
            if (node->left && node->right) {
                // node has two children
                ofs << "3\n";
            } else if (node->left) {
                // node only has left child
                ofs << "2\n";
            } else if (node->right) {
                // node only has right child
                ofs << "1\n";
            } else {
                // node is leaf
                ofs << "0\n";
            }
        }
        return ofs;
    }
    friend std::istream& operator >> (std::istream& ifs, TreeNodePtr& node)
    {
        if (nullptr != node) {
            size_t tmp;
            ifs >> tmp;
            node->setKey(tmp);
            ifs >> tmp;
            node->setLevel(tmp);
            // children is not directly read in here
        }
        return ifs;
    }
    
protected:
    
private:
    
    size_t  key_;
    size_t  level_;
};

#endif
