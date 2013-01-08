#include <stdafx.h>
#include <iostream>
#include <algorithm>
#include <boost/iterator_adaptors.hpp>
using namespace std;
using namespace boost;

// http://j2k.naver.com/j2k_frame.php/korean/shinh.skr.jp/boost/iterator_adaptors.html


struct MyLinkedList
{   // �ܹ��� ��ũ ����Ʈ ����
	MyLinkedList* next;
	int           data;
	MyLinkedList( MyLinkedList* n, int d )	: next(n), data(d) {}
public:
	struct iterator: iterator_adaptor<iterator,
	      MyLinkedList*,        // �� ���¸� ���̽���
	      int,                  // �� ���¸� �����ش�
	      forward_traversal_tag > // forward_iterator�� ���� �ʹ�.
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

	// ���� �� ���� ���׷���Ÿ�� ����� ����.
	for_each( a.begin(), a.end(), print );
	return 0;
}

/*
indirect_iterator 


* �����ڷ�, ���׷���Ÿ�� ����Ű�� �ִ� ���� ����Ű�� �ִ� ���� �����ֵ���(����) �ϴ� ������Դϴ�. 
std::vector<int> (��)��� �������� �� �� �־��µ�, std::vector<int*> (��)��� �� �� ����, �� ���� ����ϴ� ���Դϴ�. 

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
++ �����ڷ�,-- �����ڸ� �θ�����(����) �ϴ� ������Դϴ�. rbegin rend (��)�� ����ϸ� ���ٰ� �����ϴ� ���� �����Դϱ�? 


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

	// ��?����¸�߲��ͤ��ʤ�
	std::copy(is.rbegin(), is.rend(),
			  std::ostream_iterator<int>(std::cout, "\n"));

}



*/



/*
/// transform_iterator
* �������� ����ÿ�, ������ �Լ��� ��ȯ�� �ֵ���(����) �ϴ� ������Դϴ�. ���ϴٰ� �����մϴ�. std::map ��簡�� �ü� ��޷����� ����� ���ϰ� ����ϴ�. 

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
transform (��)�� �� ����ϴٸ�, ��ȯ �ÿ�, ������ �̿��ϴ� ��(��)�� �ٸ��ϴ�. ũ�� transform (��)�� �ʿ������� ��ī�ǰ� �ٹ��ϹǷ�, �װ��� ���ϰ� ���� ���� ����� �ּ���. 

������ �̻��� ������ �����Ƿ� ����� ���� ���� �ڵ带 ������ �ּ���. ������ �����ִµ� ������ �ƴ϶�� �����ϴ�, �̻��� �Լ� ������Ʈ�� ������ ������ �ȵ˴ϴ�.�Ƹ�. 

partial specialization �׸��� transform (��)�� ��ü �� �� ���� ������ �����ϴ� ���� �����Դϱ�? 



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