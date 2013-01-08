#include <stdafx.h>
#include <iostream>
#include <boost/random.hpp>
using namespace std;
using namespace boost;
 
int main_random()
{
    // -3이상4이하의 정수를 램덤하게 생성하는 의사난수계열 작성
    mt19937       gen;
    uniform_int<> dst( -3, 4 );
    variate_generator< mt19937, uniform_int<>  > rand( gen, dst );
 
    // 20개 출려 해 본다
    for( int i=0; i!=20; ++i )
        cout << rand() << ' ';


    return 0;
}

 
#include <iostream>
#include <ctime>
#include <boost/random.hpp>
using namespace std;
using namespace boost;
 
// 사이크로 클래스
//   Lagged Fibonacci법을 사용하여、1～6의 정수를 랜던하게 반환한다
class Dice
{
public:
    Dice( uint32_t seed )
      : rand( lagged_fibonacci607(seed), uniform_int<>(1,6) ) {}
    int operator()() { return rand(); }
 
private:
    variate_generator< lagged_fibonacci607, uniform_int<> > rand;
};
 
int main_random2()
{
	cout << "\n\nmain_random2 test" <<endl;
    // 현재시간을 기초로 사이크로 초기화
    uint32_t seed = static_cast<uint32_t>( time(0) );
    Dice xiA( seed   );
    Dice xiB( seed+1 );
 
    while( true )
    {
        // 랜덤하게 값을 빼낸다
        const int    a = xiA();
        const int    b = xiB();
        const bool cho = ((a+b)%2 == 0);
 
        // 플레이어에게 묻는다
        cout << ">>> 두개의 숫자가 같은가(0) 다른가(1)인가？ ";
        int guess=-1; cin >> guess;
        if( guess!=0 && guess!=1 ) break;
 
        // 결과의 표시
        cout << a << " " << b << " 가 "
             << (cho?"같음":"다름")  << "."
             << (cho ^ (guess==1) ? "당첨！" : "꽝！")
             << endl;
    }
    return 0;
}


 
#include <iostream>
#include <ctime>
#include <algorithm>
#include <boost/random.hpp>
using namespace std;
using namespace boost;
 
int main_random3()
{
    const int CarArrivalPerMinute = 3; // 차가 1분 사이에 도착하는 평균 대수
    const int CapacityPerMinute   = 3; // 요금소가 1분간에 팔리는 대수
    // 난수 생성기
    // ?분포는 평균 CarArrivalPerMinute포와슨(?)분포
    variate_generator< mt19937, poisson_distribution<> >
      rand( mt19937(static_cast<uint32_t>(time(0))),
            poisson_distribution<int>(CarArrivalPerMinute) ) ;
 
    // 30분간 시뮬레이션
    int car = 0;
    for(int m=0; m!=30; ++m)
    {
         car += rand();                          // 랜덤한 도착 대수
         car  = max( car-CapacityPerMinute, 0 ); // 응대
         for(int i=0; i!=car; ++i)               // 기다리는 대수 분"凸"를 표시
             cout << "凸";
         cout << endl;
    }
    return 0;
}
