# Sudoku
A simple toy
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
