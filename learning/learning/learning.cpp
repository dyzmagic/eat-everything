#include <iostream>
#include <ctime>
#include <conio.h>
#include <string>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <fstream>
using namespace std;
const char level_1[] = "level_1.txt";
const char level_2[] = "level_2.txt";
const char level_3[] = "level_3.txt";
const char level_4[] = "level_4.txt";
const char level_5[] = "level_5.txt";
const char temp[] = "template.txt";


/* You can make your own level using "template.txt" by template, to make the template change the parameters and run the program */
const int width = 26;//		26	MAX
const int length = 81;//	81	MAX


const char barrier = '#';
const char air = ' ';

char place[width][length];
char player_sym;
int level_num = 0;
int level_points[5];
int points = 0;
int all_points = 0;
int cols, rows;
enum moving { UP, LEFT, DOWN, RIGHT };

void draw();
void movem(moving go);

void replace()
{
	ifstream level1(level_1);
	ofstream template_level(temp);

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			level1 >> place[i][j];
			template_level << ".";
			if (place[i][j] == '.')
				place[i][j] = air;
		}
		template_level << endl;
	}
	
	
	template_level.close();
	level1.close();
}

int nextlevel(int level_num)
{
	ifstream level2(level_2);
	ifstream level3(level_3);
	ifstream level4(level_4);
	ifstream level5(level_5);


	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {

			if (level_num == 1)
				level2 >> place[i][j];

			if (level_num == 2)
				level3 >> place[i][j];

			if (level_num == 3)
				level4 >> place[i][j];

			if (level_num == 4)
				level5 >> place[i][j];

			if (place[i][j] == '.') place[i][j] = air;
		}
	}

	srand(static_cast<unsigned int>(time(nullptr)));
	cols = rand() % width;
	rows = rand() % length;
	while (place[cols][rows] != air)
	{
		cols = rand() % width;
		rows = rand() % length;
	}
	place[cols][rows] = player_sym;

	level2.close();
	level3.close();
	level4.close();
	level5.close();
	return 0;
}

void count_objects()
{
	ifstream read_l1(level_1);
	ifstream read_l2(level_2);
	ifstream read_l3(level_3);
	ifstream read_l4(level_4);
	ifstream read_l5(level_5);

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			
			read_l1 >> place[i][j];
			if (place[i][j] != air && place[i][j] != barrier && place[i][j] != '.')
				level_points[0]++;

			read_l2 >> place[i][j];
				if (place[i][j] != air && place[i][j] != barrier && place[i][j] != '.')
				level_points[1]++;

			read_l3 >> place[i][j];
				if (place[i][j] != air && place[i][j] != barrier && place[i][j] != '.')
					level_points[2]++;

			read_l4 >> place[i][j];
				if (place[i][j] != air && place[i][j] != barrier && place[i][j] != '.')
					level_points[3]++;

			read_l5 >> place[i][j];
				if (place[i][j] != air && place[i][j] != barrier && place[i][j] != '.')
					level_points[4]++;

		}
	}

	all_points = level_points[0] + level_points[1] + level_points[2] + level_points[3] + level_points[4];
	read_l1.close();
	read_l2.close();
	read_l3.close();
	read_l4.close();
	read_l5.close();
}

void text_EatEverthing()
{
	cout << " _____      _                               _   _     _             \n"
		"| ____|__ _| |_    _____   _____ _ __ _   _| |_| |__ (_)_ __   __ _ \n"
		"|  _| / _` | __|  / _ \\ \\ / / _ \\ '__| | | | __| '_ \\| | '_ \\ / _` |\n"
		"| |__| (_| | |_  |  __/\\ V /  __/ |  | |_| | |_| | | | | | | | (_| |\n"
		"|_____\\__,_|\\__|  \\___| \\_/ \\___|_|   \\__, |\\__|_| |_|_|_| |_|\\__, |\n"
		"                                      |___/                   |___/ " << endl;
}

