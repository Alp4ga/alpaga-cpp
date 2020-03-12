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
		/*! @brief calcul distance between 2 string with Ratclikff algorithm
		 *
		 * @param a Frist string
		 * @param b Second string
		 *
		 * @return Distance between string
		*/
		double ratclikffObershelp(const char *a, const char *b);
	};
};