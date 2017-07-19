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

class CartWindow : public QWidget {
	Q_OBJECT

	public: 

		CartWindow(MyDataStore* ds, User* curr); 
		~CartWindow();

	private slots: 

		void BuyCart();
		void RemoveItem(); 

	private: 

		// Layouts
		QVBoxLayout* overallLayout;

		// MyDataStore Object Pointer 
		MyDataStore* ds_;

		// Current User 
		User* current_; 

		// Products in user's cart 
		QListWidget* products_;

		// Buy Cart 
		QPushButton* buyCart; 

		// Remove Item 
		QPushButton* remove_item; 

		// Current cart 
		std::vector<Product*> cart_; 
}; 