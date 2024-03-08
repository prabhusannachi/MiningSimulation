/**
 * @file  BlockingQueue.cpp
 *
 * Blocking Queue class methods implementation
 */

#include "BlockingQueue.h"

template <typename T> void BlockingQueue<T>::push(T const& data)
{
	{
		std::lock_guard<std::mutex> lock(m_guard);
		m_queue.push(data);
	}
	m_signal.notify_one();
}

template <typename T> bool BlockingQueue<T>::empty() const
{
	std::lock_guard<std::mutex> lock(m_guard);
	return m_queue.empty();
}

template <typename T> uint64_t BlockingQueue<T>::size() const
{
	std::lock_guard<std::mutex> lock(m_guard);
	return m_queue.size();
}

template <typename T> bool BlockingQueue<T>::pop(T& value, int milliseconds)
{
	std::unique_lock<std::mutex> lock(m_guard);
	while (m_queue.empty())
	{
		if (m_signal.wait_for(lock, std::chrono::milliseconds(milliseconds) == std::cv_status::timeout))
		{
			return false;
		}
	}

	value = m_queue.front();
	m_queue.pop();
	return true;
}
