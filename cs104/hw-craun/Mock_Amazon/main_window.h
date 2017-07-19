#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QComboBox> 
#include <QRadioButton>

#include <string>
#include <vector>

#include "product.h"
#include "datastore.h"
#include "mydatastore.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "msort.h"
#include "cartwindow.h"
#include "revwindow.h"
#include "recwindow.h"

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow(MyDataStore* ds, User* u); 
	~MainWindow();

private slots:
	void search();
	void radio1Selected();
	void radio2Selected(); 
	void sort1Selected(); 
	void sort2Selected(); 
	void userChange(); 
	void userSearch(); 
	void openCartWindow(); 
	void addToCart();  
	void saveFile(); 
	void selectProduct(); 
	void sortRevs(); 
	void openRevWindow(); 
	void prodRecs(); 

private:

	// // UI

	// Cart Window 
	CartWindow* cartWindow; 
	QPushButton* viewCart; 

	// Main layout 
	QVBoxLayout* overallLayout;

	// ListWidget Layout 
	QHBoxLayout* listLayout; 

	// List of search results
	QListWidget* lastSearch;

	// List of review 
	QVBoxLayout* reviewLayout; 
	QListWidget* reviews; 
	QLabel* review_label; 

	// Add Review 
	RevWindow* revWindow; 
	QPushButton* addReview; 

	// Form for product search
	QLabel* product_label; 
	QVBoxLayout* formLayout;
	QLabel* searchLabel;
	QLineEdit* searchInput;
	QPushButton* searchButton;

	QHBoxLayout* searchLayout; 

	QVBoxLayout* radioLayout; 
	QRadioButton* AND; 
	QRadioButton* OR;  

	QVBoxLayout* sortLayout; 
	QRadioButton* alpha; 
	QRadioButton* avg; 

	QPushButton* addToCartButton; 

	// User selection
	QHBoxLayout* userLayout; 
	QComboBox* user_list;  
	QLineEdit* userInput;
	QPushButton* userButton; 
	QLabel* userDisplay; 
	QLabel* userLabel; 

	// User choices Layout
	QHBoxLayout* userChoiceLayout; 

	// Product Recommendations 
	QPushButton* prodrecsButton; 
	RecWindow* recWindow; 

	// Saving to file, quitting, and logging out
	QHBoxLayout* saveLayout; 
	QLineEdit* fileInput; 
	QPushButton* saveButton; 
	QPushButton* quit; 

	// List of search results
	std::vector<Product*> results_;

	// MyDataStore Object Pointer 
	MyDataStore* ds_; 

	// Determines AND or OR search 
	bool searchType_; 

	// Current user 
	User* current_; 

	// Current reviews 
	std::vector<Review*> reviews_; 
};