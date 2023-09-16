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
#include <memory>

namespace fs = std::filesystem;

namespace database {

class Writer {
public:
    Writer() = default;

    

private:

};

class FileHandler {
public:
    FileHandler() {
        const std::string home_dir = std::getenv("HOME");

        fs::path path_to_database_dir{home_dir.c_str()};
        path_to_database_dir /= ".login_and_registration";
        if (not fs::exists(path_to_database_dir)) {
            fs::create_directory(path_to_database_dir);
            fs::permissions(path_to_database_dir, fs::perms::all);
        }
        path_to_database = fs::path{home_dir} / DATABASE_FILE_PATH_EXT;
        std::cout << "Database directory: " << path_to_database << std::endl;
    }

    const fs::path GetPath() const {
        return path_to_database;
    }

    std::fstream& GetFileHandle() {
        if (not database_file.is_open()) {
            database_file.open(path_to_database, std::ios::out | std::ios::binary);
        }
        return database_file;
    }

private:
    static constexpr auto DATABASE_FILE_PATH_EXT{".login_and_registration/database.db"};
    fs::path path_to_database;
    std::fstream database_file;

};

class Handler {
public:
    Handler(std::unique_ptr<FileHandler> database_file_handler) 
        : db_file_handler{std::move(database_file_handler)}
    {

    }

private:
    std::unique_ptr<FileHandler> db_file_handler;

};

} // namespace database

int main() {
}
