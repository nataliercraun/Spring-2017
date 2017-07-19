#include "main_window.h"
#include <string> 
#include <vector> 
#include <sstream> 
#include <iostream>
#include <fstream> 
#include <iomanip> 

using namespace std; 

struct AlphaComp { 

	bool operator()(Product* lhs, Product* rhs) {
		return lhs->getName() < rhs->getName(); 
	}
}; 

struct AvgComp {

	AvgComp(MyDataStore* ds_) { ds = ds_; }

	bool operator()(Product* lhs, Product* rhs) {
		return ds->getAvg(lhs) > ds->getAvg(rhs); 
	}

	MyDataStore* ds; 
}; 

struct DateComp {
	bool operator()(Review* lhs, Review* rhs) {
		return lhs->date > rhs->date; 
	}

}; 

MainWindow::MainWindow(MyDataStore* ds, User* u)
{
	// Initialize MyDataStore pointer 
	ds_ = ds; 

	// Initialize Current User 
	current_ = u; 

	// Title
	setWindowTitle("Amazon");

	// Overall layout
	overallLayout = new QVBoxLayout();

	// List widget layout 
	listLayout = new QHBoxLayout(); 

	// User Choices Layout
	userChoiceLayout = new QHBoxLayout();

	// // Form to search
	// Layout

	formLayout = new QVBoxLayout();
	overallLayout->addLayout(formLayout);

	searchInput = new QLineEdit();
	formLayout->addWidget(searchInput); 

	searchLayout = new QHBoxLayout; 
	overallLayout->addLayout(searchLayout); 

	radioLayout = new QVBoxLayout(); 
	searchLayout->addLayout(radioLayout);  
	AND = new QRadioButton("AND"); 
	OR = new QRadioButton("OR");  
	product_label = new QLabel("Search Results");
	radioLayout->addWidget(AND); 
	radioLayout->addWidget(OR);   
	radioLayout->addWidget(product_label); 
	connect(OR, SIGNAL(clicked()), this, SLOT(radio1Selected()) );
	connect(AND, SIGNAL(clicked()), this, SLOT(radio2Selected()) );

	sortLayout = new QVBoxLayout(); 
	review_label = new QLabel("Product Reviews"); 
	searchLayout->addLayout(sortLayout);  
	alpha = new QRadioButton("Sort by Name"); 
	avg = new QRadioButton("Sort by Rating"); 
	sortLayout->addWidget(alpha); 
	sortLayout->addWidget(avg);
	sortLayout->addWidget(review_label);  
	connect(alpha, SIGNAL(clicked()), this, SLOT(sort1Selected()) );
	connect(avg, SIGNAL(clicked()), this, SLOT(sort2Selected()) );

	// // List of all search results 
	overallLayout->addLayout(listLayout); 

	lastSearch = new QListWidget();
	listLayout->addWidget(lastSearch);

	// // List of product reviews
	reviews = new QListWidget(); 
	listLayout->addWidget(reviews); 
	connect(lastSearch, SIGNAL(currentRowChanged(int)), this, SLOT(selectProduct())); 

	reviewLayout = new QVBoxLayout; 
	listLayout->addLayout(reviewLayout); 

	// Adding to current user's cart 

	addToCartButton = new QPushButton("Add to Cart"); 
	userChoiceLayout->addWidget(addToCartButton);
	connect(addToCartButton, SIGNAL(clicked()), this, SLOT(addToCart()));

	// Search button

	searchButton = new QPushButton("Search Products");
	connect(searchButton, SIGNAL(clicked()), this, SLOT(search()));
	formLayout->addWidget(searchButton);

	// User selection 
	// User selection by search 
	userLayout = new QHBoxLayout(); 
	userInput = new QLineEdit(); 
	userLayout->addWidget(userInput); 
	userButton = new QPushButton("Search Users"); 
	userLayout->addWidget(userButton); 
	connect(userButton, SIGNAL(clicked()), this, SLOT(userSearch())); 

	// User choice layout
	overallLayout->addLayout(userChoiceLayout); 
	

	// User selection by dropdown menu
	user_list = new QComboBox;
	userLayout->addWidget(user_list); 
	overallLayout->addLayout(userLayout);  
	map<string, User*> users = ds_->getUsers(); 
	map<string, User*>::iterator it; 
	for (it = users.begin(); it != users.end(); ++it) {
		string username = it->first; 
		QString qstr(username.c_str());
		user_list->addItem(qstr); 
	}

	QString curr = user_list->currentText(); 
	string curr_ = curr.toStdString();
	it = users.find(curr_);  
	//current_ = it->second; 
	connect(user_list, SIGNAL(currentIndexChanged(int)), this, SLOT(userChange())); 

	userLabel = new QLabel("Current User:"); 
	overallLayout->addWidget(userLabel); 

	string name = current_->getName(); 
	QString qstr_name(name.c_str());
	userDisplay = new QLabel(qstr_name); 
	overallLayout->addWidget(userDisplay);


	// Cart Window 
	viewCart = new QPushButton("View Cart"); 
	userChoiceLayout->addWidget(viewCart);
	connect(viewCart, SIGNAL(clicked()), this, SLOT(openCartWindow())); 

	// Saving file 
	saveLayout = new QHBoxLayout; 
	overallLayout->addLayout(saveLayout); 
	fileInput = new QLineEdit; 
	saveLayout->addWidget(fileInput); 
	saveButton = new QPushButton("Save to File");  
	saveLayout->addWidget(saveButton); 
	connect(saveButton, SIGNAL(clicked()), this, SLOT(saveFile())); 

	// Quitting 
	quit = new QPushButton("Quit"); 
	saveLayout->addWidget(quit); 
	connect(quit, SIGNAL(clicked()), this, SLOT(close())); 

	// Adding Review 
	addReview = new QPushButton("Add Review"); 
	reviewLayout->addWidget(addReview); 
	connect(addReview, SIGNAL(clicked()), this, SLOT(openRevWindow())); 

	// Product Recommendations 
	prodrecsButton = new QPushButton("Product Recommendations"); 
	userChoiceLayout->addWidget(prodrecsButton); 
	connect(prodrecsButton, SIGNAL(clicked()), this, SLOT(prodRecs())); 


	// Set overall layout
	setLayout(overallLayout);
}

