#include <iostream>
#include <iterator>
#include <vector>
#include <string>

// Spirit 의 코드를 인클루드 (			필요한 것만)
#include <boost/spirit/core.hpp>
#include <boost/spirit/iterator/file_iterator.hpp>

using namespace std;
using namespace boost::spirit;

// 값을 벡터에 카피한다 Semantic Action
// 편입의 append (와)과 같은 처리를 하고 있다(  (이)라고 생각한다)	 하지만, 여기에서는,
// 				  다브르크트가 겹치고 있으면,1개에 떨어뜨린다고 하는 처리가 추가되고 있다
struct push_val {
	vector<string>& values;
	push_val( vector<string>& vec ) : values(vec) { }

	template<class IteratorT>
		void operator()(IteratorT first, IteratorT last) const { // const 하지만 중요
#ifdef _MSC_VER
				// 				왜일까 VC6 	(이)라면 constructor　 　 에 의한 초기화가 잘 되지 않는다
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

// csv 파서
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

// 파서 호출용의 나팔 함수
template<typename IteratorT>
parse_info<IteratorT>
parse_csv(const IteratorT& first, const IteratorT& last, vector<string>& v)
{
	csv_parser csv(v);

	return parse(first, last, csv);
}

// 파일로부터csv 데이터를 읽어내 표시하는 예
int main_spirit_csv( int argc, char** argv)
{
	if (argc != 2) return 1;

	// Spirit 	하 forward		이테레이타를 요구하므로,ifstream 		그럼 역부족.
		// 		그 때문에 spirit 		하지만 준비해 있다 file_iterator 		(을)를 사용한다.
		typedef file_iterator<char> iterator_t;

	// 	파일을 열고, 그 선두를 가리키는 이테레이타를 생성
		iterator_t begin(argv[1]);
	if (!begin) {
		cout << "Unable to open file: " << argv[1] << endl;
		return -1;
	}

	// 	선두를 가리키는 이테레이타를 복제
		iterator_t first = begin;
	// 	종단을 가리키는 이테레이타를 생성
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

		// 		다음의 해석 위치를 설정
			first = info.stop;
	}

	return 0;
}

