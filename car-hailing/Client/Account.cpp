#include "pch.h"
#include "Account.h"


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

Account Account::FromCString(const CString& cstring) {
	// Assuming that the elements in the CString are separated by commas
	int pos1 = cstring.Find(_T(","), 0); // Find the first comma
	int pos2 = cstring.Find(_T(","), pos1 + 1); // Find the second comma
	int pos3 = cstring.Find(_T(","), pos2 + 1); // Find the third comma
	int pos4 = cstring.Find(_T(","), pos3 + 1); // Find the fourth comma

	// Extract individual values from the CString
	CString email = cstring.Mid(0, pos1); // Email is from the beginning to the first comma
	CString username = cstring.Mid(pos1 + 1, pos2 - pos1 - 1); // Username is between the first and second comma
	CString avatar = cstring.Mid(pos2 + 1, pos3 - pos2 - 1); // Avatar is between the second and third comma
	CString password = cstring.Mid(pos3 + 1, pos4 - pos3 - 1); // Password is between the third and fourth comma
	CString bio = cstring.Mid(pos4 + 1); // Bio is after the fourth comma

	// Create an Account object with the extracted values
	return Account(email, username, avatar, password, bio);
}


// Overload the assignment operator to assign a valid CString to an Account instance
Account& Account::operator=(const CString& cstring) {
	*this = FromCString(cstring);
	return *this;
}
