#include <stdafx.h>
#include <iostream>
#include <boost/random.hpp>
using namespace std;
using namespace boost;
 
int main_random()
{
    // -3�̻�4������ ������ �����ϰ� �����ϴ� �ǻ糭���迭 �ۼ�
    mt19937       gen;
    uniform_int<> dst( -3, 4 );
    variate_generator< mt19937, uniform_int<>  > rand( gen, dst );
 
    // 20�� ��� �� ����
    for( int i=0; i!=20; ++i )
        cout << rand() << ' ';


    return 0;
}

 
#include <iostream>
#include <ctime>
#include <boost/random.hpp>
using namespace std;
using namespace boost;
 
// ����ũ�� Ŭ����
//   Lagged Fibonacci���� ����Ͽ���1��6�� ������ �����ϰ� ��ȯ�Ѵ�
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
    // ����ð��� ���ʷ� ����ũ�� �ʱ�ȭ
    uint32_t seed = static_cast<uint32_t>( time(0) );
    Dice xiA( seed   );
    Dice xiB( seed+1 );
 
    while( true )
    {
        // �����ϰ� ���� ������
        const int    a = xiA();
        const int    b = xiB();
        const bool cho = ((a+b)%2 == 0);
 
        // �÷��̾�� ���´�
        cout << ">>> �ΰ��� ���ڰ� ������(0) �ٸ���(1)�ΰ��� ";
        int guess=-1; cin >> guess;
        if( guess!=0 && guess!=1 ) break;
 
        // ����� ǥ��
        cout << a << " " << b << " �� "
             << (cho?"����":"�ٸ�")  << "."
             << (cho ^ (guess==1) ? "��÷��" : "�Σ�")
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
    const int CarArrivalPerMinute = 3; // ���� 1�� ���̿� �����ϴ� ��� ���
    const int CapacityPerMinute   = 3; // ��ݼҰ� 1�а��� �ȸ��� ���
    // ���� ������
    // ?������ ��� CarArrivalPerMinute���ͽ�(?)����
    variate_generator< mt19937, poisson_distribution<> >
      rand( mt19937(static_cast<uint32_t>(time(0))),
            poisson_distribution<int>(CarArrivalPerMinute) ) ;
 
    // 30�а� �ùķ��̼�
    int car = 0;
    for(int m=0; m!=30; ++m)
    {
         car += rand();                          // ������ ���� ���
         car  = max( car-CapacityPerMinute, 0 ); // ����
         for(int i=0; i!=car; ++i)               // ��ٸ��� ��� ��"��"�� ǥ��
             cout << "��";
         cout << endl;
    }
    return 0;
}
