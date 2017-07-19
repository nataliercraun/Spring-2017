#include "revwindow.h"

using namespace std; 


RevWindow::RevWindow(MyDataStore* ds, Product* p, User* curr) {

	// Initialize MyDataStore pointer 
	ds_ = ds; 

	// Initialize product, user, and reviews 
	current_ = curr; 
	pro_ = p; 

	// Title
	setWindowTitle("Review Form");

	overallLayout = new QHBoxLayout;
	labelLayout = new QVBoxLayout; 
	inputLayout = new QVBoxLayout; 
	overallLayout->addLayout(labelLayout);
	overallLayout->addLayout(inputLayout); 

	rating_label = new QLabel("Rating: ");  
	text_label = new QLabel("Review: "); 
	year_label = new QLabel("Year: "); 
	month_label = new QLabel("Month: "); 
	day_label = new QLabel("Day: "); 

	labelLayout->addWidget(day_label);
	labelLayout->addWidget(month_label);
	labelLayout->addWidget(year_label);
	labelLayout->addWidget(rating_label); 
	labelLayout->addWidget(text_label);

	rating = new QComboBox;  
	text = new QLineEdit;  
	year = new QComboBox; 
	month = new QComboBox; 
	day = new QComboBox; 

	for (int i = 1; i < 32; i++) {
		stringstream integer;
		if (i < 10) {
			integer << 0; 
		} 
		integer << i; 
		string str = integer.str(); 
		QString qstr(str.c_str());
		day->addItem(qstr); 
	}

	for (int i = 1; i < 13; i++) {
		stringstream integer; 
		if (i < 10) {
			integer << 0; 
		}
		integer << i; 
		string str = integer.str(); 
		QString qstr(str.c_str());
		month->addItem(qstr);
	}

	for (int i = 2016; i < 2031; i++) {
		stringstream integer; 
		integer << i; 
		string str = integer.str(); 
		QString qstr(str.c_str());
		year->addItem(qstr);
	}

	for (int i = 1; i < 6; i++) {
		stringstream integer; 
		integer << i; 
		string str = integer.str(); 
		QString qstr(str.c_str());
		rating->addItem(qstr);
	}

	inputLayout->addWidget(day);
	inputLayout->addWidget(month); 
	inputLayout->addWidget(year);
	inputLayout->addWidget(rating); 
	inputLayout->addWidget(text); 
	 
	submit = new QPushButton("Submit"); 
	overallLayout->addWidget(submit); 
	connect(submit, SIGNAL(clicked()), this, SLOT(createReview())); 

	setLayout(overallLayout);
}

RevWindow::~RevWindow() {

}

void RevWindow::createReview() {

	if ( text->text().isEmpty() )
	{
		return;
	}

	QString q_rating = rating->currentText(); 
	string s_rating = q_rating.toStdString();
	int rate = atoi(s_rating.c_str()); 

	QString q_text = text->text(); 
	string s_text = q_text.toStdString();

	QString q_day = day->currentText(); 
	string s_day = q_day.toStdString();

	QString q_month = month->currentText(); 
	string s_month = q_month.toStdString();

	QString q_year = year->currentText(); 
	string s_year = q_year.toStdString();

	stringstream ss; 
	ss << s_year << "-" << s_month << "-" << s_day; 
	string date = ss.str(); 

	Review* new_rev = new Review(pro_->getName(),
           rate,
           current_->getName(),
           date,
           s_text); 

	ds_->addReview(new_rev); 
	text->setText("");
	this->hide(); 
}

