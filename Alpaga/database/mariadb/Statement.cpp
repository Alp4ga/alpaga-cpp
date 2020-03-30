/*
 * Company: Your Company
 * File: Statement.cpp
 * Project: mariadb
 * File Created: Monday, 30th March 2020 5:52:52 pm
 * Author: Alp4ga (you@you.you)
 * -----
 * Last Modified: Monday, 30th March 2020 5:52:54 pm
 * Modified By: Alp4ga (you@you.you>)
 * -----
 */

#include "Statement.hpp"
#include "Private.hpp"

Mariadb::Statement::Statement(Mariadb::Database &db, const std::string &query)
	: _db(db), _stmt(nullptr)
{
	if (!db.isConnected())
		MARIADB_INTERNAL_ERROR_TROW("Database is not connected.");

	_stmt = mysql_stmt_init(db.getInstanceMysql());
	if (!_stmt)
		MARIADB_INTERNAL_ERROR_TROW("Cannot create STMT object.");

	if (mysql_stmt_prepare(_stmt, query.c_str(), query.size()))
		STMT_ERROR_TRHOW(_stmt);

	_bindCount = mysql_stmt_param_count(_stmt);
	if (_bindCount > 0) {
		_bind = new MYSQL_BIND[_bindCount];
	}
}