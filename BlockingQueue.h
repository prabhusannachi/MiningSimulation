/**
 * @file  BlockingQueue.h
 *
 * Class for the Blocking Queue. This class provides
 * a set of methods to add the item, get the item from
 * blocking queue, check the size of the queue and its
 * empty status.
 */

#include <thread>
#include <unistd.h>
#include <queue>
#include <mutex>
#include <condition_variable>

/**
 * Blocking Queue class
 * @tparam T the type of data stored in the queue
 */
template<typename T> class BlockingQueue
{
public:
   /**
	* Add the item in the queue.
	*
	* @param[in] data Data to be added in the queue.
	*/
    void push(T const& data);
    /**
 	* Check if queue is empty or not
 	*
 	*  @return bool  True if queue is empty or False.
 	*/
    bool empty() const;
    /**
 	* Get the size of the queue
 	*
 	* @return Unsigned Integer   Size of the queue.
 	*/
    uint64_t  size() const;
    /**
 	* Get the first item from the queue.
 	* If queue is empty, this call is blocked
 	* until data is added in the queue or given
 	* timeout value is expired.
 	*
 	* @param[out] value         Stores the data retrieved from the queue.
 	* @param[in] milliseconds   Timeout value in milliseconds.
 	* @return    bool           True if it copies the data from the queue in the value
 	*                           out parameter.False if there is no data in the queue and
 	*                           timeout is expired
 	*/
    bool pop(T& value, int milliseconds);

private:
    // Queue to store the data
    std::queue<T> m_queue;
    // Mutex used to lock with conditional variable
    mutable std::mutex m_guard;
    // Conditional variable to synchronize the status of the queue.
    std::condition_variable m_signal;
};
