/*
 *  Project: LoginAndRegistrationSystem 
 *
 *  File: main.cc
 *
 *  Date: 12.09.2023  
 *  
 */
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <cstdlib>

namespace fs = std::filesystem;

class DatabaseFileHandler {
public:
    DatabaseFileHandler() : path_to_database{std::getenv("HOME")} {
        path_to_database /= ".login_and_registration";
        if (not fs::exists(path_to_database)) {
            fs::create_directory(path_to_database);
            fs::permissions(path_to_database, fs::perms::all);
        }
        std::cout << "Database directory: " << path_to_database << std::endl;
        path_to_database
    }

    void CreateDatabaseIfNotCreated() {
    }

    fs::path GetDatabaseDirectoryPath() const {
        return path_to_database;
    }

private:
    static constexpr auto DATABASE_FILE_PATH_EXT{".login_and_registration/database.db"};
    fs::path path_to_database;

};

int main() {
    DatabaseFileHandler path_handler;
}
