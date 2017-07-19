#include "cartwindow.h"

using namespace std; 


CartWindow::CartWindow(MyDataStore* ds, User* curr) {

	// Initialize MyDataStore pointer 
	ds_ = ds; 

	// Initialize current user 
	current_ = curr; 

	// Title
	string name = current_->getName(); 
	QString qstr_name(name.c_str());
	setWindowTitle(qstr_name);

	// Overall layout
	overallLayout = new QVBoxLayout();

	products_ = new QListWidget; 
	overallLayout->addWidget(products_); 

	cart_ = ds_->getCart(current_); 
	for (unsigned int i = 0; i < cart_.size(); i++) {
		string display = cart_[i]->displayString(); 
		QString qstr(display.c_str());
		products_->addItem(qstr);
	}
	
	setLayout(overallLayout);

	buyCart = new QPushButton("Buy Cart"); 
	overallLayout->addWidget(buyCart); 
	connect(buyCart, SIGNAL(clicked()), this, SLOT(BuyCart())); 

	remove_item = new QPushButton("Remove"); 
	overallLayout->addWidget(remove_item); 
	connect(remove_item, SIGNAL(clicked()), this, SLOT(RemoveItem())); 

}

CartWindow::~CartWindow() {

}

void CartWindow::BuyCart() {
	ds_->BuyCart(current_->getName());
	products_->clear();  
	cart_ = ds_->getCart(current_); 
	for (unsigned int i = 0; i < cart_.size(); i++) {
		string display = cart_[i]->displayString(); 
		QString qstr(display.c_str());
		products_->addItem(qstr);
	} 
}

void CartWindow::RemoveItem() {
	int curr = products_->currentRow();
	products_->takeItem(curr);
	cart_.erase(cart_.begin()+curr); 
	ds_->updateCart(current_, cart_); 
}