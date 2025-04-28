#include <limits>

#include "floyd_warshall.hpp"

int floyd_warshall_decoder(char n) {
    return (n != '-') ? n - '1' : -1;
}

char floyd_warshall_encoder(int n) {
    return n + '1';
}

Graph* create_floyd_warshall_graph() {
    Graph* floyd_warshall_graph = new Graph(NUM_FLOYD_WAR_NODES, floyd_warshall_decoder, floyd_warshall_encoder);

    floyd_warshall_graph->add_edge('1', '2', 3);
    floyd_warshall_graph->add_edge('1', '3', 8);
    floyd_warshall_graph->add_edge('1', '5', -4);
    floyd_warshall_graph->add_edge('2', '4', 1);
    floyd_warshall_graph->add_edge('2', '5', 7);
    floyd_warshall_graph->add_edge('3', '2', 4);
    floyd_warshall_graph->add_edge('4', '1', 2);
    floyd_warshall_graph->add_edge('4', '3', -5);
    floyd_warshall_graph->add_edge('5', '4', 6);

    return floyd_warshall_graph;
}

floyd_warshall_result* floyd_warshall_algo(Graph& graph, std::function<char(int)> encoder) {
    int num_nodes = graph.get_node_count();
    floyd_warshall_result* res = new floyd_warshall_result();
    
    res->distances = std::vector<std::vector<int>>(num_nodes, std::vector<int>(num_nodes));
    res->previous  = std::vector<std::vector<char>>(num_nodes, std::vector<char>(num_nodes));

    for(int i = 0; i < num_nodes; i++) {
        for(int j = 0; j < num_nodes; j++) {
            int cost = graph.get_edge(i, j);
            if(cost != 0) {
                res->distances[i][j] = cost;
                res->previous[i][j]  = encoder(i);
            } else if(i == j) {
                res->distances[i][j] = 0;
                res->previous[i][j]  = '-';
            } else {
                res->distances[i][j] = std::numeric_limits<int>::max();
                res->previous[i][j]  = '-';
            }
        }
    }

    for(int k = 0; k < num_nodes; k++) {
        std::vector<std::vector<int>> new_distances(num_nodes, std::vector<int>(num_nodes));

        for(int i = 0; i < num_nodes; i++) {
            for(int j = 0; j < num_nodes; j++) {
                if(i != j && res->distances[i][k] != std::numeric_limits<int>::max() && res->distances[k][j] != std::numeric_limits<int>::max()) {
                    new_distances[i][j] = std::min(res->distances[i][j], res->distances[i][k] + res->distances[k][j]);

                    if(new_distances[i][j] != res->distances[i][j]) {
                        res->previous[i][j] = encoder(k);
                    }
                } else {
                    new_distances[i][j] = res->distances[i][j];
                }
            }
        }

        res->distances = new_distances;
    }

    return res;
}

void floyd_warshall_print_result(floyd_warshall_result& r, std::function<char(int)> encoder) {
    int node_count = r.distances.size();
    std::cout << "Distances:\n" << "   | ";
    for(int i = 0; i < node_count; i++) {
        std::cout << encoder(i) << "  | ";
    }
    std::cout << std::endl;

    for(int i = 0; i < node_count; i++) {
        
        for(int i = 0; i < node_count+1; i++) {
            std::cout << "-----";
        }
        std::cout << std::endl;

        for(int j = -1; j < node_count; j++) {
            if (j == -1) {
                std::cout << " " << encoder(i) << " | ";
            } else {
                std::cout << ((r.distances[i][j] < 0) ? "" : " ") << r.distances[i][j] << " | ";
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Previous Nodes:\n" << "   | ";
    for(int i = 0; i < node_count; i++) {
        std::cout << encoder(i) << " | ";
    }
    std::cout << std::endl;

    for(int i = 0; i < node_count; i++) {
        
        for(int i = 0; i < node_count+1; i++) {
            std::cout << "----";
        }
        std::cout << std::endl;

        for(int j = -1; j < node_count; j++) {
            if (j == -1) {
                std::cout << " " << encoder(i) << " | ";
            } else {
                std::cout << r.previous[i][j] << " | ";
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}