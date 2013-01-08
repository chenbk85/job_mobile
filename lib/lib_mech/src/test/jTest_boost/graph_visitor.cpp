#include <stdafx.h>
#include <iostream>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/graph_utility.hpp>

using namespace std;
using namespace boost;


typedef adjacency_list< vecS, vecS, directedS,
	no_property,
	property<edge_weight_t, int>
> Graph;

typedef graph_traits<Graph>::vertex_descriptor
  Vertex;

typedef pair<int,int>
  Edge;

//http://j2k.naver.com/j2k_frame.php/korean/www.kmonos.net/alang/boost/classes/graph.html
int main_graph_visitor()
{
	// 옆의 리스트
	Edge links[] = {
		Edge(0,1), Edge(0,2),
		Edge(1,2), Edge(1,4),
		Edge(2,0), Edge(2,3),
		Edge(3,4),
	};
	// 각변의 거리
	// (여기를 바꾸는 것으로0(와)과1의 사이가 멀어서2 (와)과3 하지만 가까운,
	// 　같은 일도 표현할 수 있습니다.)
	int weights[] = {
		1, 1,
		1, 1,
		1, 1,
		1,
	};
	const size_t nEdges = sizeof(links)/sizeof(*links);

	// 5점의 그래프를 구축
	Graph g( links, links+nEdges, weights, 5 );

	Vertex p[5] = {0};

	// 시점을 점0(으)로 해dijkstra의 알고리즘을 실행.
	// # 점0(으)로부터 점i에 최단 경로에서 가려면 , 점i의 전에 점p[i]
	// # 에 가서 거기로부터i에 진행되면 좋다는, 정보가 들어간다.
	Vertex s = 0;
	dijkstra_shortest_paths( g, s,
		visitor( make_dijkstra_visitor (
		record_predecessors( p, on_edge_relaxed() )
	)));

	cout << "shortest paths tree" << endl;

	// 결과의 표시
	adjacency_list<> tree(5);
	graph_traits<Graph>::vertex_iterator vi, vend;
	for( tie(vi,vend) = vertices(g); vi!=vend; ++vi )
		if( *vi != p[*vi] )
			add_edge( p[*vi], *vi, tree );

	print_graph(tree);

	return 0;
}
/*
출력예
0 --> 1 2
1 --> 4
2 --> 3
3 -->
4 -->

요컨데,0 (으)로부터 시작되는 최단 루트는 

0 -- 1 
0 -- 2 
0 -- 2 -- 3 
0 -- 1 -- 4 
인 것을 알 수 있습니다.0 -- 2 -- 3 -- 4 등은 길기 때문에 안 됨, 이라고. 

*/