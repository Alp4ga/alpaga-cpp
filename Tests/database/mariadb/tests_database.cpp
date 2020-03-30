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

#include "tests_config.hpp"
#include "database/mariadb/Database.hpp"

TEST(DATABASE_MARIADB, database_connection_success)
{
	Mariadb::Database db;
	auto res = db.connection(
		Mariadb::TestsConfig::HOSTNAME,
		Mariadb::TestsConfig::USER,
		Mariadb::TestsConfig::PASSWORD,
		Mariadb::TestsConfig::DATABASE,
		Mariadb::TestsConfig::PORT
	);
	ASSERT_TRUE(res);
}

TEST(DATABASE_MARIADB, database_connection_failed)
{
	Mariadb::Database db;
	auto res = db.connection(
		Mariadb::TestsConfig::HOSTNAME,
		Mariadb::TestsConfig::USER
	);
	ASSERT_FALSE(res);
}

TEST(DATABASE_MARIADB, database_test_connection_success)
{
	Mariadb::Database db;
	auto res = db.connection(
		Mariadb::TestsConfig::HOSTNAME,
		Mariadb::TestsConfig::USER,
		Mariadb::TestsConfig::PASSWORD,
		Mariadb::TestsConfig::DATABASE,
		Mariadb::TestsConfig::PORT
	);
	ASSERT_TRUE(res);
	ASSERT_TRUE(db.isConnected());
}

TEST(DATABASE_MARIADB, database_test_connection_failed)
{
	Mariadb::Database db;
	auto res = db.connection(
		Mariadb::TestsConfig::HOSTNAME,
		Mariadb::TestsConfig::USER
	);
	ASSERT_FALSE(res);
	ASSERT_FALSE(db.isConnected());
}

TEST(DATABASE_MARIADB, database_connected_disconect)
{
	Mariadb::Database db;
	auto res = db.connection(
		Mariadb::TestsConfig::HOSTNAME,
		Mariadb::TestsConfig::USER,
		Mariadb::TestsConfig::PASSWORD,
		Mariadb::TestsConfig::DATABASE,
		Mariadb::TestsConfig::PORT
	);
	ASSERT_TRUE(res);
	db.disconnect();
	ASSERT_FALSE(db.isConnected());
}

TEST(DATABASE_MARIADB, database_disconected_disconect)
{
	Mariadb::Database db;
	auto res = db.connection(
		Mariadb::TestsConfig::HOSTNAME,
		Mariadb::TestsConfig::USER
	);
	ASSERT_FALSE(res);
	db.disconnect();
	ASSERT_FALSE(db.isConnected());
}

TEST(DATABASE_MARIADB, database_host)
{
	Mariadb::Database db;
	auto res = db.connection(
		Mariadb::TestsConfig::HOSTNAME,
		Mariadb::TestsConfig::USER,
		Mariadb::TestsConfig::PASSWORD,
		Mariadb::TestsConfig::DATABASE,
		Mariadb::TestsConfig::PORT
	);
	ASSERT_EQ(Mariadb::TestsConfig::HOSTNAME, db.getHost());
}

TEST(DATABASE_MARIADB, database_user)
{
	Mariadb::Database db;
	auto res = db.connection(
		Mariadb::TestsConfig::HOSTNAME,
		Mariadb::TestsConfig::USER,
		Mariadb::TestsConfig::PASSWORD,
		Mariadb::TestsConfig::DATABASE,
		Mariadb::TestsConfig::PORT
	);
	ASSERT_EQ(Mariadb::TestsConfig::USER, db.getUser());
}

TEST(DATABASE_MARIADB, database_port_default)
{
	Mariadb::Database db;
	auto res = db.connection(
		Mariadb::TestsConfig::HOSTNAME,
		Mariadb::TestsConfig::USER,
		Mariadb::TestsConfig::PASSWORD,
		Mariadb::TestsConfig::DATABASE
	);
	ASSERT_EQ(3307, db.getPort());
}

TEST(DATABASE_MARIADB, database_port)
{
	Mariadb::Database db;
	auto res = db.connection(
		Mariadb::TestsConfig::HOSTNAME,
		Mariadb::TestsConfig::USER,
		Mariadb::TestsConfig::PASSWORD,
		Mariadb::TestsConfig::DATABASE,
		Mariadb::TestsConfig::PORT
	);
	ASSERT_EQ(Mariadb::TestsConfig::PORT, db.getPort());
}