#include <iostream>

#include "dijkstra.hpp"
#include "bellman_ford.hpp"
#include "floyd_warshall.hpp"

int main() {
    std::cout << "===== DIJKSTRA DEMO =====" << std::endl;
    Graph* dijkstra_graph = create_dijkstra_graph();
    dijkstra_graph->print_graph_matrix();
    dijkstra_graph->print_graph_list();

    dijkstra_result* dijkstra_r = dijkstra_algo(*dijkstra_graph, 's', dijkstra_decoder);
    dijkstra_print_result(*dijkstra_r, dijkstra_encoder);
    delete dijkstra_r;
    std::cout << std::endl;

    std::cout << "===== BELLMAN FORD DEMO =====" << std::endl;
    Graph* bellman_ford_graph = create_bell_ford_graph();
    bellman_ford_graph->print_graph_matrix();
    bellman_ford_graph->print_graph_list();

    bell_ford_result* bell_ford_r = bellman_ford_algo(*bellman_ford_graph, 's', bell_ford_decoder);
    if(bell_ford_r != nullptr) {
        bell_ford_print_result(*bell_ford_r, bell_ford_encoder);
        delete bell_ford_r;
    }
    std::cout << std::endl;

    std::cout << "===== FLOYD WARSHALL DEMO =====" << std::endl;
    Graph* floyd_warshall_graph = create_floyd_warshall_graph();
    floyd_warshall_graph->print_graph_matrix();
    floyd_warshall_graph->print_graph_list();

    floyd_warshall_result* floyd_warshall_r = floyd_warshall_algo(*floyd_warshall_graph, floyd_warshall_encoder);
    floyd_warshall_print_result(*floyd_warshall_r, floyd_warshall_encoder);
    delete floyd_warshall_r;
    std::cout << std::endl;


    delete dijkstra_graph;
    delete bellman_ford_graph;
    delete floyd_warshall_graph;
    return 0;
}