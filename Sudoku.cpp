/*
mp记录数独格局[1][1]-[9][9]，求解成功是记录答案
标志数组r[i][j],c[i][j],b[i][j]分别表示第i行,第i列,第i块,中j已经用过
isPrint表示bfs搜到结果是是否输出，1表示输出,0,表示不输出，默认输出


初始化可直接初始化，也可用一个第一维为10的数组初始化
setMap()表示用一个二维数组设置棋局
changeValue()表示将mp[x][y]设置成v
getMapFromFile()表示从路径p中的文件读出格局
printMap()打印格局
check()检查mp[x][y]是否可放i,可放返回1，否则返回0
changeStatus()因为mp[x][y] = i,所以将有关的标志数组进行赋值0或者1
init()将一个读到的新格局的标志数组进行初始化
dfs()暴搜求答案，有解返回1并输出结果，无解返回0;
solve()求解结果
hasAnswer()是否可解，可借返回1，否则返回0
zero()将标志数组全部置0
setisPrint()设置搜索到结果时是否输出结果，设置成0不输出结果，否则输出结果，默认输出结果
*/
#include<bits/stdc++.h>
using namespace std;
#define REP(x,l,r) for(int x = l; x <= r; x++)

class Sudoku
{
private:
    const int SIZE = 9;
    int mp[10][10];
    int r[10][10];
    int c[10][10];
    int b[10][10];
    int isPrint = 1;
    int cnt = 0;
public:
    Sudoku(){}
    Sudoku(int a[][10]);
    void setMap(int a[][10]);
    void changeValue(int x, int y, int v);
    void getMapFromFile(string p);
    void printMap();
    int check(int x, int y, int i);
    void changeStatus(int x, int y, int i, int v);
    void init();
    int dfs(int x, int y);
    void allAnswer(int x, int y);
    void solve();
    int hasAnswer();
    void zero();
    void setisPrint(int v = 1);
    int getCnt();
};
Sudoku::Sudoku(int a[][10])
{
    setMap(a);
}
void Sudoku::setMap(int a[][10])
{
    REP(i,1,SIZE)
        REP(j,1,SIZE)
            mp[i][j] = a[i][j];
}
void Sudoku::changeValue(int x, int y, int v)
{
    mp[x][y] = v;
}
void Sudoku::getMapFromFile(string p)
{
    freopen(p.c_str(),"r",stdin);
    for(int i = 1; i <= SIZE; i++)
        for(int j = 1; j <= SIZE; j++)
            scanf("%d",&mp[i][j]);
    fclose(stdin);
}
void Sudoku::printMap()
{
    for(int i = 1; i <= SIZE; i++)
    {
        for(int j = 1; j <= SIZE; j++)
        {
            printf("%d ",mp[i][j]);
            if(j % 3 == 0)
                printf("  ");
        }
        printf("\n");
        if(i % 3 == 0)
            printf("\n\n");
    }
}
int Sudoku::check(int x, int y,int i)
{
    int block = (x-1)/3*3 + (y-1)/3 + 1;
    if(!r[x][i] && !c[y][i] && !b[block][i])
        return 1;
    return 0;
}
void Sudoku::changeStatus(int x, int y, int i, int v)
{
    int block = (x-1)/3*3 + (y-1)/3 + 1;
    r[x][i] = v;
    c[y][i] = v;
    b[block][i] = v;
}
void Sudoku::init()
{
    zero();
    for(int i = 1; i <= SIZE; i++)
    {
        for(int j = 1; j <= SIZE; j++)
        {
            if(mp[i][j])
                changeStatus(i, j, mp[i][j], 1);
        }
    }
}
int Sudoku::dfs(int x, int y)
{
    if(y > SIZE)
        x ++, y = 1;
    if(x > SIZE)
    {
        if(isPrint)
            printMap();
        return 1;
    }
    if(mp[x][y])
    {
        if(dfs(x,y+1))
            return 1;
    }
    else
    {
        for(int i = 1; i <= SIZE; i++)
        {
            if(check(x, y, i))
            {
                changeStatus(x, y, i, 1);
                mp[x][y] = i;
                if(dfs(x, y+1))
                    return 1;
                changeStatus(x, y, i, 0);
                mp[x][y] = 0;
            }
        }
    }
    return 0;
}
void Sudoku::allAnswer(int x, int y)
{
    //printf("x = %d y =%d\n",x,y);
    if(y > SIZE)
        x ++, y = 1;
    if(x > SIZE)
    {
        if(isPrint)
            printMap();
        cnt++;
        return ;
    }
    if(mp[x][y])
        allAnswer(x,y+1);
    else
    {
        for(int i = 1; i <= SIZE; i++)
        {
            if(check(x, y, i))
            {
                changeStatus(x, y, i, 1);
                mp[x][y] = i;
                allAnswer(x, y+1);
                changeStatus(x, y, i, 0);
                mp[x][y] = 0;
            }
        }
    }
}
void Sudoku::solve()
{
    if(!hasAnswer() || !dfs(1, 1))
        printf("NO ANSWER!\n");
}
int Sudoku::hasAnswer()
{
    zero();
    REP(i,1,SIZE)
    {
        REP(j,1,SIZE)
        {
            if(mp[i][j])
            {
                int x = mp[i][j];
                int block = (i-1)/3*3 + (j-1)/3 + 1;
                if(r[i][x])
                    return 0;
                if(c[j][x])
                    return 0;
                if(b[block][x])
                    return 0;
                r[i][x] = 1;
                c[j][x] = 1;
                b[block][x] = 1;
            }
        }
    }
    return 1;
}
void Sudoku::zero()
{
    memset(r,0,sizeof r);
    memset(c,0,sizeof c);
    memset(b,0,sizeof b);
    cnt = 0;
}
void Sudoku::setisPrint(int v)
{
    isPrint = v;
}
int Sudoku::getCnt()
{
    return cnt;
}
int main()
{
    Sudoku s;
    s.getMapFromFile("shudu.txt");
    s.init();
//    s.setisPrint(0);
    s.solve();
}
