#include <stdafx.h>
// 길어서 미안해요…
#include <iostream>
#include <string>
#include <boost/ref.hpp>
#include <boost/thread.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/condition.hpp>

using namespace std;

class myThread
{
	typedef boost::mutex::scoped_lock scope_lock_t;
	volatile bool                     m_isEnd;
	boost::mutex                      m_mutex;
	boost::condition                  m_exitCondition;

public:
	myThread() : m_isEnd(false) {}

	// 스렛드의 메인 루틴
	void operator()()
	{
		// 기본적으로 엔들레스 루프 해 둔다
		for(;;)
		{
			scope_lock_t lock(m_mutex);
			if( m_isEnd ) break;

			// 현재의5초 후의 시간을 계산
			boost::xtime xt;
			boost::xtime_get(&xt, boost::TIME_UTC);
			xt.sec += 1;

			// 종료 통지를 기다립니다.다만 1초 경과하면 대기 해제
			if( m_exitCondition.timed_wait( lock, xt ) ) break;
			else cout << "\n xt = " << xt.sec <<  " 무엇인가 쓰세요！: " << flush;
		}
	}

	void exit()
	{
		// 종료를 통지합니다.
		scope_lock_t lock(m_mutex);
		m_isEnd = true;
		m_exitCondition.notify_one();
	}
};

int main_thread()
{
	// 여기서boost::ref(을)를 사용하고 있는 것은,myThread하지만 카피 불가능 클래스
	// 일에 대한 고육지책입니다.물론 보통으로 함수 포인터나
	// 함수 오브젝트를 건네주어 기동하는 것은 가능합니다.

	// 재촉 스렛드 기동
	myThread u;
	boost::thread thr( boost::ref(u) );

	// 입력 대기
	cout << "무엇인가 써: ";
	string str;
	getline( cin, str );

	// 입력이 끝나면, 종료해 주었으면 한 것을 스렛드에 통지
	u.exit();

	// 재촉 스렛드의 종료 대기
	thr.join();

	cout << "Thank you!" << endl;
	return 0;
}
/*
출력
아무것도 박지 않고 있으면, 5초 마다 재촉 해 옵니다.(^^; 

*/