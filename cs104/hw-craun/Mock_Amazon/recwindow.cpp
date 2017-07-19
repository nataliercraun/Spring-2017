#include "recwindow.h"
#include "heap.h"

#include <string> 
#include <vector> 
#include <map> 
#include <sstream> 
#include <iostream> 
#include <iomanip> 

using namespace std; 

RecWindow::RecWindow(MyDataStore* ds, User* u, std::vector<std::pair<std::string, double> > suggestions) {

	// Initialize datastore and user data members with given arguments 
	ds_ = ds; 
	curr_ = u; 

	// Title
	setWindowTitle("Product Recommendations");

	// Layouts 
	overallLayout = new QVBoxLayout(); 

	widge = new QListWidget(); 

	for (unsigned int i = 0; i < suggestions.size(); i++) {

		stringstream ss; 
		string product = suggestions[i].first; 
		double num = suggestions[i].second; 

		ss << product << endl << setprecision(3) << num; 

		string finish = ss.str();  

		QString qstr(finish.c_str());

		widge->addItem(qstr);
	}

	overallLayout->addWidget(widge); 

	// Buttons 
	done = new QPushButton("Done"); 
	overallLayout->addWidget(done); 
	connect(done, SIGNAL(clicked()), this, SLOT(close()));


	setLayout(overallLayout);
}

RecWindow::~RecWindow() {


}
