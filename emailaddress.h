#ifndef EMAILADDRESS_H
#define EMAILADDRESS_H

#include <QString>


class EmailAddress
{
public:
    EmailAddress();
    EmailAddress(QString address, QString password = "");

    QString address() const;
    void setAddress(const QString &address);

    QString password() const;
    void setPassword(const QString &password);

private:
    QString address_;
    QString password_;
};

#endif // EMAILADDRESS_H
