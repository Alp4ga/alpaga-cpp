/*
  * @Author: Alpaga
  * @Date: 2020-02-08 12:08:39
 * @Last Modified by: Alpaga
 * @Last Modified time: 2020-02-20 15:34:41
*/

#pragma once

#include <queue>
#include <mutex>
#include <vector>
#include <thread>
#include <future>
#include <memory>
#include <functional>
#include <condition_variable>
#include <stdexcept>

/*! @namespace Alpaga
 * @brief include all file of Alpaga's cpp library
*/
namespace Alpaga {
	class ThreadPool;
};

/*! @class Alpaga::ThreadPool
 * @brief Create and manage threadPoll Cross-platforme
 *
*/
class Alpaga::ThreadPool {
	public:
		/*! @brief Constructor Generate thread
		 *
		 * @param nbrThread Number of thread in the thread pool 
		 *
		*/
		explicit ThreadPool(size_t nbrThread)
			: _stop(false)
		{
			for (size_t i = 0; i < nbrThread; i++) {
				_slaves.emplace_back([this] {
					while (true) {
						std::function<void()> task;
						{
							std::unique_lock<std::mutex> lock(_mutex);
							_condition.wait(lock, [this]{ return _stop || !_tasks.empty(); });
							if (_stop && _tasks.empty()) return;
							task = std::move(_tasks.front());
							_tasks.pop();
						}
						task();
					}
				});
			}
		}

		/*! @brief moreWork add task in salves queue
		 *
		 * @param fct Function to call by the thread
		 * @param arguments argument for the function task
		 *
		 * @return future -> guess the return type 
		*/
		template<class F, class... Args>
		auto task(F &&fct, Args&&... arguments) -> std::future<typename std::result_of<F(Args...)>::type>
		{
			using expectation = typename std::result_of<F(Args...)>::type;

			auto task = std::make_shared<std::packaged_task<expectation()>>(std::bind(std::forward<F>(fct), std::forward<Args>(arguments)...));
			std::future<expectation> result = task->get_future();
			{
				std::unique_lock<std::mutex> lock(_mutex);
				if (_stop)
					throw std::runtime_error("ThreadPoll kill during more workd.");
				_tasks.emplace([task](){ (*task)(); });
			}
			_condition.notify_one();
			return result;
		}

		/*!
		 * @brief Descrutor class Threadpool
		 * Wait thread to finish before destroy them
		*/
		~ThreadPool() noexcept
		{
			{
				std::unique_lock<std::mutex> lock(_mutex);
				_stop = true;
			}
			_condition.notify_all();
			for (auto &slave : _slaves)
        		slave.join();
		}

	private:
		/*!
		 * @brief All thread declare
		*/
		std::vector<std::thread> _slaves;
		/*!
		 * @brief Queue for task in comming
		*/
		std::queue<std::function<void()>> _tasks;
		/*!
		 * @brief Always keep save your thread
		*/
		std::mutex _mutex;
		/*!
		 * @brief Wait until action in comming
		*/
		std::condition_variable _condition;
		/*!
		 * @brief Stop thread pool if true
		*/
		bool _stop;
};