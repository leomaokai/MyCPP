#include <iostream>
#include <stack>
using namespace std;
/*
深度遍历迷宫路径搜索   0可走 1不可走
每个节点有4个方向,判断顺序为 右 下 左 上

1.将第一个0节点入栈,判断其4个方向是否可走
2.当其中一个方向判断可走后,为防止重复行走,将这两个节点之间改为不可走
3.再将可走方向的0节点入栈,成为栈顶,判断其它3个方向是否可走
4.若此节点4个方向都不可走,则出栈
5.此时栈顶为上一个0节点,并且有一个会死路的可走方向被第二步改为不可走
6.重新判断一个可走方向

0 0 0 1 1 1
1 1 0 0 0 1
1 1 0 0 1 1
1 1 0 0 0 1
1 1 0 1 0 1
1 1 0 0 0 0
深度遍历结果路径不会是最佳路径
* * * 1 1 1
1 1 * * 0 1
1 1 0 * 1 1
1 1 0 * * 1
1 1 0 1 * 1
1 1 0 0 * *
*/

// 定义迷宫每一个节点的四个方向
const int right = 0;
const int down = 1;
const int left = 2;
const int up = 3;

// 迷宫每一个节点方向的数量
const int way_num = 4;

// 定义节点行走状态
const int yes = 4;
const int no = 5;

// 迷宫
class maze
{
public:
	// 初始化迷宫，根据用户输入的行列数，生成存储迷宫路径信息的二维数组
	maze(int row, int col)
		: _row(row), _col(col)
	{
		_pmaze = new node *[_row];
		for (int i = 0; i < _row; ++i)
		{
			_pmaze[i] = new node[_col];
		}
	}

	// 初始化迷宫路径节点信息
	void initnode(int x, int y, int val)
	{
		_pmaze[x][y]._x = x;
		_pmaze[x][y]._y = y;
		_pmaze[x][y]._val = val;
		// 节点四个方向默认的初始化,默认不可走
		for (int i = 0; i < way_num; ++i)
		{
			_pmaze[x][y]._state[i] = no;
		}
	}

	// 初始化迷宫0节点四个方向的行走状态信息
	void setnodestate()
	{
		for (int i = 0; i < _row; ++i)
		{
			for (int j = 0; j < _col; ++j)
			{
				if (_pmaze[i][j]._val == 1)
				{
					continue;
				}
				//向右判断时,j不可以是最后一列,不然j+1会越界
				if (j < _col - 1 && _pmaze[i][j + 1]._val == 0)
				{
					_pmaze[i][j]._state[right] = yes;
				}
				//同理,向下判断时,i不能是最后一行
				if (i < _row - 1 && _pmaze[i + 1][j]._val == 0)
				{
					_pmaze[i][j]._state[down] = yes;
				}

				if (j > 0 && _pmaze[i][j - 1]._val == 0)
				{
					_pmaze[i][j]._state[left] = yes;
				}

				if (i > 0 && _pmaze[i - 1][j]._val == 0)
				{
					_pmaze[i][j]._state[up] = yes;
				}
			}
		}
	}

	// 深度搜索迷宫路径
	void searchmazepath()
	{
		//第一个节点不为0,则迷宫无入口
		if (_pmaze[0][0]._val == 1)
		{
			return;
		}
		//将第一个0节点入栈
		_stack.push(_pmaze[0][0]);

		while (!_stack.empty())
		{
			//每次判断栈顶节点
			node top = _stack.top();
			int x = top._x;
			int y = top._y;

			// 已经找到右下角出口得迷宫路径
			if (x == _row - 1 && y == _col - 1)
			{
				return;
			}

			// 往右方向寻找
			if (_pmaze[x][y]._state[right] == yes)
			{
				//为了防止两个节点之间重复判断(行走),将它们之间改为不可走
				_pmaze[x][y]._state[right] = no;
				_pmaze[x][y + 1]._state[left] = no;
				//将判断可走方向的节点入栈
				_stack.push(_pmaze[x][y + 1]);
				continue;
			}

			// 往下方向寻找
			if (_pmaze[x][y]._state[down] == yes)
			{
				_pmaze[x][y]._state[down] = no;
				_pmaze[x + 1][y]._state[up] = no;
				_stack.push(_pmaze[x + 1][y]);
				continue;
			}

			// 往左方向寻找
			if (_pmaze[x][y]._state[left] == yes)
			{
				_pmaze[x][y]._state[left] = no;
				_pmaze[x][y - 1]._state[right] = no;
				_stack.push(_pmaze[x][y - 1]);
				continue;
			}

			// 往上方向寻找
			if (_pmaze[x][y]._state[up] == yes)
			{
				_pmaze[x][y]._state[up] = no;
				_pmaze[x - 1][y]._state[down] = no;
				_stack.push(_pmaze[x - 1][y]);
				continue;
			}

			_stack.pop();
		}
	}

	// 打印迷宫路径搜索结果
	void showmazepath()
	{
		//此时栈内的节点就是迷宫路径
		if (_stack.empty())
		{
			cout << "不存在一条迷宫路径！" << endl;
		}
		else
		{
			while (!_stack.empty())
			{
				node top = _stack.top();
				_pmaze[top._x][top._y]._val = '*';
				_stack.pop();
			}

			for (int i = 0; i < _row; ++i)
			{
				for (int j = 0; j < _col; ++j)
				{
					if (_pmaze[i][j]._val == '*')
					{
						cout << "* ";
					}
					else
					{
						cout << _pmaze[i][j]._val << " ";
					}
				}
				cout << endl;
			}
		}
	}

private:
	// 定义迷宫节点路径信息
	struct node
	{
		int _x;
		int _y;
		int _val;			 // 节点的值
		int _state[way_num]; // 记录节点四个方向的状态
	};

	node **_pmaze; // 动态生成迷宫路径
	int _row;
	int _col;
	stack<node> _stack; // 栈结构，辅助深度搜索迷宫路径
};

int main()
{
	cout << "请输入迷宫的行列数(例如：10 10):";
	int row, col, data;
	cin >> row >> col;

	maze maze(row, col); // 创建迷宫对象

	cout << "请输入迷宫的路径信息(0表示可以走，1表示不能走):" << endl;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			cin >> data;
			// 可以初始化迷宫节点的基本信息
			maze.initnode(i, j, data);
		}
	}

	// 开始设置所有节点的四个方向的状态
	maze.setnodestate();

	// 开始从左上角搜索迷宫的路径信息了
	maze.searchmazepath();

	cout << "--------------" << endl;

	// 打印迷宫路径搜索的结果
	maze.showmazepath();

	return 0;
}