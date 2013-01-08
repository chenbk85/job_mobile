//-----------------------------------------------------------------
class fvector_int
{
private:
	int* v; // v points to the allocated area

public:

	explicit fvector_int(std::size_t n) : v(new int[n]) {}
	
	int get(std::size_t n) const 
	{ 
		return v[n]; 
	}
	
	void set(std::size_t n, int a) 
	{ 
		v[n] = a; 
	}
};









//-----------------------------------------------------------------
void foobar()
{
	fvector_int squares(std::size_t(64));
	
	for (size_t i = 0; i < 64; ++i)
			squares.set(i, int(i * i));
}

//-----------------------------------------------------------------

void foobar()
{
	fvector_int foo(size_t(15));

	//some stuff
	std::swap(foo[0], foo[14]);
}


inline
void fvector_int_swap(	fvector& v, 
						std::size_t n, 
						std::size_t m)
{
	int tmp = v.get(n);
	v.set(n, v.get(m));
	v.set(m, tmp);
}

void foobar()
{
	fvector_int foo(size_t(15));
	//some stuff
	fvector_int_swap(foo, 0, 14);	
}

//-----------------------------------------------------------------

void foobar()
{
	fvector_int foo(size_t(15));
	fvector_int bar(size_t(15));
	//some stuff
	std::swap(foo[0], bar[0]);
}


inline
void fvector_int_swap(	fvector& v, std::size_t n,
						fvector& u, std::size_t m)
{
	int tmp = v.get(n);
	v.set(n, u.get(m));
	u.set(m, tmp);
}





void foobar()
{
	fvector_int foo(size_t(15));
	fvector_int bar(size_t(15));
	//some stuff
	fvector_int_swap(foo, 0, bar, 0);
}



//-----------------------------------------------------------------

class fvector_int
{
private:
	int* v; // v points to the allocated memory

public:
	explicit fvector_int(std::size_t n) : v(new int[n]) {}
	
	int& operator[](std::size_t n) 
	{
		return v[n];
	}
	const int& operator[](std::size_t n) const 
	{
		return v[n];
	}
};

//-----------------------------------------------------------------

void foobar()
{
	fvector_int foo(std::size_t(10)) = b;
	// fill the fvector with integers

	std::sort(&foo[0], &foo[0] + 10);

	int a[10];

}

//-----------------------------------------------------------------
void foobar()
{
	std::vector<T> v;
	//some stuff with v

	sort(v.begin(), v.end());
	
	//some stuff with v

	if (!v.empty()) 
		sort(&*v.begin(), &*v.begin() + v.size());

	//some stuff with v	
}

//[ )

void foobar(std::vector<T> v)
{
	sort(&*v.begin(), &*v.begin() + v.size()); // may be crash!! Why?

	//some stuff with v

	if (!v.empty()) 
		sort(&*v.begin(), &*v.end()); //  crash!!. Why?
}

//-----------------------------------------------------------------
	
void print_shuffled_integers(std::size_t n)
{
	fvector_int integers(n);

	for (std::size_t i = 0; i < n; ++i)
		integers[i] = int(i);

	std::random_shuffle(&integers[0], &integers[n]);

	for (std::size_t i = 0; i < n; ++i)
		std::cout << integers[i] << std::endl;

	// called integers::~fvector_int();
};

//-----------------------------------------------------------------
class fvector_int
{
private:
	int* v; // v points to the allocated memory
public:
	explicit fvector_int(std::size_t n) : v(new int[n]) {}
	~fvector_int() { delete [] v; }
	int& operator[](std::size_t n) 
	{
		return v[n];
	}
	const int& operator[](std::size_t n) const 
	{
		return v[n];
	}
};
//-----------------------------------------------------------------
void foo_bar
{
	int foo_array[10];
	foo_function(foo_array);

	struct foo_strcut
	{
		int foo_array[10];
	};
	foo_function(foo_strcut);
};

