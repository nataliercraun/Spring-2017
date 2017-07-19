#include "loginwindow.h"
#include <cmath> 
#include <string> 
#include <iostream> 

using namespace std; 

LoginWindow::LoginWindow(MyDataStore* ds) {

	// Initialize MyDataStore pointer 
	ds_ = ds; 

	// Title
	setWindowTitle("Login");

	// Layouts 

		// Overall layout
		overallLayout = new QVBoxLayout();

		// Input layout 
		inputLayout = new QVBoxLayout(); 
		overallLayout->addLayout(inputLayout); 

		// Button layout 
		buttonLayout = new QHBoxLayout(); 
		overallLayout->addLayout(buttonLayout); 

	// Buttons 

		// Create login button 
		loginbutton = new QPushButton("Login"); 
		buttonLayout->addWidget(loginbutton);
		connect(loginbutton, SIGNAL(clicked()), this, SLOT(login())); 

		// Create new user button 
		newuser = new QPushButton("New User"); 
		buttonLayout->addWidget(newuser); 
		connect(newuser, SIGNAL(clicked()), this, SLOT(addUser()));

		// Create quit button 
		quitbutton = new QPushButton("Quit"); 
		buttonLayout->addWidget(quitbutton); 
		connect(quitbutton, SIGNAL(clicked()), this, SLOT(close()));

	// User Login 

		username = new QLabel("Username:"); 
		inputLayout->addWidget(username);  
		userInput = new QLineEdit(""); 
		inputLayout->addWidget(userInput);
		pass = new QLabel("Password:"); 
		inputLayout->addWidget(pass);
		passInput = new QLineEdit("");
		inputLayout->addWidget(passInput); 

	// Set overall layout
	setLayout(overallLayout);
}

LoginWindow::~LoginWindow() {

}

void LoginWindow::login() {

	if ( userInput->text().isEmpty() || passInput->text().isEmpty() )
	{
		return;
	}

	QString curr = userInput->text(); 
	string curr_ = curr.toStdString();

	map<string, User*> users = ds_->getUsers(); 
	map<string, User*>::iterator it; 

	it = users.find(curr_);  


	if (it == users.end()){
		QMessageBox mymsg(this); 	
		mymsg.setText("Error: Invalid Username"); 
		mymsg.exec(); 
		userInput->setText("");
		passInput->setText(""); 
		return; 
	}

	QString pass = passInput->text(); 
	string pass_ = pass.toStdString();
	unsigned long long hash = hashit(pass_); 

	if (it->second->getHash() != hash) {
		QMessageBox mymsg(this); 	
		mymsg.setText("Error: Incorrect Password"); 
		mymsg.exec(); 
		userInput->setText("");
		passInput->setText(""); 
		return; 
	}

	MainWindow* mainWindow = new MainWindow(ds_, it->second); 
	mainWindow->show();
	close(); 
}

void LoginWindow::addUser() {

	if ( userInput->text().isEmpty() || passInput->text().isEmpty() )
	{
		return;
	}

	QString curr = userInput->text(); 
	string curr_ = curr.toStdString();

	QString pass = passInput->text(); 
	string pass_ = pass.toStdString();

	map<string, User*> users = ds_->getUsers(); 
	map<string, User*>::iterator it; 
	it = users.find(curr_);  

	if (it != users.end()){
		QMessageBox mymsg(this); 	
		mymsg.setText("Error: Username already taken"); 
		mymsg.exec(); 
		userInput->setText("");
		passInput->setText(""); 
		return; 
	}

	if (pass_.size() > 8) {
		QMessageBox mymsg(this); 	
		mymsg.setText("Error: Password longer than eight characters"); 
		mymsg.exec(); 
		userInput->setText("");
		passInput->setText(""); 
		return; 
	}

	unsigned long long hash = hashit(pass_); 
	User* thatnewnew = new User(curr_, 100.00, 1, hash);
	ds_->addUser(thatnewnew); 
	userInput->setText(""); 
	passInput->setText(""); 

	MainWindow* mainWindow = new MainWindow(ds_, thatnewnew); 
	mainWindow->show();
	close();
}

unsigned long long LoginWindow::hashit(string pass) {

	unsigned long long first = 0; 
	unsigned int hashtemp[4]; 
	int power = 0; 

	for (string::reverse_iterator rit = pass.rbegin(); rit != pass.rend(); ++rit) {
		unsigned int temp = (unsigned int)*rit;
		first += (unsigned long long)pow(128, power) * temp;
		power++; 
	}

	int i = 0; 
	int index = 3; 
	while ( first > 0) {
		unsigned int leastsig = (first % 65521); 
		hashtemp[index] = leastsig; 
		first = first / 65521; 
		i++; 
		index--; 
	}

	for (int j = index; j >= 0; j--) {
		hashtemp[j] = 0;
	}

	unsigned long long hashcode; 
	
	hashcode = (45912 * hashtemp[0] + 35511 * hashtemp[1] + 65169 * hashtemp[2] + 4625 * hashtemp[3]) % 65521; 
	return hashcode; 

}


