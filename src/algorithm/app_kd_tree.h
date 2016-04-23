#ifndef _APP_KDTREE_H_
#define _APP_KDTREE_H_

#include "kd_tree.h"

/******************************************************************************
 * KDTree class, derived based on KDTreeBase
 * Support: generate tree from input data points
 *          write tree to stream
 *          read tree from stream
 *          read query points from stream and output the found nearest point
 *          indices to stream
 *****************************************************************************/

template<typename Type>
class KDTree : public KDTreeBase<Type> {
    
public:
    
    typedef std::unique_ptr<TreeNode<Type> >  TreeNodePtr;
    
    KDTree(const size_t& dim = 3) : KDTreeBase<Type>(dim) { }
    KDTree(std::istream& ifs);
    ~KDTree() {}
    
    void    generateFromFile(std::istream& ifs);
    void    saveToFile(std::ostream& ofs);
    void    readFromFile(std::istream& ifs);
    void    queryNearestNodes(std::istream& ifs, std::ostream& ofs, size_t k = 1);
protected:
    
private:
    
    void    gentQueryPoints(std::istream& ifs,
                            std::vector<Point<Type> >& query_points);
    void    findNearestNodesForQuery(std::ostream& ofs,
                                      std::vector<Point<Type> >& query_points,
                                      size_t k);
    void    save(std::ostream& ofs, TreeNodePtr& node);
    void    read(std::istream& ifs, TreeNodePtr& node);
};

template<typename Type>
KDTree<Type>::KDTree(std::istream& ifs)
{
    // constructor with file of input points
    if (!ifs) {
        throw ERR(ErrorMsg() << "KDTree(), " << "Invalid Input");
    }
    generateFromFile(ifs);
}

/*
 * generate KDtree from input file.
 * Input file contains one point at each line.
 * Extensive checking of input is not provided.
 * Input: istream ifs.
 */
template<typename Type>
void   KDTree<Type>::generateFromFile(std::istream& ifs)
{
    if (!ifs) {
        throw ERR(ErrorMsg() << "KDTree(), " << "Invalid input");
    }
    // no extensive checking of input file is provided
    std::string line;
    std::getline(ifs, line);
    // get dimension
    size_t dim = std::count(line.begin(), line.end(), ',') + 1;
    std::cout << "\t" << "KDTree dimension: " << dim << "\n";
    
    KDTreeBase<Type>::setDimension(dim);
    ifs.clear();
    ifs.seekg(0, std::ios::beg);

    // get number of points
    size_t num_points = 0;
    while (std::getline(ifs, line))
        ++num_points;
    ifs.clear();
    ifs.seekg(0, std::ios::beg);
    std::cout  << "\t" << "Number of tree nodes: " << num_points << "\n";
    
    // read points from file
    KDTreeBase<Type>::points.resize(num_points);
    char c;
    for (auto i = 0; i < num_points; ++i) {
        for (size_t j = 0; j < dim; ++j) {
            ifs >> KDTreeBase<Type>::points[i][j] >> c;
        }
    }
    // build the tree
    KDTreeBase<Type>::buildTree();
    
    return;
}

/*
 * Read query points from the input, output the found nearest tree node index
 * Input: ifs, input file contains all the query points
 * Output: ofs, output all the found index of the nearest tree node
 */
template<typename Type>
void    KDTree<Type>::queryNearestNodes(std::istream& ifs,
                                         std::ostream& ofs,
                                         size_t k)
{
    std::vector<Point<Type> > query_points;
    gentQueryPoints(ifs, query_points);
    if (KDTreeBase<Type>::empty()) {
        std::cerr << "KDTree is empty.\n";
        return;
    }
    findNearestNodesForQuery(ofs, query_points, k);
    
    return;
}

/*
 * Find the top k nearest points for each query point.
 * Input: ofs, output file to store the found indeices
 *        query_points, vector of query points
 * Output: ofs with all the found indices,
 */
template<typename Type>
void    KDTree<Type>::findNearestNodesForQuery(std::ostream& ofs,
                                                std::vector<Point<Type> >& query_points,
                                                size_t k)
{
    for (auto &q : query_points) {
        auto ans = KDTreeBase<Type>::knearstNodes(q, k);
        for (auto &r :ans) {
            ofs << r <<"\t";
        }
        ofs <<"\n";
    }
    return;
}

/*
 * Read query points from input file
 * Input: ifs, input file contains all the query points
 * Output: query_points, extracted vector containing all the query points
 */
