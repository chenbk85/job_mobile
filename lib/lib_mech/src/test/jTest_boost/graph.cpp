#include <stdafx.h>

#include <iostream>                  // for std::cout
  #include <utility>                   // for std::pair
  #include <algorithm>                 // for std::for_each
  #include <boost/graph/graph_traits.hpp>
  #include <boost/graph/adjacency_list.hpp>
  #include <boost/graph/dijkstra_shortest_paths.hpp>
 
  using namespace boost;
  
  int main_graph()
  {
    // �׷����� Ÿ���� ���� typedef�� �ۼ�
    typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;
 
    // �����̱� ������ ���ǻ��� ���� �����
    enum { A, B, C, D, E, N };
    const int num_vertices = N;
    const char* name = "ABCDE";
 
    // �׷����� ������ ���´�.
    typedef std::pair<int, int> Edge;
    Edge edge_array[] = 
    { Edge(A,B), Edge(A,D), Edge(C,A), Edge(D,C),
      Edge(C,E), Edge(B,D), Edge(D,E), };
    const int num_edges = sizeof(edge_array)/sizeof(edge_array[0]);
 
    // �׷��� ������Ʈ�� ����
    Graph g(num_vertices);
 
    // �׷��� ������Ʈ�� ������ �߰�
    for (int i = 0; i < num_edges; ++i)
      add_edge(edge_array[i].first, edge_array[i].second, g);


/*
	//Accessing the Edge Set
	  std::cout << "edges(g) = ";
    graph_traits<Graph>::edge_iterator ei, ei_end;
    for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
        std::cout << "(" << index[source(*ei, g)] 
                  << "," << index[target(*ei, g)] << ") ";
    std::cout << std::endl;
*/


	return 0;
  }
 

