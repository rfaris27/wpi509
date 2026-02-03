#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h>
#include <cppconn/resultset_metadata.h> // Required for getMetaData
#include <iostream>
#include <string>

int main()
{
    try
    {
        sql::mysql::MySQL_Driver *driver;
        sql::Connection *con;

        driver = sql::mysql::get_mysql_driver_instance();

        // Using your specific host, port 3333, and password 'p'
        con = driver->connect("tcp://host.docker.internal:3333", "root", "p");
        con->setSchema("dev_db");

        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *res;
        sql::ResultSetMetaData *res_meta;

        // --- SECTION 1: DELTAS ---
        std::cout << "--- Deltas Flight Data ---" << std::endl;
        res = stmt->executeQuery("SELECT * FROM deltas LIMIT 1");
        res_meta = res->getMetaData();
        int delta_cols = res_meta->getColumnCount();

        while (res->next())
        {
            for (int i = 1; i <= delta_cols; i++)
            {
                std::cout << res->getString(i);
                if (i < delta_cols)
                    std::cout << ", ";
            }
            std::cout << std::endl;
        }

        // --- SECTION 2: SOUTHWESTS ---
        std::cout << "\n--- Southwest Flight Data ---" << std::endl;
        res = stmt->executeQuery("SELECT * FROM southwests LIMIT 1");
        res_meta = res->getMetaData();
        int sw_cols = res_meta->getColumnCount();

        while (res->next())
        {
            for (int i = 1; i <= sw_cols; i++)
            {
                std::cout << res->getString(i);
                if (i < sw_cols)
                    std::cout << ", ";
            }
            std::cout << std::endl;
        }

        // Clean up
        delete res;
        delete stmt;
        delete con;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}