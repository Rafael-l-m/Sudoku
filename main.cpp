#include <iostream>
#include <limits>
#include <stdexcept>

class Sudoku {
public:
    explicit Sudoku(const int form) {if (form == 9) this->form = form; else throw std::runtime_error("The integer should be 9");}

    void refillSudoku(){
        std::cout << "Please input the integer correspondence of each block: " << std::endl;

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                std::string result = "Position [" + std::to_string(i + 1) + "][" + std::to_string(j + 1) + "]:";
                this->sudoku[i][j] = verify_input(result);
            }
        }
    }

    void getSolution() {
        if (this->solve_sudoku()) this->outputSolution();

        else {
            std::cout << "No solution exists" << std::endl;
            exit(-1);
        }
    }

    ~Sudoku() { std::cout << "\nProcess finished" << std::endl; }

private:
    int form;
    int sudoku[9][9] = {};

    static int verify_input(const std::string& str) {
        int temp = 0;

        while (true) {
            std::cout << str << std::endl;
            std::cin >> temp;

            if (std::cin.fail() || temp < 0 || temp > 9) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input (requires an integer between 0 and 9)" << std::endl;
            }

            else return temp;
        }
    }

    [[nodiscard]] bool isValid(const int row, const int col, const int num) const {
        for (int x = 0; x < this->form; x++) {
            if (this->sudoku[row][x] == num || this->sudoku[x][col] == num) return false;
        }

        const int startRow = row - row % 3;
        const int startCol = col - col % 3;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (this->sudoku[startRow + i][startCol + j] == num) return false;
            }
        }

        return true;
    }

    bool solve_sudoku() {
        for (int row = 0; row < this->form; ++row) {
            for (int col = 0; col < this->form; ++col) {
                if (this->sudoku[row][col] == 0) {
                    for (int num = 1; num <= 9; ++num) {
                        if (isValid(row, col, num)) {
                            this->sudoku[row][col] = num;

                            if (solve_sudoku()) return true;

                            this->sudoku[row][col] = 0;
                        }
                    }

                    return false;
                }
            }
        }

        return true;
    }

    void outputSolution() const {
        std::cout << "The result of the sudoku is: " << std::endl;

        for (int i = 0; i < this->form; i++) {
            for (int j = 0; j < this->form; j++) {
                std::cout << this->sudoku[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    char response;

    auto sudoku = Sudoku(9);

    while (true) {
        sudoku.refillSudoku();
        sudoku.getSolution();

        std::cout << "Would you like to continue: (Y/N)" << std::endl;
        std::cin >> response;
        std::cin.get();

        if (response == 'y' || response == 'Y') continue;

        break;
    }

    std::cin.get();

    return 0;
}