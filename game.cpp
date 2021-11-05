#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <thread>

using namespace std;

#define KEY_UP 72
#define KEY_RIGHT 77
#define KEY_DOWN 80
#define KEY_LEFT 75

int key = KEY_RIGHT;
int lost = 0;


class SnakePoint
{
public:

	int x = 0;
	int y = 0;
	int oldx = 0;
	int oldy = 0;
	bool isHead;

	SnakePoint(int column, int row, bool ishead = false)
	{
		x = oldx = row;
		y = oldy = column;
		isHead = ishead;
	};

	void Move(int side, vector<SnakePoint> snake, SnakePoint* i = nullptr)
	{
		if (isHead)
		{
			switch (side)
			{
			case KEY_UP:
				y--;
				if (y == -1)
					lost = 2;
				break;
			case KEY_RIGHT:
				x++;
				if (x == 25)
					lost = 2;
				break;
			case KEY_DOWN:
				y++;
				if (y == 22)
					lost = 2;
				break;
			case KEY_LEFT:
				x--;
				if (x == -1)
					lost = 2;
				break;
			}
			if (find(snake.begin(), snake.end(), SnakePoint(y, x)) != snake.end())
				lost = 1;
		}
		else
		{
			x = i->oldx;
			y = i->oldy;
			i->oldx = i->x;
			i->oldy = i->y;
		}
	}

	bool operator==(const SnakePoint& s)
	{
		return (x == s.x && y == s.y);
	}
};

void PrintGame(const int map[2], vector<SnakePoint> snake, int food[2])
{
	for (int column = 0; column < map[0]; column++)
	{
		for (int row = 0; row < map[1]; row++)
		{
			auto pnt = find(snake.begin(), snake.end(), SnakePoint(column, row));
			if (pnt != snake.end())
			{
				if (pnt._Ptr->isHead)
					cout << "O ";
				else
					cout << "* ";
			}
			else if (column == food[0] && row == food[1])
				cout << "o ";
			else
				cout << ". ";
		}
		cout << endl;
	}
}

void Game()
{
	srand(time(0));
	const int map[] = { 22, 25 };
	vector<SnakePoint> snake{ SnakePoint(11, 11, true), SnakePoint(11, 10), SnakePoint(11, 9) };
	int food[2] = { rand() % map[0] , rand() % map[1] };
	PrintGame(map, snake, food);
	cout << "Starting in ";

	for (int i = 1; i <= 3; i++)
	{
		cout << i << " ";
		Sleep(1000);
	}

	do
	{
		system("cls");
		for (int i = 0, k = 1; i < snake.size(); i++)
		{
			snake[i].Move(key, snake, &snake[k - 1]);
			if (snake[i].x == food[1] && snake[i].y == food[0])
			{
				food[0] = rand() % map[0];
				food[1] = rand() % map[1];
				snake.push_back(SnakePoint(-1, -1));
			}
			if (i > 0)
				k++;
		}
		PrintGame(map, snake, food);
		Sleep(50);
		cout << "Size: " << snake.size() - 1 << endl;
	} while (lost == 0 || snake.size() < map[0] * map[1]);

	if (lost == 1)
		cout << "You bite yourself!" << endl;
	else if (lost == 2)
		cout << "You fell into the void!" << endl;
	if (snake.size() >= map[0] * map[1])
	{
		cout << "You win!" << endl;
		lost = 4;
	}
		

	cout << "Press R to restart the game..." << endl;
}

int main(int argc, char* argv[])
{

	thread t(Game);

	while (key = _getch())
	{
		if (lost > 0 && key == 114)
		{
			system("cls");
			key = KEY_RIGHT;
			t.detach();
			lost = 0;
			break;
		}
	}
	main(0, NULL);

	system("pause");
	return 0;
}

