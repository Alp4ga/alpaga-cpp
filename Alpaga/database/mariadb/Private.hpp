/*
 * Company: Your Company
 * File: Private.hpp
 * Project: mariadb
 * File Created: Saturday, 28th March 2020 7:15:31 pm
 * Author: Alp4ga (you@you.you)
 * -----
 * Last Modified: Saturday, 28th March 2020 7:15:34 pm
 * Modified By: Alp4ga (you@you.you>)
 * -----
 */

#include <iostream>

/*!
 * @brief Use for internal error
*/
#define MARIADB_INTERNAL_ERROR(error)							\
	std::cerr << "[Mariadb Error]: " << error << std::endl		\
			  << "In function: " << __FUNCTION__ << std::endl	\
			  << "In file: " << __FILE__ << std::endl			\
			  << "On line: " << __LINE__ << std::endl;

/*!
 * @brief Use for mariadb error
*/
#define MARIADB_ERROR(mysql)										\
	std::cerr << "[Mariadb Error(" << mysql_errno(mysql) << ")]: "	\
			  << mysql_error(mysql) << std::endl					\
			  << "In function: " << __FUNCTION__ << std::endl		\
			  << "In file: " << __FILE__ << std::endl				\
			  << "On line: " << __LINE__ << std::endl;

/*!
 * @brief Use to display a simple message
*/
#define MARIABD_COUT(message)							\
	std::cout << "[Mariadb] " << message << std::endl;