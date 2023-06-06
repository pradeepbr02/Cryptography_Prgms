#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string performEncryption(const string& message, int keyA, int keyB) {
    string encryptedMessage;
    for (char ch : message) {
        if (isalpha(ch)) {
            char encryptedChar = (keyA * (toupper(ch) - 'A') + keyB) % 26 + 'A';
            encryptedMessage += encryptedChar;
        } else {
            encryptedMessage += ch;
        }
    }
    return encryptedMessage;
}

string performDecryption(const string& message, int keyA, int keyB) {
    
    int keyAInverse = -1;
    for (int i = 0; i < 26; ++i) {
        if ((keyA * i) % 26 == 1) {
            keyAInverse = i;
            break;
        }
    }

    if (keyAInverse == -1) {
        cout << "Invalid value of 'keyA'. It must be coprime with 26." << endl;
        return "";
    }

    string decryptedMessage;
    for (char ch : message) {
        if (isalpha(ch)) {
            char decryptedChar = (keyAInverse * (toupper(ch) - 'A' - keyB + 26)) % 26 + 'A';
            decryptedMessage += decryptedChar;
        } else {
            decryptedMessage += ch;
        }
    }
    return decryptedMessage;
}

int main() {
    string message;
    int keyA, keyB;
    cout << "Enter the message: ";
    getline(cin, message);
    cout << "Enter the value of 'keyA': ";
    cin >> keyA;
    cout << "Enter the value of 'keyB': ";
    cin >> keyB;
    string encryptedMessage = performEncryption(message, keyA, keyB);
    cout << "Encrypted message: " << encryptedMessage << endl;
    string decryptedMessage = performDecryption(encryptedMessage, keyA, keyB);
    cout << "Decrypted message: " << decryptedMessage << endl;
    return 0;
}
