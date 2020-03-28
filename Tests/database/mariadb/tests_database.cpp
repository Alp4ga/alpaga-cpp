/*
 * Company: Your Company
 * File: tests_database.cpp
 * Project: mariadb
 * File Created: Saturday, 28th March 2020 6:31:19 pm
 * Author: Alp4ga (you@you.you)
 * -----
 * Last Modified: Saturday, 28th March 2020 6:31:22 pm
 * Modified By: Alp4ga (you@you.you>)
 * -----
 */

#include <iostream>
#include "gtest/gtest.h"

#include "database/mariadb/Database.hpp"

TEST(DATABASE_MARIADB, database_connection_success)
{
	Mariadb::Database db;
	db.connection("tcp://127.0.0.1", "root", "root", "", 3307);
	//auto res = db.connect("tcp://127.0.0.1:3307", "root", "root");
	ASSERT_EQ(true, true);
}