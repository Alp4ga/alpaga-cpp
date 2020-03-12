/*
  * @Author: Alpaga
  * @Date: 2020-02-28 10:34:34
  * @Last Modified by:   Alpaga
  * @Last Modified time: 2020-02-28 10:34:34
*/

#pragma once

#include <string>

/*! @namespace Alpaga
 * @brief include all file of Alpaga's cpp library
*/
namespace Alpaga {
	/*! @namespace Distance
	 * @brief Include all function to calcul distance between two string
	*/
	namespace Distance {
		/*! @brief Calcul the best distance between 2 string with JaroWinkler algorithm and Ratclikff
		 *
		 * @param a First string
		 * @param b Second string
		 *
		 * @return Best distance between strings
		*/
		double JaroRatclikff(const std::string &a, const std::string &b);
	};
};