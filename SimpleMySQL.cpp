//============================================================================
// Name        : SimpleMySQL.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <exception>

#include "mysql_connection.h"
#include "mysql_driver.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <cppconn/resultset_metadata.h>

using namespace std;

int main(void) {
	puts("Starting Simple MySQL Project");

	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
	sql::PreparedStatement *prep_stmt;

	try {
		/* Create a connection */
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "willtl", "w3423004");
		/* Connect to the MySQL test database */
		con->setSchema("java_backend");

		/* Execute query */
		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT * FROM Operation");

		/* Get result set metadata */
		sql::ResultSetMetaData *res_meta = res->getMetaData();
		int columns = res_meta->getColumnCount();

		/* Loop for each row */
		while (res->next()) {
			/* Access column data by index, 1-indexed*/
			for (int i = 1; i <= columns; i++) {
				cout << res->getString(i) << "|";
			}
			cout << endl;
		}

		/* Insert object */
		/* Prepared statement */
		prep_stmt =
				con->prepareStatement(
						"INSERT INTO Operation(end, idJob, machine, start) VALUES (?, ?, ?, ?)");

		/* Define statement values */
		prep_stmt->setUInt64(1, 1501844400000);
		prep_stmt->setInt(2, 4);
		prep_stmt->setInt(3, 4);
		prep_stmt->setUInt64(4, 1501840800000);

		/* Execute prepared statement*/
		prep_stmt->execute();

		delete res;
		delete stmt;
		delete con;
	} catch (const exception& e) {
		cout << "Exception: " << e.what() << endl;
	}
	return EXIT_SUCCESS;
}
