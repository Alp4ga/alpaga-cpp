/*
  * @Author: Alpaga
  * @Date: 2020-01-03 12:37:43
 * @Last Modified by: Alpaga
 * @Last Modified time: 2020-02-14 19:37:21
*/

#include <stdexcept>

#include "Database.hpp"

Alpaga::SQLite3::Database::Database() noexcept
	: _db(nullptr)
{}

Alpaga::SQLite3::Database::Database(const std::string &filename, int flags, const char *zVfs) {
	if (sqlite3_open_v2(filename.c_str(), &_db, flags, zVfs) != SQLITE_OK)
		throw std::runtime_error("[SQLite3]: Failed open database: " + std::string(sqlite3_errmsg(_db)));
}

Alpaga::SQLite3::Database::~Database() noexcept {
	if (_db != nullptr)
		sqlite3_close_v2(_db);
}

void Alpaga::SQLite3::Database::open(const std::string &filename, int flags, const char *zVfs) {
	if (_db != nullptr)
		throw std::runtime_error("[SQLite3]: Database is already open.");
	if (sqlite3_open_v2(filename.c_str(), &_db, flags, zVfs) != SQLITE_OK)
		throw std::runtime_error("[SQLite3]: Failed open database.");
}

void Alpaga::SQLite3::Database::close() {
	if (_db != nullptr && sqlite3_close_v2(_db) != SQLITE_OK)
		throw std::runtime_error("[SQLite3]: Failed close db.");
}

void Alpaga::SQLite3::Database::boost(size_t memorySize) noexcept {
	sqlite3_exec(_db, "PRAGMA synchronous = OFF", NULL, NULL, NULL);
	sqlite3_exec(_db, "PRAGMA journal_mode = WAL", NULL, NULL, NULL);
	if (memorySize != 0) {
		auto cache_size = "PRAGMA cache_size = " + std::to_string(memorySize);
		sqlite3_exec(_db, cache_size.c_str(), NULL, NULL, NULL);
	}
}

void Alpaga::SQLite3::Database::exec(const std::string &sql) {
	if (sqlite3_exec(_db, sql.c_str(), nullptr, nullptr, nullptr) != SQLITE_OK)
		throw std::runtime_error("[SQLite3]: failed exec.");
}