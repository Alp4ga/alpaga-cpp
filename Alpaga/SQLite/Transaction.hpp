/*
  * Company: HIDLO
  * @Author: Alpaga
  * @Date: 2020-01-10 12:19:45
 * @Last Modified by: Alpaga
 * @Last Modified time: 2020-02-20 20:34:55
*/

#pragma once

#include "Database.hpp"

/*! @namespace Alpaga
 * @brief include all file of Alpaga's cpp library
*/
namespace Alpaga {
	/*! @namespace SQLite3
	* @brief Include all files for lib SQLite3
	*/
	namespace SQLite3 {
		class Transaction;
	};
}

/*! @class Alpaga::SQLite3::Transaction
 * @brief Handle transaction with the database
 * 
*/
class Alpaga::SQLite3::Transaction {
	public:
		/*! @brief Build new class Transaction
		 *
		 * @param db SQLite3 database
		*/
		explicit Transaction(SQLite3::Database &db);
		/*!
		 * @brief Default descructor class Transaction
		*/
		~Transaction() noexcept = default;
		/*!
		 * @brief Default copy constructor class Transaction
		*/
		Transaction(const Transaction &) noexcept = default;
		/*!
		 * @brief Default operator= class Transaction
		*/
		Transaction &operator=(const Transaction &) noexcept = default;

	public:
		/*!
		 * @brief Start the transaction
		*/
		void begin();
		/*!
		 * @brief Finish the transaction
		*/
		void end();
		/*!
		 * @brief Execute transaction
		*/
		void commit();
		/*!
		 * @brief Remove the last transaction
		*/
		void rollback();

	private:
		/*!
		 * @brief Reference to the open database
		*/
		SQLite3::Database _db;
};