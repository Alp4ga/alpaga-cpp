/*
  * Company: Alpaga
  * @Author: Alpaga
  * @Date: 2020-01-03 12:53:39
 * @Last Modified by: Alpaga
 * @Last Modified time: 2020-02-20 19:24:44
*/

#include <stdexcept>

#include "Statement.hpp"

Alpaga::SQLite3::Statement::Statement(SQLite3::Database &db, const std::string &statement) {
	if (sqlite3_prepare_v2(db.getDatabasePtr(), statement.c_str(), -1, &_stmt, NULL) != SQLITE_OK)
		throw std::runtime_error("[SQLite3]: Prepare failed. " +  std::string(sqlite3_errmsg(db.getDatabasePtr())));
}

Alpaga::SQLite3::Statement::~Statement() noexcept {
	sqlite3_finalize(_stmt);
}

bool Alpaga::SQLite3::Statement::step() noexcept {
	return sqlite3_step(_stmt) == SQLITE_ROW;
}

void Alpaga::SQLite3::Statement::clear() {
	if (sqlite3_clear_bindings(_stmt) != SQLITE_OK)
		throw std::runtime_error("[SQLite3]: Failed clearBinding.");
}

void Alpaga::SQLite3::Statement::reset() noexcept {
	sqlite3_reset(_stmt);
}

void Alpaga::SQLite3::Statement::stepAndClean() {
	this->step();
	this->clear();
	this->reset();
}