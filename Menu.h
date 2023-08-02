#pragma once

void showScore(User* user) {
	ifstream file("LeaderBoard.txt");
	string username, score;
	vector <pair<string, string>> players;
	if (file.is_open()) {
		while (getline(file, username, ' ')) {
			getline(file, score);
			players.push_back({ username, score });
		}
		file.close();
	}
	for (auto& i : players) {
		setColor(14);
		if (i.first == user->getUsername()) cout << "Your score: " << i.second << endl;
	}
}

void checkQuizName(string quizname) {
	string quizname_from_file;
	ifstream file("quizNames.txt");
	if (file.is_open()) {
		while (getline(file, quizname_from_file)) {
			setColor(12);
			if (quizname_from_file == quizname) 
				throw exception("This quiz name already used!");
		}
	}
}

void createQuiz() {
	string filename, question, answer, correctAnswer;
	vector<string> answers;
	while (true) {
		system("cls");
		setColor(14);
		cout << "Enter quiz name" << endl;
		setColor(10);
		cin >> filename;
		try {
			for (auto& i : filename) {
				setColor(12);
				if (!(isdigit(i) || isalpha(i))) {
					throw exception("You cannot use other characters in quiz name!!!");
				}
			}
			filename += ".txt";
			checkQuizName(filename);
		}
		catch (const exception& ex) {
			system("cls");
			cout << ex.what() << endl;
			Sleep(2000);
			continue;
		}
		break;
	}

	for (size_t i = 0; i < 5; i++) {
		setColor(10);
		cout << "Add your " << i + 1 << ". question: " << endl;
		getline(cin >> ws, question);
		question.erase(remove(question.begin(), question.end(), '?'), question.end());
		cout << "Add four variant: " << endl;
		for (size_t i = 0; i < 4; i++) {
			cout << i + 1 << ". ";
			getline(cin >> ws, answer);
			answer.erase(remove(answer.begin(), answer.end(), ','), answer.end());
			answers.push_back(answer);
		}
		cout << "Correct answer: " << endl;
		getline(cin >> ws, correctAnswer);
		correctAnswer.erase(remove(correctAnswer.begin(), correctAnswer.end(), ','), correctAnswer.end());
		ofstream file(filename, ios::app);
		if (file.is_open()) {
			file << question << "?";
			for (auto& i : answers) {
				file << i << ", ";
			}
			file << correctAnswer << "\n";
			file.close();
		}
		answers.clear();
	}
	ofstream file_("quizNames.txt", ios::app);
	if (file_.is_open()) {
		file_ << filename << "\n";
		file_.close();
	}
}

void menu() {
	bool choice;
	while (true) {
		try {
			choice = loginOrSignChoice();
		}
		catch (const exception& ex) {
			cout << ex.what() << endl << endl;
			continue;
		}
		break;
	}
	char choice_;
	if (!choice) {
		while (true) {
			try {
				signIn();
			}
			catch (const exception& ex) {
				cout << endl << ex.what() << endl;
				Sleep(4000);
				continue;
			}
			break;
		}
	}
	// Admin
	User* user = logIn();
	if (checkAdminOrPlayer(user->getUsername(), user->getPassword())) {
		while (true) {
			system("cls");
			cin.ignore();
			setColor(10);
			cout << "1. Start Quiz" << endl;
			cout << "2. Leader Board" << endl;
			cout << "3. Create Quiz" << endl;
			cout << "4. Exit" << endl << endl;
			setColor(14);
			cout << "Enter your choice (1-4): ";
			setColor(10);
			cin >> choice_;
			if (choice_ == '1') startQuiz(user);
			else if (choice_ == '2') {
				system("cls");
				leaderBoard();
				Sleep(4000);
			}
			else if (choice_ == '3') createQuiz();
			else if (choice_ == '4') {
				setColor(12);
				cout << "\nExiting the game";
				Sleep(1000);
				cout << ".";
				Sleep(1000);
				cout << ".";
				Sleep(1000);
				cout << ".\n";
				Sleep(500);
				setColor(7);
				exit(0);
			}
			else {
				setColor(12);
				cout << ("\nInvalid choice!");
				Sleep(2000);
			}
		}
	}
	// User
	else {
		while (true) {
			system("cls");
			cin.ignore();
			setColor(10);
			cout << "1. Start Quiz" << endl;
			cout << "2. Leader Board" << endl;
			cout << "3. Show my score" << endl;
			cout << "4. Exit" << endl << endl;
			setColor(14);
			cout << "Enter your choice (1-4): ";
			setColor(10);
			cin >> choice_;
			if (choice_ == '1') startQuiz(user);
			else if (choice_ == '2') {
				system("cls");
				leaderBoard();
				Sleep(4000);
			}
			else if (choice_ == '3') {
				system("cls");
				showScore(user);
				Sleep(4000);
			}
			else if (choice_ == '4') {
				setColor(12);
				cout << "\nExiting the game";
				Sleep(1000);
				cout << ".";
				Sleep(1000);
				cout << ".";
				Sleep(1000);
				cout << ".\n";
				Sleep(500);
				setColor(7);
				exit(0);
			}
			else {
				setColor(12);
				cout << ("\nInvalid choice!");
				Sleep(2000);
			}
		}
	}
	delete user;
}