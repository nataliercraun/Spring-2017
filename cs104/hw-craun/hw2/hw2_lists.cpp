#include <iostream> 
#include <fstream> 
#include <sstream>  
#include <cstdlib>
#include <string> 


using namespace std;

struct Item {
  Item(int v, Item* n) { val = v; next = n; }
  int val;
  Item* next;
}; 

//function prototypes: 

void readLists(const char* filename, Item*& head1, Item*& head2);
void printList(std::ostream& ofile, Item* head); 
Item* concatenate(Item* head1, Item* head2);
void removeEvens(Item*& head);
double findAverage(Item* head); 
double helpfindTotal(Item* head); 
double helpfindCount(Item* head); 


void readLists(const char* filename, Item*& head1, Item*& head2) {

	ifstream ifile(filename); 
	string line; 
	int num = 0; // changed to int  
	//head1 = new Item(0.0, NULL); 

	if (getline(ifile, line)) {

		stringstream ss(line); 

		ss >> num;  
		head1 = new Item(num, NULL); 
		Item *temp = head1;  

		while (ss >> num) { 
			temp->next = new Item(num, NULL); 
			temp = temp->next;  
		}
	}

	else {
		head1 = NULL;  
	}

	if (getline(ifile, line)) {

		stringstream qq(line); 

		qq >> num; 
		head2 = new Item(num, NULL); 
		Item *temp2 = head2; 

		while (qq >> num) {
			temp2->next = new Item(num, NULL);
			temp2 = temp2->next;   
		}
	}

	else {
		head2 = NULL; 
	}
	
	return; 
}

Item* concatenate(Item* head1, Item* head2) {

	if (head1 == NULL && head2 == NULL) {
 		return head1; 
	}

	else { 

		if (head1 == NULL) {
			return new Item(head2->val, concatenate(head1, head2->next));
		}

		if (head2 == NULL) {
			return NULL; 
		}
		return new Item(head1->val, concatenate(head1->next, head2));  
	}

}

void removeEvens(Item*& head) {
	if (head == NULL) {
		return; 
	}

	else {
		removeEvens(head->next); 
		Item *temp; 
		if (head->val % 2 == 0) {
			temp = head; 
			head = head->next; 
			delete temp; 
		} 
	}
}

double findAverage(Item* head) {

	if (helpfindTotal(head) == 0 && helpfindCount(head) == 0) {
		return 0.0; 
	}

	else {
		return helpfindTotal(head) / helpfindCount(head); 
	}
}

double helpfindTotal(Item* head) {
	if (head == NULL) {
		return 0.0; 
	}

	else {
		int temp = head->val;   
		return temp += helpfindTotal(head->next);  
	}
}

double helpfindCount(Item* head) {
	if (head == NULL) {
		return 0.0; 
	}
	else {
		return helpfindCount(head->next) + 1; 
	}
}


void printList(std::ostream& ofile, Item* head)
{ 
  if(head == NULL)
    ofile << std::endl;
  else {
    ofile << head->val << " "; 
    printList(ofile, head->next);   
  }
}


int main (int argc, const char* argv[]) {

	if (argc < 3) {
		cout << "Error" << endl; 
		return -1; 
	}

	Item* head1; 
	Item* head2; 
	readLists(argv[1], head1, head2); 

	ofstream ofile(argv[2]);  

	Item* head3 = concatenate(head1, head2);

	Item *h1_temp = head1; 
	Item *h1_temp2; 
	while (h1_temp != NULL) {
		h1_temp2 = h1_temp; 
		h1_temp = h1_temp->next; 
		delete h1_temp2; 
	}

	Item *h2_temp = head2; 
	Item *h2_temp2; 
	while (h2_temp != NULL) {
		h2_temp2 = h2_temp; 
		h2_temp = h2_temp->next; 
		delete h2_temp2; 
	}

	printList(ofile, head3); 
	removeEvens(head3); 
	printList(ofile, head3); 
	cout << findAverage(head3) << endl; 
	printList(ofile, head3); 
	ofile << findAverage(head3) << endl;

	Item *temp = head3; 
	Item *temp2; 
	while (temp != NULL) {
		temp2 = temp; 
		temp = temp->next; 
		delete temp2; 
	}


	return 0; 
}
