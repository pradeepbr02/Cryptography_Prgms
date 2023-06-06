#include <iostream>
#include <utility> 

using namespace std;

pair<int, pair<int, int> > calculateExtendedEuclid(int numA, int numB) 
{
    int x = 1, y = 0;
    int xLast = 0, yLast = 1;
    int quotient, remainder, tempX, tempY;
    while (numA != 0) 
    {
        quotient = numB / numA;
        remainder = numB % numA;
        tempX = xLast - quotient * x;
        tempY = yLast - quotient * y;
        xLast = x; 
        yLast = y;
        x = tempX; 
        y = tempY;
        numB = numA; 
        numA = remainder;
    }
    return make_pair(numB, make_pair(xLast, yLast));
}
 
int calculateModularInverse(int numA, int mod) 
{
    return (calculateExtendedEuclid(numA, mod).second.first + mod) % mod;
}
 
//Main
int main()
{
    int numA, mod;
    cout << "Enter number to find modular multiplicative inverse: ";
    cin >> numA;
    cout << "Enter Modular Value: ";
    cin >> mod;
    cout << calculateModularInverse(numA, mod) << endl;
}

