//log in and registeration
// user can log in, register, forget password? function
//menu has: login, registration, forgot password, exit
#include<iostream>
#include<fstream>
#include<string.h>
#include<sstream>
#include<string>

bool loggedOn = 0;
int count = 0;
std::string adminAccount;
std::string currentUserLoggedIn;

void login();
void registeration();
void forgotPass();
void logout();
void viewAccounts();
void setAdmin();
void resetPass();

int main() {
	int c;//c for choice
	std::cout << "\t\t\t_____________________________________________________________\n\n\n";
	std::cout << "\t\t\t                     Welcome to the Login Page               \n\n\n";
	std::cout << "\t\t\t________________________     MENU     _______________________\n\n\n";
	std::cout << "                                                                    \n\n\n";
	std::cout << "\t| Press 1 to LOGIN                                                |" << std::endl;
	std::cout << "\t| Press 2 to REGISTER                                             |" << std::endl;
	std::cout << "\t| Press 3 to Forget password? Enter your username to find it      |" << std::endl;
	std::cout << "\t| Press 4 to Logout                                               |" << std::endl;
	std::cout << "\t| Press 5 to EXIT                                                 |" << std::endl;
	std::cout << "\t| Press 6 to View all the accounts (for admin)                    |" << std::endl;
	std::cout << "\t| Press 7 to Set the Admin account                                |" << std::endl;
	std::cout << "\t| Press 8 to reset your password                                  |" << std::endl;

	std::cout << "\n\tPlease enter your choice: " << std::endl;
	//std::vector<int> choices;
	//= { 1, 2, 3, 4, 5, 6, 7, 8 };
	std::cin >> c;
	//(std::find(choices.begin(), choices.end(), my_var) != my_list.end())
	//if (!(c std::find choices) {
	//	std::cout << "Please enter a valid digit" << std::endl;
	//	main();
	//} // add a guard for entering anythign other than 1-8. 
	//std::cout << std::endl;
	switch (c) {
	case 1:
		login();
		break;
	case 2:
		registeration();
		break;
	case 3:
		forgotPass();
		break;
	case 4:
		logout();
		break;
	case 5:
		std::cout << "Thank you, come again!" << std::endl;
		exit(0);
		break;
	case 6:
		viewAccounts();
		break;
	case 7:
		setAdmin();
		break;
	case 8:
		resetPass();
		break;
	default:
		system("cls");
		std::cout << "\t\t\t Please select from the option given above!" << std::endl;
		main();
	}
}

void login() {
	std::string userId, password, id, pass;
	system("cls");
	std::cout << "Please enter the username and the password" << std::endl;
	std::cout << "Username: ";
	std::cin >> userId;
	std::cout << "Password: ";
	std::cin >> password;

	//input the username and password inputted into the file?
	std::ifstream input("records.txt");

	while (input >> id >> pass) {
		if (id == userId && pass == password) {
			count = 1;
			system("cls");
		}
	}
	input.close();

	if (count == 1) {
		std::cout << "Welcome " << userId << ". Your login was successful, thanks for logging in" << std::endl;
		currentUserLoggedIn = userId;
		loggedOn = 1;
		main();
	}
	else {
		std::cout << "\n LOGIN ERROR \n Your username or password is incorrect, please try again." << std::endl;
		main();
	}
}

void registeration() {
	std::string ruserId, rpassword, rid, rpass;
	system("cls");
	std::cout << "Please enter your new username: ";
	std::cin >> ruserId;
	//TODO
	//if there exists the username already on the file,
	//then do not make the account, navigate hte user to main or ask to enter a different username
	std::string sId, spass;
	std::ifstream f2("records.txt");
	while (f2 >> sId >> spass) {
		//std::cout << sId<< ": " << spass << std::endl;
		int choice;
		if (sId == ruserId) {
			std::cout << "Username already exists. Press 1 to login or Press 2 to enter a new username or Press 3 to go back to the main menu" << std::endl;
			std::cin >> choice;
			switch (choice) {
			case 1:
				login();
			case 2:
				registeration();
			case 3:
				main();
			default:
				std::cout << "\t\t\t Invalid selection, going back to the main page." << std::endl;
				break;
			}

		}
	}

	bool correctPassword = 0;
	std::cout << "Please enter your new password (between 6-15 numbers/characters): ";
	std::cin >> rpassword;
	while (!correctPassword) {
		if (!(rpassword.length() >= 6)) {
			std::cout << "Your password was too short, please enter a different password (between 6-15 numbers/characters): ";
			std::cin >> rpassword;
		}
		else if (!(rpassword.length() <= 15)) {
			std::cout << "Your password is too long, please enter your password again (between 6-15 numbers/characters): ";
			std::cin >> rpassword;
		}
		else if (rpassword.length() >= 6) {
			correctPassword = 1;
		}
		else if (rpassword.length() <= 15) {
			correctPassword = 1;
		}
	}
	//add it to records.txt
	std::ofstream f1("records.txt", std::ios::app);
	f1 << ruserId << " " << rpassword << std::endl;
	system("cls");
	std::cout << "Registeration successful. \nYour new username is: " << ruserId << "\nYour new password is: " << rpassword << std::endl;
	main();
}

