#include<iostream>
#include<cstdlib>
#include<ctime>

#define SIZE 10

using namespace std;

class Node {
public:
    Node() {
        Node(0, 0);
    }

    Node(int r, int c) {
        row = r;
        col = c;
    }

    int getRow() { return row; }

    int getCol() { return col; }

    void setRow(int r) {
        if (r >= 0 && r < SIZE)
            row = r;
    }

    void setCol(int c) {
        if (c >= 0 && c < SIZE)
            col = c;
    }

private:
    int col, row;
};

class List {
public:
    List() {
        top = 0;
    }

    /*
    function addElement
    Insert an element from list
    */
    void addElement(int r, int c) {
        if (top < SIZE * SIZE) {
            data[top] = Node(r, c);
            ++top;
        }
    }

    /*
    function removeElement
    remove an element from list and return a pointer point to the element.
    If list is empty, return NULL.
    */
    Node *removeElement() {
        if (top == 0)
            return NULL;
        else
            return &data[--top];
    }

    void printList() {
        int j;
        for (j = 0; j < top; j++) {
            cout << "(" << data[j].getRow() << ", " << data[j].getCol() << ")" << endl;
        }
    }

private:
    Node data[SIZE * SIZE];
    int top;
};

class Maze {
public:
    Maze() {
        initMaze(SIZE);
    }

    /*
    function initMaze
    Allocate a 2-D array with s * s sizes as the map of maze.
    Inside the maze where 0 represent empty space and 1 represent wall.
    [0][0] is start point and [s - 1][s - 1] is finish point.
    Randomly generate 20% wall in the maze.
    Make sure [0][0] and [s - 1][s - 1] are 0

    動態配置一個二維的陣列，大小是 s * s ，用這個陣列表示迷宮的地圖
    陣列中 0 的值表示可以移動的空間， 1 表示牆壁
    [0][0] 的位置表示起點 [s - 1][s - 1] 的位置表示終點
    請在迷宮中加入 20% 的牆壁
    然後確定起點跟終點都是可以移動的位置
    */
    void initMaze(int s) {

        maze = new int *[s];
        for (int i = 0; i < s; ++i) {
            maze[i] = new int[s]();
        }
        srand(time(NULL));
        int wallCounter = 0;
        while (wallCounter < s * s * 0.2) {
            for (int i = 0; i < s; i++) {
                for (int j = 0; j < s; j++) {
                    if (rand() % 5 == 0 && maze[i][j] != 1 && (!(i == 0 && j == 0) && !(i == s - 1 && j == s - 1))) {
                        maze[i][j] = 1;
                        wallCounter++;
                    }
                    if (wallCounter >= s * s * 0.2) return;
                }
            }
        }
    }


    /*
    function getPath
    This function will find a path between start point and finish point.
    Return a list content the path information inside.
    If there is no path between two point then the list will be empty.

    這個函數會找到起點到終點間的一條路徑
    回傳一個 list 包含著路徑的資訊
    如果找不到路徑的話 list 就會是空的
    */
    List *getPath() {
        List *path = new List();
        DFS(0, 0, path);
        return path;
    }

    bool DFS(int r, int c, List *path) {
        // If out of bound
        if (r < 0 || c < 0 || r >= SIZE || c >= SIZE || maze[r][c] != 0)
            return false;

        // Mark as Visited
        maze[r][c] = 2;
        Node tmpNode(r, c);
        path->addElement(tmpNode.getRow(), tmpNode.getCol());

        // If destination is reached
        if (r == SIZE - 1 && c == SIZE - 1)
            return true;

        // Moving forward
        if (DFS(r + 1, c, path) || DFS(r, c + 1, path) || DFS(r - 1, c, path) || DFS(r, c - 1, path))
            return true;

        // If no path is found, remove the node from the path and mark cell as unvisited
        path->removeElement();
        maze[r][c] = 0;
        return false;
    }

    void printMaze() {
        int j, k;
//        int **temp[10];
//        temp = &maze;
        for (j = 0; j < SIZE; j++) {
            for (k = 0; k < SIZE; k++) {
                if (maze[j][k] == 0)
                    cout << "0";
                else if (maze[j][k] == 1)
                    cout << "*";
            }
            cout << "\n";
        }
    }

private:
    int **maze;
};

int main() {
    Maze *maze = new Maze();
    maze->printMaze();
    maze->getPath()->printList();
}
