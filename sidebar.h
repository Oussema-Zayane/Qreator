#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QPushButton;
QT_END_NAMESPACE

class SideBar : public QWidget
{
    Q_OBJECT

public:
    explicit SideBar(QWidget *parent = nullptr);

signals:
    void menuClicked(const QString &menuName);

private slots:
    void onClientsClicked();
    void onEmployesClicked();
    void onProjetsClicked();
    void onFinancesClicked();

private:
    void setupUI();

    QVBoxLayout *mainLayout;
    QPushButton *clientsBtn;
    QPushButton *employesBtn;
    QPushButton *projetsBtn;
    QPushButton *financesBtn;
};

#endif // SIDEBAR_H
