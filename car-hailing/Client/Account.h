#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <atlstr.h>  // 包含CString所需的头文件
#include <stdexcept>  // 包含std::invalid_argument

class Account {
private:
    std::string email;
    std::string username;
    std::string avatar;
    std::string password;
    std::string bio;

    // Function to check if the email is valid
    bool IsEmailValid(const std::string& email);

public:
    // Constructors
    Account();
    Account(const std::string& email, const std::string& username, const std::string& avatar, const std::string& password, const std::string& bio);

    // Destructor
    ~Account();

    // Other member functions (getters, setters, etc.)
    std::string getEmail() const;
    std::string getUsername() const;
    std::string getAvatar() const;
    std::string getPassword() const;
    std::string getBio() const;

    void setEmail(const std::string& email);
    void setUsername(const std::string& username);
    void setAvatar(const std::string& avatar);
    void setPassword(const std::string& password);
    void setBio(const std::string& bio);

    // Function to convert Account to CString
    CString ToCString() const;

    // Function to convert a valid CString back to an Account
    static Account FromCString(const CString& cstring);

    // Overload the assignment operator to assign a valid CString to an Account instance
    Account& operator=(const CString& cstring);
};

#endif // ACCOUNT_H
