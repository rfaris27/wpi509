#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h> // Corrected header
#include <iostream>
#include <string>

int main() {
    try {
        sql::mysql::MySQL_Driver *driver;
        sql::Connection *con;

        driver = sql::mysql::get_mysql_driver_instance();
        
        // Connect using the service name 'db' from your docker-compose
        con = driver->connect("tcp://db:3307", "root", "root_password");
        
        // Ensure this matches the database name you imported
        con->setSchema("dev_db");

        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *res1;
        sql::ResultSet *res2;

        // Query 1: Deltas
        res1 = stmt->executeQuery("SELECT * FROM deltas LIMIT 1");
        while (res1->next()) {
            // Replace "column_name" with an actual column name from your table
            std::cout << "Deltas Data: " << res1->getString(1) << std::endl;
        }

        // Query 2: Southwest
        res2 = stmt->executeQuery("SELECT * FROM southwests LIMIT 1");
        while (res2->next()) {
            std::cout << "Southwest Data: " << res2->getString(1) << std::endl;
        }

        delete res1;
        delete res2;
        delete stmt;
        delete con;

    } catch (sql::SQLException &e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
    }

    return 0;
}