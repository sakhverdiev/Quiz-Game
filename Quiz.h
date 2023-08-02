#pragma once

bool quizCheck(User* user, string quiz_name) {
	pair<string, string> quiz;
	quiz.first = user->getUsername();
	quiz.second = quiz_name;
	string username, quizName;
	ifstream file("playedQuizes.txt");
	if (file.is_open()) {
		while (getline(file, username, ':')) {
			while (getline(file, quizName, ',') && quizName != "#") {
				if (quiz.first == username && quiz.second == quizName) return false;
			}
		}
		file.close();
	}
	return true;
}

string quizChoice(User* user) {
	system("cls");
	string choice, quizName; {
		ifstream quizes("quizNames.txt");
		if (quizes.is_open()) {
			while (getline(quizes, quizName, '.')) {
				cout << quizName << endl;
				getline(quizes, quizName);
			}
		}
	}
	while (true) {
		while (true) {
			setColor(14);
			cout << "Enter quiz name: ";
			setColor(10);
			cin >> choice;
			choice += ".txt";
			try {
				setColor(12);
				if (!quizCheck(user, choice)) throw exception("You already played this Quiz!");
			}
			catch (const exception& ex) {
				cout << ex.what() << endl;
				continue;
			}
			break;
		}
		ifstream quizes("quizNames.txt");
		if (quizes.is_open()) {
			while (getline(quizes, quizName)) {
				if (choice == quizName) return choice;
			}
			quizes.close();
			setColor(12);
			cout << "Invalid Quiz Name!" << endl;
		}
	}
}

void addQuizToUser(User* user, string quiz) {
	vector<string> quizes;
	map<string, vector<string>> playedQuizes;
	string username, quizName;
	ifstream file("playedQuizes.txt");
	if (file.is_open()) {
		while (getline(file, username, ':')) {
			quizes.clear();
			while (getline(file, quizName, ',') && quizName != "") {
				quizes.push_back(quizName);
			}
			getline(file, quizName);
			if (user->getUsername() == username) quizes.push_back(quiz);
			playedQuizes.insert({ username, quizes });
		}
		file.close();
	}
	try {
		ofstream file_("playedQuizes.txt");
		if (file_.is_open()) {
			for (auto& i : playedQuizes) {
				file_ << i.first << ":";
				for (auto& j : i.second) {
					file_ << j << ",";
				}file_ << ",#\n";
			}
			file_.close();
		}
	}
	catch (const exception& ex) {
		cout << ex.what() << endl;
	}
}

void fillVariants(vector<string>& variants) {
	for (size_t i = 0; i < 5; i++) {
		variants.push_back(" ");
	}
}

void startQuiz(User* user) {
	user->setScore(0);

	string choice, quizName;
	string question, answer, correct;
	vector<string> answers;
	vector<pair<string, pair<string, vector<string>>>> questions;
	quizName = quizChoice(user);
	char variant;
	char correctVariant;
	vector<string>variants;
	vector<string> correctVars;
	fillVariants(variants);

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();    // suallari qarisdirir
	default_random_engine e(seed);

	ifstream quizFile(quizName);
	if (quizFile.is_open()) {
		while (getline(quizFile, question, '?')) {
			answers.clear();
			for (int i = 0; i < 4; i++) {
				getline(quizFile, answer, ',');
				answers.push_back(answer);
			}
			getline(quizFile, correct);
			shuffle(answers.begin(), answers.end(), e);
			questions.push_back({ question,{correct, answers} });
		}
		quizFile.close();
	}
	shuffle(questions.begin(), questions.end(), e);

	int i = 0;
	int score = 0;
	while (true) {
		system("cls");
		setColor(10);
		variant = 65;
		cout << questions[i].first << "? " << endl;
		for (auto& j : questions[i].second.second) {
			if (j == questions[i].second.first) correctVariant = variant;
			cout << variant++ << "." << j << "  ";
		}
		cout << endl << endl;
		setColor(11);
		if (i == 0) cout << "s->save    " << "n->next" << endl << endl;	                          
		else if (i == questions.size() - 1) cout << "b->back    " << "s->save" << endl << endl;   	
		else cout << "b->back    " << "s->save    " << "n->next" << endl << endl;                  
		setColor(14);
		cout << "Enter answer (A s): ";
		setColor(10);
		cin >> choice;
		if (choice == "b" && i != 0) i--;
		else if (choice == "s" && variants[i] != " ") {      
			string corVar = { correctVariant };          
			if (variants[i] == corVar) score += 5;
			questions.erase(questions.begin() + i);    
			variants.erase(variants.begin() + i);
			if (i == questions.size()) i--;          
		}
		else if (choice == "s" && variants[i] == " ") {    
			system("cls");
			setColor(14);
			cout << "Choose variant!" << endl;
			Sleep(2000);
		}
		else if (choice == "n" && i < questions.size() - 1) i++;

		else if (choice == "a" || choice == "b" || choice == "c" || choice == "d" || choice == "A" || choice == "B" || choice == "C" || choice == "D") {
			choice == "a" ? choice = "A" : choice;
			choice == "b" ? choice = "B" : choice;
			choice == "c" ? choice = "C" : choice;
			choice == "d" ? choice = "D" : choice;
			variants[i] = choice;
		}

		if (questions.size() == 0) {
			if (!checkAdminOrPlayer(user->getUsername(), user->getPassword())) {
				leaderBoard(user);
				addQuizToUser(user, quizName);
			}
			break;
		}
	}
}