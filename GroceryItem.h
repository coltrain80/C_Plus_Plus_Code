#ifndef GROCERYITEM_H
#define GROCERYITEM_H

#include <string>

using namespace std;

class GroceryItem {
    public:
        // Constructors
        GroceryItem(const string& name);
        GroceryItem(const string& name, int quantity);

        // Accessors
        string getName() const;
        int getQuantity() const;

        // Modifiers
        void addItem();
        void removeItem();

        // Overloaded operator
        bool operator<(const GroceryItem& other) const;

    private:
        string name;
        int quantity;
};

#endif // GROCERYITEM_H
