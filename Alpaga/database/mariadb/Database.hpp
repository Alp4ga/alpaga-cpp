/*
 * Company: Your Company
 * File: Database.hpp
 * Project: mariadb
 * File Created: Friday, 27th March 2020 11:57:39 am
 * Author: Alp4ga (you@you.you)
 * -----
 * Last Modified: Friday, 27th March 2020 11:57:48 am
 * Modified By: Alp4ga (you@you.you>)
 * -----
 */

#pragma once

#include <mysql.h>

/*! @namespace Mariadb
 * @brief Include all class about mariadb-connector-cpp
*/
namespace Mariadb {
	class Database;
};

/*! @class Mariadb::Database
 * @brief Handle management with database
 * 
*/
class Mariadb::Database {
	public:
		/*!
		 * @brief Default constructor class Database
		*/
		Database() noexcept;
		/*!
		 * @brief Default descructor class Database
		*/
		~Database() noexcept = default;
		/*!
		 * @brief Default copy constructor class Database
		*/
		Database(const Database &) noexcept = default;
		/*!
		 * @brief Default constructor class Database
		*/
		Database &operator=(const Database &) noexcept = default;

	public:
		/*! @brief Start a connection with the database
		 *
		 * @param host Host to the database
		 * @param user Username
		 * @param password Password user
		 * @param db Database name
		 * @param port Database port
		 *
		 * @return True on success
		*/
		bool connection(const std::string &host, const std::string &user, const std::string &password,
						const std::string &db, std::uint32_t port) noexcept;

	private:
		MYSQL* _mysql;
};