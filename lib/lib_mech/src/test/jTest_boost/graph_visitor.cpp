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
	// ���� ����Ʈ
	Edge links[] = {
		Edge(0,1), Edge(0,2),
		Edge(1,2), Edge(1,4),
		Edge(2,0), Edge(2,3),
		Edge(3,4),
	};
	// ������ �Ÿ�
	// (���⸦ �ٲٴ� ������0(��)��1�� ���̰� �־2 (��)��3 ������ �����,
	// ������ �ϵ� ǥ���� �� �ֽ��ϴ�.)
	int weights[] = {
		1, 1,
		1, 1,
		1, 1,
		1,
	};
	const size_t nEdges = sizeof(links)/sizeof(*links);

	// 5���� �׷����� ����
	Graph g( links, links+nEdges, weights, 5 );

	Vertex p[5] = {0};

	// ������ ��0(��)�� ��dijkstra�� �˰����� ����.
	// # ��0(��)�κ��� ��i�� �ִ� ��ο��� ������ , ��i�� ���� ��p[i]
	// # �� ���� �ű�κ���i�� ����Ǹ� ���ٴ�, ������ ����.
	Vertex s = 0;
	dijkstra_shortest_paths( g, s,
		visitor( make_dijkstra_visitor (
		record_predecessors( p, on_edge_relaxed() )
	)));

	cout << "shortest paths tree" << endl;

	// ����� ǥ��
	adjacency_list<> tree(5);
	graph_traits<Graph>::vertex_iterator vi, vend;
	for( tie(vi,vend) = vertices(g); vi!=vend; ++vi )
		if( *vi != p[*vi] )
			add_edge( p[*vi], *vi, tree );

	print_graph(tree);

	return 0;
}
/*
��¿�
0 --> 1 2
1 --> 4
2 --> 3
3 -->
4 -->

������,0 (��)�κ��� ���۵Ǵ� �ִ� ��Ʈ�� 

0 -- 1 
0 -- 2 
0 -- 2 -- 3 
0 -- 1 -- 4 
�� ���� �� �� �ֽ��ϴ�.0 -- 2 -- 3 -- 4 ���� ��� ������ �� ��, �̶��. 

*/