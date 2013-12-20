#include <iostream>

int moves_num[10] = {2,2,2,2,3,0,3,2,2,2}; // число возможных ходов
int knight_moves[10][3] = {{4,6},{6,8},{7,9},{4,8},{0,3,9},{},{1,7,0},{2,6},{1,3},{2,4}}; // возможные ходы коня 

long long int **possible_moves; /* таблица количества возможных номеров possible_moves[n][m] 
                                   где n - число цифр в номере, m - начиная с 
                                    какой цифры начинаем ходить конем */
void count(int digits)
{
    for(int i=2;i<=digits;i++) {
        for(int j = 0; j < 10; j++) { // перебираем все цифры телефона
            for(int k = 0; k < moves_num[j]; k++) { // перебираем все ходы коня
            possible_moves[i][j] += possible_moves[i-1][knight_moves[j][k]];
            }
        }
    }
}

void allocateTable(int num) {
    possible_moves = new long long int*[num+1];
    for(int i=0;i<num+1;i++) {
        possible_moves[i] = new long long int[10];
    } 
}

int main()
{
    int num;
    std::cin >> num;
    allocateTable(num);
    for(int i = 0; i < 10; i++) 
        possible_moves[1][i] = 1; /* очевидно, если номер состоит из одной цифры, 
                                    то есть только 1 вариант набора ( это будет i-я цифра )
                                    это и есть база динамики */
    long long int answer=0;
    count(num);
    for(int i=1;i<10;i++) { 
        if(i!=8) // номер не начинается с 8 
        answer += possible_moves[num][i];
    }
    std::cout << answer;
}
