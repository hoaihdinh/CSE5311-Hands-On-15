#pragma once

#include <vector>

#include "graph.hpp"

#define NUM_DIJKSTRA_NODES 5

struct dijkstra_stats {
    int  tag;
    int  dist_from_src;
    int  prev_node;
};

struct dijkstra_result {
    char src_name;
    std::vector<dijkstra_stats> dest;
};

int dijkstra_decoder(char n);

char dijkstra_encoder(int n);

Graph* create_dijkstra_graph();

dijkstra_result* dijkstra_algo(Graph& graph, char start_node, std::function<int(char)> decoder);

void dijkstra_print_result(dijkstra_result& r, std::function<char(int)> encoder);

