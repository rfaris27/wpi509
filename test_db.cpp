#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <iostream>

int main() {
    try {
        sql::mysql::MySQL_Driver *driver;
        sql::Connection *con;

        driver = sql::mysql::get_mysql_driver_instance();
        
        // We use "db" because that is the name in our docker-compose.yml
        con = driver->connect("tcp://db:3306", "root", "root_password");

        std::cout << "Successfully connected to MySQL from C++!" << std::endl;

        delete con;
    } catch (sql::SQLException &e) {
        std::cout << "Connection Failed! Error: " << e.what() << std::endl;
    }
    return 0;
}