void end()
{
	system("cls");

	text_EatEverthing();

	cout << endl << "Thanks for playing!" << endl;
	cout << "All collected points: " << all_points << endl;
	cout << endl <<"-----------------------------------------------------------------------------------------------------------------" << endl;
	cout << endl<<endl <<   "__   __            _                _     _   _                                       _ \n"
							"\\ \\ / /__  _   _  | |__   ___  __ _| |_  | |_| |__   ___    __ _  __ _ _ __ ___   ___| |\n"
							" \\ V / _ \\| | | | | '_ \\ / _ \\/ _` | __| | __| '_ \\ / _ \\  / _` |/ _` | '_ ` _ \\ / _ \\ |\n"
							"  | | (_) | |_| | | |_) |  __/ (_| | |_  | |_| | | |  __/ | (_| | (_| | | | | | |  __/_|\n"
							"  |_|\\___/ \\__,_| |_.__/ \\___|\\__,_|\\__|  \\__|_| |_|\\___|  \\__, |\\__,_|_| |_| |_|\\___(_)\n"
							"                                                           |___/                        " << endl;
	cout << "- Made by: Rafal Suckel\nIn 3 days" << endl;
}

int main()
{
	bool thread = 1;
	count_objects();
	replace();

	text_EatEverthing();
	cout << "  Controls | Meaning \n"
			" ----------|--------- \n"
			"  W S D A  | Walk    \n"
			"  Enter    | Leave   \n" << endl;
	cout << "Enter player symbol ... ";	
	cin >> player_sym;

	srand(static_cast<unsigned int>(time(nullptr)));
	cols = rand() % width;
	rows = rand() % length;
	while (place[cols][rows] != air)
	{
		cols = rand() % width;
		rows = rand() % length;
	}

	place[cols][rows] = player_sym;

	draw();
	while (thread)
	{
		if (level_num == 5) {
			end();
			break;
		}
		if (level_points[level_num] != points)
			{
			int keyPressed = _getch();// Check if the 'W' key is pressed

			switch (keyPressed)
			{
			case 'w': movem(moving::UP);
				break;
			case 'a': movem(moving::LEFT);
				break;
			case 's': movem(moving::DOWN);
				break;
			case 'd': movem(moving::RIGHT);
				break;
			case '\r': system("cls");
				cout << "You left the game!" << endl;
				thread = false;
				break;
			default: cout << "[ERROR] You did not press the correct key" << endl;
				break;
			}
		}
		else
		{
			level_num++;
			nextlevel(level_num);
			points = 0;
			draw();
		}
	}
	this_thread::sleep_for(std::chrono::milliseconds(100));
}

void movem(moving go)
{
	bool num = false;
	if (go == moving::UP)
	{
		if (place[cols - 1][rows] != barrier && cols > 0) {
			if (place[cols - 1][rows] != barrier && place[cols - 1][rows] != air)
				points++;
			place[cols][rows] = air;
			place[--cols][rows] = player_sym;
			draw();
		}
	}
	if (go == moving::DOWN)
	{
		if (place[cols + 1][rows] != barrier && cols + 1 < width) {
			if (place[cols + 1][rows] != barrier && place[cols + 1][rows] != air)
				points++;
			place[cols][rows] = air;
			place[++cols][rows] = player_sym;
			draw();
		}
	}
	if (go == moving::LEFT)
	{
		if (place[cols][rows - 1] != barrier && rows > 0) {
			if (place[cols][rows - 1] != barrier && place[cols][rows - 1] != air)
				points++;
			place[cols][rows] = air;
			place[cols][--rows] = player_sym;
			draw();
		}
	}
	if (go == moving::RIGHT)
	{
		if (place[cols][rows + 1] != barrier && rows+1 < length) {
			if (place[cols][rows + 1] != barrier && place[cols][rows + 1] != air)
				points++;
			place[cols][rows] = air;
			place[cols][++rows] = player_sym;
			draw();
		}
	}
}

void draw()
{
	bool num = false;

	system("cls");
	cout << endl;

	if (length > 9) cout << "\t  ";
	else cout << "\t ";
	for (size_t i = 0; i < length + 2; i++)
	{
		cout << barrier;
	}
	cout << "\ty: " << cols << endl;

	for (int i = 0; i < width; i++)
	{
		if (length > 9)
		{
			if (i < 10)
				cout << "\t " << i << barrier;
			else
				cout <<"\t" << i << barrier;
		}
		else cout << i << barrier;
		for (int j = 0; j < length; j++)
		{
			
			cout << place[i][j];
		}
		cout << barrier;
		if (i == 0) cout << "\tx: " << rows << endl;
		else if (i == 1) cout << "\tpoints: " << points << "/" << level_points[level_num] << endl;
		else if (i == 2) cout << "\tlevel: " << level_num + 1 << endl;
		else cout << endl;
	}

	if (length > 9) cout << "\t  ";
	else cout << "\t ";
	for (size_t i = 0; i < length+2; i++)
	{
		cout << barrier;
	}
	cout << endl;
}