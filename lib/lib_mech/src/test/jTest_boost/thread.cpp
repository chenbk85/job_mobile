#include <stdafx.h>
// �� �̾��ؿ䡦
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

	// �������� ���� ��ƾ
	void operator()()
	{
		// �⺻������ ���鷹�� ���� �� �д�
		for(;;)
		{
			scope_lock_t lock(m_mutex);
			if( m_isEnd ) break;

			// ������5�� ���� �ð��� ���
			boost::xtime xt;
			boost::xtime_get(&xt, boost::TIME_UTC);
			xt.sec += 1;

			// ���� ������ ��ٸ��ϴ�.�ٸ� 1�� ����ϸ� ��� ����
			if( m_exitCondition.timed_wait( lock, xt ) ) break;
			else cout << "\n xt = " << xt.sec <<  " �����ΰ� �����䣡: " << flush;
		}
	}

	void exit()
	{
		// ���Ḧ �����մϴ�.
		scope_lock_t lock(m_mutex);
		m_isEnd = true;
		m_exitCondition.notify_one();
	}
};

int main_thread()
{
	// ���⼭boost::ref(��)�� ����ϰ� �ִ� ����,myThread������ ī�� �Ұ��� Ŭ����
	// �Ͽ� ���� ������å�Դϴ�.���� �������� �Լ� �����ͳ�
	// �Լ� ������Ʈ�� �ǳ��־� �⵿�ϴ� ���� �����մϴ�.

	// ���� ������ �⵿
	myThread u;
	boost::thread thr( boost::ref(u) );

	// �Է� ���
	cout << "�����ΰ� ��: ";
	string str;
	getline( cin, str );

	// �Է��� ������, ������ �־����� �� ���� �����忡 ����
	u.exit();

	// ���� �������� ���� ���
	thr.join();

	cout << "Thank you!" << endl;
	return 0;
}
/*
���
�ƹ��͵� ���� �ʰ� ������, 5�� ���� ���� �� �ɴϴ�.(^^; 

*/