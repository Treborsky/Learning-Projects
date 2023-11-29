/*
 *  Project: LoginAndRegistrationSystem 
 *
 *  File: main.cc
 *
 *  Date: 12.09.2023  
 *  
 */
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <memory>
#include <optional>
#include <charconv>
#include <iomanip>

#include "log.h"

#define LOG_DBG_MAIN(stream_fmt) LOG_DEBUG(MAIN, stream_fmt)
#define LOG_INF_MAIN(stream_fmt) LOG_INFO(MAIN, stream_fmt)

struct Record {
    long unsigned int id;
    std::string username;
    std::string password;
};

class Database {
  std::string storedDatabaseFilePath;
  bool loaded;
  std::vector<Record> database;

 public:
  Database(const std::string& databaseFilePath) {
    Init(databaseFilePath);
    storedDatabaseFilePath = databaseFilePath;
  }

  ~Database() {
    Write();
  }

  bool CheckPassword(const std::string& usernameInput, const std::string& passwordInput) const {
    const auto passwordFromDatabase = GetPasswordForUsername(usernameInput);
    if (!passwordFromDatabase.has_value()) {
        return false;
    }
    else {
        return passwordInput == passwordFromDatabase.value();
    }
  }

  std::vector<Record> GetRecords() const {
    return database;
  }

 private:
  Record LineToRecord(const std::string& lineBuffer) {
    std::string buffer = lineBuffer; // copy to new buffer
    /* 
     * Schema is : 
     * Id               , Username, Password
     * long unsigned int, string  , string
     */
    Record newRecord;

    std::vector<std::string> splitBuffer;
    /* Split the buffer by comma and put into splitBuffer */
    std::size_t pos = 0;
    // LOG_DBG_MAIN("dbg1");
    while ((pos = buffer.find(',')) != std::string::npos) {
      splitBuffer.emplace_back(buffer.substr(0, pos));
      buffer.erase(0, pos + 1);
    }
    splitBuffer.emplace_back(buffer);
    // LOG_DBG_MAIN("dbg2");

    /* Parse each split in the splitBuffer into the appropriate record value */
    // LOG_DBG_MAIN("length of splitBuffer: " << splitBuffer.size());
    newRecord.id = std::stoul(splitBuffer[0]);
    newRecord.username = splitBuffer[1];
    newRecord.password = splitBuffer[2];

    // LOG_DBG_MAIN("dbg3");
    return newRecord;
  }

  void Init(const std::string& databaseFilePath) {
    const std::string kCsvFileEnding{".csv"};
    if (not std::equal(kCsvFileEnding.rbegin(), kCsvFileEnding.rend(), databaseFilePath.rbegin())) {
      throw "Invalid database path";
    }

    std::ifstream file;
    file.open(databaseFilePath, std::ios_base::in);

    /* Parse the file line by line - schema is embedded in the logic here, no .csv header */
    std::string lineBuffer;
    while (std::getline(file, lineBuffer)) {
      database.emplace_back(LineToRecord(lineBuffer));
    }
  }

  void Write() {
    std::ofstream file;
    file.open(storedDatabaseFilePath.c_str(), std::ios_base::out);

    for (const auto& record : database) {
      file << record.id << "," << record.username << "," << record.password << "\n";
    }
  }

  std::optional<const std::string> GetPasswordForUsername(const std::string& usernameInput) const {
    std::optional<const std::string> matchingPassword;
    for (const auto& record : database) {
        if (record.username == usernameInput) {
            matchingPassword.emplace(record.password);
        }
    }
    return matchingPassword;
  }

};

int main() {
  Database database{"/home/treborsky/Learning-Projects/beginner/login_and_registration_system/database.csv"};

  /* TODO: go into the CLI client here */
  /* CLI should allow us to:
   *  - print the database without passwords 
   *  - add new users
   *  - delete users if password was supplied
   */

  return 0;
}
