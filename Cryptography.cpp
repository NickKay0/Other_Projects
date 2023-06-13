/*
The purpose of this code is to give a user the choice of encypting and/or decrypting a string to the user-selected algorithm
these algorithms are:
    1.Polyalphabetic Substitution / vignere
    2.Transposition
    3.Stream Transposition
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

string RemoveSpaces(string s) {
    string filteredString = "";
    for (int i = 0; i < s.length(); i++) {
        if (!(s[i] == ' '))
            filteredString += s[i];
    }
    transform(filteredString.begin(), filteredString.end(), filteredString.begin(), ::toupper);
    return filteredString;
}

string GetMessage(){
    char tempMessage[100];
    string s;

    cin.ignore();
    cout << endl;
    cin.getline(tempMessage, 100);
    s = tempMessage;
    return RemoveSpaces(s);
}

vector<int> TranslateKey(string eKey) {
    string temp = "";
    vector<int> keys;

    for (int i = 0; i < eKey.length();i++) {
        if (eKey[i] == ',') {
            keys.push_back(stoi(temp));
            temp = "";
        }
        else {
            if (i == eKey.length() - 1) {
                keys.push_back(stoi(temp + eKey[i]));
            }
            else temp += eKey[i];
        }
    }
    return keys;
}

vector<string> SplitString(string message, int blockSize) {
    int count = 0;
    string temp = "";
    vector<string> splitMessage;

    for (int i = 0; i < message.length();i++) {
        if (count != blockSize) {
            temp += message[i];
            count++;
        }
        else {
            splitMessage.push_back(temp);
            temp = message[i];
            count = 1;
        }

        if (i == message.length() - 1) {
            splitMessage.push_back(temp);
        }
    }
    return splitMessage;
}




int main() {
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVYWXZ";

    map<char, string> AlphabetToBinary = {
        {'A', "00001"},{'B', "00010"},{'C', "00011"},{'D', "00100"},{'E', "00101"},{'F', "00110"},{'G', "00111"},
        {'H', "01000"},{'I', "01001"},{'J', "01010"},{'K', "01011"},{'L', "01100"},{'M', "01101"},{'N', "01110"},
        {'O', "01111"},{'P', "10000"},{'Q', "10001"},{'R', "10010"},{'S', "10011"},{'T', "10100"},{'U', "10101"},
        {'V', "10110"},{'W', "10111"},{'X', "11000"},{'Y', "11001"},{'Z', "11010"}
    };


    string choice, whatDo;
    string backChoice;
    string message;

    //menu
MainMenu:

    system("CLS");
    cout << "Welcome To Nikk's Encryptor/Decryptor. I'm Nikk.\n\nPlease Select The Algorithm:\n  1.Polyalphabetic "
        "Substitution\n  2.Transposition\n  3.Stream\nSelect: ";
    cin >> choice;

    while (choice != "1" && choice != "2" && choice != "3") {
        cout << "Invalid Option. Please Try Again: ";
        cin >> choice;
    }
    int intChoice = stoi(choice);

    cout << "\nSelect An Option\n  1.Encrypt\n  2.Decrypt\nSelect: ";
    cin >> whatDo;

    while (whatDo != "1" && whatDo != "2") {
        cout << "Invalid Option. Please Try Again: ";
        cin >> whatDo;
    }

    cout << choice;

    int blockSize;
    vector<int> keys;
    vector<string> splitMessage;
    string eKey;
    string result;
    
    int intWhatDo = stoi(whatDo);

    string substitutionKey;
    string transpositionKey;
    bool isValid = false;

    switch (intChoice) {
    case 1:
        //POLYALPHABETIC SUBSTITUTION VIGENERE CIPHER

        //get message
        cout << "\nType The Message: ";
        message = GetMessage();

        //get block size
        cout << "Enter Block Size: ";
        cin >> blockSize;
        if (blockSize > message.length()) {
            blockSize = message.length();
            cout << "\nBlocksize Exceeds Message's Lenght. Blocksize Has Been Defaulted To: " << blockSize << endl<<endl;
        }

        //get key
        cout << "Enter Encryption Key (ints separated by commas). Keys Must Not Be More Than The Block Size: ";
        eKey = GetMessage();

        //translate key
        keys = TranslateKey(eKey);
        

        //split string
        splitMessage = SplitString(message, blockSize);

        if (intWhatDo == 1) {

            //encrypt
            result = "";
            for (auto x : splitMessage) {
                for (int i = 0; i < x.length();i++) {
                    int index = 0;
                    for (int y = 0;y < alphabet.length();y++) {
                        if (x[i] == alphabet[y]) {
                            index = y;
                        }
                    }
                    if (isdigit(x[i]) || ispunct(x[i])) {
                        result += x[i];
                    }else result += alphabet[(index + keys[i])%26];
                }
            }

            //show result
            cout << "\nHere Is Your Encrypted Message:" << endl << result <<"\n\n\n\n";
 
        }
        else {
            //decrypt
            result = "";
            for (auto x : splitMessage) {
                for (int i = 0; i < x.length();i++) {
                    int index = 0;
                    for (int y = 0;y < alphabet.length();y++) {
                        if (x[i] == alphabet[y]) {
                            index = y;
                        }
                    }

                    int c;
                    if (index - keys[i] < 0) {
                        c = 26 - (keys[i] - index);
                    }
                    else {
                        c = index - keys[i];
                    }
                    if (isdigit(x[i]) || ispunct(x[i])) {
                        result += x[i];
                    }else result += alphabet[c];
                }
            }
            //show result
            cout << "\nHere Is Your Decrypted Message:" << endl << result << "\n\n\n\n";
        }
        cout << "Go Back To Main Menu? (Y/N): ";
        cin >> backChoice;
        if (backChoice == "Y" || backChoice == "y") goto MainMenu;
        break;

    case 2:
        //Transposition Cipher
        //get message
        cout << "\nType The Message: ";
        message = GetMessage();

        //get block size
        cout << "Enter Block Size: ";
        cin >> blockSize;
        if (blockSize > message.length()) blockSize = message.length();

        //get key
        cout << "Enter Encryption Key (ints separated by commas). Keys Must Not Be More Than The Block Size: ";
        eKey = GetMessage();

        //translate key
        keys = TranslateKey(eKey);

        //split string
        splitMessage = SplitString(message, blockSize);


        result = "";
        for (auto x : splitMessage) {
            if (x.length() == blockSize) {
                for (int i = 0; i < x.length();i++) {
                    result += x[keys.at(i) - 1];
                }
            }
            else {
                result += x;
            }
        }
        cout << "\nHere Is Your Message: " << endl << result << endl<<endl;

        cout << "Go Back To Main Menu? (Y/N): ";
        cin >> backChoice;
        if (backChoice == "Y" || backChoice == "y") goto MainMenu;

        break;
    case 3:
        //Substitution - Transposition Stream Cipher
        //get message
        cout << "\nType The Message: ";
        message = GetMessage();

        //get substitution key
        //string substitutionKey;
        cout << "\nEnter Substitution Key (Must Be 5 Digit Binary eg. 10001): ";
        //bool isValid = false;
        do {
            cin >> substitutionKey;

            if (substitutionKey.length() == 5) isValid = true;

            for (auto x : substitutionKey) {
                if (x != '0' && x != '1') {
                    isValid = false;
                    break;
                }
            }

            if (!isValid) cout << "Invalid Key. Try Again: ";
        } while (!isValid);

        //get transposition key
        //string transpositionKey;
        cout << "\nEnter Transposition Key (Must Be 5 Digit Number eg 54321): ";
        isValid = false;
        do {
            cin >> transpositionKey;

            if (transpositionKey.length() == 5) isValid = true;

            for (auto x : transpositionKey) {
                if (!isdigit(x)) {
                    isValid = false;
                    break;
                }
            }

            if (!isValid) cout << "Invalid Key. Try Again: ";
        } while (!isValid);


        if (intWhatDo == 1) {
            //encrypt
            vector<string> convertedMessage;
            for (char x : message) {
                if (AlphabetToBinary.count(x) > 0) {
                    convertedMessage.push_back(AlphabetToBinary.find(x)->second);
                }
                else {
                    string s(1,x);
                    convertedMessage.push_back(s);
                }
            }

            //xor
            vector<string> xorMessage;
            string temp;
            for (auto x : convertedMessage) {
                temp = "";
                if (x.length() > 1) {
                    for (int i = 0; i < x.length();i++) {
                        if (x[i] == substitutionKey[i]) {
                            temp += "0";
                        }
                        else if (x[i] == '1' || substitutionKey[i] == '1') {
                            temp += "1";
                        }
                        else temp += "0";
                    }
                }
                else {
                    temp += x;
                }
                xorMessage.push_back(temp);
            }

            //transposition
            result = "";
            for (auto x : xorMessage) {
                if (x.length() > 1) {
                    for (int i = 1; i <= 5;i++) {
                        result += x[int(transpositionKey[i - 1]) - 49];
                    }
                }
                else result += x;
            }

            cout << endl << "The Encrypted Message Is: " << result<<endl<<endl;
            
        }
        else {
            //decrypt
            //split message
            vector<string> splitMessage;
            string temp = "";
            for (int i = 0; i < message.length();i++) {
                if (message[i] != '0' && message[i] != '1') {
                    temp = message[i];
                    splitMessage.push_back(temp);
                    temp = "";
                }
                else {
                    temp += message[i];
                    if (temp.length() == 5) {
                        splitMessage.push_back(temp);
                        temp = "";
                    }
                }
            }

            //transposition
            vector<string> transpositionedMessage;
            for (auto x : splitMessage) {
                temp = "";
                if (x.length() > 1) {
                    for (int i = 1; i <= 5;i++) {
                        temp += x[int(transpositionKey[i - 1]) - 49];
                    }
                }
                else temp += x;
                transpositionedMessage.push_back(temp);
            }

            //xor
            vector<string> xorMessage;
            for (auto x : transpositionedMessage) {
                temp = "";
                if (x.length() > 1) {
                    for (int i = 0; i < x.length();i++) {
                        if (x[i] == substitutionKey[i]) {
                            temp += "0";
                        }
                        else if (x[i] == '1' || substitutionKey[i] == '1') {
                            temp += "1";
                        }
                        else temp += "0";
                    }
                }
                else {
                    temp += x;
                }
                xorMessage.push_back(temp);
            }

            //convert back to text
            result = "";
            for (auto x : xorMessage) {
                if (x.length() > 1) {
                    for (auto it = AlphabetToBinary.begin(); it != AlphabetToBinary.end(); it++) {
                        if (it->second == x) {
                            result += it->first;
                        }
                    }
                }
                else result += x;
            }

            cout << endl << "The Decrypted Message Is: " << result << endl << endl;
        }
        cout << "Go Back To Main Menu? (Y/N): ";
        cin >> backChoice;
        if (backChoice == "Y" || backChoice == "y") goto MainMenu;

        break;
    case 4:

        return (0);
        break;
    }
    
}
