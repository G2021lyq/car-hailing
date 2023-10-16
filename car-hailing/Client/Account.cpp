#include "Account.h"

// Constructors
Account::Account() {}

Account::Account(const std::string& email, const std::string& username, const std::string& avatar, const std::string& password, const std::string& bio)
    : email(email), username(username), avatar(avatar), password(password), bio(bio) {}

// Destructor
Account::~Account() {
    // Perform any necessary cleanup
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

// Function to convert Account to CString
CString Account::ToCString() const {
    CString cstr;
    cstr.Format(_T("%s,%s,%s,%s,%s"), CString(email.c_str()), CString(username.c_str()), CString(avatar.c_str()), CString(password.c_str()), CString(bio.c_str()));
    return cstr;
}

// Function to convert a valid CString back to an Account
    Account Account::FromCString(const CString& cstring) {
    CString email, username, avatar, password, bio;
    int pos = 0;
    email = cstring.Tokenize(_T(","), pos);
    username = cstring.Tokenize(_T(","), pos);
    avatar = cstring.Tokenize(_T(","), pos);
    password = cstring.Tokenize(_T(","), pos);
    bio = cstring.Tokenize(_T(","), pos);

    return Account(email.GetString(), username.GetString(), avatar.GetString(), password.GetString(), bio.GetString());
}

// Overload the assignment operator to assign a valid CString to an Account instance
Account& Account::operator=(const CString& cstring) {
    *this = FromCString(cstring);
    return *this;
}

