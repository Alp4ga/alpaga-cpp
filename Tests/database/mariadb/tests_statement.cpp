/*
 * Company: Your Company
 * File: tests_statement.cpp
 * Project: mariadb
 * File Created: Monday, 30th March 2020 6:14:22 pm
 * Author: Alp4ga (you@you.you)
 * -----
 * Last Modified: Monday, 30th March 2020 6:14:25 pm
 * Modified By: Alp4ga (you@you.you>)
 * -----
 */

#include <iostream>
#include "gtest/gtest.h"

#include "tests_config.hpp"
#include "database/mariadb/Statement.hpp"

TEST(STATEMENT_MARIADB, GENERATE_STATEMENT)
{
	Mariadb::Database db;
	Mariadb::Statement stmt(db, "INSERT INTO tmp VALUES(?,?)");
}