#include<iostream>
#include<vector>
#include<queue>
#include<string>

using namespace std;

int solution(vector<string> &plan) {
    const int X = plan.size();
    const int Y = plan[0].size();

    // std::vector<std::vector<bool>> visited(X, vector<bool>(Y, false)); //No need. Saves space complexity

    int result(0);
    std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for(size_t i(0) ; i < X; ++i)
        for(size_t j(0); j < Y; ++j)
            if(plan[i][j] == '*')
            {
                ++result;
                std::queue <std::pair<int,int>>  q;
                q.push({i,j});

                while (!q.empty()) {
                    int x = q.front().first;
                    int y = q.front().second;

                    q.pop();

                    for (const auto& dir : directions) {
                        int nx = x + dir.first;
                        int ny = y + dir.second;
                        if (nx >= 0 && ny >= 0 && nx < X && ny < Y && plan[nx][ny]!= '_' && (plan[nx][ny] == '*' || plan[nx][ny] == '.') ) {
                            plan[nx][ny] = '_';
                            q.push({nx, ny});
                        }
                    }
                }
            }
    return result;
}

int main()
{

    vector<string> vec = {".*#..*",
                          ".*#*.#",
                          "######",
                          ".*..#.",
                          "...###"};

    cout << solution(vec) << endl;

     vec = {"*#..",
            "#..#",
            ".##.",
            "...*"};
    cout << solution(vec) << endl;

    vec = {"**###**",
           "*#*#*#*",
           "##*#*##",
           "*#***#*",
           ".#####.",
           "..*#*.."};
    cout << solution(vec) << endl;
    vec = {"#####",
           "#***#",
           "#.###",
           "#.#*#",
           "#####"};
    ;
    cout << solution(vec) << endl;

    return 0;
}