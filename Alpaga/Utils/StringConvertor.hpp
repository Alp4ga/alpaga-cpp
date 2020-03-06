/*
  * @Author: Alpaga
  * @Date: 2020-02-28 10:33:28
 * @Last Modified by: Alpaga
 * @Last Modified time: 2020-02-28 10:53:02
*/

#pragma once

#include <boost/algorithm/string.hpp>

#include <string>
#include <vector>

/*! @namespace Alpaga
 * @brief include all file of Alpaga's cpp library
*/
namespace Alpaga {
	/*!
	 * @brief There functions can convert a string in anything just with a template
	*/
	namespace StringConvertor {
		template<typename T>
		/*! @brief Default convert if type wanted used unkown so throw an error
		 * @param value Value to convert
		 * @return Value converted in specific type
		*/
		static inline T conv(const std::string &value) { throw std::runtime_error("[Alpaga::StringConvertor] This type is not handleYetSorry"); }
		/*!
		 * @brief Specialisation for int type
		*/
		template<>
		static inline int conv<int>(const std::string &value) { return stoi(value); }
		/*!
		 * @brief Specialisation for double type
		*/
		template<>
		static inline double conv<double>(const std::string &value) { return stol(value); }
		/*!
		 * @brief Specialisation for vector<string> type
		*/
		template<>
		static inline std::vector<std::string> conv<std::vector<std::string>>(const std::string &value) { 
			std::vector<std::string> values;
			boost::split(values, value, boost::is_any_of(","), boost::token_compress_on);
			return values;
		}
		/*!
		 * @brief Specialisation for vector<int> type
		*/
		template<>
		static inline std::vector<int> conv<std::vector<int>>(const std::string &value) { 
			std::vector<std::string> values;
			boost::split(values, value, boost::is_any_of(","), boost::token_compress_on);
			std::vector<int> valuesInt;
			std::transform(values.begin(), values.end(), std::back_inserter(valuesInt), [](const std::string& str) { return std::stoi(str); });
			return valuesInt;
		}
		/*!
		 * @brief Specialisation for vector<double> type
		*/
		template<>
		static inline std::vector<double> conv<std::vector<double>>(const std::string &value) { 
			std::vector<std::string> values;
			boost::split(values, value, boost::is_any_of(","), boost::token_compress_on);
			std::vector<double> valuesDouble;
			std::transform(values.begin(), values.end(), std::back_inserter(valuesDouble), [](const std::string& str) { return std::stol(str); });
			return valuesDouble;
		}
	};
};