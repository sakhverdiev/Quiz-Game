#pragma once

map<string, string> fromFileToMap(string filename) {
	map<string, string> users;
	string username, password;
	ifstream file(filename);
	if (file.is_open()) {
		while (getline(file, username, ' ')) {
			getline(file, password);
			users.insert({ username, password });
		}
		file.close();
	}
	return users;
}

bool checkAdminOrPlayer(string username, string password) {
	map<string, string> admins;
	map<string, string> players;
	admins = fromFileToMap("admins.txt");
	players = fromFileToMap("players.txt");
	for (auto& i : admins) {
		if (username == i.first && password == i.second) return true;
	}
	for (auto& i : players) {
		if (username == i.first && password == i.second) return false;
	}
	setColor(12);
	throw exception("\nInvalid User!");
}

bool loginOrSignChoice() {
	string choice;
	setColor(10);
	cout << "1. Log in" << endl;
	cout << "2. Sign in" << endl << endl;
	setColor(14);
	cout << "Enter 1 or 2: ";
	setColor(10);
	cin >> choice;
	setColor(12);
	if (choice != "1" && choice != "2") throw exception("\nInvalid choice");
	if (choice == "1") return true;
	return false;
}

User* logIn() {
	string username;
	string password;
	bool userCheck;
	while (true) {
		system("cls");
		setColor(14);
		cout << "Enter Username: ";
		setColor(10);
		cin >> username;
		setColor(14);
		cout << "Enter Password: ";
		setColor(10);
		cin >> password;
		try {    // logini yoxlamaq ucun
			userCheck = checkAdminOrPlayer(username, password);
		}
		catch (const exception& ex) {
			cout << ex.what() << endl;
			Sleep(2000);
			continue;
		}
		break;
	}
	// Admin
	if (userCheck) {
		map<string, string> admins;
		admins = fromFileToMap("admins.txt");
		for (auto& i : admins) {
			if (username == i.first && password == i.second) return new Admin(i.first, i.second);
		}
	}
	// User
	else {
		map<string, string> player;
		player = fromFileToMap("players.txt");
		for (auto& i : player) {
			if (username == i.first && password == i.second) return new Player(i.first, i.second);
		}
	}
}

bool signIn() {
	string username, password;
	Player p;
	while (true) {
		system("cls");
		try {
			setColor(14);
			cout << "Enter New Username: ";
			setColor(10);
			cin >> username;
			setColor(14);
			cout << "Enter Password: ";
			setColor(10);
			cin >> password;
			p.setUsername(username);
			p.setPassword(password);
		}
		catch (const exception& ex) {
			cout << endl << ex.what() << endl;
			Sleep(2000);
			continue;
		}
		break;
	}
	ifstream file_("players.txt");
	if (file_.is_open()) {
		string playerUsername;
		while (getline(file_, playerUsername, ' ')) {
			setColor(12);
			if (username == playerUsername) throw exception("This username already used!");
			getline(file_, playerUsername);
		}
	}
	ofstream file("players.txt", ios::app);
	if (file.is_open()) {
		file << p.getUsername() << " " << p.getPassword() << "\n";
		file.close();
		ofstream file__("LeaderBoard.txt", ios::app);
		if (file__.is_open()) {
			file__ << p.getUsername() << " " << 0 << "\n";
			file__.close();
		}
		ofstream playedQuizes("playedQuizes.txt", ios::app);
		{
			if (playedQuizes.is_open()) {
				playedQuizes << p.getUsername() << ":,#\n";
				playedQuizes.close();
			}
		}
		return true;
	}
	return false;
}