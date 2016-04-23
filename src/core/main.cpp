#include <iostream>
#include <iostream>
#include "kd_tree.h"
#include "app_kd_tree.h"

int main(int argc, char** argv)
{
    if (argc == 1 || argv[1][0] != '-'
        || argv[1][1] =='h' || argv[1][1] =='\0') {
        std::cout << "Usage:\n";

        std::cout << "-h:\t" << "display help information.\n";
        std::cout << "-k [data]\t" << "find the top k nearest node, k = 1 by default.\n";
        std::cout << "-p [file]\t" << "generate KDTree for point file.\n";
        std::cout << "-q [file]\t" << "read query points from file.\n";
        std::cout << "-r [file]\t" << "load KDTree from KDTree output file.\n";
        std::cout << "-s [file]\t" << "save query results to output file.\n";
        std::cout << "-w [file]\t" << "write KDTree to KDTree output file.\n";

    } else {
        std::ifstream gen_tree, load_tree, load_query;
        std::ofstream write_tree, write_query_result;
        int load_query_pos = 0;
        size_t k = 1;
        for (auto i = 1; i < argc; i += 2) {
            if (argv[i][0] != '-' || argv[i][1] =='\0' ||
                argc == i + 1 || argv[i][2] != '\0') {
                std::cerr << "Error input parameter. Try -h for help.\n";
                return 0;
            } else if (argv[i][1] == 'k') {
                auto intk = atoi(argv[i+1]);
                if (intk <= 0) {
                    std::cerr << "Error of input parameter k, non-zero value is needed.\n";
                    std::cerr << "Default value 1 is used.\n";
                } else
                    k = (size_t) intk;
            }
            else if (argv[i][1] == 'p') {
                if (gen_tree.is_open()) {
                    gen_tree.close();
                }
                gen_tree.open(argv[i+1]);
            } else if (argv[i][1] == 'q') {
                if (load_query.is_open()) {
                    load_query.close();
                }
                load_query.open(argv[i+1]);
                load_query_pos = i;
            } else if (argv[i][1] == 'r') {
                if (load_tree.is_open()) {
                    load_tree.close();
                }
                load_tree.open(argv[i+1]);
            } else if (argv[i][1] == 's') {
                if (write_query_result.is_open()) {
                    write_query_result.close();
                }
                write_query_result.open(argv[i+1]);
            } else if (argv[i][1] == 'w') {
                if (write_tree.is_open()) {
                    write_tree.close();
                }
                write_tree.open(argv[i+1]);
            }
        }
        KDTree<double> kd_tree;
        if (gen_tree.is_open()) {
            kd_tree.generateFromFile(gen_tree);
            gen_tree.close();
        } else if (load_tree.is_open()) {
            kd_tree.readFromFile(load_tree);
            load_tree.close();
        }
        if (load_query.is_open()) {
            if (write_query_result.is_open() == false) {
                // generate query output file
                std::string load_q_name(argv[load_query_pos+1]);
                auto pos = load_q_name.find_last_of(".");
                if (pos != std::string::npos) {
                    if (0 == pos) {
                        load_q_name = load_q_name.substr(1);
                    } else {
                        load_q_name = load_q_name.substr(0, pos);
                    }
                }
                load_q_name +="_qresult.txt";
                write_query_result.open(load_q_name);
            }
            kd_tree.queryNearestNodes(load_query, write_query_result, k);
            load_query.close();
            write_query_result.close();
        }
        if (write_tree.is_open()) {
            kd_tree.saveToFile(write_tree);
            write_tree.close();
        }
        std::cout << "Done\n";
    }

    return 0;
}


