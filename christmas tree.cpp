#include <iostream>
#include <vector>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <fstream>
using namespace std;

const vector<string> colors = { "\033[31m", "\033[34m", "\033[33m", "\033[35m", "\033[36m" };
const vector<string> toySymbols = { "@", "%", "#", "&", "+" };

// ������� ��� ��������� ���������� �������
string getNextColor(int index) {
    return colors[index % colors.size()];
}

// ������� ��� �������� ������
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ������� ��� ��������� ������
vector<vector<string>> createTree(int levels) {
    vector<vector<string>> tree(levels + 2);  // ������ ���� ��� ��������
    for (int level = 0; level < levels; ++level) {
        int stars = 2 * level + 1;
        int spaces = levels - level - 1;

        string row(spaces, ' '); // ������ ����� ������
        for (int i = 0; i < stars; ++i) {
            if (i % 3 == 0 && level > 0) {
                row += toySymbols[i % toySymbols.size()]; // ������ �������
            }
            else {
                row += "\033[32m*"; // ������ ����
            }
        }
        row += string(spaces, ' '); // ������ ���� ����
        tree[level] = { row };
    }
    // ������ �������
    string trunk(levels - 1, ' ');
    trunk += "\033[33m***";
    tree[levels] = { trunk };
    tree[levels + 1] = { trunk };
    return tree;
}

// ������� ��� ��������� ������ � ��������
void displayTree(vector<vector<string>>& tree, int animationCycles) {
    for (int cycle = 0; cycle < animationCycles; ++cycle) {
        clearScreen();
        // �������� ������ � ��������
        for (int i = 0; i < tree.size(); ++i) {
            string row = tree[i][0];
            for (int j = 0; j < row.length(); ++j) {
                if (row[j] == '@' || row[j] == '%' || row[j] == '#' || row[j] == '&' || row[j] == '+') {
                    cout << getNextColor(cycle) << row[j];
                }
                else {
                    cout << row[j];
                }
            }
            cout << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(500)); // �������� ��� �������
    }
}

// ������� ��� ���������� ������ � ����
void saveTreeToFile(const vector<vector<string>>& tree) {
    ofstream file("christmas_tree_animated.txt");
    if (file.is_open()) {
        for (const auto& row : tree) {
            for (const auto& symbol : row[0]) {
                if (symbol == '@' || symbol == '%' || symbol == '#' || symbol == '&' || symbol == '+') {
                    file << symbol;
                }
                else if (symbol == '*') {
                    file << '*';
                }
                else {
                    file << symbol;
                }
            }
            file << endl;
        }
        file.close();
        cout << "������ ��������� �� �����!" << endl;
    }
    else {
        cerr << "������� �� ��� ���������� ������!" << endl;
    }
}

int main() {
    srand(time(0));
    int h;
    cout << "������ ������� ����: ";
    cin >> h;
    vector<vector<string>> tree = createTree(h);
    int animationCycles = 10; // ʳ������ ����� �������
    displayTree(tree, animationCycles);
    saveTreeToFile(tree);
    return 0;
}
