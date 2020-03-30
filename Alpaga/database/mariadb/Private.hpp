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
#include <exception>

/*!
 * @brief Use to display a simple message
*/
#define MARIABD_OUTPUT(message)							\
	std::cout << "[Mariadb] " << message << std::endl;

/*!
 * @brief Throw exception error
*/
#define MARIADB_THROW(error)			\
	throw std::runtime_error(error);

/*!
 * @brief Use for internal error
*/
#define MARIADB_INTERNAL_ERROR(error)							\
	std::cerr << "[Mariadb Error]: " << error << std::endl		\
			  << "In function: " << __FUNCTION__ << std::endl	\
			  << "In file: " << __FILE__ << std::endl			\
			  << "On line: " << __LINE__ << std::endl;

#define MARIADB_INTERNAL_ERROR_TROW(error)	\
	MARIADB_INTERNAL_ERROR(error);			\
	MARIADB_THROW(error)

/*!
 * @brief Display un mariadb error
*/
#define DSIPLAY_ERROR(error_id, error)								\
	std::cerr << "[Mariadb Error(" << error_id << ")]: "			\
			  << error << std::endl									\
			  << "In function: " << __FUNCTION__ << std::endl		\
			  << "In file: " << __FILE__ << std::endl				\
			  << "On line: " << __LINE__ << std::endl;

/*!
 * @brief Display un mariadb error
*/
#define MARIADB_ERROR(mysql)								\
	DSIPLAY_ERROR(mysql_errno(mysql), mysql_error(mysql));

/*!
 * @brief Display un mariadb error and throw an critical error
*/
#define MARIADB_ERROR_THROW(mysql)							\
	DSIPLAY_ERROR(mysql_errno(mysql), mysql_error(mysql))	\
	MARIADB_THROW(mysql_error(mysql));

/*!
 * @brief Display un stmt error
*/
#define STMT_ERROR(statement)												\
	DSIPLAY_ERROR(mysql_stmt_errno(statement), mysql_stmt_error(statement));

/*!
 * @brief Display un stmt error and throw
*/
#define STMT_ERROR_TRHOW(statement)												\
	DSIPLAY_ERROR(mysql_stmt_errno(statement), mysql_stmt_error(statement));	\
	MARIADB_THROW(mysql_stmt_error(statement));	