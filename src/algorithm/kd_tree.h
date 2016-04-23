#ifndef _KD_TREE_H_
#define _KD_TREE_H_

#include "tree_node.h"


/******************************************************************************
 * Helper class IndexDis
 * index_: index of tree node in the data points
 * dis_:   distance between tree node and query node
 *****************************************************************************/
class IndexDis
{
public:
    
    size_t index_;
    long double dis_;
    IndexDis() : index_(0), dis_(0.0) {}
    IndexDis(size_t index, double distance) : index_(index), dis_(distance) {}
    
    bool operator < (const IndexDis& ids) const { return this->dis_ < ids.dis_;}
    bool operator > (const IndexDis& ids) const { return this->dis_ > ids.dis_;}
    
protected:
private:
};

/******************************************************************************
 * KDTreeBase class, provide interface for basic tree operations.
 * Data points of each tree node is stored separately, the key of one tree node
 * is the index of this node in the vector of data points.
 * Support: build tree from data points
            insert tree node
            remove tree node
            clear tree
            find top k nearest neighbor of query point
 *****************************************************************************/
template <typename Type>
class KDTreeBase {
    
public:
    
    typedef Point<Type> TPoint;
    typedef TreeNode<Type> KDTreeNode;
    typedef typename std::vector<TPoint>::const_iterator Iter;
    typedef typename std::vector<size_t>::iterator IdxIter;
    typedef std::unique_ptr<TreeNode<Type> >  TreeNodePtr;
    
    KDTreeBase(const size_t dim = 3) : dimension_(dim), size_(0), root(nullptr) {}
    KDTreeBase(const KDTreeBase<Type>& t);
    KDTreeBase& operator=(const KDTreeBase<Type>& t);
    ~KDTreeBase() { clear(); }
    
    size_t  dimension() const { return dimension_; }
    size_t  size() const { return size_; }
    void    setDimension(const size_t dim) { dimension_ = dim; }
    Iter    begin() const { return points.begin(); }
    Iter    end() const { return points.end(); }
    bool    empty() const { return 0 == size_; }
    void    insert(const TPoint& p);
    void    clear() { size_ = 0; deleteTree(root); points.clear(); }
    void    deleteNode(size_t index);
    TreeNodePtr getRoot() const { return std::move(root); }
    
    void                buildTree();
    size_t              nearstNode(const TPoint& pt);
    std::vector<size_t> knearstNodes(const TPoint& pt, const size_t k);

protected:
    
    size_t      dimension_; // dimension of the tree
    size_t      size_; // size of the tree
    std::unique_ptr<TreeNode<Type> >    root; // root of tree
    std::vector<Point<Type> >           points; // data points

    typedef std::priority_queue<IndexDis,
                                std::vector<IndexDis>,
                                std::greater<IndexDis> > NodeMinPQ;
    void        kNearstNodeSubTree(TreeNodePtr& node,
                                    size_t level,
                                    size_t k,
                                    const TPoint& pt,
                                    NodeMinPQ& q);
    
private:
    
    TreeNodePtr insertSubTree(TreeNodePtr& node, size_t index, size_t level);
    TreeNodePtr buildSubTree(IdxIter p_begin, IdxIter p_end, size_t level);
    TreeNodePtr deleteNodeSubTree(TreeNodePtr& node, size_t index, size_t level);
    size_t      findMin();
    size_t      findMinSubTree(TreeNodePtr& node, size_t level);
    void        deleteTree(TreeNodePtr& r);
};
 
template<typename Type>
KDTreeBase<Type>::KDTreeBase(const KDTreeBase<Type>& t)
{
    if (nullptr != t) {
        dimension_ = t.dimension();
        size_ = t.size();
        points.resize(t.size());
        std::copy(t.begin(), t.end(), points.begin());
        root = TreeNodePtr(new KDTreeNode(t.getRoot()));
    }
}

template<typename Type>
KDTreeBase<Type>& KDTreeBase<Type>::operator=(const KDTreeBase<Type>& t)
{
    if (this != &t) {
        dimension_ = t.dimension();
        size_ = t.size();
        points.resize(t.size());
        std::copy(t.begin(), t.end(), points.begin());
        root = TreeNodePtr(new KDTreeNode(t.getRoot()));
    }
    return *this;
}

/*
 * Insert data point to tree, helper function insertSubTree is used
 * Input: p, data point;
 * Output: none.
 */
template<typename Type>
void KDTreeBase<Type>::insert(const TPoint& p)
{
    points.push_back(p);
    root = insertSubTree(root, points.size() -1, 0);
    return;
}

/*
 * Insert data point to subtree recursively.
 * Input: node, pointer to starting tree node,
          index, index of inserted node in data point vector,
          level, level of the tree node to be inserted;
 * Output: pointer to inserted tree node, or next tree node to insert the node.
 */
