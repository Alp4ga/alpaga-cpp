/*
 * Company: Your Company
 * File: Database.cpp
 * Project: mariadb
 * File Created: Friday, 27th March 2020 11:57:43 am
 * Author: Alp4ga (you@you.you)
 * -----
 * Last Modified: Friday, 27th March 2020 11:58:30 am
 * Modified By: Alp4ga (you@you.you>)
 * -----
 */

#include <iostream>
#include <string>
#include <mysql.h>

#include "Database.hpp"

Mariadb::Database::Database() noexcept
	: _mysql(nullptr)
{}

bool Mariadb::Database::connection(const std::string &host, const std::string &user, const std::string &password,
								   const std::string &db, std::uint32_t port) noexcept
{
	if (_mysql) {
		_mysql = mysql_init(nullptr);
		if (!_mysql) {
			return false;
		}
	}

	if (!mysql_real_connect(_mysql, host.c_str(), user.c_str(), password.c_str(), nullptr, port, nullptr, CLIENT_MULTI_STATEMENTS)) {
		return false;
	}
	std::cout << "[Mariadb] Connection success" << std::endl;
	return true;
}