//-----------------------------------------------------------------
template < std::size_t m>
struct cvector_int 
{
	int values[m];

	int& operator[](std::size_t n) 
	{
		assert(n < m);
		return values[n];
	}
	const int& operator[](std::size_t n) const 
	{
		assert(n < m);
		return values[n];
	}
};

template<std::size_t m>
cvector_int<m> reverse_copy(cvector_int<m> x) 
{
	std::reverse(&x[0], &x[m]);
	return x;
}

void foobar()
{
	cvector_int<5> array5_a;
	for(std::size_t i = 0; i < 5; i++)
		array5_a[i] = i+1;
	// array5_a={1, 2, 3, 4, 5}

	cvector_int<5> array5_b = reverse_copy(array5_a);
	// array5_b={5, 4, 3, 2, 1}
	// array5_a={1, 2, 3, 4, 5}
}

//-----------------------------------------------------------------
class fvector_int
{
private:
	std::size_t length; // the size of the allocated area
	int* v;				// the pointer to the allocated area
public:
	fvector_int(const fvector_int& x);
	explicit fvector_int(std::size_t n)
		: length(n), v(new int[n]) {}

	~fvector_int() { delete [] v; }
	
	int& operator[](std::size_t n) 
	{
		assert(n < length);
		return v[n];
	}
	const int& operator[](std::size_t n) const 
	{
		assert(n < length);
		return v[n];
	}
};

// copy constructor
fvector_int::fvector_int(const fvector_int& x)
	:	length(x.length), 
		v(new int[x.length]) 
{
		for(std::size_t i = 0; i < length; ++i)
			(*this)[i] = x[i];
}

//-----------------------------------------------------------------
template<typename T>
void foo_01(T &b)
{
	{
		T a(b);	// copy constructor
	}
	{
		T a;	// default constructor
		a = b;	// assignment operator
	}
}

//-----------------------------------------------------------------
T& T::operator=(const T& x)
{
	if (this != &x) 
	{
		this -> ~T();		// destroy object in place
		new (this) T(x);	// construct it in place, in other words 'placement new'
	}
	return *this;
}

//-----------------------------------------------------------------

template <typename T>
void foo()
{
	T a, b, c;
	a = (b = c);	// dangerous
	(a = b) = c;	// dangerous!! why?
}

//-----------------------------------------------------------------
class fvector_int
{
private:
	std::size_t length; // the size of the allocated area
	int* v;				// the pointer to the allocated area

public:
	fvector_int(const fvector_int& x);

	explicit fvector_int(std::size_t n)
		: length(n), v(new int[n]) {}

	~fvector_int() { delete [] v; }

	fvector_int& operator=(const fvector_int& x);

	int& operator[](std::size_t n) 
	{
		assert(n < length);
		return v[n];
	}
	const int& operator[](std::size_t n) const 
	{
		assert(n < length);
		return v[n];
	}
};

// copy constructor
fvector_int::fvector_int(const fvector_int& x)
	: length(x.length), v(new int[x.length]) 
{
		for(std::size_t i = 0; i < length; ++i)
			(*this)[i] = x[i];
}
// assignment operator
fvector_int& fvector_int::operator=(const fvector_int& x)
{
	if (this != &x)
	{
		if (this->length == x.length)
		{
			for (std::size_t i = 0; i < length; ++i)
				(*this)[i] = x[i];
		}
		else 
		{
			this -> ~fvector_int ();
			new (this) fvector_int (x);
		}
	}
	return *this;
}

//-----------------------------------------------------------------
template <typename T>
void foo(const T& b)
{	
	{
		T a(b); // copy constructor		
	}
	{
		T a;	// default constructor
		a = b;	// assignment operator		
	}	
}
// for the resource requirements for default constructors. 
// It is almost totally clear that the only resource 
//	that a default constructor should allocate is 
//	the stack space for the object.

