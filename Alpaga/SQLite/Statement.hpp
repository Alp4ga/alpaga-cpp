/*
  * @Author: Alpaga
  * @Date: 2020-01-03 12:51:48
 * @Last Modified by: Alpaga
 * @Last Modified time: 2020-02-28 10:34:04
*/

#pragma once

#include <iostream>

#include <string>
#include <typeinfo>

#include "Database.hpp"

/*! @namespace Alpaga
 * @brief include all file of Alpaga's cpp library
*/
namespace Alpaga {
	/*! @namespace SQLite3
	* @brief Include all files for lib SQLite3
	*/
	namespace SQLite3 {
		class Statement;
	};
}

/*! @class Alpaga::SQLite3::Statement
 * @brief Generate a statement for sqlite3
 * 
*/
class Alpaga::SQLite3::Statement {
	public:
		/*! @brief Build new Statement
		 *
		 * @param db Database SQLite3
		 * @param statement Query request (SELECT * FROM Example)
		*/
		explicit Statement(SQLite3::Database &db, const std::string &statement);
		/*!
		 * @brief Destructor class Statement
		*/
		~Statement() noexcept;
		/*!
		 * @brief Default copy constructor class Statement
		*/
		Statement(const Statement &) noexcept = default;
		/*!
		 * @brief Default operator= class Statement
		*/
		Statement &operator=(const Statement &) noexcept = default;

	public:
		/*! @brief Bind argument to statement
		 *
		 * @param pos Postion of the argument in query
		 * @param value Value of argument
		 *
		 * @return void
		*/
		template<typename T>
		void bind(int pos, T value) { throw std::runtime_error("[SQLite] Type can not be bind. " + std::string(typeid(value).name())); }
		template<> void bind<const char *>(int pos, const char *value) noexcept { sqlite3_bind_text(_stmt, pos, value, -1, SQLITE_STATIC); }
		template<> void bind<char *>(int pos, char *value) noexcept { sqlite3_bind_text(_stmt, pos, value, -1, SQLITE_STATIC); }
		template<> void bind<char>(int pos, char value) noexcept { sqlite3_bind_int(_stmt, pos, value); }
		template<> void bind<int>(int pos, int value) noexcept { sqlite3_bind_int(_stmt, pos, value); }
		template<> void bind<unsigned int>(int pos, unsigned int value) noexcept { sqlite3_bind_int64(_stmt, pos, value); }
		template<> void bind<double>(int pos, double value) noexcept { sqlite3_bind_double(_stmt, pos, value); }
		template<> void bind<bool>(int pos, bool value) noexcept { sqlite3_bind_int(_stmt, pos, value); }
		/*! @brief Bind agrument to the statement
		 *
		 * @param start postion of the first statement
		 * @param first First arguement 
		 * @param args Unlimited number of argument to bind
		 *
		 * @return void
		*/
		template <typename T, typename... Args>
		void bind(int start, T first, Args... args) {
			bind(start++, first);
			bind(start, args...);
		}

	public:
		/*! @brief Get column value
		 *
		 * @param pos Position of the column start 1 not 0 !!!!
		 *
		 * @return Template type
		*/
		template<typename T> T column(int pos) { throw std::runtime_error("SQLite3: Unkown column type."); };
		/*!
		 * @brief Get type: int
		*/
		template<> int column<int>(int pos) { return sqlite3_column_int(_stmt, pos); }
		/*!
		 * @brief Get type: unsigned int
		*/
		template<> unsigned int column<unsigned int>(int pos) { return (unsigned int)sqlite3_column_int64(_stmt, pos); }
		/*!
		 * @brief Get type: char
		*/
		template<> char column<char>(int pos) { return sqlite3_column_int(_stmt, pos); }
		/*!
		 * @brief Get type: bool
		*/
		template<> bool column<bool>(int pos) { return sqlite3_column_int(_stmt, pos) == 1 ? true : false; }
		/*!
		 * @brief Get type: double
		*/
		template<> double column<double>(int pos) { return sqlite3_column_double(_stmt, pos); }
		/*!
		 * @brief Get type: std::string
		*/
		template<> std::string column<std::string>(int pos) { return std::string(reinterpret_cast<const char*>(sqlite3_column_text(_stmt, pos))); }
		/*!
		 * @brief Get type: const char *
		*/
		template<> const char *column<const char *>(int pos) { return reinterpret_cast<const char*>(sqlite3_column_text(_stmt, pos)); }

	public:
		/*!
		 * @brief Execute statement
		*/
		bool step() noexcept;
		/*!
		 * @brief clear binding
		*/
		void clear();
		/*!
		 * @brief Reset statement
		*/
		void reset() noexcept;
		/*!
		 * @brief Call function 1. Step() 2. Clear() 3. Reset()
		*/
		void stepAndClean();

	private:
		/*!
		 * @brief Pointer to the statement
		*/
		sqlite3_stmt *_stmt;
};