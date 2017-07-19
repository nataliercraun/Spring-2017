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

#include "product.h"
#include "datastore.h"
#include "mydatastore.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "msort.h"


class RecWindow: public QWidget {
	Q_OBJECT

	public: 

		RecWindow(MyDataStore*, User*, std::vector<std::pair<std::string, double> >); 
		~RecWindow();

	private slots: 

	
	private: 

		 

		// Layouts
		QVBoxLayout* overallLayout; 

		// Buttons 
		QPushButton* done; 

		// List Widget
		QListWidget* widge; 

		MyDataStore* ds_;
		User* curr_; 
		std::vector<User*> basic; 
}; 