//-----------------------------------------------------------------
class fvector_int
{
private:
	std::size_t length; // the size of the allocated area
	int* v;				// the pointer to the allocated area
public:
	fvector_int() : length(std::size_t(0)), v(NULL) {}

	fvector_int(const fvector_int& x);

	explicit fvector_int(std::size_t n)
		: length(n), v(new int[n]) {}

	~fvector_int() { delete [] v; }

	fvector_int& operator=(const fvector_int& x);

	int& operator[](std::size_t n) {
		assert(n < length);
		return v[n];
	}
	const int& operator[](std::size_t n) const {
		assert(n < length);
		return v[n];
	}
};

//-----------------------------------------------------------------
template <typename T>
void foo(const T& b)
{	
	{
		T a(b);
		assert(a == b);
	}
	{
		T a; 
		a = b; 
		assert(a == b);
	}	
}
// It is a self-evident rule: 
//		to make a copy means to create an object equal to the original.


//-----------------------------------------------------------------
template <std::size_t m>
bool operator==(const cvector_int<m>& x,
				const cvector_int<m>& y)
{
	for (std::size_t i(0); i < m; ++i)
		if (x[i] != y[i]) return false;

	return true;
}

//-----------------------------------------------------------------
class fvector_int
{
private:
	std::size_t length; // the size of the allocated area
	int* v;				 // v points to the allocated area

public:
	fvector_int() : length(std::size_t(0)), v(NULL) {}

	fvector_int(const fvector_int& x);

	explicit fvector_int(std::size_t n)
		: length(n), v(new int[n]) {}

	~fvector_int() { delete [] v; }

	fvector_int& operator=(const fvector_int& x);

	// note that not member function but global function
	friend std::size_t size(const fvector_int& x) 
	{
		return x.length;
	}

	int& operator[](std::size_t n) 
	{
		assert(n < size(*this));
		return v[n];
	}
	const int& operator[](std::size_t n) const 
	{
		assert(n < size(*this));
		return v[n];
	}
};

// global scoped equality operator 
bool operator==(const fvector_int& x,
				const fvector_int& y) 
{
		if (size(x) != size(y)) 
			return false;

		for (std::size_t i = 0; i < size(x); ++i)
			if (x[i] != y[i]) return false;

		return true;
}

// rewrite copy constructor using global function size
fvector_int::fvector_int(const fvector_int& x)
	: length(size(x)), v(new int[size(x)])
{
	for(std::size_t i = 0; i < size(x); ++i)
		(*this)[i] = x[i];
}

// rewrite assignment operator using global function size
fvector_int& fvector_int::operator=(const fvector_int& x)
{
	if (this != &x)
	{
		if (size(*this) == size(x))
		{
			for (std::size_t i = 0;	i < size(*this); ++i)
				(*this)[i] = x[i];
		}
		else 
		{
			this -> ~fvector_int ();
			new (this) fvector_int(x); // placement new
		}
	}

	return *this;
}


//-----------------------------------------------------------------
template <std::size_t m>
struct cvector_int;

template <std::size_t m>
inline
size_t size(const cvector_int<m>&)
{
	return m;
}

template < std::size_t m>
struct cvector_int 
{
	int values[m];
	int& operator[](std::size_t n) 
	{
		assert(n < size(*this));
		return values[n];
	}
	const int& operator[](std::size_t n) const 
	{
		assert(n < size(*this));
		return values[n];
	}
};


template <std::size_t m, std::size_t n>
bool operator==(const cvector_int<m>& x,
	const cvector_int<n>& y)
{
	if (size(x) != size(y)) 
		return false;

	for (std::size_t i = 0; i < size(x); ++i)
		if (x[i] != y[i]) return false;

	return true;
}

{
	cvector_int<3> a;
	cvector_int<5> b;

	if (a==b)
		return false;
	return true;

}
//-----------------------------------------------------------------