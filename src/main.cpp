#include <iostream>
#include <iomanip>
#include <vector>
#include <sqlite3.h>
using namespace std;


bool tableExists(sqlite3* db);

int main() {

	// introduction
	cout << "Welcome to STM. Your premium stock management application." << endl;
	cout << "Creating an opening a database right now!" << endl;

	// creating/opening a database
	sqlite3* db;
	int rc = sqlite3_open("STMdatabase.db", &db);
	if (rc) {
    	// Handle the error (failed to open the database)
		cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
		return 1;
	} 

	// db creation
	 if (!tableExists(db)) {
        // SQL statement to create the table
        const char* createTableSQL = "CREATE TABLE STMdatabase ("
                                     "id INTEGER PRIMARY KEY,"
                                     "name TEXT NOT NULL,"
                                     "information TEXT,"
                                     "stock INTEGER NOT NULL);";

        rc = sqlite3_exec(db, createTableSQL, 0, 0, 0);
        if (rc != SQLITE_OK) {
            cerr << "Error creating table: " << sqlite3_errmsg(db) << endl;
            sqlite3_close(db);
            return 1;
        }

        cout << "Table 'STMdatabase' created successfully." << endl;
    } else {
        cout << "Table 'STMdatabase' already exists." << endl;
    }

    // adding in 2 rows of stock
    vector<const char*> insertDataSQLs = {
        "INSERT INTO STMdatabase (id, name, information, stock) VALUES (001, 'Baby Wipes', 'Cleaning supply', 230);",
        "INSERT INTO STMdatabase (id, name, information, stock) VALUES (002, 'Apples', 'Food', 938);",
    };


    // error handling
    for (const char* insertDataSQL : insertDataSQLs) {
            rc = sqlite3_exec(db, insertDataSQL, 0, 0, 0);
            if (rc != SQLITE_OK) {
                std::cerr << "Error inserting data: " << sqlite3_errmsg(db) << std::endl;
                sqlite3_close(db);
                return 1;
            }
    }

 
    sqlite3_close(db);
    return 0;
}

bool tableExists(sqlite3* db) {
    sqlite3_stmt* stmt;
    const char* checkTableSQL = "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='STMdatabase';";
    int rc = sqlite3_prepare_v2(db, checkTableSQL, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        cerr << "Error checking table existence: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    rc = sqlite3_step(stmt);
    int count = 0;
    if (rc == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);

    return count > 0;
}


