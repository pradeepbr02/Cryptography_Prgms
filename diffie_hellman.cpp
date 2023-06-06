#include <iostream>
#include <cmath>

using namespace std;

long long calculatePower(long long x, long long y, long long P)
{
    long long result = 0;
    if (y == 1) {
        return x;
    }
    else {
        result = (static_cast<long long>(pow(x, y))) % P;
        return result;
    }
}

int main()
{
    long long P, G, x, a, y, b, ka, kb;
    cout << "Both the users should be agreed upon the public keys G and P" << endl;
    cout << "Enter value for public key G: ";
    cin >> G;
    cout << "Enter value for public key P: ";
    cin >> P;
    cout << "Enter value for private key a selected by user1: ";
    cin >> a;
    cout << "Enter value for private key b selected by user2: ";
    cin >> b;
    x = calculatePower(G, a, P);
    y = calculatePower(G, b, P);
    ka = calculatePower(y, a, P);
    kb = calculatePower(x, b, P);
    cout << "Secret key for User1 is: " << ka << endl;
    cout << "Secret key for User2 is: " << kb << endl;
    return 0;
}
