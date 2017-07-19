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
#include <sstream> 

#include "product.h"
#include "datastore.h"
#include "mydatastore.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "msort.h"

class RevWindow : public QWidget {
	Q_OBJECT

	public: 

		RevWindow(MyDataStore*, Product* p, User* curr); 
		~RevWindow();

	private slots: 

		void createReview(); 
	
	private: 

		MyDataStore* ds_; 

		QHBoxLayout* overallLayout; 

		QVBoxLayout* labelLayout; 

		QLabel* rating_label;  
		QLabel* text_label; 
		QLabel* year_label;
		QLabel* month_label;
		QLabel* day_label;

		QVBoxLayout* inputLayout; 

		QComboBox* rating;  
		QLineEdit* text; 
		QComboBox* day; 
		QComboBox* month; 
		QComboBox* year; 
		QPushButton* submit; 

		User* current_; 
		Product* pro_; 
		std::vector<Review*> reviews; 
 
}; 