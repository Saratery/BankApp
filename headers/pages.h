#ifndef PAGES_H
#define PAGES_H
#include <QObject>
#include <QSpinBox>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>

class AbstractPage : public QWidget
{
	Q_OBJECT
public:
	AbstractPage(QWidget *parent = 0);
	virtual ~AbstractPage();
	QGridLayout *mainLayout;

	QLabel *titleLabel;
	QWidget *parent;
	QPushButton *finishButton;

	QPushButton *withdrawalButton;
	QPushButton *depositionButton;

	QLineEdit *moneyAmountLine;
	QPushButton *largeDenomButton;
	QPushButton *smallDenomButton;
	QPushButton *detailedExchangeButton;

	QPushButton *nextButton;
	QSpinBox *note50SB;
	QSpinBox *note100SB;
	QSpinBox *note500SB;
	QSpinBox *note1000SB;
	QSpinBox *note5000SB;
	QLabel *note50L;
	QLabel *note100L;
	QLabel *note500L;
	QLabel *note1000L;
	QLabel *note5000L;
	
	QPushButton *closeButton;
signals:
	void finished();

};

class StartPage : public AbstractPage
{
public:
	StartPage(QWidget *parent = 0);
	virtual ~StartPage();

};

class MoneyWithdrawalSumPage : public AbstractPage
{
public:
	MoneyWithdrawalSumPage(QWidget *parent = 0);
	virtual ~MoneyWithdrawalSumPage();
};

class MoneyWithdrawalChoicePage : public AbstractPage
{
public:
	MoneyWithdrawalChoicePage(QWidget *parent = 0);
	virtual ~MoneyWithdrawalChoicePage();
};

class MoneyWithdrawalExchangePage : public AbstractPage
{
public: 
	MoneyWithdrawalExchangePage(int, QWidget *parent = 0);
	virtual ~MoneyWithdrawalExchangePage();
};

class MoneyDepositionPage : public AbstractPage
{
public:
	MoneyDepositionPage(int, QWidget *parent = 0);
	virtual ~MoneyDepositionPage();
};

class MoneyDepositionIsCanceledPage : public AbstractPage
{
public:
	MoneyDepositionIsCanceledPage(QWidget *parent = 0);
	virtual ~MoneyDepositionIsCanceledPage();
};

class FinalPage : public AbstractPage
{
public:
	FinalPage(QWidget *parent = 0);
	virtual ~FinalPage();
};

#endif