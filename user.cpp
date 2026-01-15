#include "user.h"

User::User()
    : m_id(-1)
{
}

User::User(int id, const QString& login, const QString& password, const QString& role)
    : m_id(id)
    , m_login(login)
    , m_password(password)
    , m_role(role)
{
}
