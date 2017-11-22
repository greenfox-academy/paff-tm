#include <iostream>
#include <string>
#include "User.h"

User::User()
{
    //ctor
}

User::User(string _name, string _pin, int _money, tUser _user_type)
{
    name = _name;
    pin = _pin;
    money = _money;
    user_type = _user_type;
}

User::~User()
{
    //dtor
}

string User::getName()
{
    return name;
}

bool User::checkPIN(string _pin)
{
    if (_pin == pin) {
        return true;
    }
    throw "Incorrect PIN.";
}

tUser User::getUserType(string _pin)
{
    if (checkPIN(_pin)) {
        return user_type;
    }
    return NA;
}

int User::getBalance(string _pin)
{
    if (checkPIN(_pin)) {
        return money;
    } else {
        return 0;
    }
}

void User::withdraw(string _pin, unsigned int _amount) throw (char const*)
{
    if (checkPIN(_pin)) {
        if (money >= (int)_amount) {
            money -= _amount;
            cout << "You've got " << _amount << "Ft." << endl;
            cout << "Reamain " << money << "Ft on your balance." << endl;
        } else {
            throw "There is not enough money on your account";
        }
    }
}
