//#include<iostream>
//#include<stack>
//using namespace std;
///*
//��ȱ����Թ�·������   0���� 1������
//ÿ���ڵ���4������,�ж�˳��Ϊ �� �� �� ��
//
//1.����һ��0�ڵ���ջ,�ж���4�������Ƿ����
//2.������һ�������жϿ��ߺ�,Ϊ��ֹ�ظ�����,���������ڵ�֮���Ϊ������
//3.�ٽ����߷����0�ڵ���ջ,��Ϊջ��,�ж�����3�������Ƿ����
//4.���˽ڵ�4�����򶼲�����,���ջ
//5.��ʱջ��Ϊ��һ��0�ڵ�,������һ������·�Ŀ��߷��򱻵ڶ�����Ϊ������
//6.�����ж�һ�����߷���
//
//0 0 0 1 1 1
//1 1 0 0 0 1
//1 1 0 0 1 1
//1 1 0 0 0 1
//1 1 0 1 0 1
//1 1 0 0 0 0
//��ȱ������·�����������·��
//* * * 1 1 1
//1 1 * * 0 1
//1 1 0 * 1 1
//1 1 0 * * 1
//1 1 0 1 * 1
//1 1 0 0 * *
//*/
//
//// �����Թ�ÿһ���ڵ���ĸ�����
//const int RIGHT = 0;
//const int DOWN = 1;
//const int LEFT = 2;
//const int UP = 3;
//
//// �Թ�ÿһ���ڵ㷽�������
//const int WAY_NUM = 4;
//
//// ����ڵ�����״̬
//const int YES = 4;
//const int NO = 5;
//
//// �Թ�
//class Maze
//{
//public:
//	// ��ʼ���Թ��������û�����������������ɴ洢�Թ�·����Ϣ�Ķ�ά����
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
//	// ��ʼ���Թ�·���ڵ���Ϣ
//	void initNode(int x, int y, int val)
//	{
//		_pMaze[x][y]._x = x;
//		_pMaze[x][y]._y = y;
//		_pMaze[x][y]._val = val;
//		// �ڵ��ĸ�����Ĭ�ϵĳ�ʼ��,Ĭ�ϲ�����
//		for (int i = 0; i < WAY_NUM; ++i)
//		{
//			_pMaze[x][y]._state[i] = NO;
//		}
//	}
//
//	// ��ʼ���Թ�0�ڵ��ĸ����������״̬��Ϣ
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
//				//�����ж�ʱ,j�����������һ��,��Ȼj+1��Խ��
//				if (j < _col - 1 && _pMaze[i][j + 1]._val == 0)
//				{
//					_pMaze[i][j]._state[RIGHT] = YES;
//				}
//				//ͬ��,�����ж�ʱ,i���������һ��
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
//	// ��������Թ�·��
//	void searchMazePath()
//	{
//		//��һ���ڵ㲻Ϊ0,���Թ������
//		if (_pMaze[0][0]._val == 1)
//		{
//			return;
//		}
//		//����һ��0�ڵ���ջ
//		_stack.push(_pMaze[0][0]);
//		
//		while (!_stack.empty())
//		{
//			//ÿ���ж�ջ���ڵ�
//			Node top = _stack.top();
//			int x = top._x;
//			int y = top._y;
//
//			// �Ѿ��ҵ����½ǳ��ڵ��Թ�·��
//			if (x == _row - 1 && y == _col - 1)
//			{
//				return;
//			}
//
//			// ���ҷ���Ѱ��
//			if (_pMaze[x][y]._state[RIGHT] == YES)
//			{
//				//Ϊ�˷�ֹ�����ڵ�֮���ظ��ж�(����),������֮���Ϊ������
//				_pMaze[x][y]._state[RIGHT] = NO;
//				_pMaze[x][y + 1]._state[LEFT] = NO;
//				//���жϿ��߷���Ľڵ���ջ
//				_stack.push(_pMaze[x][y + 1]);
//				continue;
//			}
//
//			// ���·���Ѱ��
//			if (_pMaze[x][y]._state[DOWN] == YES)
//			{
//				_pMaze[x][y]._state[DOWN] = NO;
//				_pMaze[x + 1][y]._state[UP] = NO;
//				_stack.push(_pMaze[x + 1][y]);
//				continue;
//			}
//
//			// ������Ѱ��
//			if (_pMaze[x][y]._state[LEFT] == YES)
//			{
//				_pMaze[x][y]._state[LEFT] = NO;
//				_pMaze[x][y - 1]._state[RIGHT] = NO;
//				_stack.push(_pMaze[x][y - 1]);
//				continue;
//			}
//
//			// ���Ϸ���Ѱ��
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
//	// ��ӡ�Թ�·���������
//	void showMazePath()
//	{
//		//��ʱջ�ڵĽڵ�����Թ�·��
//		if (_stack.empty())
//		{
//			cout << "������һ���Թ�·����" << endl;
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
//	// �����Թ��ڵ�·����Ϣ
//	struct Node
//	{
//		int _x;
//		int _y;
//		int _val; // �ڵ��ֵ
//		int _state[WAY_NUM]; // ��¼�ڵ��ĸ������״̬
//	};
//
//	Node** _pMaze; // ��̬�����Թ�·��
//	int _row;
//	int _col;
//	stack<Node> _stack; // ջ�ṹ��������������Թ�·��
//};
//
//int main()
//{
//	cout << "�������Թ���������(���磺10 10):";
//	int row, col, data;
//	cin >> row >> col;
//
//	Maze maze(row, col); // �����Թ�����
//
//	cout << "�������Թ���·����Ϣ(0��ʾ�����ߣ�1��ʾ������):" << endl;
//	for (int i = 0; i < row; ++i)
//	{
//		for (int j = 0; j < col; ++j)
//		{
//			cin >> data;
//			// ���Գ�ʼ���Թ��ڵ�Ļ�����Ϣ
//			maze.initNode(i, j, data);
//		}
//	}
//
//	// ��ʼ�������нڵ���ĸ������״̬
//	maze.setNodeState();
//
//	// ��ʼ�����Ͻ������Թ���·����Ϣ��
//	maze.searchMazePath();
//
//	cout << "--------------" << endl;
//
//	// ��ӡ�Թ�·�������Ľ��
//	maze.showMazePath();
//
//	return 0;
//}