#pragma once

#include <iostream>
#include <functional>

class Graph {
    private:
        int *data;
        int node_count;
        std::function<int(char)> decoder;
        std::function<char(int)> encoder;

    public:
        Graph(int num_nodes);
        Graph(int num_nodes, std::function<int(char)> letter_to_num, std::function<char(int)> num_to_letter);
        ~Graph();

        int get_node_count();
        std::vector<std::tuple<int, int, int>>* get_edges();

        void add_edge(int src, int dst, int cost=1);
        void add_bi_dir_edge(int src, int dst, int cost=1);
        int  get_edge(int src, int dst);
        
        void add_edge(char src, char dst, int cost=1);
        void add_bi_dir_edge(char src, char dst, int cost=1);
        int  get_edge(char src, char dst);

        void print_graph_matrix();
        void print_graph_list();
};