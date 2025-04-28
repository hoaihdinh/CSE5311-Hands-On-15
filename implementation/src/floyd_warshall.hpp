#pragma once

#include "graph.hpp"

#define NUM_FLOYD_WAR_NODES 5

struct floyd_warshall_result {
    std::vector<std::vector<int>> distances;
    std::vector<std::vector<char>> previous;
};

int floyd_warshall_decoder(char n);

char floyd_warshall_encoder(int n);

Graph* create_floyd_warshall_graph();

floyd_warshall_result* floyd_warshall_algo(Graph& graph, std::function<char(int)> encoder);

void floyd_warshall_print_result(floyd_warshall_result& r, std::function<char(int)> encoder);
