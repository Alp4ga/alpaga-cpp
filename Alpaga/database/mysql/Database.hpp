/*
 * Company: Your Company
 * File: Database.hpp
 * Project: mysql
 * File Created: Thursday, 26th March 2020 4:50:27 pm
 * Author: Alp4ga (you@you.you)
 * -----
 * Last Modified: Thursday, 26th March 2020 4:50:29 pm
 * Modified By: Alp4ga (you@you.you>)
 * -----
 */

#pragma once

/*! @namespace Mysql
 * @brief Include all mysql class
*/
namespace Mysql {
	class Database;
};

/*! @class Mysql::Database
 * @brief Manage connection with database
 * 
*/
class Mysql::Database {
	public:
		/*!
		 * @brief Default constructor class Database
		*/
		Database() noexcept = default;
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

	private:
};