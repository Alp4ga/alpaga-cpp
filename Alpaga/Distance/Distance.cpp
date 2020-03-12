/*
  * @Author: Alpaga
  * @Date: 2020-02-28 10:34:34
  * @Last Modified by:   Alpaga
  * @Last Modified time: 2020-02-28 10:34:34
*/

#include <algorithm>

#include "Distance.hpp"
#include "JaroWinkler.hpp"
#include "Ratclikff.hpp"

double Alpaga::Distance::JaroRatclikff(const std::string &a, const std::string &b) {
	return std::max(Alpaga::Distance::jaroWinkler(a, b), Alpaga::Distance::ratclikffObershelp(a.c_str(), b.c_str()));
}