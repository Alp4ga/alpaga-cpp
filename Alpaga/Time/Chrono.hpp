/*
  * @Author: Alpaga
  * @Date: 2020-02-08 12:08:39
 * @Last Modified by: Alpaga
 * @Last Modified time: 2020-02-20 15:34:41
*/

#pragma once

#include <chrono>
#include <ostream>

/*! @namespace Alpaga
 * @brief Include all file of Alpaga's cpp library
*/
namespace Alpaga {
	/*! @namespace Time
	* @brief Include all Class/Function about time in C++
	*/
	namespace Time {
		class Chrono;
	};
}

/*! @class Alpaga::Time::Chrono
 * @brief Make easier the manipulation of std::chrono
 * 
*/
class Alpaga::Time::Chrono {
	public:
		/*!
		 * @brief Default constructor class Chrono
		*/
		Chrono() noexcept = default;
		/*!
		 * @brief Default descructor class Chrono
		*/
		~Chrono() noexcept = default;
		/*!
		 * @brief Default copy constructor class Chrono
		*/
		Chrono(const Chrono &) noexcept = default;
		/*!
		 * @brief Default constructor class Chrono
		*/
		Chrono &operator=(const Chrono &) noexcept = default;
		/*! @brief Display the current time
		 *
		 * @param os Output stream
		 * @param chrono Class Alpaga::Time::Chrono
		 *
		 * @return Output stream
		*/
		friend std::ostream &operator<<(std::ostream &os, const Alpaga::Time::Chrono &chrono) {
			os << std::chrono::duration<double>(std::chrono::system_clock::now() - chrono._time).count();
			return os;
		}

	public:
		/*!
		 * @brief Restart the clock to 0
		*/
		void restart() noexcept;
		/*! @brief Cast time in string
		 *
		 * @return String of current time
		*/
		std::string str();

	private:
		/*!
		 * @brief Current time of the chrono
		*/
		std::chrono::system_clock::time_point _time = std::chrono::system_clock::now();
};