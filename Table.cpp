#include "Table.h"
#include <vector>
#include "Customer.h"
#include "Dish.h"
using namespace std;

/*Constructor*/
Table::Table(int t_capacity) : capacity(t_capacity), open(false) {}

/*Copy Constructor*//*TODO check what to tod with orderList*/
Table::Table(const Table &OtherTable) : capacity(OtherTable.capacity), open(OtherTable.open),
                                        orderList(OtherTable.orderList) {
    for (auto const &customer : OtherTable.customersList) {
        customersList.push_back(customer);
    }
}

/*destructor*/
Table::~Table() {
    for (int i(0); i < customersList.size(); ++i) {
        delete customersList[i];
    }
}

/*Copy Assignment Operator*/
Table &Table::operator=(const Table &otherTable) {
    if (this != &otherTable) {
        capacity = otherTable.capacity;
        open = otherTable.open;
        for (int i(0); i < customersList.size(); ++i) {
            delete customersList[i];
        }
        customersList.clear();/*TODO we might need to assign memory on the heap*/
        for (int j(0); j < otherTable.customersList.size(); ++j) {
            customersList.push_back(otherTable.customersList[j]);
        }
        orderList = otherTable.orderList;
        return *this;
    }
}

/*Move Constructor*/
Table::Table(Table &&otherTable) noexcept : capacity{otherTable.capacity}, open(otherTable.open),
                                            customersList(otherTable.customersList), orderList(otherTable.orderList) {
    for (int i(0); i < otherTable.customersList.size(); ++i) {
        otherTable.customersList[i] = nullptr;
    }
}


/*Move Assignment Operator*/
Table &Table::operator=(Table &&otherTable) noexcept {
    if (this != &otherTable) {
        capacity = otherTable.capacity;
        open = otherTable.open;
        orderList = otherTable.orderList;
        for (auto &thisCustomer : customersList) {
            delete thisCustomer;
        }
        customersList = otherTable.customersList;
        for (auto &customer:otherTable.customersList) {
            customer = nullptr;
        }
        return *this;
    }
}


bool Table::isOpen() {
    return open;
}

int Table::getCapacity() const {
    return capacity;
}

void Table::addCustomer(Customer *customer) {
    customersList.push_back(customer);
}

void Table::removeCustomer(int id) {
    int i(0);
    for (auto const &customer : customersList) {
        if (customer->getId() == id) {
            customersList.erase(customersList.begin() + i);
        } else i++;
    }
}

Customer *Table::getCustomer(int id) {
    Customer *returnCustomer(nullptr);
    for (auto const &customer : customersList) {
        if (customer->getId() == id) {
            returnCustomer = customer;
            break;
        }
    }
    return returnCustomer;
}

std::vector<Customer *> &Table::getCustomers() {
    return customersList;
}

std::vector<OrderPair> &Table::getOrders() {
    return orderList;
}

void Table::order(const std::vector<Dish> &menu) {
    for (auto const &customer:customersList) {
        int id(customer->getId());
        vector<int> dishID = customer->order(menu);
        for (auto dishNum : dishID) {
            for (auto dish : menu) {
                if (dishNum == dish.getId()) {
                    OrderPair temp(id, dish);
                    orderList.push_back(temp);
                }
            }

        }
    }
}

void Table::openTable() {
    open = true;
}

void Table::closeTable() {
    open = false;
}

int Table::getBill() {
    int bill(0);
    for (auto pair : orderList) {
        bill += pair.second.getPrice();
    }
    return bill;
}
