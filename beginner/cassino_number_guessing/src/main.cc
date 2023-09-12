/*
 *  Project: CassinoNumberGuessing
 *
 *  File: main.cc
 *
 *  Date: 11.09.2023
 */
#include <iostream>
#include <random>

template<int lower, int upper>
class GuessingGame {
public:
    GuessingGame() 
        : rd{}, mersenne_twister{rd()}, dist{lower, upper}
        , SCORING_RATE{(static_cast<float>(upper - lower) / 2.0) / static_cast<float>(upper + lower)}
        , BEST_SCORE{static_cast<float>(upper + lower)}, number_of_guesses{0U}, score{0.0} 
    {
        std::cout << "Guessing game: [scoring_rate: " << SCORING_RATE 
                  << ", best_score: " << BEST_SCORE << "]" << std::endl;
    }

    void UpdateScore() {
        float latest_score = BEST_SCORE;
        for (unsigned int i = 0; i < number_of_guesses; ++i) {
            latest_score *= SCORING_RATE;
        }
        score += latest_score;
    }

    int RandomNumberGenerator() {
        return dist(mersenne_twister);
    }

    void GuessMadeCallback() {
        number_of_guesses += 1U;
    }

    float GetScore() const {
        return score;
    }

    unsigned int GetNumberOfGuesses() const {
        return number_of_guesses;
    }

private:
    std::random_device rd;
    std::mt19937 mersenne_twister;
    std::uniform_int_distribution<std::mt19937::result_type> dist;
    const float SCORING_RATE;
    const float BEST_SCORE;
    unsigned int number_of_guesses;
    float score;

};

int main() {
    std::cout << "Cassino Number Guessing Game.\n"
              << "Type integer numbers and confirm with [enter] until you guess the number. "
              << "The range is [0, 10]." << std::endl;

    GuessingGame<0, 10> game;
    
    const int random_number = game.RandomNumberGenerator();
    int guess = -1;
    
    while (true) {
        std::cout << "Your guess: ";
        std::cin >> guess;
        
        game.GuessMadeCallback();

        if (guess == random_number) {
            game.UpdateScore();
            break;
        }
        else {
            std::cout << "Your guess was wrong." << std::endl;
        }
    }

    std::cout << "Your guess was right! You've managed the score of: " << game.GetScore()
              << " in " << game.GetNumberOfGuesses() << " guesses" << std::endl;
}