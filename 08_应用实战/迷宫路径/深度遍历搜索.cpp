//#include<iostream>
//#include<stack>
//using namespace std;
///*
//深度遍历迷宫路径搜索   0可走 1不可走
//每个节点有4个方向,判断顺序为 右 下 左 上
//
//1.将第一个0节点入栈,判断其4个方向是否可走
//2.当其中一个方向判断可走后,为防止重复行走,将这两个节点之间改为不可走
//3.再将可走方向的0节点入栈,成为栈顶,判断其它3个方向是否可走
//4.若此节点4个方向都不可走,则出栈
//5.此时栈顶为上一个0节点,并且有一个会死路的可走方向被第二步改为不可走
//6.重新判断一个可走方向
//
//0 0 0 1 1 1
//1 1 0 0 0 1
//1 1 0 0 1 1
//1 1 0 0 0 1
//1 1 0 1 0 1
//1 1 0 0 0 0
//深度遍历结果路径不会是最佳路径
//* * * 1 1 1
//1 1 * * 0 1
//1 1 0 * 1 1
//1 1 0 * * 1
//1 1 0 1 * 1
//1 1 0 0 * *
//*/
//
//// 定义迷宫每一个节点的四个方向
//const int RIGHT = 0;
//const int DOWN = 1;
//const int LEFT = 2;
//const int UP = 3;
//
//// 迷宫每一个节点方向的数量
//const int WAY_NUM = 4;
//
//// 定义节点行走状态
//const int YES = 4;
//const int NO = 5;
//
//// 迷宫
//class Maze
//{
//public:
//	// 初始化迷宫，根据用户输入的行列数，生成存储迷宫路径信息的二维数组
//	Maze(int row, int col)
//		:_row(row)
//		, _col(col)
//	{
//			_pMaze = new Node * [_row];
//		for (int i = 0; i < _row; ++i)
//		{
//			_pMaze[i] = new Node[_col];
//		}
//	}
//
//	// 初始化迷宫路径节点信息
//	void initNode(int x, int y, int val)
//	{
//		_pMaze[x][y]._x = x;
//		_pMaze[x][y]._y = y;
//		_pMaze[x][y]._val = val;
//		// 节点四个方向默认的初始化,默认不可走
//		for (int i = 0; i < WAY_NUM; ++i)
//		{
//			_pMaze[x][y]._state[i] = NO;
//		}
//	}
//
//	// 初始化迷宫0节点四个方向的行走状态信息
//	void setNodeState()
//	{
//		for (int i = 0; i < _row; ++i)
//		{
//			for (int j = 0; j < _col; ++j)
//			{
//				if (_pMaze[i][j]._val == 1)
//				{
//					continue;
//				}
//				//向右判断时,j不可以是最后一列,不然j+1会越界
//				if (j < _col - 1 && _pMaze[i][j + 1]._val == 0)
//				{
//					_pMaze[i][j]._state[RIGHT] = YES;
//				}
//				//同理,向下判断时,i不能是最后一行
//				if (i < _row - 1 && _pMaze[i + 1][j]._val == 0)
//				{
//					_pMaze[i][j]._state[DOWN] = YES;
//				}
//
//				if (j > 0 && _pMaze[i][j - 1]._val == 0)
//				{
//					_pMaze[i][j]._state[LEFT] = YES;
//				}
//
//				if (i > 0 && _pMaze[i - 1][j]._val == 0)
//				{
//					_pMaze[i][j]._state[UP] = YES;
//				}
//			}
//		}
//	}
//
//	// 深度搜索迷宫路径
//	void searchMazePath()
//	{
//		//第一个节点不为0,则迷宫无入口
//		if (_pMaze[0][0]._val == 1)
//		{
//			return;
//		}
//		//将第一个0节点入栈
//		_stack.push(_pMaze[0][0]);
//		
//		while (!_stack.empty())
//		{
//			//每次判断栈顶节点
//			Node top = _stack.top();
//			int x = top._x;
//			int y = top._y;
//
//			// 已经找到右下角出口得迷宫路径
//			if (x == _row - 1 && y == _col - 1)
//			{
//				return;
//			}
//
//			// 往右方向寻找
//			if (_pMaze[x][y]._state[RIGHT] == YES)
//			{
//				//为了防止两个节点之间重复判断(行走),将它们之间改为不可走
//				_pMaze[x][y]._state[RIGHT] = NO;
//				_pMaze[x][y + 1]._state[LEFT] = NO;
//				//将判断可走方向的节点入栈
//				_stack.push(_pMaze[x][y + 1]);
//				continue;
//			}
//
//			// 往下方向寻找
//			if (_pMaze[x][y]._state[DOWN] == YES)
//			{
//				_pMaze[x][y]._state[DOWN] = NO;
//				_pMaze[x + 1][y]._state[UP] = NO;
//				_stack.push(_pMaze[x + 1][y]);
//				continue;
//			}
//
//			// 往左方向寻找
//			if (_pMaze[x][y]._state[LEFT] == YES)
//			{
//				_pMaze[x][y]._state[LEFT] = NO;
//				_pMaze[x][y - 1]._state[RIGHT] = NO;
//				_stack.push(_pMaze[x][y - 1]);
//				continue;
//			}
//
//			// 往上方向寻找
//			if (_pMaze[x][y]._state[UP] == YES)
//			{
//				_pMaze[x][y]._state[UP] = NO;
//				_pMaze[x - 1][y]._state[DOWN] = NO;
//				_stack.push(_pMaze[x - 1][y]);
//				continue;
//			}
//
//			_stack.pop();
//		}
//	}
//
//	// 打印迷宫路径搜索结果
//	void showMazePath()
//	{
//		//此时栈内的节点就是迷宫路径
//		if (_stack.empty())
//		{
//			cout << "不存在一条迷宫路径！" << endl;
//		}
//		else
//		{
//			while (!_stack.empty())
//			{
//				Node top = _stack.top();
//				_pMaze[top._x][top._y]._val = '*';
//				_stack.pop();
//			}
//
//			for (int i = 0; i < _row; ++i)
//			{
//				for (int j = 0; j < _col; ++j)
//				{
//					if (_pMaze[i][j]._val == '*')
//					{
//						cout << "* ";
//					}
//					else
//					{
//						cout << _pMaze[i][j]._val << " ";
//					}
//				}
//				cout << endl;
//			}
//		}
//	}
//private:
//	// 定义迷宫节点路径信息
//	struct Node
//	{
//		int _x;
//		int _y;
//		int _val; // 节点的值
//		int _state[WAY_NUM]; // 记录节点四个方向的状态
//	};
//
//	Node** _pMaze; // 动态生成迷宫路径
//	int _row;
//	int _col;
//	stack<Node> _stack; // 栈结构，辅助深度搜索迷宫路径
//};
//
//int main()
//{
//	cout << "请输入迷宫的行列数(例如：10 10):";
//	int row, col, data;
//	cin >> row >> col;
//
//	Maze maze(row, col); // 创建迷宫对象
//
//	cout << "请输入迷宫的路径信息(0表示可以走，1表示不能走):" << endl;
//	for (int i = 0; i < row; ++i)
//	{
//		for (int j = 0; j < col; ++j)
//		{
//			cin >> data;
//			// 可以初始化迷宫节点的基本信息
//			maze.initNode(i, j, data);
//		}
//	}
//
//	// 开始设置所有节点的四个方向的状态
//	maze.setNodeState();
//
//	// 开始从左上角搜索迷宫的路径信息了
//	maze.searchMazePath();
//
//	cout << "--------------" << endl;
//
//	// 打印迷宫路径搜索的结果
//	maze.showMazePath();
//
//	return 0;
//}