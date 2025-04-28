#include <iostream>
#include <stdexcept>

#include "graph.hpp"

int default_coder(int n) {
    return n;
}

Graph::Graph(int num_nodes) {char
    node_count = num_nodes;
    decoder = default_coder;
    encoder = default_coder;
    data = new int[node_count * node_count]();
}

Graph::Graph(int num_nodes, std::function<int(char)> letter_to_num, std::function<char(int)> num_to_letter) {
    node_count = num_nodes;
    decoder = letter_to_num;
    encoder = num_to_letter;
    data = new int[node_count * node_count]();
}

Graph::~Graph() {
    delete data;
}

int Graph::get_node_count() {
    return node_count;
}

std::vector<std::tuple<int, int, int>>* Graph::get_edges() {
    std::vector<std::tuple<int, int, int>>* edges = new std::vector<std::tuple<int, int, int>>;
    for(int i = 0; i < node_count; i++) {
        for(int j = 0; j < node_count; j++) {
            int cost =  data[i*node_count + j];
            if(cost != 0) {
                edges->push_back(std::tuple<int, int, int>(i, j, cost));
            }
        }
    }

    return edges;
}

void Graph::add_edge(int src, int dst, int cost) {
    data[src*node_count + dst] = cost;
}

void Graph::add_bi_dir_edge(int src, int dst, int cost) {
    data[src*node_count + dst] = cost;
    data[dst*node_count + src] = cost;
}

int  Graph::get_edge(int src, int dst) {
    return data[src*node_count + dst];
}


void Graph::add_edge(char src, char dst, int cost) {
    data[decoder(src)*node_count + decoder(dst)] = cost;
}

void Graph::add_bi_dir_edge(char src, char dst, int cost) {
    data[decoder(src)*node_count + decoder(dst)] = cost;
    data[decoder(dst)*node_count + decoder(src)] = cost;
}

int Graph::get_edge(char src, char dst) {
    return data[decoder(src)*node_count + decoder(dst)];
}

void Graph::print_graph_matrix() {

    std::cout << "   | ";
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
                std::cout << data[i * node_count + j] << " | ";
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void Graph::print_graph_list() {

    for(int i = 0; i < node_count; i++) {
        
        std::cout << encoder(i) << " -> ";
        for(int j = 0; j < node_count; j++) {
            int cost_value = data[i * node_count + j];
            if(cost_value) {
                std::cout << "[ " << encoder(j) << " : " << data[i * node_count + j] << " ] -> ";
            }
        }
        std::cout << "[ END ]" << std::endl;
    }

    std::cout << std::endl;
}