template<typename Type>
std::unique_ptr<TreeNode<Type> > KDTreeBase<Type>::insertSubTree(
                                                                 TreeNodePtr& node,
                                                                 size_t index,
                                                                 size_t level)
{
    if (nullptr == node) {
        ++size_;
        return TreeNodePtr(new TreeNode<Type>(index, level));
    } else {
        auto nxt_level = (level + 1) % dimension_;
        // use the data ponits' level value to decide if to
        // insert to the left tree or right tree
        if(points.at(index)[level] < points.at(node->key())[level]) {
            node->left = insertSubTree(node->left, index, nxt_level);
        }
        else {
            // points with same level value are assigned to right child
            node->right = insertSubTree(node->right, index, nxt_level);
        }
    }
    return std::move(node);
}

/*
 * Build tree with data points. Data points are pre-initialized
 * Helper function buildSubTree is called
 * Input: none;
 * Output: pointer to root of tree.
 */
template<typename Type>
void KDTreeBase<Type>::buildTree()
{
    if (0 == points.size()) return;
    std::vector<size_t> index(points.size());
    for (auto i = 0; i <index.size(); ++i) {
        index[i] = i;
    }
    root = buildSubTree(index.begin(), index.end(), 0);
    return;
}

/*
 * Build tree recursively. Indeices of data points are used to build the tree.
 * Data points are pre-sorted to improve efficienty.
 * Input: p_begin, iterator to the start data point index,
 *        p_end, iterator to the end data point index,
 *        level, subTree level;
 * Output: pointer to the root of subtree.
 */
template<typename Type>
std::unique_ptr<TreeNode<Type> > KDTreeBase<Type>::buildSubTree(IdxIter p_begin,
                                                                IdxIter p_end,
                                                                size_t level)
{
    auto range = std::distance(p_begin, p_end);
    if (0 == range) {
        return nullptr;
    } else {
        // sort the data points based on the given level value
        std::sort(p_begin,
                  p_end,
                  [&](size_t a, size_t b) {
                      return points.at(a)[level] < points.at(b)[level]; }
                  );
        auto mid = p_begin + range/2;
        // points with same level value are assigned to right child
        while(mid != p_begin  &&
              points.at(*(mid))[level] == points.at(*(mid - 1))[level]){
            --mid;
        }
        auto node = TreeNodePtr(new TreeNode<Type>(*mid, level));
        ++size_;
        auto nxt_level = (level+1) % dimension_;
        node->left  = buildSubTree(p_begin, mid, nxt_level);
        node->right = buildSubTree(mid + 1, p_end, nxt_level);
        return std::move(node);
    }
}

/*
 * Delete one node from the tree. 
 * Helper function deleteNodeSubTree is called
 * Input: index, index of the tree node in the data point;
 * Output: none.
 */
template<typename Type>
void KDTreeBase<Type>::deleteNode(const size_t index)
{
    root = deleteNodeSubTree(root, index, 0);
}

/*
 * Delete one node from subTree.
 * Input: node, root of subTree,
 *        index, index of the tree node in the data point,
 *        level, level of subTree
 * Output: pointer to the root of the new subTree
 */
template<typename Type>
std::unique_ptr<TreeNode<Type> > KDTreeBase<Type>::deleteNodeSubTree(
                                                          TreeNodePtr& node,
                                                          size_t index,
                                                          size_t level)
{
    if (nullptr == node)
        return nullptr;
    // invalid input node index, do nothing
    if (index >= points.size()) {
        std::cerr<< "Invalid node index\n";
        return std::move(node);
    }
    auto nxt_level = (level + 1) % dimension_;
    
    // found node to delete
    if(node->key() == index){
        if(nullptr != node->right){
            auto right_min = findMinSubTree(node->right, nxt_level);
            node->setKey(right_min);
            node->setLevel(level);
            node->right = deleteNodeSubTree(node->right, right_min, nxt_level);
        } else if(nullptr != node->left){
            auto left_min = findMinSubTree(node->left, nxt_level);
            node->setKey(left_min);
            node->setLevel(level);
            node->right = deleteNodeSubTree(node->left, left_min, nxt_level);
            --size_;
            node->left.reset(nullptr);
        } else {
            --size_;
            node = nullptr;
        }
        
    } else if(points.at(index)[level] < points.at(node->key())[level]){
        // go to left child to find the node to delete
        node->left = deleteNodeSubTree(node->left, index, nxt_level);
    } else {
        // go to right child to find the node to delete
        node->right = deleteNodeSubTree(node->right, index, nxt_level);
    }
    return std::move(node);
}

/*
 * Find node with min value.
 * Helper function findMinSubTree is called
 * Input: none;
 * Output: none.
 */
template<typename Type>
size_t  KDTreeBase<Type>::findMin()
{
    return findMinSubTree(root, 0);
}

/*
 * Find node with min value in subTree.
 * Input: node, root of subTree,
 *        level, tree level of the root;
 * Output: index of found tree node.
 */
