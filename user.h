#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User();
    User(int id, const QString& login, const QString& password, const QString& role);

    int getId() const { return m_id; }
    void setId(int id) { m_id = id; }

    QString getLogin() const { return m_login; }
    void setLogin(const QString& login) { m_login = login; }

    QString getPassword() const { return m_password; }
    void setPassword(const QString& password) { m_password = password; }

    QString getRole() const { return m_role; }
    void setRole(const QString& role) { m_role = role; }

    bool isManager() const { return m_role == "MANAGER"; }
    bool isEmployee() const { return m_role == "EMPLOYEE"; }

private:
    int m_id;
    QString m_login;
    QString m_password;
    QString m_role;
};

#endif // USER_H
