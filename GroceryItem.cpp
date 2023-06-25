#include "GroceryItem.h"

using namespace std;

// Constructors
// 
//Constructor for GroceryItem class that sets name and quantity
//@param name - reference to a string constant that represents the name of the item
GroceryItem::GroceryItem(const string& name)
	: name(name), quantity(0) {
}

// Constructor for GroceryItem class that sets name and quantity
//@param name - reference to a string constant that represents the name of the item
//@param quantity - an integer that represents quantity
GroceryItem::GroceryItem(const string& name, int quantity)
	: name(name), quantity(quantity) {
}

// Accessors

//Method that gets the name of a GroceryItem class object
//@param NA
//@returns - the name of the item
string GroceryItem::getName() const {
	return name;
}

//Method that gets the quantity of a GroceryItem class object
//@param NA
//@returns - quantity of the item
int GroceryItem::getQuantity() const {
	return quantity;
}

// Settors

//Method to increment the quantity by 1
//@param NA
//@returns NA
void GroceryItem::addItem() {
	quantity += 1;
}


//Method to decrement the quantity by 1
//@param NA
//@returns NA
void GroceryItem::removeItem() {
	quantity -= 1;
	if (quantity < 0) {
		quantity = 0;
	}
}

// Overloaded operator

//Overloading < operator to allow for comparing item names
//@param other - reference to a constant GroceryItem that will be compared to current item
//@returns - boolean true or false
bool GroceryItem::operator<(const GroceryItem& other) const {
	return name.compare(other.getName()) < 0;
}
