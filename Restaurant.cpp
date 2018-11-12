#include "Restaurant.h"

using namespace std;

/*no args constructor*/
Restaurant::Restaurant() {}

/*constructor*/
Restaurant::Restaurant(const std::string &configFilePath) {}

/*Copy Constructor*/
Restaurant::Restaurant(const Restaurant &otherRestaurant) : open(otherRestaurant.open),
                                                            tables(otherRestaurant.tables),
                                                            menu(otherRestaurant.menu),
                                                            actionsLog(otherRestaurant.actionsLog) {}

/*Destructor*/
Restaurant::~Restaurant() {
    for (int i(0); i < tables.size(); ++i) {
        delete tables[i];
    }
    for (int j(0); j < actionsLog.size(); ++j) {
        delete actionsLog[j];
    }
}

/*TODO tables.size() might be long*/
int Restaurant::getNumOfTables() const {
    return (int) tables.size();
}

Table *Restaurant::getTable(int ind) {
    if (ind < tables.size()) {
        return tables[ind];
    }
}
const std::vector<BaseAction *>& Restaurant::getActionsLog() const {
    return actionsLog;
}

std::vector<Dish>& Restaurant::getMenu() {
    return menu;
}

void Restaurant::start() {
    open = true;
}