template<typename Type>
void    KDTree<Type>::gentQueryPoints(std::istream& ifs,
                                      std::vector<Point<Type> >& query_points)
{
    if (!ifs) {
        throw ERR(ErrorMsg() << "KDTree(), " << "Invalid input");
    }
    std::cout << "\t" << "Reading query points from input.\n";
    std::cout << "\t" << "No extensive checking of input file is provided...\n";
    
    // no extensive checking of input file is provided
    std::string line;    // get number of quert points
    size_t num_points = 0;
    while (std::getline(ifs, line))
        ++num_points;
    ifs.clear();
    ifs.seekg(0, std::ios::beg);
    std::cout << "\t" << "Number of query nodes: " << num_points << "\n";
    
    // read points from file
    size_t dim = KDTreeBase<Type>::dimension();
    query_points = std::vector<Point<Type> >(num_points, Point<Type>(dim));
    size_t index = 0;
    char c;
    for (auto i = 0; i < num_points; ++i) {
        query_points[index].resize(dim);
        for (size_t j = 0; j < dim; ++j) {
            ifs >> query_points[i][j] >> c;
        }
    }
    return;
}

/*
 * Save KDTree to file
 * Output: ofs,
 * Input: ifs, input file contains all the query points
 */
template<typename Type>
void    KDTree<Type>::saveToFile(std::ostream& ofs)
{
    if (!ofs) {
        throw ERR(ErrorMsg() << "KDTree(), " << "Invalid output file");
    }
    if (KDTreeBase<Type>::empty()) {
        std::cerr << "Empty tree.\n";
        return;
    }
    ofs.precision(16);
    
    // write header
    ofs << std::to_string(KDTreeBase<Type>::dimension_) << "\t";
    ofs << std::to_string(KDTreeBase<Type>::points.size()) << "\n";
    // write points
    for (auto &i : KDTreeBase<Type>::points) {
        ofs << i;
    }
    // write tree nodes
    ofs << KDTreeBase<Type>::size() <<"\n";
    save(ofs, KDTreeBase<Type>::root);
    
    return;
}

/*
 * Input: ofs, output stream,
          node, KDTree node, use recursion to do the output
 * Output: none.
 */
template<typename Type>
void    KDTree<Type>::save(std::ostream& ofs, TreeNodePtr& node)
{
    if (node != nullptr) {
        ofs << node;
        if (node->left)
            save(ofs, node->left);
        if (node->right)
            save(ofs, node->right);
    }
    return;
}

/*
 * Read KDTree from the input recursively
 * Input: ifs, input stream
 * Output: none.
 * First read all the data points of the tree, then read nodes of the tree
 */
template<typename Type>
void    KDTree<Type>::readFromFile(std::istream& ifs)
{
    if (!ifs) {
        throw ERR(ErrorMsg() << "KDTree(), " << "Invalid Input file");
    }
    std::cout << "\t" << "Reading data points from input.\n";
    std::cout << "\t" << "No extensive checking of input file is provided...\n";
    
    // clear old tree
    KDTreeBase<Type>::clear();
    KDTreeBase<Type>::points.clear();
    
    // no extensive checking of input file is provided
    size_t dim, num_points;
    ifs >> dim >> num_points;
    std::cout << "\t" << "KDTree dimension: " << dim << "\n";
    KDTreeBase<Type>::setDimension(dim);
    // read points from file
    KDTreeBase<Type>::points.resize(num_points);
    for (auto i = 0; i < num_points; ++i) {
        ifs >> KDTreeBase<Type>::points[i];
    }
    size_t num_tree_nodes = 0;
    ifs >> num_tree_nodes;
    KDTreeBase<Type>::size_ = num_tree_nodes;
    
    // generate the root node
    KDTreeBase<Type>::root = TreeNodePtr(new TreeNode<Type>(0, 0));
    ifs >> KDTreeBase<Type>::root;
    // recursively read all the tree nodes
    read(ifs, KDTreeBase<Type>::root);
    
    return;
}

/*
 * Read node from the input recursively.
 * Input: ifs, input stream; node, starting tree node.
 * Output: none.
 */
template<typename Type>
void    KDTree<Type>::read(std::istream& ifs, TreeNodePtr& node)
{
    size_t chld_sz = 0;
    auto& dim = KDTreeBase<Type>::dimension_;
    ifs >> chld_sz;
    switch (chld_sz) {
        case 3:
            // left child and right child
            node->left = TreeNodePtr(new TreeNode<Type>(dim));
            ifs >> node->left;
            read(ifs, node->left);
            
            node->right = TreeNodePtr(new TreeNode<Type>(dim));
            ifs >> node->right;
            read(ifs, node->right);
            
            break;
        case 2:
            // left child
            node->left = TreeNodePtr(new TreeNode<Type>(dim));
            ifs >> node->left;
            read(ifs, node->left);
            break;
        case 1:
            // right child
            node->right = TreeNodePtr(new TreeNode<Type>(dim));
            ifs >> node->right;
            read(ifs, node->right);
            
            break;
        default:
            break;
    }
    return;
}

#endif
