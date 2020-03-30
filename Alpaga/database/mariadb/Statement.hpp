/*
 * Company: Your Company
 * File: Statement.hpp
 * Project: mariadb
 * File Created: Monday, 30th March 2020 5:41:59 pm
 * Author: Alp4ga (you@you.you)
 * -----
 * Last Modified: Monday, 30th March 2020 5:42:09 pm
 * Modified By: Alp4ga (you@you.you>)
 * -----
 */

#pragma once

#include "Database.hpp"

/*! @namespace Mariadb
 * @brief Include all class about mariadb-connector-cpp
*/
namespace Mariadb {
	class Statement;
};

/*! @class Mariadb::Statement
 * @brief Class representing a prepared statement with binding functionality
*/
class Mariadb::Statement {
	public:
		/*!
		 * @brief Default constructor class Statement
		*/
		Statement() = delete;
		/*! @brief Contructor class Statement
		 * @param db Maraiadb database
		 * @param query Query set to the statement
		*/
		Statement(Mariadb::Database &db, const std::string &query);
		/*!
		 * @brief Default descructor class Statement
		*/
		~Statement() noexcept = default;
		/*!
		 * @brief Default copy constructor class Statement
		*/
		Statement(const Statement &) noexcept = default;
		/*!
		 * @brief Default constructor class Statement
		*/
		Statement &operator=(const Statement &) noexcept = default;

	private:
		/*!
		 * @brief Reference to database where the statement will be executed
		*/
		Mariadb::Database _db;
		/*!
		* @brief pointer to underlying statement
		*/
		MYSQL_STMT *_stmt;
		/*!
		 * @brief pointer to raw binds
		*/
		MYSQL_BIND *_bind;
		/*!
		 * @brief Bind number
		*/
		std::uint32_t _bindCount;
};