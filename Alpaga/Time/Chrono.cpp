/*
  * @Author: Alpaga
  * @Date: 2020-02-08 12:08:39
 * @Last Modified by: Alpaga
 * @Last Modified time: 2020-02-20 15:34:41
*/

#include <sstream>
#include "Chrono.hpp"

void Alpaga::Time::Chrono::restart() noexcept {
	_time = std::chrono::system_clock::now();
}

std::string Alpaga::Time::Chrono::str() {
	std::stringstream ss;
	ss << std::chrono::duration<double>(std::chrono::system_clock::now() - _time).count();
	return ss.str();
}
