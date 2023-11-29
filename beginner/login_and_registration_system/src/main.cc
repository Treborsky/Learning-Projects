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
#include <vector>
#include <fstream>
#include <cstdlib>
#include <memory>
#include <optional>

struct Record {
    std::string username;
    std::string password;
};

class Database {
  std::vector<Record> database;
  bool loaded;

 public:
  Database() {}

  void Init(const std::string& databaseFilePath) {
    /* TODO: actual work X D */
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

 private:
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

}
