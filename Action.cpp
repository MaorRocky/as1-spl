#include "Action.h"
#include "Restaurant.h"

using namespace std;

/*Constructor*/
BaseAction::BaseAction() {
    status = PENDING;
}

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::complete() {
    status = COMPLETED;
}

void BaseAction::error(std::string errorMsg) {
    status = ERROR;
    cout << "ERROR: " + errorMsg << endl;
}

std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}

/******************************END OF BASE ACTION****************************************/

/*TODO do we need a deep copy in customers?*/
/*Constructor*/
OpenTable::OpenTable(int id, std::vector<Customer *> &customersList) : tableId(id), customers(customersList) {

}

/*if the tableID is indeed valid and the table is not open already than:*/
void OpenTable::act(Restaurant &restaurant) {
    if (tableId < restaurant.getNumOfTables() && tableId >= 0
        && !(restaurant.getTable(tableId)->isOpen())) {
        (restaurant.getTable(tableId))->openTable();
        for (auto const &customer : customers) {
            (restaurant.getTable(tableId))->addCustomer(customer);
        }
    } else {
        error("Table does not exist or is already open");
    }
}

std::string OpenTable::toString() const {
    for(auto const &customer : customers){
;
    }
}

/***********END OF OPEN TABLE*******/

Order::Order(int id) : tableId(id) {}

