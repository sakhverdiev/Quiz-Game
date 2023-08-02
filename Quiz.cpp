#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <conio.h>
#include <windows.h>
#include <thread>

using namespace std;

void setColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

#include"Users.h"
#include"Login.h"
#include"LeaderBoard.h"
#include"Quiz.h"
#include"Menu.h"

int main() {
	// Admin login-i: admin admin123
	// Her quiz-de 5 sual var, her sual 5 bal verir. Suallar ve cavablar randomdur.
	menu();
}