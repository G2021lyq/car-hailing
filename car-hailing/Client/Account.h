#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <atlstr.h>  // ����CString�����ͷ�ļ�
#include <stdexcept>  // ����std::invalid_argument



class Account {
private:
    CString email;
    CString username;
    CString avatar;
    CString password;
    CString bio;

    // ���������Ƿ�Ϸ��ĺ���
    bool IsEmailValid(const CString& email);

public:
    // ���캯��
    Account();
    Account(const CString& email, const CString& username, const CString& avatar, const CString& password, const CString& bio);

    // ��������
    ~Account();

    //  getters, setters
    CString getEmail() const;
    CString getUsername() const;
    CString getAvatar() const;
    CString getPassword() const;
    CString getBio() const;

    void setEmail(const CString& email);
    void setUsername(const CString& username);
    void setAvatar(const CString& avatar);
    void setPassword(const CString& password);
    void setBio(const CString& bio);

    // Function to convert Account to CString
    CString ToCString() const;

    // Function to convert a valid CString back to an Account
    static Account FromCString(const CString& cstring);

    // Overload the assignment operator to assign a valid CString to an Account instance
    Account& operator=(const CString& cstring);
};


#endif // ACCOUNT_H