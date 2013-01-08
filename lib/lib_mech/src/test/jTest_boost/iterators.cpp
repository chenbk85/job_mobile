#include <stdafx.h>
#include <iostream>
#include <algorithm>
#include <boost/iterator_adaptors.hpp>
using namespace std;
using namespace boost;

// http://j2k.naver.com/j2k_frame.php/korean/shinh.skr.jp/boost/iterator_adaptors.html


struct MyLinkedList
{   // 단방향 링크 리스트 정의
	MyLinkedList* next;
	int           data;
	MyLinkedList( MyLinkedList* n, int d )	: next(n), data(d) {}
public:
	struct iterator: iterator_adaptor<iterator,
	      MyLinkedList*,        // 이 형태를 베이스로
	      int,                  // 이 형태를 돌려준다
	      forward_traversal_tag > // forward_iterator를 갖고 싶다.
	{
	  iterator( MyLinkedList* p )
	    : iterator_adaptor<iterator,
	         MyLinkedList*,int,forward_traversal_tag>( p ) {}

	  void increment()         { base_reference() = base()->next; }
	  int& dereference() const { return base_reference()->data; }
	};

	iterator begin(){ return iterator(this); }
	iterator end()  { return iterator(NULL); }
};

void print(int x)
{
	cout << x << endl;
}

int main_iterator_adaptor()
{
	// 100->200->300->400->500->600->end.
	MyLinkedList f( NULL, 600 );
	MyLinkedList e(  &f , 500 );
	MyLinkedList d(  &e , 400 );
	MyLinkedList c(  &d , 300 );
	MyLinkedList b(  &c , 200 );
	MyLinkedList a(  &b , 100 );

	// 조금 전 만든 이테레이타를 사용해 본다.
	for_each( a.begin(), a.end(), print );
	return 0;
}

/*
indirect_iterator 


* 연산자로, 이테레이타가 가리키고 있는 것이 가리키고 있는 것을 돌려주도록(듯이) 하는 어댑터입니다. 
std::vector<int> (이)라면 보통으로 할 수 있었는데, std::vector<int*> (이)라면 할 수 없어, 는 때에 사용하는 것입니다. 

*/
#include <boost/iterator_adaptors.hpp>

#include <vector>
#include <numeric>
#include <iostream>
#include <boost/iterator/indirect_iterator.hpp>

int main_indirect_iterator() {
	std::vector<int*> is;
	is.push_back(new int(1));
	is.push_back(new int(2));
	is.push_back(new int(3));

	// 6
	std::cout
	<< std::accumulate(
			boost::make_indirect_iterator(is.begin())
			,boost::make_indirect_iterator(is.end())
			, 0)
	<< std::endl;
	return 0;
}

/*
/// reverse_iterator
++ 연산자로,-- 연산자를 부르도록(듯이) 하는 어댑터입니다. rbegin rend (을)를 사용하면 좋다고 생각하는 것은 나만입니까? 


//#include <boost/reverse_iterator.hpp>

#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

int main_reverse_iterator() {
	std::vector<int> is1;
	is.push_back(1);
	is.push_back(2);
	is.push_back(3);
	is.push_back(4);

	std::copy(boost::make_reverse_iterator(is.end()),
			  boost::make_reverse_iterator(is.begin()),
			  std::ostream_iterator<int>(std::cout, "\n"));

	// ⅳ?ⅳΑ쨍뷔꼰촐ㄼㅚㄲ
	std::copy(is.rbegin(), is.rend(),
			  std::ostream_iterator<int>(std::cout, "\n"));

}



*/



/*
/// transform_iterator
* 연산자의 실행시에, 지정한 함수로 변환해 주도록(듯이) 하는 어댑터입니다. 편리하다고 생각합니다. std::map 라든가의 궁수 배급량에는 상당히 편리하게 여깁니다. 

*/
#include <boost/iterator_adaptors.hpp>

#include <vector>
#include <numeric>
#include <iostream>
#include <functional>

class Class {
public:
	explicit Class(int id) : id_(id) {}
	int getId() const { return id_; }
private:
	int id_;
};

int main_iterator_adaptors() {
	std::vector<Class> is;
	is.push_back(Class(1));
	is.push_back(Class(2));
	is.push_back(Class(3));

	std::cout
		<< std::accumulate(
			boost::make_transform_iterator(is.begin(),
										   std::mem_fun_ref(&Class::getId)),
			boost::make_transform_iterator(is.end(),
										   std::mem_fun_ref(&Class::getId)),
			0)
		<< std::endl;
	return 0;
}


/*
/// projection_iterator
transform (을)를 꼭 닮습니다만, 변환 시에, 참조를 이용하는 곳(중)이 다릅니다. 크다 transform (은)는 필연적으로 값카피가 다발하므로, 그것을 피하고 싶을 때에 사용해 주세요. 

사용법에 이상한 버릇이 있으므로 사용할 때는 샘플 코드를 응시해 주세요. 참조를 돌려주는데 참조가 아니라고 주장하는, 이상한 함수 오브젝트를 만들지 않으면 안됩니다.아마. 

partial specialization 그리고 transform (와)과 합체 할 수 있지 않을까 생각하는 것은 나만입니까? 



#include <boost/iterator_adaptors.hpp>

#include <vector>
#include <numeric>
#include <iostream>
#include <functional>
#include <iterator>
#include <string>

class Class {
public:
	explicit Class(const std::string& name) : name_(name) {}
	const std::string& getName() const { return name_; }
private:
	std::string name_;
};

struct GetName : public std::unary_function<Class, std::string> {
	const std::string& operator()(const Class& c) const {
		return c.getName();
	}
};

int main_projection_iterator() {
	std::vector<Class> is;
	is.push_back(Class("Alice"));
	is.push_back(Class("Bob"));
	is.push_back(Class("Carol"));

	std::copy(boost::make_const_projection_iterator<GetName>(is.begin()),
			  boost::make_const_projection_iterator<GetName>(is.end()),
			  std::ostream_iterator<std::string>(std::cout, "\n"));

}

*/

#if 0
#include "node_iterator2.hpp"
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>
#include <boost/mem_fn.hpp>
#include <cassert>

int main()
{
    std::auto_ptr<node<int> > nodes(new node<int>(42));
    nodes->append(new node<std::string>(" is greater than "));
    nodes->append(new node<int>(13));

    // Check interoperability
    assert(node_iterator(nodes.get()) == node_const_iterator(nodes.get()));
    assert(node_const_iterator(nodes.get()) == node_iterator(nodes.get()));
    
    assert(node_iterator(nodes.get()) != node_const_iterator());
    assert(node_const_iterator(nodes.get()) != node_iterator());
    
    std::copy(
        node_iterator(nodes.get()), node_iterator()
      , std::ostream_iterator<node_base>(std::cout, " ")
    );
    std::cout << std::endl;
    
    std::for_each(
        node_iterator(nodes.get()), node_iterator()
      , boost::mem_fn(&node_base::double_me)
    );

    std::copy(
        node_const_iterator(nodes.get()), node_const_iterator()
      , std::ostream_iterator<node_base>(std::cout, "/")
    );
    std::cout << std::endl;
    return 0;
}

#endif