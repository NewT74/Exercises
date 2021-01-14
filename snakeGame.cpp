#include<iostream>
#include<random>
#include<vector>
using namespace std;

random_device rd;
mt19937 gen(rd());

int random(int start, int end) {
    uniform_int_distribution <> distrib(start, end);
    return distrib(gen);
}

struct Point {
    int x, y;
    Point() {};
    Point(int a, int b) {
        x = a;
        y = b;
    };
};

struct Frame {
    int n, m;
    Point snake;
    Point food;
    char step;
    int countSteps;
    vector <vector <char>> data;
    vector <Point> snakeBody;
    bool loose = false;
    void createGame() {
        cout << "Nhap n, m:";
        cin >> n >> m;
        cout << "Nhap vi tri bat dau:";
        cin >> snake.x >> snake.y;
        snakeBody.push_back(Point(snake.x, snake.y));
        data.resize(n);
        for (int i = 0; i < n; i++) data[i].resize(m);
        createMap();
    }
    void createFood() {
        food.x = random(1, n - 2);
        food.y = random(1, m - 2);
        for (int i = 0; i < snakeBody.size(); i++) {
            if (snakeBody[i].x == food.x && snakeBody[i].y == food.y) {
                food.x = random(1, n - 2);
                food.y = random(1, m - 2);
            }
        }
        data[food.x][food.y] = 'O';
    }
    void createMap() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 || i == n - 1) data[i][j] = 'H';
                else if (i == 0 || i == n - 1) data[i][j] = 'H';
                else if (j == 0 || j == m - 1) data[i][j] = 'H';
                else data[i][j] = ' ';
            }
        }
        createFood();
        data[snake.x][snake.y] = 'X';
    }
    void printMap() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }
    void checkLoose() {
        if (snake.x == 0 || snake.x >= n - 1) loose = true;
        else if (snake.y == 0 || snake.y >= m - 1) loose = true;
        for (int i = 0; i < snakeBody.size(); i++) {
            if (snake.x == snakeBody[i].x && snake.y == snakeBody[i].y) {
                loose = true;
                break;
            }
        }
    }
    void updateGame() {
        for (int i = 0; i < countSteps; i++) {
            if (step == 'l') snake.y--;
            else if (step == 'r') snake.y++;
            else if (step == 'u') snake.x--;
            else snake.x++;
            checkLoose();
            if (!loose) {
                data[snakeBody[0].x][snakeBody[0].y] = ' ';
                if (snake.x == food.x && snake.y == food.y) createFood();
                else snakeBody.erase(snakeBody.begin());
                snakeBody.push_back(Point(snake.x, snake.y));
                for (int j = 0; j < snakeBody.size(); j++) {
                    data[snakeBody[j].x][snakeBody[j].y] = (j == snakeBody.size() - 1) ? 'X' : 'x';
                }
            }
            else break;
        }
    }
    void run() {
        while (!loose) {
            system("cls");
            printMap();
            cout << "Nhap huong di chuyen (l, r, u, d):";
            cin >> step;
            cout << "Nhap so buoc di chuyen:";
            cin >> countSteps;
            updateGame();
        }
        cout << "Thua";
        system("pause");
    }
};

main() {
    Frame snakeGame;
    snakeGame.createGame();
    snakeGame.run();
}
