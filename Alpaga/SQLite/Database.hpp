/*
  * @Author: Alpaga
  * @Date: 2020-01-03 12:35:08
 * @Last Modified by: Alpaga
 * @Last Modified time: 2020-02-28 10:33:51
*/

#pragma once

#include <sqlite3.h>
#include <string>

/*! @namespace Alpaga
 * @brief include all file of Alpaga's cpp library
*/
namespace Alpaga {
	/*! @namespace SQLite3
 	 * @brief Include all files for lib SQLite3
	*/
	namespace SQLite3 {
		class Database;
	};
}

/*! @class Alpaga::SQLite3::Database
 * @brief Handle database management
 * 
*/
class Alpaga::SQLite3::Database {
	public:
		/*!
		* @brief Contructor Database object without init database
		*/
		Database() noexcept;
		/*! @brief Contructor Database object with init database
		 *
		 * @param database path to the database
		 * @param flags Flags SQLite3 to open a new database (https://www.sqlite.org/c3ref/open.html)
		 				- SQLITE_OPEN_READONLY The database is opened in read-only mode. If the database does not already exist, an error is returned.
						- SQLITE_OPEN_READWRITE/SQLITE_OPEN_READWRITE The database is opened for reading and writing if possible, or reading only if the file is write protected by the operating system. In either case the database must already exist, otherwise an error is returned.
						- SQLITE_OPEN_CREATE The database is opened for reading and writing, and is created if it does not already exist. This is the behavior that is always used for sqlite3_open() and sqlite3_open16().
						- SQLITE_OPEN_URI The filename can be interpreted as a URI if this flag is set.
						- SQLITE_OPEN_MEMORY The database will be opened as an in-memory database. The database is named by the "filename" argument for the purposes of cache-sharing, if shared cache mode is enabled, but the "filename" is otherwise ignored.
						- SQLITE_OPEN_NOMUTEX The new database connection will use the "multi-thread" threading mode. This means that separate threads are allowed to use SQLite at the same time, as long as each thread is using a different database connection.
						- SQLITE_OPEN_FULLMUTEX The new database connection will use the "serialized" threading mode. This means the multiple threads can safely attempt to use the same database connection at the same time. (Mutexes will block any actual concurrency, but in this mode there is no harm in trying.)
						- SQLITE_OPEN_SHAREDCACHE The database is opened shared cache enabled, overriding the default shared cache setting provided by sqlite3_enable_shared_cache().
						- SQLITE_OPEN_PRIVATECACHE The database is opened shared cache disabled, overriding the default shared cache setting provided by sqlite3_enable_shared_cache().
						- SQLITE_OPEN_NOFOLLOW The database filename is not allowed to be a symbolic link
		 * @param zVfs object that defines the operating system interface that the new database connection should use. If the fourth parameter is a NULL pointer then the default sqlite3_vfs object is used
		 * @return 
		*/
		Database(const std::string &database, int flags = SQLITE_OPEN_READONLY, const char *zVfs = nullptr);
		/*!
		 * @brief Destructor object Close database.
		*/
		~Database() noexcept;
		/*!
		 * @brief Default copy constructor class Database
		*/
		Database(const Database &) noexcept = default;
		/*!
		 * @brief Default operator= class Database
		*/
		Database &operator=(const Database &) noexcept = default;

	public:
		/*! @brief Open Database (See Constructor database to information)
		 * @return void
		*/
		void open(const std::string &filename, int flags = SQLITE_OPEN_READONLY, const char *zVfs = nullptr);
		/*!
		 * @brief Destructor object Close database.
		*/
		void close();
		/*! @brief Active Async on database and write the journal in memory
		 * @param memorySize Change the memory size of the database
		 * 
		*/
		void boost(size_t memorySize = 0) noexcept;
		/*! @brief Exec simple query request
		 *
		 * @param sql query request
		*/
		void exec(const std::string &sql);
		/*! @brief return the ptr on database SQLite3
		 * @return sqlite3 *ptr
		*/
		sqlite3 *getDatabasePtr() const { return _db; }

	private:
		/*!
		 * @brief Pointer to database sqlite3
		*/
		sqlite3 *_db;
};