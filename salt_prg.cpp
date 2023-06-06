#include <bits/stdc++.h>

using namespace std;

string generateSalt(int length = 8) {
    string saltCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_-+=<>?/\\";
    random_device rd;
    mt19937 generator(rd());
    shuffle(saltCharacters.begin(), saltCharacters.end(), generator);
    return saltCharacters.substr(0, length);
}

string hashPassword(const string& password, const string& salt) {
    string saltedPassword = password + salt;
    stringstream ss;
    for (unsigned char c : saltedPassword) {
        ss << setw(2) << hex << static_cast<int>(c);
    }
    return ss.str();
}

bool checkPassword(const string& password, const string& hashedPassword, const string& salt) {
    string saltedPassword = password + salt;
    stringstream ss;
    for (unsigned char c : saltedPassword) {
        ss << setw(2) << hex << static_cast<int>(c);
    }
    return ss.str() == hashedPassword;
}

int main() {
    map<string, string> passwordFile;
    int numUsers;
    cout << "Enter the number of users: ";
    cin >> numUsers;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i = 0; i < numUsers; ++i) {
        string username, password;
        cout << "Enter the username for User " << i + 1 << ": ";
        getline(cin, username);
        cout << "Enter the password for User " << i + 1 << ": ";
        getline(cin, password);
        passwordFile[username] = password;
    }

    map<string, pair<string, string>> hashedPasswordFile;
    for (const auto& entry : passwordFile) {
        const string& username = entry.first;
        const string& password = entry.second;
        string salt = generateSalt();
        string hashedPassword = hashPassword(password, salt);
        hashedPasswordFile[username] = make_pair(hashedPassword, salt);
    }

    ofstream outputFile("hashed_passwords.txt");
    if (outputFile.is_open()) {
        for (const auto& entry : hashedPasswordFile) {
            const string& username = entry.first;
            const string& hashedPassword = entry.second.first;
            const string& salt = entry.second.second;
            outputFile << username << ":" << hashedPassword << ":" << salt << endl;
        }
        outputFile.close();
        cout << "Hashed passwords are saved in 'hashed_passwords.txt'." << endl;
    } else {
        cout << "Unable to open file for writing." << endl;
    }

    string inputUsername, inputPassword;
    cout << "Enter username: ";
    getline(cin, inputUsername);
    cout << "Enter password: ";
    getline(cin, inputPassword);

    ifstream inputFile("hashed_passwords.txt");
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            stringstream ss(line);
            string storedUsername, storedHashedPassword, storedSalt;
            getline(ss, storedUsername, ':');
            getline(ss, storedHashedPassword, ':');
            getline(ss, storedSalt, ':');
            if (storedUsername == inputUsername) {
                if (checkPassword(inputPassword, storedHashedPassword, storedSalt)) {
                    cout << "Login successful." << endl;
                } else {
                    cout << "Login failed. Invalid username or password." << endl;
                }
                inputFile.close();
                return 0;
            }
        }
        inputFile.close();
        cout << "Login failed. Invalid username or password." << endl;
    } else {
        cout << "Unable to open file for reading." << endl;
    }

    return 0;
}
