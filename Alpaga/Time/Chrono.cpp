/*
  * @Author: Alpaga
  * @Date: 2020-02-08 12:08:39
 * @Last Modified by: Alpaga
 * @Last Modified time: 2020-02-20 15:34:41
*/

#include "Chrono.hpp"

void Alpaga::Time::Chrono::restart() noexcept {
	_time = std::chrono::system_clock::now();
}