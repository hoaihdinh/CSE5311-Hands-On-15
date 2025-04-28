#include <limits>

#include "bellman_ford.hpp"

int bell_ford_decoder(char n) {
    switch(n) {
        case 's': return 0;
        case 't': return 1;
        case 'x': return 2;
        case 'y': return 3;
        case 'z': return 4;
    }
    return -1;
}

char bell_ford_encoder(int n) {
    switch(n) {
        case 0: return 's';
        case 1: return 't';
        case 2: return 'x';
        case 3: return 'y';
        case 4: return 'z';
        default: return '-';
    }
}

Graph* create_bell_ford_graph() {
    Graph* dijkstra_graph = new Graph(NUM_BELL_FORD, bell_ford_decoder, bell_ford_encoder);

    dijkstra_graph->add_edge('s', 't', 6);
    dijkstra_graph->add_edge('s', 'y', 7);
    dijkstra_graph->add_edge('t', 'x', 5);
    dijkstra_graph->add_edge('t', 'y', 8);
    dijkstra_graph->add_edge('t', 'z', -4);
    dijkstra_graph->add_edge('x', 't', -2);
    dijkstra_graph->add_edge('y', 'x', -3);
    dijkstra_graph->add_edge('y', 'z', 9);
    dijkstra_graph->add_edge('z', 's', 2);
    dijkstra_graph->add_edge('z', 'x', 7);
    
    return dijkstra_graph;
}

bell_ford_result* bellman_ford_algo(Graph& graph, char start_node, std::function<int(char)> decoder) {
    int num_nodes = graph.get_node_count();
    std::vector<std::tuple<int, int, int>>* all_edges = graph.get_edges();

    bell_ford_result* res = new bell_ford_result();

    res->src_name = start_node;
    for(int i = 0; i < num_nodes; i++) {
        if(i != decoder(start_node)) {
            res->dest.push_back({i, std::numeric_limits<int>::max(), '-'});
        } else {
            res->dest.push_back({i, 0, '-'});
        }
    }

    for(int i = 1; i < num_nodes; i++) {
        for(int j = 0; j < all_edges->size(); j++) {
            std::tuple<int, int, int>& edge = (*all_edges)[j];
            bell_ford_stats& u = res->dest[std::get<0>(edge)];
            bell_ford_stats& v = res->dest[std::get<1>(edge)];
            int u_to_v = std::get<2>(edge);

            if(u_to_v != 0 && v.dist_from_src > u.dist_from_src + u_to_v) {
                v.dist_from_src = u.dist_from_src + u_to_v;
                v.prev_node = u.tag;
            }
        }
    }

    for(int j = 0; j < all_edges->size(); j++) {
        std::tuple<int, int, int>& edge = (*all_edges)[j];
        bell_ford_stats& u = res->dest[std::get<0>(edge)];
        bell_ford_stats& v = res->dest[std::get<1>(edge)];
        int u_to_v = std::get<2>(edge);

        if(v.dist_from_src > u.dist_from_src + u_to_v) {
            delete res;
            return nullptr;
        }
    }

    return res;
}

void bell_ford_print_result(bell_ford_result& r, std::function<char(int)> encoder) {
    std::cout << "Source Node: " << r.src_name << std::endl;
    std::cout << "Node | Dist | Prev\n"
              << "-----+------+-----" << std::endl;
    for(int i = 0; i < r.dest.size(); i++) {
        bell_ford_stats s = r.dest[i];
        printf("%3c  |%3d   |%3c\n", encoder(s.tag), s.dist_from_src, encoder(s.prev_node));
    }
}