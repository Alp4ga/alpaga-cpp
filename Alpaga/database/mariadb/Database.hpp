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
#include <string>

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
		~Database() noexcept;
		/*!
		 * @brief Default copy constructor class Database
		*/
		Database(const Database &) = default;
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
		bool connection(const std::string &host, const std::string &user, const std::string &password = "",
						const std::string &db = "", std::uint32_t port = 3307) noexcept;
		/*!
		 * @brief Close the connection to database
		*/
		void disconnect() noexcept;
		/*! @brief Indicates whether the connection is active. Also detects stale connections
		 * @return True on active connection
		*/
		bool isConnected() const noexcept;

	public:
		/*! @brief Connection host to the database
		 * @return String containing the host
		*/
		const std::string &getHost() const noexcept;
		/*! @brief Connection host to the database
		 * @return String containing the user name connected to the database
		*/
		const std::string &getUser() const noexcept;
		/*! @brief Connection host to the database
		 * @return Number containing the connection port
		*/
		std::uint32_t getPort() const noexcept;

	public:
		/*! @brief Sets the schema (database name).
		 * The connection MUST be already establish
		 * @param schema The new schema name
		 * @return True on success
		*/
		bool setSchema(const std::string &schema) noexcept;
		/*!
		 * @brief Get the schema (database name).
		 * @return String containing the schema
		*/
		const std::string &getSchema() const noexcept;

	public:
		/*! @brief Instance to mysql pointer
		 * @return Pointer to the mysql database
		*/
		MYSQL *getInstanceMysql() const noexcept;

	private:
		/*!
		 * @brief Mysql object
		*/
		MYSQL* _mysql;
		/*!
		 * @brief Host to the database
		*/
		std::string _host;
		/*!
		 * @brief User connected to the database
		*/
		std::string _user;
		/*!
		 * @brief Port use for the connection
		*/
		std::uint32_t _port;
		/*!
		 * @brief Database schema
		*/
		std::string _schema;
};