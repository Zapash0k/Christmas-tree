#include <iostream>
#include <vector>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <fstream>
using namespace std;

const vector<string> colors = { "\033[31m", "\033[34m", "\033[33m", "\033[35m", "\033[36m" };
const vector<string> toySymbols = { "@", "%", "#", "&", "+" };

// Функція для отримання наступного кольору
string getNextColor(int index) {
    return colors[index % colors.size()];
}

// Функція для очищення екрану
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Функція для створення ялинки
vector<vector<string>> createTree(int levels) {
    vector<vector<string>> tree(levels + 2);  // Додаємо місце для стовбура
    for (int level = 0; level < levels; ++level) {
        int stars = 2 * level + 1;
        int spaces = levels - level - 1;

        string row(spaces, ' '); // Пробіли перед зірками
        for (int i = 0; i < stars; ++i) {
            row += "\033[32m*"; // Додаємо зірки
        }
        row += string(spaces, ' '); // Пробіли після зірок
        tree[level] = { row };
    }
    // Додаємо стовбур
    string trunk(levels - 1, ' ');
    trunk += "\033[33m***";
    tree[levels] = { trunk };
    tree[levels + 1] = { trunk };
    return tree;
}

// Функція для виведення ялинки з випадковими прикрасами
void displayTreeWithRandomToys(vector<vector<string>>& tree, int animationCycles) {
    for (int cycle = 0; cycle < animationCycles; ++cycle) {
        clearScreen();
        // Виводимо ялинку з випадковими прикрасами
        for (int i = 0; i < tree.size(); ++i) {
            string row = tree[i][0];
            for (int j = 0; j < row.length(); ++j) {
                // Випадково додаємо прикраси (з ймовірністю 1 до 5)
                if (row[j] == '*' && rand() % 5 == 0) {
                    cout << getNextColor(cycle) << toySymbols[rand() % toySymbols.size()];
                }
                else {
                    cout << row[j];
                }
            }
            cout << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(500)); // Затримка для анімації
    }
}

// Функція для збереження ялинки у файл
void saveTreeToFile(const vector<vector<string>>& tree) {
    ofstream file("christmas_tree_animated.txt");
    if (file.is_open()) {
        for (const auto& row : tree) {
            for (const auto& symbol : row[0]) {
                if (symbol == '*' || symbol == ' ' || symbol == '\033') {
                    file << symbol;
                }
            }
            file << endl;
        }
        file.close();
        cout << "Save was successful!" << endl;
    }
    else {
        cerr << "Error occurred while saving the tree into a file!" << endl;
    }
}

int main() {
    srand(time(0));
    int h;
    cout << "Enter number of levels: ";
    cin >> h;
    vector<vector<string>> tree = createTree(h);
    int animationCycles = 10; // Кількість циклів анімації
    displayTreeWithRandomToys(tree, animationCycles);
    saveTreeToFile(tree);
    return 0;
}
