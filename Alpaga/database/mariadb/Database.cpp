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
#include "Private.hpp"

Mariadb::Database::Database() noexcept
	: _mysql(nullptr)
{}

bool Mariadb::Database::connection(const std::string &host, const std::string &user, const std::string &password,
								   const std::string &db, std::uint32_t port) noexcept
{
	if (!_mysql) {
		_mysql = mysql_init(nullptr);
		if (!_mysql) {
			MARIADB_INTERNAL_ERROR("FCannot create MYSQL object.");
			return false;
		}
	}

	if (!mysql_real_connect(_mysql, host.c_str(), user.c_str(), password.c_str(), nullptr, port, nullptr, CLIENT_MULTI_STATEMENTS)) {
		MARIADB_ERROR(_mysql);
		return false;
	}
	MARIADB_COUT("Connection success");
	return true;
}