#include <iostream>
#include <string>

using namespace std;

// Write a function that can throw two kinds of exceptions: int and const char*
// It should receive an integer.
// It should return a string from the char* array defined below.
// If the integer is larger than 5, throw an integer exception. The value of the exception should be how much larger it is.
// If the integer is less than 0, it should throw a const char* exception stating, that it is a negative number.
//
// Illustrate both cases in the main function.
// HINT: Put each protected code segmetn in a new try-catch block.

const char* sentence[6] = {"What", "a", "pleasant", "surprie", "this", "is."};

string myFunc(int x) throw(int, const char*)
{
    if (x > 5) {
        throw x - 5;
    } else if (x < 0) {
        throw "negative number";
    } else {
        return sentence[x];
    }
}

int main ()
{
    int x;
    cin >> x;

    try {
        cout << myFunc(x);
    }
    catch (int x) {
        cout << x << endl;
    }
    catch (const char *c) {
        cout << c << endl;
    }

    return 0;
}

