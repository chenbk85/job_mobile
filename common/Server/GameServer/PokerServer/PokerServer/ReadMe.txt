
/*
void Test_Print()
{
	vector<string> m_list;
	// m_list 에 데이타가 100개 있다.

	struct A
	{
		int iCount;

		A():iCount(0)
		{

		}
		bool operator() (string& str)
		{
			if( iCount > 50)
				return true;
			++this->iCount;
			std::cout << this->iCount << ":" << str << std::endl;
			
			return false;
		}
		void operator() (string& str)
		{
			++this->iCount;
			std::cout << this->iCount << ":" << str << std::endl;
		}
	}
	struct B
	{
		int iCount;

		B(int i):iCount(0)
		{

		}
		bool operator() (string& str)
		{
			if( iCount > 50)
				return true;
			++this->iCount;
			std::cout << this->iCount << ":" << str << std::endl;

			return false;
		}
	}
	std::find_if(m_list.begin(), m_list.end(), A());
	std::for_each(m_list.begin(), m_list.end(), B());


	for(int i=0; i< m_list.size() ; ++i)
	{
		cout << m_list[i];
	}
}
*/