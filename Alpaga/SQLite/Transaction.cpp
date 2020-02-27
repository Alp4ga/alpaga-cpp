/*
  * Company: Alpaga
  * @Author: Alpaga
  * @Date: 2020-01-10 12:20:51
 * @Last Modified by: Alpaga
 * @Last Modified time: 2020-02-20 20:37:48
*/

#include <iostream>
#include <stdexcept>

#include "Transaction.hpp"

Alpaga::SQLite3::Transaction::Transaction(SQLite3::Database &db) : _db(db) {}

void Alpaga::SQLite3::Transaction::begin() {
	if (sqlite3_exec(_db.getDatabasePtr(), "BEGIN TRANSACTION", NULL, NULL, NULL) != SQLITE_OK)
		std::cerr << "[SQLite3] Transaction failed: BEGIN " << sqlite3_errmsg(_db.getDatabasePtr()) << std::endl;
}

void Alpaga::SQLite3::Transaction::end() {
	if (sqlite3_exec(_db.getDatabasePtr(), "END TRANSACTION", NULL, NULL, NULL) != SQLITE_OK)
		std::cerr << "[SQLite3] Transaction failed: END " << sqlite3_errmsg(_db.getDatabasePtr()) << std::endl;
}

void Alpaga::SQLite3::Transaction::commit() {
	if (sqlite3_exec(_db.getDatabasePtr(), "COMMIT", NULL, NULL, NULL) != SQLITE_OK)
		std::cerr << "[SQLite3] Transaction failed: COMMIT " << sqlite3_errmsg(_db.getDatabasePtr()) << std::endl;
}

void Alpaga::SQLite3::Transaction::rollback() {
	if (sqlite3_exec(_db.getDatabasePtr(), "ROLLBACK", NULL, NULL, NULL) != SQLITE_OK)
		std::cerr << "[SQLite3] Transaction failed: ROLLBACK " << sqlite3_errmsg(_db.getDatabasePtr()) << std::endl;
}
