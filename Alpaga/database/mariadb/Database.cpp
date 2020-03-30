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

Mariadb::Database::~Database() noexcept
{
	this->disconnect();
}

bool Mariadb::Database::connection(const std::string &host, const std::string &user, const std::string &password,
								   const std::string &schema, std::uint32_t port) noexcept
{
	if (!_mysql) {
		_mysql = mysql_init(nullptr);
		if (!_mysql) {
			MARIADB_INTERNAL_ERROR("Cannot create MYSQL object.");
			return false;
		}
	}

	if (!mysql_real_connect(
			_mysql, 
			host.c_str(), 
			user.c_str(), 
			(password.empty() ? nullptr : password.c_str()), 
			(schema.empty() ? nullptr : schema.c_str()),
			port,
			nullptr,
			CLIENT_MULTI_STATEMENTS
		)
	) {
		MARIADB_ERROR(_mysql);
		return false;
	}

	_host = host;
	_user = user;
	_schema = schema;
	_port = port;

	MARIABD_OUTPUT("Connection success");
	return true;
}

void Mariadb::Database::disconnect() noexcept
{
	if (!_mysql)
		return;

	mysql_close(_mysql);
    mysql_thread_end();

    _mysql = nullptr;
}


bool Mariadb::Database::isConnected() const noexcept
{
	return _mysql && !mysql_ping(_mysql);
}

const std::string &Mariadb::Database::getHost() const noexcept
{
	return _host;
}
const std::string &Mariadb::Database::getUser() const noexcept
{
	return _user;
}
std::uint32_t Mariadb::Database::getPort() const noexcept
{
	return _port;
}


bool Mariadb::Database::setSchema(const std::string &schema) noexcept
{
	if (!this->isConnected())
		return false;

	if (mysql_select_db(_mysql, schema.c_str())) {
		return false;
		MARIADB_ERROR(_mysql);
	}

	_schema = schema;
	return true;
}

const std::string &Mariadb::Database::getSchema() const noexcept
{
	return _schema;
}


MYSQL *Mariadb::Database::getInstanceMysql() const noexcept
{
	return _mysql;
}