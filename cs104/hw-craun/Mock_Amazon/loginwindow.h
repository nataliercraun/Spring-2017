#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout> 
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QComboBox> 
#include <QRadioButton>
#include <QMessageBox> 

#include <string>
#include <vector>
#include <sstream> 

#include "main_window.h"
#include "product.h"
#include "datastore.h"
#include "mydatastore.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "msort.h"


class LoginWindow: public QWidget {
	Q_OBJECT

	public: 

		LoginWindow(MyDataStore*); 
		~LoginWindow();
		unsigned long long hashit(std::string pass);

	private slots: 

		void login(); 
		void addUser(); 
	
	private: 

		MyDataStore* ds_; 

		// Layouts
		QVBoxLayout* overallLayout; 
		QHBoxLayout* buttonLayout; 
		QVBoxLayout* inputLayout; 

		// Buttons 
		QPushButton* loginbutton;
		QPushButton* quitbutton;  
		QPushButton* newuser; 

		// User Login 
		QLineEdit* userInput; 
		QLabel* username; 
		QLabel* pass; 
		QLineEdit* passInput; 
		//QMessageBox* repeat; 
}; 