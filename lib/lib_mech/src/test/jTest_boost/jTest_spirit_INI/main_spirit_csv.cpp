#include <iostream>
#include <iterator>
#include <vector>
#include <string>

// Spirit �� �ڵ带 ��Ŭ��� (			�ʿ��� �͸�)
#include <boost/spirit/core.hpp>
#include <boost/spirit/iterator/file_iterator.hpp>

using namespace std;
using namespace boost::spirit;

// ���� ���Ϳ� ī���Ѵ� Semantic Action
// ������ append (��)�� ���� ó���� �ϰ� �ִ�(  (��)��� �����Ѵ�)	 ������, ���⿡����,
// 				  �ٺ긣ũƮ�� ��ġ�� ������,1���� ����߸��ٰ� �ϴ� ó���� �߰��ǰ� �ִ�
struct push_val {
	vector<string>& values;
	push_val( vector<string>& vec ) : values(vec) { }

	template<class IteratorT>
		void operator()(IteratorT first, IteratorT last) const { // const ������ �߿�
#ifdef _MSC_VER
				// 				���ϱ� VC6 	(��)��� constructor�� �� �� ���� �ʱ�ȭ�� �� ���� �ʴ´�
				string s;
			s.resize(distance(first, last));
			for (size_t i = 0; first != last; ++i) {
				s[i] = *first++;
			}
#else
				string s( first, last );
#endif
			string::size_type pos = 0;
			while (1) {
				pos = s.find("""", pos);
				if (pos == string::npos)
					break;
				++pos;
				s.erase(pos, 1);
			}
			values.push_back(s);
		}
};

// csv �ļ�
struct csv_parser : public grammar<csv_parser> {
	vector<string>& v;

	csv_parser( vector<string>& vec ) : v(vec) { }

	template<typename ScannerT>
	struct definition {
		rule<ScannerT> csv, val, quoted_val, naked_val;

		definition(const csv_parser& self)
		{
			csv = val >> *(',' >> val) >> (eol_p | end_p);

			val = *blank_p >>
				ch_p('"') >> quoted_val[push_val(self.v)] >> ch_p('"') >>
				*blank_p
				| naked_val[push_val(self.v)];

			quoted_val = *(~ch_p('"') | str_p(""""));

			naked_val = *(~ch_p(',') & ~ch_p('"') & ~ch_p('n'));
		}

		const rule<ScannerT>& start() const { return csv; }
	};
};

// �ļ� ȣ����� ���� �Լ�
template<typename IteratorT>
parse_info<IteratorT>
parse_csv(const IteratorT& first, const IteratorT& last, vector<string>& v)
{
	csv_parser csv(v);

	return parse(first, last, csv);
}

// ���Ϸκ���csv �����͸� �о ǥ���ϴ� ��
int main_spirit_csv( int argc, char** argv)
{
	if (argc != 2) return 1;

	// Spirit 	�� forward		���׷���Ÿ�� �䱸�ϹǷ�,ifstream 		�׷� ������.
		// 		�� ������ spirit 		������ �غ��� �ִ� file_iterator 		(��)�� ����Ѵ�.
		typedef file_iterator<char> iterator_t;

	// 	������ ����, �� ���θ� ����Ű�� ���׷���Ÿ�� ����
		iterator_t begin(argv[1]);
	if (!begin) {
		cout << "Unable to open file: " << argv[1] << endl;
		return -1;
	}

	// 	���θ� ����Ű�� ���׷���Ÿ�� ����
		iterator_t first = begin;
	// 	������ ����Ű�� ���׷���Ÿ�� ����
		iterator_t last = first.make_end();

	while ( first != last ) {
		vector<string> v;
		parse_info<iterator_t> info = parse_csv( first, last, v );

		if (!info.hit) {
			cout << "Error! Point: " << distance(begin, info.stop) << endl;
			break;
		}

		cout << "Parses OK:" << endl;
		for (vector<string>::size_type i = 0; i < v.size(); ++i)
			cout << i << ": " << v[i] << endl;

		cout << "-------------------------n";

		// 		������ �ؼ� ��ġ�� ����
			first = info.stop;
	}

	return 0;
}

