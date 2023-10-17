#include "Account.h"
#include"pch.h"

// 检验邮箱是否合法的函数
bool Account::IsEmailValid(const CString& email) {
    // Simple email validation for demonstration purposes
    // You can implement a more thorough email validation logic
    return email.Find('@') != -1;
}

//构造函数
Account::Account() {}

Account::Account(const CString& email, const CString& username, const CString& avatar, const CString& password, const CString& bio) {
    if (!IsEmailValid(email)) {
        // Handle invalid email (you can throw an exception or handle it as needed)
        throw std::invalid_argument("Invalid email address");
    }

    this->email = email;
    this->username = username;
    this->avatar = avatar;
    this->password = password;
    this->bio = bio;
}

// 析构函数
Account::~Account() {
    // Perform any necessary cleanup
}

// Getters
CString Account::getEmail() const {
    return email;
}

CString Account::getUsername() const {
    return username;
}

CString Account::getAvatar() const {
    return avatar;
}

CString Account::getPassword() const {
    return password;
}

CString Account::getBio() const {
    return bio;
}

// Setters
void Account::setEmail(const CString& newEmail) {
    email = newEmail;
}

void Account::setUsername(const CString& newUsername) {
    username = newUsername;
}

void Account::setAvatar(const CString& newAvatar) {
    avatar = newAvatar;
}

void Account::setPassword(const CString& newPassword) {
    password = newPassword;
}

void Account::setBio(const CString& newBio) {
    bio = newBio;
}

// Function to convert Account to CString
CString Account::ToCString() const {
    return CString(email + _T(",") + username + _T(",") + avatar + _T(",") + password + _T(",") + bio);
}

// Function to convert a valid CString back to an Account
Account Account::FromCString(const CString& cstring) {
    int pos = 0;
    CString email = cstring.Tokenize(_T(","), pos);
    CString username = cstring.Tokenize(_T(","), pos);
    CString avatar = cstring.Tokenize(_T(","), pos);
    CString password = cstring.Tokenize(_T(","), pos);
    CString bio = cstring.Tokenize(_T(","), pos);

    return Account(static_cast<const char*>(CStringA(email)), static_cast<const char*>(CStringA(username)), static_cast<const char*>(CStringA(avatar)), static_cast<const char*>(CStringA(password)), static_cast<const char*>(CStringA(bio)));
}

// Overload the assignment operator to assign a valid CString to an Account instance
Account& Account::operator=(const CString& cstring) {
    *this = FromCString(cstring);
    return *this;
}
