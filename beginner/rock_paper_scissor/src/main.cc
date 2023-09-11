/*
 *  Project: RockPaperScissor 
 *
 *  File: main.cc
 *
 *  Date: 11.09.2023  
 *  
*/
#include <iostream>
#include <random>
#include <string>
#include <map>

const static std::map<int, char> shape_int_to_char_mapper {
    {1, 'r'},
    {2, 'p'},
    {3, 's'}
};

int GenerateRandomShape() {
    static std::random_device rd;
    static std::mt19937 mersenne_twister(rd());
    static std::uniform_int_distribution<std::mt19937::result_type> dist(1, 3);
    return dist(mersenne_twister);
}

void UpdateUserScore(const char computer_shape, const char user_shape, int& user_score) {
    if (computer_shape == user_shape) {
        return;
    }

    if ((user_shape == 'p' && computer_shape == 'r') || 
        (user_shape == 's' && computer_shape == 'p') ||
        (user_shape == 'r' && computer_shape == 's')) {
        user_score += 1;
    }
    else {
        user_score -= 1;
    }
}

int main() {
    std::cout << "The Rock, Paper, Scissor Game.\n"
                 "Type either: 'r' - rock, 'p' - paper, 's' - scissor to play.\n"
                 "After each time you type, press enter and the computer will "
                 "show what it has selected RANDOMLY." << std::endl;
    
    int user_score = 0;      
    char input_shape = '\0';
    while (user_score < 2 and user_score > -2) {
        const char computer_shape = shape_int_to_char_mapper.at(GenerateRandomShape());

        std::cout << "Input shape (r | p | s): ";
        std::cin >> input_shape;
        if (not (input_shape == 'r' or input_shape == 'p' or input_shape == 's')) {
            std::cout << "Invalid input: " << input_shape << std::endl;
            return 0;
        }
        
        UpdateUserScore(computer_shape, input_shape, user_score);
        std::cout << "Computer: " << computer_shape 
                  << " | user: " << input_shape 
                  << ", user score: " << user_score << std::endl;
    }

    if (user_score > 0) {
        std::cout << "User won!" << std::endl;
    }
    else {
        std::cout << "Computer won!" << std::endl;
    }
}