template<typename Type>
size_t KDTreeBase<Type>::findMinSubTree(TreeNodePtr& node, size_t level)
{
    if (nullptr == node) return SIZE_MAX;
    auto nxt_level = (level+1) % dimension_;
    if(level == node->level()){
        // go to the end of left
        if(node->left == nullptr){
            return node->key();
        } else {
            return findMinSubTree(node->left, nxt_level);
        }
    } else {
        size_t left_min = SIZE_MAX, right_min = SIZE_MAX;
        if(nullptr != node->left){
            left_min = findMinSubTree(node->left, nxt_level);
        }
        if(nullptr != node->right){
            right_min = findMinSubTree(node->right, nxt_level);
        }
        auto value = points.at(node->key())[level];
        if(nullptr != node->left && points.at(left_min)[level] < value){
            if(node->right){
                if (points.at(right_min)[level] < points.at(right_min)[level]) {
                    return left_min;
                } else {
                    return right_min;
                }
            } else {
                return left_min;
            }
        } else if(nullptr != node->right && points.at(right_min)[level] < value){
            return right_min;
        } else {
            return node->key();
        }
    }
}

/*
 * Find the nearest neighbor point of query point.
 * Helper function kNearstNodeSubTree is called.
 * k is set as 1.
 * Input: pt, query data point;
 * Output: found index.
 */
template<typename Type>
size_t KDTreeBase<Type>::nearstNode(const TPoint& pt)
{
    NodeMinPQ q;
    kNearstNodeSubTree(root, 0, 1, pt, q);
    if (!q.empty()) {
        if (q.size() > 1) q.pop();
        return q.top().index_;
    } else {
        std::cerr << "Error, tree is empty.\n";
        return SIZE_MAX;
    }
}

/*
 * Find the top k nearest neighbor point of query point.
 * Helper function kNearstNodeSubTree is called.
 * Input: pt, query data point;
 * Output: vector of found index.
 */
template<typename Type>
std::vector<size_t> KDTreeBase<Type>::knearstNodes(const TPoint& pt,
                                                    const size_t k)
{
    NodeMinPQ q; // priority queue which store the results
    kNearstNodeSubTree(root, 0, k, pt, q);
    if (!q.empty()) {
        if (q.size() > k) q.pop();
        std::vector<size_t> ret(q.size());
        auto iter = ret.rbegin();
        while (!q.empty()) {
            *iter = q.top().index_;
            q.pop();
            ++iter;
        }
        return ret;
    } else {
        std::cerr << "Error, tree is empty.\n";
        return std::vector<size_t>();
    }
}

/*
 * Find the top k+1 nearest neighbor point of query point from subTree.
 * Function is recursively called to find k+1 nearest neighbor nodes.
 * Squared distance between data points are used to improve efficienty.
 * Priority queue which stores the negative value of squared distance 
 * between the query point and found node. So the queue stores the top 
 * k+1 nodes, and the front of the queue is the k+1th result
 * Input: node, root of subtree,
          level, level of root,
          k, top k+1 nearest,
          pt, query data point,
          q, priority queue stores the top k+1 results
 * Output: none.
 */
template<typename Type>
void  KDTreeBase<Type>::kNearstNodeSubTree(TreeNodePtr& node,
                                               size_t level,
                                               const size_t k,
                                               const TPoint& pt,
                                               NodeMinPQ& q)
{
    if (nullptr == node || 0 == k) {
        return;
    }
    
    auto nxt_level = (level + 1) % dimension_;
    // distance from current tree node and query point
    auto local_dis = points.at(node->key()).squareDis(pt);
    auto dis = fabs(pt[level] - points.at(node->key())[level]);
    // longest distance in the found results
    auto longest = q.empty()
                ? std::numeric_limits<long double>::max() : -q.top().dis_;
    // negaive square distance is stored
    IndexDis idd(node->key(), -local_dis);
    // k+1 results are stored in the queue
    if (q.size() > k) {
        q.pop();
    }
    q.push(idd);
    if(pt[level] < points.at(node->key())[level]){
        //query goes into the left subtree
        kNearstNodeSubTree(node->left, nxt_level, k, pt, q);
        // If hypersphere crosses the splitting plane, check the other subTree
        if(q.size() < k || longest > dis) {
            kNearstNodeSubTree(node->right, nxt_level, k, pt, q);
        }
    } else {
        //query goes into the right subtree
        kNearstNodeSubTree(node->right, nxt_level, k, pt, q);
        // If hypersphere crosses the splitting plane, check the other subTree
        if(q.size() < k || longest > dis) {
            kNearstNodeSubTree(node->left, nxt_level, k, pt, q);
        }
    }
    return;
}

/*
 * Recursively delete the subTree
 * Input: r, root of subTree;
 * Output: none.
 */
template<typename Type>
void KDTreeBase<Type>::deleteTree(TreeNodePtr& r) {
    if (r) {
        deleteTree(r->left);
        deleteTree(r->right);
        r.reset(nullptr);
    }
    return;
}

#endif

