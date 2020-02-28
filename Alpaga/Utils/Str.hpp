/*
  * @Author: Alpaga
  * @Date: 2020-02-28 10:33:28
 * @Last Modified by: Alpaga
 * @Last Modified time: 2020-02-28 10:53:02
*/

#pragma once

#include <boost/algorithm/string.hpp>
#include <boost/locale.hpp>
#include <boost/locale/encoding.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/algorithm/string/detail/trim.hpp>
#include <boost/algorithm/string/case_conv.hpp>

#include <sstream>

/*! @namespace Alpaga
 * @brief include all file of Alpaga's cpp library
*/
namespace Alpaga {
	/*! @namespace Utils
	 * @brief Include all utils fonctions
	*/
	namespace Utils {
		/*! @namespace Str
		 * @brief Include all Utils fonction using string
		*/
		namespace Str {
			/*! @brief Fomat the string in parameter
			 *
			 * 1. To upper
			 * 2. Remvoe accents
			 * 3. Remove usless characters
			 * 4. Remove usless space
			 * @param str String to format 
			 *
			 * @return String formated
			*/
			inline static std::string format(const std::string &str) {
				static boost::locale::generator gen;
				static auto loc = gen("");

				if (str.empty())
					return str;
				auto ret = boost::locale::to_upper(str, loc);
				ret = boost::locale::conv::from_utf(boost::locale::normalize(ret, boost::locale::norm_nfd, loc), "ISO8859-15");
				if (ret.empty())
					return "Formating failed.";
				boost::range::remove_erase_if(ret, boost::is_any_of("[_.,;\\-`'\n\r]+^~\""));
				boost::algorithm::trim(ret);
				ret.erase(std::unique(std::begin(ret), std::end(ret), [](char a, char b){ return std::isspace(a) && std::isspace(b); }), std::end(ret));
				return ret;
			}

			/*! @brief Return the number of word.
			 *
			 * @param str Str to count the number of word
			 *
			 * @return number of word
			*/
			inline static size_t nbrWord(const std::string &str) {
				std::stringstream ss(str);
				return std::distance(std::istream_iterator<std::string>(ss), std::istream_iterator<std::string>());
			}
		};
	};
};