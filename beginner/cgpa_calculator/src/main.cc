/*
 *  Project: CgpaCalculator
 *
 *  File: main.cc
 *
 *  Date: 11.09.2023
 */
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <functional>
#include <optional>
#include <fstream>

struct Grade {
    std::string subject_name;
    float value;
};

struct Subject {
    std::string subject_name;
    int ects_weight;
};

float CalculateCgpa(const std::vector<Grade>& grades) {
    float cgpa = 0.0;
    for (const auto& grade : grades) {
        cgpa += grade.value;
    }
    return cgpa / grades.size();
}

int GetSubjectWeight(const Grade& grade, const std::vector<Subject>& subjects) {
    for (const auto& subject : subjects) {
        if (grade.subject_name == subject.subject_name) {
            return subject.ects_weight;
        }
    }
    return 1; // no weight found, return 1, meaning no weight is applied (?)
}

class CsvRow {
public:
    std::string_view operator[](std::size_t index) const {
        return std::string_view(&line[data[index] + 1], data[index + 1] - (data[index] + 1));
    }

    std::size_t size() const {
        return data.size() - 1;
    }

    void read_next_row(std::istream& str) {
        std::getline(str, line);

        data.clear();
        data.emplace_back(-1);
        
        std::string::size_type pos = 0;
        while ((pos = line.find(',', pos)) != std::string::npos) {
            data.emplace_back(pos);
            ++pos;
        }

        pos = line.size();
        data.emplace_back(pos);
    }

private:
    std::string line;
    std::vector<int> data;

};

std::istream& operator>>(std::istream& str, CsvRow& data) {
    data.read_next_row(str);
    return str;
}

float CalculateCgpaWeighted(const std::vector<Grade>& grades, const std::vector<Subject>& subjects) {
    float cgpa = 0.0;
    float weight_sum = 0.0;
    for (const auto& grade : grades) {
        const float weight = static_cast<float>(GetSubjectWeight(grade, subjects));
        cgpa += grade.value * weight;
        weight_sum += weight;
    }
    return cgpa / weight_sum;
}

int main(int argc, char** argv) {
    std::optional<std::vector<Grade>> grades;
    std::optional<std::vector<Subject>> subjects;

    if (argc >= 2) { /* load only grade data */
        const std::string path_to_grade_data{argv[1]};
        std::ifstream file{path_to_grade_data, std::ios::in};
        if (!file.is_open()) {
            std::cout << "Failed to open: " << path_to_grade_data << std::endl;
            return 0;
        }
        else {
            std::cout << "Reading file: " << path_to_grade_data << std::endl;
            CsvRow row;
            file >> row;
            const std::size_t schema_len = row.size();
            
            std::cout << "Schema length: " << schema_len << ", schema: \"";
            for (std::size_t i = 0U; i < row.size() - 1; ++i) {
                std::cout << row[i] << ", ";
            }
            std::cout << row[row.size() - 1] << "\"." << std::endl;

            /* here we assume the schema is followed, otherwise a segfault is guaranteed */
            std::vector<Grade> tmp_grades;
            try {
                while (file >> row) {
                    tmp_grades.push_back({std::string{row[0]}, std::stof(std::string{row[1]})});
                }
            } catch (std::exception& e) {
                std::cout << "Schema in file: " << path_to_grade_data << " is not being followed." << std::endl;
                return 0;
            }

            grades.emplace(tmp_grades);
        }

        if (argc >= 3) { /* load additional subject data for weighted sum */
            const std::string path_to_subject_data{argv[2]};
            file.close();
            file.open(path_to_subject_data, std::ios::in);
            if (!file.is_open()) {
                std::cout << "Failed to open: " << path_to_subject_data << std::endl;
                return 0;
            }
            else {
                std::cout << "Reading file: " << path_to_subject_data << std::endl;
                CsvRow row;
                file >> row;
                const std::size_t schema_len = row.size();
                
                std::cout << "Schema length: " << schema_len << ", schema: \"";
                for (std::size_t i = 0U; i < row.size() - 1; ++i) {
                    std::cout << row[i] << ", ";
                }
                std::cout << row[row.size() - 1] << "\"." << std::endl;

                /* here we assume the schema is followed, otherwise a segfault is guaranteed */
                std::vector<Subject> tmp_subjects;
                try {
                    while (file >> row) {
                        tmp_subjects.push_back({std::string{row[0]}, std::stoi(std::string{row[1]})});
                    }
                } catch (std::exception& e) {
                    std::cout << "Schema in file: " << path_to_subject_data << " is not being followed." << std::endl;
                    return 0;
                }

                subjects.emplace(tmp_subjects);
            }
        }
    }

    std::cout << "\nCGPA Calculator. Calculator for student's average grade. "
                 "\nSupports weighted average if subject file supplied.\n"
                 "------------------------------------------------------------\n"
                 "Usage: CgpaCalculator <grades file name> <subjects file name>\n";

    if (grades.has_value()) {

        std::cout << "------------------------------------------------------------\n"
                  << "Grade data:\n"
                  << "------------------------------------------------------------\n";
        
        for (const auto& grade : *grades) {
            std::cout << std::left << std::setw(50) << grade.subject_name << "   |" 
                    << std::right << std::setw(5) << grade.value << std::endl;
        }

        if (subjects.has_value()) {
            std::cout << "------------------------------------------------------------\n"
                    << "Subject data:\n"
                    << "------------------------------------------------------------\n";

            for (const auto& subject : *subjects) {
                std::cout << std::left << std::setw(50) << subject.subject_name << "   |" 
                        << std::right << std::setw(5) << subject.ects_weight << std::endl;
            }
        }

        std::cout << "------------------------------------------------------------\n"
                  << "Calculated CGPA: " << std::setprecision(3) << CalculateCgpa(*grades) << "\n";
        if (subjects.has_value()) {
            std::cout << "Calculated weighted CGPA: " << std::setprecision(3) << CalculateCgpaWeighted(*grades, *subjects) << "\n";
        }
        std::cout << "------------------------------------------------------------" << std::endl;
    }
}
