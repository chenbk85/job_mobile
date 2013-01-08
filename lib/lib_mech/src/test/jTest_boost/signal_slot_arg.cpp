#include <stdafx.h>

void print_sum(float x, float y)
{
  std::cout << "The sum is " << x+y << std::endl;
}

void print_product(float x, float y)
{
  std::cout << "The product is " << x*y << std::endl;
}

void print_difference(float x, float y)
{
  std::cout << "The difference is " << x-y << std::endl;
}

void print_quotient(float x, float y)
{
  std::cout << "The quotient is " << x/y << std::endl;
}


float product(float x, float y) { return x*y; }
float quotient(float x, float y) { return x/y; }
float sum(float x, float y) { return x+y; }
float difference(float x, float y) { return x-y; }


template<typename T>
struct maximum
{
  typedef T result_type;

  template<typename InputIterator>
  T operator()(InputIterator first, InputIterator last) const
  {
    // If there are no slots to call, just return the
    // default-constructed value
    if (first == last)
      return T();

    T max_value = *first++;
    while (first != last) {
      if (max_value < *first)
        max_value = *first;
      ++first;
    }
  
    return max_value;
  }
};
void test0()
	{
		boost::signal<float (float x, float y), 
					maximum<float> > sig;
		sig.connect(&quotient);
		sig.connect(&product);
		sig.connect(&sum);
		sig.connect(&difference);
		std::cout << sig(5, 3) << std::endl;
	}



template<typename Container>
struct aggregate_values
{
  typedef Container result_type;

  template<typename InputIterator>
  Container operator()(InputIterator first, InputIterator last) const
  {
    return Container(first, last);
  }
};


static void test1()
{

boost::signal<float (float, float), 
    aggregate_values<std::vector<float> > > sig;

sig.connect(&quotient);
sig.connect(&product);
sig.connect(&sum);
sig.connect(&difference);

std::vector<float> results = sig(5, 3);
std::copy(results.begin(), results.end(), 
    std::ostream_iterator<float>(cout, "-- \n"));


}

/*
//Blocking Slots (Beginner)

void test2()
{
	boost::signals::connection c = sig.connect(HelloWorld());
	sig(); // Prints "Hello, World!"

	c.block(); // block the slot
	assert(c.blocked());
	sig(); // No output: the slot is blocked

	c.unblock(); // unblock the slot
	sig(); // Prints "Hello, World!"

}
*/

int main_signal_slot_arg()
{
	boost::signal<void (float, float)> sig;

	sig.connect(&print_sum);
	sig.connect(&print_product);
	sig.connect(&print_difference);
	sig.connect(&print_quotient);

	sig(5, 3);

	{
		boost::signal<float (float x, float y)> sig;

		sig.connect(&product);
		sig.connect(&quotient);
		sig.connect(&sum);
		sig.connect(&difference);
		std::cout << sig(5, 3) << std::endl;
	}

	test0();
	test1();

	return 0;
}