MainWindow::~MainWindow()
{
	delete ds_; 
}

void MainWindow::openCartWindow() {
	cartWindow = new CartWindow(ds_, current_); 
	cartWindow->show(); 	
}

void MainWindow::openRevWindow() {
	int curr = lastSearch->currentRow(); 
	if (curr == -1) {
		return; 
	}
	Product* p = results_[curr]; 
	revWindow = new RevWindow(ds_, p, current_); 
	revWindow->show(); 
	reviews->clear(); 
	sortRevs();
	reviews->show();  
}

void MainWindow::addToCart() {

	if (lastSearch->currentRow() > -1) {

		int curr = lastSearch->currentRow(); 
		ds_->AddtoCart(current_->getName(), results_[curr]); 
	}
}

void MainWindow::radio1Selected() {
	searchType_ = true; 
}

void MainWindow::radio2Selected() {
	searchType_ = false; 
}

void MainWindow::sort1Selected() {

	AlphaComp comp1; 
	lastSearch->clear();  
	mergeSort(results_, comp1); 

	for (unsigned int i = 0; i < results_.size(); i++) {
		string display = results_[i]->displayString(); 
		QString qstr(display.c_str());
		lastSearch->addItem(qstr);
	}
} 

void MainWindow::sort2Selected() {

	AvgComp* comp2 = new AvgComp(ds_); 
	mergeSort(results_, *comp2); 
	lastSearch->clear();
	  
	for (unsigned int i = 0; i < results_.size(); i++) {
		string name = results_[i]->getName();
		string display = results_[i]->displayString(); 
		QString qstr(display.c_str());
		lastSearch->addItem(qstr);
	}
}

