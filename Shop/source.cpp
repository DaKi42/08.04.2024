#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

class Observer {
public:
    virtual void update(const string& item) = 0;
};

class Shop {
    vector<Observer*> observers;
public:
    void addObserver(Observer* observer) { 
        observers.push_back(observer); 
    }
    void removeObserver(Observer* observer) { 
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end()); 
    }
    void purchaseItem(const string& item) { 
        for (Observer* observer : observers) { 
            observer->update(item); 
        } 
    }
};

class Customer : public Observer {
    string name;
    int age;

    string getReaction() {
        vector<string> reactions = {
            "Oh no, not again!",
            "Hmm, okay, I guess.",
            "Not bad, I like it.",
            "Wow, that's cool!",
            "Amazing! I love it!"
        };
        return reactions[rand() % reactions.size()];
    }
public:
    Customer(const string& name, int age) : name(name), age(age) {}
    void update(const string& item) override { 
        string reaction = getReaction(); 
        cout << "Name: " << name << "\n Age: " << age << "\n Bought: " << item << "\n Reaction: " << reaction << "\n\n";
    }
};

int main() {
    srand((time(nullptr)));
    Shop shop;
    vector<Customer> customers = {
        { "Kristina", 28 },
        { "Illia", 19 },
        { "Maria", 20 }
    };

    for (Customer& customer : customers) { shop.addObserver(&customer); }
    shop.purchaseItem("Apple");
    cout << endl;
    shop.purchaseItem("Powerbank");
    cout << endl;
    shop.purchaseItem("Tesla Model X");
    return 0;
}
