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
		/*! @brief calcul distance between 2 string with JaroWinkler algorithm
		 *
		 * @param a Frist string r-value
		 * @param b Second string r-value
		 *
		 * @return Distance between string
		*/
		double jaroWinkler(const std::string &&a, const std::string &&b);
		/*! @brief calcul distance between 2 string with JaroWinkler algorithm
		 *
		 * @param a Frist string l-value
		 * @param b Second string l-value
		 *
		 * @return Distance between string
		*/
		double jaroWinkler(const std::string &a, const std::string &b);
	};
};