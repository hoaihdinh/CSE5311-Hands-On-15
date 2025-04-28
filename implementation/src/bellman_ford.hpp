#pragma once

#include <vector>

#include "graph.hpp"

#define NUM_BELL_FORD 5

struct bell_ford_stats {
    int  tag;
    int  dist_from_src;
    int  prev_node;
};

struct bell_ford_result {
    char src_name;
    std::vector<bell_ford_stats> dest;
};

int  bell_ford_decoder(char n);
char bell_ford_encoder(int n);

Graph* create_bell_ford_graph();

bell_ford_result* bellman_ford_algo(Graph& graph, char start_node, std::function<int(char)> decoder);

void bell_ford_print_result(bell_ford_result& r, std::function<char(int)> encoder);
