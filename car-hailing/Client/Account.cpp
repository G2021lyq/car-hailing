#include "pch.h"
#include "Account.h"
#include <regex>

// 构造函数
Account::Account() {}

Account::Account(const std::string& email, const std::string& username, const std::string& avatar, const std::string& password, const std::string& bio)
    : email(email), username(username), avatar(avatar), password(password), bio(bio) {}

//析构函数
Account::~Account() {
    
}

// Getters
std::string Account::getEmail() const {
    return email;
}

std::string Account::getUsername() const {
    return username;
}

std::string Account::getAvatar() const {
    return avatar;
}

std::string Account::getPassword() const {
    return password;
}

std::string Account::getBio() const {
    return bio;
}

// Setters
void Account::setEmail(const std::string& newEmail) {
    email = newEmail;
}

void Account::setUsername(const std::string& newUsername) {
    username = newUsername;
}

void Account::setAvatar(const std::string& newAvatar) {
    avatar = newAvatar;
}

void Account::setPassword(const std::string& newPassword) {
    password = newPassword;
}

void Account::setBio(const std::string& newBio) {
    bio = newBio;
}

// Convert Account to CString
CString Account::ToCString() const {
    CString cstring;
    cstring.Format(_T("%s,%s,%s,%s,%s"), email.c_str(), username.c_str(), avatar.c_str(), password.c_str(), bio.c_str());
    return cstring;
}

// Convert CString to Account
Account Account::FromCString(const CString& cstring) {
    Account account;
    CString delimiter = _T(",");
    int start = 0;
    int end = cstring.Find(delimiter);
    int index = 0;

    while (end != -1) {
        CString token = cstring.Mid(start, end - start);
        std::string tokenStr(token.GetString());

        switch (index) {
        case 0:
            account.email = tokenStr;
            break;
        case 1:
            account.username = tokenStr;
            break;
        case 2:
            account.avatar = tokenStr;
            break;
        case 3:
            account.password = tokenStr;
            break;
        case 4:
            account.bio = tokenStr;
            break;
        }

        start = end + delimiter.GetLength();
        end = cstring.Find(delimiter, start);
        index++;
    }

    // Retrieve the last token (bio)
    CString token = cstring.Mid(start);
    account.bio = std::string(token.GetString());

    return account;
}

// Overload assignment operator to assign from CString to Account
Account& Account::operator=(const CString& cstring) {
    *this = FromCString(cstring);
    return *this;
}


bool Account::IsEmailValid(const std::string& email) {
    // Use a simple regular expression to check email validity
    // This is a basic example and may not cover all cases
    std::regex emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return std::regex_match(email, emailRegex);
}

// Constructors
Account::Account(const std::string& email, const std::string& username, const std::string& avatar, const std::string& password, const std::string& bio) {
    // Validate email
    if (!IsEmailValid(email)) {
        throw InvalidEmailException();
    }

    this->email = email;
    this->username = username;
    this->avatar = avatar;
    this->password = password;
    this->bio = bio;
}