void MainWindow::sortRevs() {
 
	DateComp comp3; 
	int curr = lastSearch->currentRow(); 
	reviews_ = ds_->getReview(results_[curr]);

	mergeSort(reviews_, comp3); 
	reviews->clear();

	for (unsigned int i = 0; i < reviews_.size(); i++) {
		int rate = reviews_[i]->rating; 
		string name = reviews_[i]->prodName; 
		string user = reviews_[i]->username; 
		string date = reviews_[i]->date; 
		string text = reviews_[i]->reviewText; 
		stringstream ss; 
		ss << name << '\n' << rate << " "; 
		ss << user << " " << date << " " << text << '\n';  
		string final_str = ss.str();
		QString qstr(final_str.c_str());
		reviews->addItem(qstr); 
	}
}

void MainWindow::userChange() {
	userDisplay->clear(); 
	map<string, User*> users = ds_->getUsers(); 
	map<string, User*>::iterator it;
	QString curr = user_list->currentText(); 
	string curr_ = curr.toStdString();
	it = users.find(curr_);  
	current_ = it->second; 
	userDisplay->setText(curr);  
}

void MainWindow::userSearch() {

	if ( userInput->text().isEmpty() )
	{
		return;
	}

	QString curr = userInput->text(); 
	string curr_ = curr.toStdString();
	map<string, User*> users = ds_->getUsers(); 
	map<string, User*>::iterator it; 
	it = users.find(curr_);  

	if (it != users.end()) {
		userDisplay->clear(); 
		current_ = it->second; 
		userDisplay->setText(curr);
	}

	userInput->setText("");
}

void MainWindow::search()
{
	// Do nothing if user left at least one input blank
	if ( searchInput->text().isEmpty() )
	{
		return;
	}

	// Clear last search results 
	lastSearch->clear(); 
	
	QString qstring_terms = searchInput->text();
	string string_terms = qstring_terms.toStdString(); 
	vector<string> terms; 
	stringstream ss; 
	ss << string_terms; 
	string temp; 

	while (ss >> temp) {
		terms.push_back(temp); 
	}

	// AND is selected 
	if (searchType_) {
		results_ = ds_->search(terms, 1); 
	}

	// OR is selected 
	else {
		results_ = ds_->search(terms, 0);
	}

	for (unsigned int i = 0; i < results_.size(); i++) {
		string display = results_[i]->displayString(); 
		QString qstr(display.c_str());
		lastSearch->addItem(qstr);
	}

	// Clear the form inputs
	searchInput->setText("");
}

void MainWindow::saveFile() {

	if ( fileInput->text().isEmpty() )
	{
		return;
	}
	
	QString qstring = fileInput->text();
	string filename = qstring.toStdString(); 
    ofstream ofile(filename.c_str());
    ds_->dump(ofile);
    ofile.close();    

    fileInput->setText("");          
}

void MainWindow::selectProduct() {

	reviews->clear(); 

	int curr = lastSearch->currentRow(); 
	vector<Review*> reviews_ = ds_->getReview(results_[curr]); 

	sortRevs(); 
}

void MainWindow::prodRecs() {

	std::vector<std::pair<std::string, double> > suggestions = ds_->makeSuggestion(current_->getName()); 

	if (suggestions.size() == 0) {
		QMessageBox mymsg(this); 	
		mymsg.setText("No Recommendations Available"); 
		mymsg.exec(); 
		return; 
	}

	string filename = "rec.txt"; 
    ofstream ofile(filename.c_str());
    ofile << current_->getName() << endl; 
    for (unsigned int i = 0; i < suggestions.size(); i++) {
    	ofile << setprecision(3) << suggestions[i].second << " " << suggestions[i].first << endl; 
    }
    ofile.close();    
	recWindow = new RecWindow(ds_, current_, suggestions); 
	recWindow->show(); 
}
