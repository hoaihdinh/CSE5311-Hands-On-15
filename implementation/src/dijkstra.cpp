#include <iostream>
#include <functional>
#include <limits>
#include <cstdio>
#include <queue>

#include "dijkstra.hpp"

struct CompareDijkstraStats {
    bool operator()(const dijkstra_stats& a, const dijkstra_stats& b) const {
        return a.dist_from_src > b.dist_from_src;
    }
};

int dijkstra_decoder(char n) {
    switch(n) {
        case 's': return 0;
        case 't': return 1;
        case 'x': return 2;
        case 'y': return 3;
        case 'z': return 4;
    }
    return -1;
}

char dijkstra_encoder(int n) {
    switch(n) {
        case 0: return 's';
        case 1: return 't';
        case 2: return 'x';
        case 3: return 'y';
        case 4: return 'z';
        default: return '-';
    }
}


Graph* create_dijkstra_graph() {
    Graph* dijkstra_graph = new Graph(NUM_DIJKSTRA_NODES, dijkstra_decoder, dijkstra_encoder);

    dijkstra_graph->add_edge('s', 't', 10);
    dijkstra_graph->add_edge('s', 'y', 5);
    dijkstra_graph->add_edge('t', 'x', 1);
    dijkstra_graph->add_edge('t', 'y', 2);
    dijkstra_graph->add_edge('x', 'z', 4);
    dijkstra_graph->add_edge('y', 't', 3);
    dijkstra_graph->add_edge('y', 'x', 9);
    dijkstra_graph->add_edge('y', 'z', 2);
    dijkstra_graph->add_edge('z', 's', 7);
    dijkstra_graph->add_edge('z', 'x', 6);
    
    return dijkstra_graph;
}

dijkstra_result* dijkstra_algo(Graph& graph, char start_node, std::function<int(char)> decoder) {
    int num_nodes = graph.get_node_count();

    std::priority_queue<dijkstra_stats, std::vector<dijkstra_stats>, CompareDijkstraStats> unvisited;

    dijkstra_result* res = new dijkstra_result();
    
    res->src_name = start_node;
    for(int i = 0; i < num_nodes; i++) {
        if(i != decoder(start_node)) {
            res->dest.push_back({i, std::numeric_limits<int>::max(), '-'});
        } else {
            res->dest.push_back({i, 0, '-'});
        }
        unvisited.push(res->dest[i]);
    }

    while(!unvisited.empty()) {
        dijkstra_stats u = unvisited.top();
        unvisited.pop();

        std::priority_queue<dijkstra_stats, std::vector<dijkstra_stats>, CompareDijkstraStats> updated_unvisited;

        while(!unvisited.empty()) {
            dijkstra_stats v = unvisited.top();
            unvisited.pop();
            int u_to_v = graph.get_edge(u.tag, v.tag);
            if(u_to_v != 0 && v.dist_from_src > u.dist_from_src + u_to_v) {

                v.dist_from_src = u.dist_from_src + u_to_v;
                v.prev_node = u.tag;
                res->dest[v.tag] = v;
            }
            updated_unvisited.push(v);
        }

        unvisited = updated_unvisited;
    }

    return res;
}

void dijkstra_print_result(dijkstra_result& r, std::function<char(int)> encoder) {
    std::cout << "Source Node: " << r.src_name << std::endl;
    std::cout << "Node | Dist | Prev\n"
              << "-----+------+-----" << std::endl;
    for(int i = 0; i < r.dest.size(); i++) {
        dijkstra_stats s = r.dest[i];
        printf("%3c  |%3d   |%3c\n", encoder(s.tag), s.dist_from_src, encoder(s.prev_node));
    }
}