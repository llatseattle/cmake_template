#include <iostream>
#include <iostream>
#include "kd_tree.h"
#include "app_kd_tree.h"

int main(int argc, char** argv)
{
    std::cout << "Test KDTree.\n";
    
    KDTree<double> kd_tree;
    std::cout << "Generate Tree from input data ponints...\n";
    std::ifstream ifs1("sample_data.csv");
    kd_tree.generateFromFile(ifs1);
    ifs1.close();
    std::cout << "Done.\n";
    
    std::cout << "Query nearst neighbor of query points...\n";
    std::ifstream ifs2("query_data.csv");
    std::ofstream ofs1("query_data_result.txt");
    kd_tree.queryNearestNodes(ifs2, ofs1, 2);
    ifs2.close();
    ofs1.close();
    std::cout << "Done.\n";
    
    std::cout << "Write tree to file...\n";
    std::ofstream ofs2("tree.data");
    kd_tree.saveToFile(ofs2);
    ofs2.close();
    std::cout << "Done.\n";
    
    std::cout << "Read tree from file.\n";
    kd_tree.clear();
    std::ifstream ifs3("tree.data");
    kd_tree.readFromFile(ifs3);
    ifs3.close();
    std::cout << "Done.\n";
    
    std::cout << "Rewrite tree to file...\n";
    std::ofstream ofs3("tree1.data");
    kd_tree.saveToFile(ofs3);
    ofs3.close();
    std::cout << "Done.\n";
    
    std::cout << "Test done\n";
	return 0;
}


