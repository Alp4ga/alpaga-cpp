/*
  * @Author: Alpaga
  * @Date: 2020-01-03 12:53:39
 * @Last Modified by: Alpaga
 * @Last Modified time: 2020-02-28 12:15:02
*/

#include <stdexcept>

#include "Statement.hpp"

Alpaga::SQLite3::Statement::Statement(SQLite3::Database &db, const std::string &statement)
	: _db(db)
{
	auto ret = sqlite3_prepare(db.getDatabasePtr(), statement.c_str(), -1, &_stmt, NULL);
	if (ret != SQLITE_OK)
		throw std::runtime_error("[SQLite3]: Prepare failed. " +  std::string(sqlite3_errmsg(db.getDatabasePtr())));
}

Alpaga::SQLite3::Statement::~Statement() noexcept {
	sqlite3_finalize(_stmt);
}

bool Alpaga::SQLite3::Statement::step() noexcept {
	auto ret = sqlite3_step(_stmt);
	if (ret != SQLITE_ROW)
		_err = sqlite3_errmsg(_db.getDatabasePtr());
	return ret == SQLITE_ROW;
}

bool Alpaga::SQLite3::Statement::exec() noexcept {
	auto ret = sqlite3_step(_stmt);
	if (ret != SQLITE_DONE)
		_err = sqlite3_errmsg(_db.getDatabasePtr());
	return ret == SQLITE_DONE;
}

void Alpaga::SQLite3::Statement::clear() {
	if (sqlite3_clear_bindings(_stmt) != SQLITE_OK)
		throw std::runtime_error("[SQLite3]: Failed clearBinding.");
}

void Alpaga::SQLite3::Statement::reset() noexcept {
	sqlite3_reset(_stmt);
}

sqlite3_stmt *Alpaga::SQLite3::Statement::getStmt() const {
	return _stmt;
}

const std::string &Alpaga::SQLite3::Statement::errMsg() const {
	return _err;
}