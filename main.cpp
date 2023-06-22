#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>

#include<iostream>
#include<climits>     
using namespace std;


unsigned vertex_with_minimum_dist(std::vector<unsigned> dist, std::vector<bool> visited, unsigned nb_inter) 
{
	unsigned min = UINT_MAX;
    unsigned vertex = 0;
              
	for(unsigned i = 1; i <= nb_inter;++i) 
	{
		if(visited[i] == false && dist[i] <= min)      
		{
			min = dist[i];
			vertex = i;
		}
	}
	return vertex;
}

void dijkstra(std::vector<std::vector<unsigned>> graph, unsigned source, unsigned nb_inter)
{
	std::vector<unsigned> dist(nb_inter + 1); // integer array to calculate minimum distance for each node.                            
	std::vector<bool> visited(nb_inter + 1); // boolean array to mark visted/unvisted for each node.

	for(unsigned i = 1; i<nb_inter + 1; ++i)
	{
		dist[i] = UINT_MAX;
		visited[i] = false;	
	}
	
	dist[source] = 0; // Distance to source (1) is 0.       
	
	for(unsigned i = 1; i < nb_inter + 1; ++i)                           
	{
		unsigned vertex_min_dist = vertex_with_minimum_dist(dist, visited, nb_inter); 
		visited[vertex_min_dist] = true;
		for(unsigned i = 1; i < nb_inter + 1; ++i)                  
		{
			// Updating the minimum distance for the particular vertex.
			if(!visited[i] && graph[vertex_min_dist][i] && dist[vertex_min_dist] != UINT_MAX
                && dist[vertex_min_dist] + graph[vertex_min_dist][i] < dist[i])
				dist[i] = dist[vertex_min_dist] + graph[vertex_min_dist][i];
		}
	}
    std::cout << dist[1];
	for(unsigned i = 2; i < nb_inter + 1; ++i)                      
	{
		std::cout<< " " << dist[i];
	}
    std::cout << std::endl;
}


std::vector<std::vector<unsigned>> build_city_graph(
    unsigned nb_inter, const std::vector<unsigned>& shortcuts
) {
    std::vector<std::vector<unsigned>> city_graph(nb_inter + 1, std::vector<unsigned>(nb_inter + 1, 0));

    for (unsigned i = 1; i < shortcuts.size(); ++i)
    {
        // Adding edge to all other vertices with the amout of energy the walk there requires.
        for (unsigned j = 1; j <= nb_inter; ++j) {
            long subtraction = i - j; // cast so overloaded abs isn't ambiguous.
            city_graph[i][j] = std::abs(subtraction);
        }
        // Adding edge for shortcut.
        city_graph[i][shortcuts[i]] = 1;

    }
    return city_graph;
}

void total_energy_for_all_paths(unsigned nb_inter, const std::vector<unsigned>& shortcuts) { 
    auto city_graph = build_city_graph(nb_inter, shortcuts);
    // Get shortest paths to all vertices starting from 1 (Mike's home):
    dijkstra(city_graph, 1, nb_inter);
}

int main() {
    // shortcuts starts at 1 to simplify.
    unsigned nb_inter;
    std::string str_nb_inter;
    getline(cin, str_nb_inter);
    std::vector<unsigned> shortcuts(std::stoi(str_nb_inter) + 1);

    unsigned shortcut;
    std::string text_line;
    getline(cin, text_line);
    std::istringstream line_stream(text_line);
    while (line_stream >> shortcut)
    {
        shortcuts.push_back(shortcut);
    }
    // for (const auto& sh:shortcuts) {
    //     std::cout <<sh << std::endl;
    // }
    total_energy_for_all_paths(nb_inter, shortcuts);
    return 0;
}