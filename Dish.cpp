#include <string>
#include "Dish.h"


//constructor
Dish::Dish(int d_id, std::string d_name, int d_price, DishType d_type):
        id(d_id),name(d_name),price(d_price),type(d_type){}

//destructor
Dish::~Dish() {
}

/*TODO  there is a the EnuMBDISH */
int Dish::getId() const {
    return id;
}

std::string Dish::getName() const {
    return name;
}

int Dish::getPrice() const {
    return price;
}

DishType Dish::getType() const {
    return type;
}

