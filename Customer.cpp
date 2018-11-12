#include "Customer.h"

using namespace std;

/*constructor*/
Customer::Customer(std::string c_name, int c_id) : name(c_name), id(id) {}

std::string Customer::getName() const { return name; }

int Customer::getId() const { return id; }
/***********************END OF CUSTOMER***************************/

/*VegetarianCustomer constructor*/
VegetarianCustomer::VegetarianCustomer(std::string name, int id) : Customer(name, id) {}

/*VegetarianCustomer order*/
std::vector<int> VegetarianCustomer::order(const std::vector<Dish> &menu) {
    vector<int> vector;
    int minimumVegID(INT8_MAX);
    int bvgId(0);
    int bvgPrice(0);
    for (int i(0); i < menu.size(); ++i) {
        if (menu[i].getType() == VEG && minimumVegID > menu[i].getId()) {
            minimumVegID = menu[i].getId();
        } else if (menu[i].getType() == BVG && bvgPrice < menu[i].getPrice()) {
            bvgPrice = menu[i].getPrice();
            bvgId = menu[i].getId();
        } else if (menu[i].getType() == BVG && bvgPrice == menu[i].getPrice() &&
                   menu[bvgId].getId() > menu[i].getId()) {
            bvgPrice = menu[i].getPrice();
            bvgId = menu[i].getId();
        }
    }
    vector.push_back(minimumVegID);
    vector.push_back(bvgId);
    return vector;
}

std::string VegetarianCustomer::toString() const {
    string a(this->getName());
    string b("is a Vegetarian Customer");
    string s = a + " " + b;
    return s;
}

/*CheapCustomer constructor*/
CheapCustomer::CheapCustomer(std::string name, int id) : Customer(name, id), ordered(false) {}

/*CheapCustomer order*/
std::vector<int> CheapCustomer::order(const std::vector<Dish> &menu) {
    vector<int> vector;
    int dishId(0);
    if (!ordered) {
        int cheapestDish(INT8_MAX);
        for (int i(0); i < menu.size(); ++i) {
            if (menu[i].getPrice() < cheapestDish) {
                cheapestDish = menu[i].getPrice();
                dishId = menu[i].getId();
            }
        }
        vector.push_back(dishId);
        ordered = true;
    }
    return vector;
}

std::string CheapCustomer::toString() const {
    string a(this->getName());
    string b("is a Cheap Customer");
    string s = a + " " + b;
    return s;
}

/*SpicyCustomer constructor*/
SpicyCustomer::SpicyCustomer(std::string name, int id) : Customer(name, id), firstOrder(0), cheapestBvgId(-1) {}

/*SpicyCustomer order*/
std::vector<int> SpicyCustomer::order(const std::vector<Dish> &menu) {
    vector<int> vector;
    /*first order so he needs to order a dish*/
    if (firstOrder == 0) {
        int dishId(0);
        int dishPrice(0);
        for (int i(0); i < menu.size(); ++i) {
            if (menu[i].getType() == SPC && dishPrice < menu[i].getPrice()) {
                dishId = menu[i].getType();
                dishPrice = menu[i].getPrice();
            } else if (menu[i].getType() == SPC && dishPrice == menu[i].getPrice() &&
                       dishId > menu[i].getId()) {
                dishId = menu[i].getType();
                dishPrice = menu[i].getPrice();
            }
            firstOrder = 1;
            vector.push_back(dishId);
        }
    } else {
        /*not the first time he ordered is so just order the same again.*/
        if (cheapestBvgId > -1)
            vector.push_back(cheapestBvgId);
        else {
            int bvgPrice(INT8_MAX);
            for (int j(0); j < menu.size(); ++j) {
                if (menu[j].getType() == BVG) {
                    if (bvgPrice > menu[j].getPrice()) {
                        bvgPrice = menu[j].getPrice();
                        cheapestBvgId = menu[j].getId();
                    } else if (menu[j].getType() == BVG && bvgPrice == menu[j].getPrice()) {
                        if (menu[j].getId() < cheapestBvgId) {
                            cheapestBvgId = menu[j].getId();
                        }
                    }
                }
            }
            vector.push_back(cheapestBvgId);
        }
    }
    return vector;
}


std::string SpicyCustomer::toString() const {
    string a(this->getName());
    string b("is a Spicy Customer ");
    string s = a + " " + b;
    return s;
}

/*AlchoholicCustomer constructor*/
AlchoholicCustomer::AlchoholicCustomer(std::string name, int id) : Customer(name, id), lastBvgPrice(0),
                                                                   BvgOrdered("") {}

/*TODO not sure about the find*/
std::vector<int> AlchoholicCustomer::order(const std::vector<Dish> &menu) {
    vector<int> vector;
    int bvgIndex(0);
    int price(INT8_MAX);
    bool found(false);
    for (int i(0); i < menu.size(); ++i) {
        if (menu[i].getType() == ALC) {
            if (menu[i].getPrice() < price && menu[i].getPrice() >= lastBvgPrice &&
                (!BvgOrdered.find("," + menu[i].getName()) + ",")) {
                bvgIndex = i;
                price = menu[i].getPrice();
                found = true;
            }
        }
        if (found) {
            lastBvgPrice = price;
            BvgOrdered = BvgOrdered + "," + menu[bvgIndex].getName() + ",";
            vector.push_back(menu[bvgIndex].getId());
        }
    }
    return vector;
}