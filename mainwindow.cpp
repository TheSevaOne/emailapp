#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    client_ = NULL;
    connect(ui->pushButtonSend, SIGNAL(clicked(bool)), this, SLOT(sendEmail()));
    connect(ui->pushButtonClear, SIGNAL(clicked(bool)), this, SLOT(clearFields()));
}

MainWindow::~MainWindow()
{
    client_->deleteLater();
    delete ui;
}

void MainWindow::sendEmail()
{

    Email email = createEmail();

    // Создаем клиента
    client_ = new SMTPClient(ui->lineEditHost->text(),
                             ui->spinBoxPort->value());


    connect(client_, SIGNAL(status(Status::e, QString)),
            this, SLOT(onStatus(Status::e, QString)), Qt::UniqueConnection);

    // Посылаем письмо
    client_->sendEmail(email);
}

Email MainWindow::createEmail()
{
    //заголовки,тема,адрес
    EmailAddress credentials(ui->lineEditEmailCredentials->text(),
                             ui->lineEditPasswordCredentials->text());
      EmailAddress from(ui->lineEditEmailFrom->text());
    EmailAddress to(ui->lineEditEmailTo->text());


    Email email(credentials,
                from,
                to,
                ui->lineEditSubject->text(),
                ui->textEditContent->toPlainText());

    return email;
}


void MainWindow::clearFields()
{
    ui->lineEditEmailCredentials->clear();
    ui->lineEditPasswordCredentials->clear();
    ui->lineEditEmailFrom->clear();
    ui->lineEditEmailTo->clear();
    ui->lineEditSubject->clear();
    ui->textEditContent->clear();
}


void MainWindow::onStatus(Status::e status, QString errorMessage)
{

    switch (status)
    {
    case Status::Success:
        QMessageBox::information(NULL, tr("OK"), tr("ОТПРАВЛЕНО!!!!!!!!!!!"));
        break;
    case Status::Failed:
    {
        QMessageBox::warning(NULL, tr("error"), tr("НЕ МОГУ ОТПРАВИТЬ !"));
        qCritical() << errorMessage;
    }
        break;
    default:
        break;
    }


    client_->deleteLater();
}

