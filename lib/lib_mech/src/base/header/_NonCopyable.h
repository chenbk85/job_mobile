#pragma once

namespace nMech
{
	class _NonCopyable
    {
    protected:
		_NonCopyable(void)
        {
        }
        ~_NonCopyable(void)
        {
        }

	private:
		_NonCopyable(const _NonCopyable &);
        const _NonCopyable &operator=(const _NonCopyable &);
    };
}