void forgotPass() {
	int option;
	if (loggedOn == 1) {
		std::cout << "You are already logged on! Select the reset password option instead!" << std::endl;
		main();
	}
	std::cout << "\t\t\t You forgot your password? shame on you" << std::endl;
	std::cout << "Press 1 to search your id by username" << std::endl;
	std::cout << "Press 2 to go back to the main menu" << std::endl;
	std::cout << "\t\t\t Enter your choice: ";
	std::cin >> option;
	switch (option) {
	case 1: {
		int count = 0;
		std::string suserId, sId, spass;
		std::cout << "\n\t\t\t Enter your username: " << std::endl;
		std::cin >> suserId;

		std::ifstream f2("records.txt");
		while (f2 >> sId >> spass) {
			if (sId == suserId) {
				count = 1;
			}
		}
		f2.close();
		if (count == 1) {
			std::cout << "\n\n Your account is found!" << std::endl;
			std::cout << "\n\n Your password is: " << spass << std::endl;
			main();
		}
		else {
			std::cout << "\n\t Sorry! Your username does not exist in our system!" << std::endl;
			main();
		}
		break;

	}
	case 2:
	{
		main();
	} default:
		std::cout << "\t\t\t Wrong choice!, please try again!" << std::endl;
		forgotPass();
	}
}


void logout() {
	if (loggedOn == 1) {
		loggedOn = 0; //logout
		std::cout << "Successfully Logged out of the account" << std::endl;
		count = 0;
		main();
	}
	else {
		std::cout << "You are not logged in. Please login or register a new account" << std::endl;
		loggedOn = 0; //logout
		main();
	}
}

void viewAccounts() {
	//if logged in to an admin account
	//then view all the accounts
	//else say no access power here.
	if (!(loggedOn == 1)) {
		std::cout << "You have to be logged in to view the accounts" << std::endl;
		main();
	}
	else if (!(currentUserLoggedIn == adminAccount)) {
		std::cout << "You do not have Admin power to do view the accounts" << std::endl;
		main();

	}
	else if ((loggedOn == 1) && (currentUserLoggedIn == adminAccount)) {
		std::cout << "Currently, the registered username(s) and password(s) are..." << std::endl;
		std::ifstream infile("records.txt");
		std::string line;
		while (std::getline(infile, line))
		{
			std::cout << line << "\n";
		}
		main();
	}
	else {
		std::cout << "You have to be logged onto an admin power to view the accounts" << std::endl;
		main();
	}
}

void setAdmin() {
	if (!(loggedOn == 1)) {
		std::cout << "You have to be logged in first" << std::endl;
		main();
	}
	std::string adminAcc;
	std::cout << "Enter the account username you want to set the admin to :";
	std::cin >> adminAcc;
	std::string sId, spass;
	//only set admin if the username is in the file
	std::ifstream f2("records.txt");
	while (f2 >> sId >> spass) {
		//std::cout << sId<< ": " << spass << std::endl;
		if (sId == adminAcc && adminAccount == "") {
			adminAccount = adminAcc;
			std::cout << "Admin is now: " << adminAccount << std::endl;
			main();
		}
	}
	std::cout << "there is no such username in the file" << std::endl;
	main();
}



int encrypt(int p_letter) {
	return p_letter + 3;
}

int decrypt(int p_letter) {
	return p_letter - 3;
}

void resetPass() {
	std::cout << "reset pass" << std::endl;
	main();
}