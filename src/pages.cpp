#include "pages.h"

AbstractPage::AbstractPage(QWidget *parent)
{
	titleLabel = new QLabel();
	mainLayout = new QGridLayout(this);
}

AbstractPage::~AbstractPage()
{
	delete titleLabel;
	delete mainLayout;
	//delete withdrawalButton;
	//delete depositionButton;
	//delete moneyAmountLine;
	//delete largeDenomButton;
	//delete smallDenomButton;
	//delete detailedExchangeButton;
	//delete depositAmountLine;
	//delete nextButton;
	//delete closeButton;
}

StartPage::StartPage(QWidget *parent)
{
	titleLabel->setText("Please select a transaction");
	QFont titleFont("Helvetica", 11);
	titleLabel->setFont(titleFont);
	titleLabel->setMinimumSize(200, 40);

	withdrawalButton = new QPushButton("Withdraw money");
	withdrawalButton->setMinimumSize(170, 40);

	depositionButton = new QPushButton("Deposit money");
	depositionButton->setMinimumSize(170, 40);

	mainLayout->addWidget(titleLabel, 0, 0, 2, 4, Qt::AlignCenter);
	mainLayout->addWidget(withdrawalButton, 2, 1, Qt::AlignCenter);
	mainLayout->addWidget(depositionButton, 2, 2, Qt::AlignCenter);
}

StartPage::~StartPage()
{
	delete withdrawalButton;
	delete depositionButton;
}

MoneyWithdrawalSumPage::MoneyWithdrawalSumPage(QWidget *parent)
{
	titleLabel->setText("Enter the amount of money you want to withdraw.\nThe limit is 20000 Rubles");
	QFont titleFont("Helvetica", 11);
	titleLabel->setFont(titleFont);

	moneyAmountLine = new QLineEdit();
	moneyAmountLine->setMinimumSize(70, 20);
	moneyAmountLine->setMaximumSize(150, 20);

	nextButton = new QPushButton("Continue");
	nextButton->setMinimumSize(70, 20);

	mainLayout->addWidget(titleLabel, 0, 0, 2, 3, Qt::AlignCenter);
	mainLayout->addWidget(moneyAmountLine, 2, 0, 2, 3, Qt::AlignCenter);
	mainLayout->addWidget(nextButton, 4, 0, 2, 3, Qt::AlignCenter);
}

MoneyWithdrawalSumPage::~MoneyWithdrawalSumPage()
{
	delete moneyAmountLine;
}

MoneyWithdrawalChoicePage::MoneyWithdrawalChoicePage(QWidget *parent)
{
	titleLabel->setText("Choose the preferable note denominations");
	QFont titleFont("Helvetica", 11);
	titleLabel->setFont(titleFont);

	largeDenomButton = new QPushButton("Get high-denomination bills");
	largeDenomButton->setMinimumSize(170, 40);

	detailedExchangeButton = new QPushButton("Go to detailed exchange");
	detailedExchangeButton->setMinimumSize(170, 40);

	mainLayout->addWidget(titleLabel, 0, 0, 2, 2, Qt::AlignCenter);
	mainLayout->addWidget(largeDenomButton, 2, 0, Qt::AlignRight);
	mainLayout->addWidget(detailedExchangeButton, 2, 1, Qt::AlignLeft);
}

MoneyWithdrawalChoicePage::~MoneyWithdrawalChoicePage()
{
	delete largeDenomButton;
	delete detailedExchangeButton;
}

MoneyWithdrawalExchangePage::MoneyWithdrawalExchangePage(int sum, QWidget *parent)
{
	QString str = "The requested sum: " + QString::number(sum);
	titleLabel->setText(str);
	QFont titleFont("Helvetica", 11);
	titleLabel->setFont(titleFont);

	note50SB = new QSpinBox();
	note50SB->setMinimumSize(60, 20);
	note100SB = new QSpinBox();
	note100SB->setMinimumSize(60, 20);
	note500SB = new QSpinBox();
	note500SB->setMinimumSize(60, 20);
	note1000SB = new QSpinBox();
	note1000SB->setMinimumSize(60, 20);
	note5000SB = new QSpinBox();
	note5000SB->setMinimumSize(60, 20);
	note50L = new QLabel("50 Rubles");
	note100L = new QLabel("100 Rubles");
	note500L = new QLabel("500 Rubles");
	note1000L = new QLabel("1000 Rubles");
	note5000L = new QLabel("5000 Rubles");

	nextButton = new QPushButton("Continue");
	nextButton->setMinimumSize(95, 50);

	mainLayout->addWidget(titleLabel, 0, 0, 2, 4, Qt::AlignCenter);
	mainLayout->addWidget(note50L, 2, 0, 1, 2, Qt::AlignCenter);
	mainLayout->addWidget(note100L, 4, 0, 1, 2, Qt::AlignCenter);
	mainLayout->addWidget(note500L, 6, 0, 1, 2, Qt::AlignCenter);
	mainLayout->addWidget(note1000L, 2, 2, 1, 2, Qt::AlignCenter);
	mainLayout->addWidget(note5000L, 4, 2, 1, 2, Qt::AlignCenter);
	mainLayout->addWidget(note50SB, 3, 0, 1, 2, Qt::AlignCenter);
	mainLayout->addWidget(note100SB, 5, 0, 1, 2, Qt::AlignCenter);
	mainLayout->addWidget(note500SB, 7, 0, 1, 2, Qt::AlignCenter);
	mainLayout->addWidget(note1000SB, 3, 2, 1, 2, Qt::AlignCenter);
	mainLayout->addWidget(note5000SB, 5, 2, 1, 2, Qt::AlignCenter);
	mainLayout->addWidget(nextButton, 8, 0, 2, 4, Qt::AlignCenter);
}

MoneyWithdrawalExchangePage::~MoneyWithdrawalExchangePage()
{
	delete note50SB;
	delete note100SB;
	delete note500SB;
	delete note1000SB;
	delete note5000SB;
	delete note50L;
	delete note100L;
	delete note500L;
	delete note1000L;
	delete note5000L;
	delete nextButton;
}

MoneyDepositionPage::MoneyDepositionPage(int number, QWidget *parent)
{
	if (number > 20) {
		number = 20;
	}
	QString str = "Insert no more than " + QString::number(number) + " bills in the machine";
	titleLabel->setText(str);
	QFont titleFont("Helvetica", 11);
	titleLabel->setFont(titleFont);

	note50SB = new QSpinBox();
	note50SB->setMinimumSize(60, 20);
	note100SB = new QSpinBox();
	note100SB->setMinimumSize(60, 20);
	note500SB = new QSpinBox();
	note500SB->setMinimumSize(60, 20);
	note1000SB = new QSpinBox();
	note1000SB->setMinimumSize(60, 20);
	note5000SB = new QSpinBox();
	note5000SB->setMinimumSize(60, 20);
	note50L = new QLabel("50 Rubles");
	note100L = new QLabel("100 Rubles");
	note500L = new QLabel("500 Rubles");
	note1000L = new QLabel("1000 Rubles");
	note5000L = new QLabel("5000 Rubles");

	nextButton = new QPushButton("Continue");
	nextButton->setMinimumSize(95, 50);

	mainLayout->addWidget(titleLabel, 0, 0, 2, 4, Qt::AlignCenter);
	mainLayout->addWidget(note50L, 2, 0, 1, 2, Qt::AlignCenter);
	mainLayout->addWidget(note100L, 4, 0, 1, 2, Qt::AlignCenter);
	mainLayout->addWidget(note500L, 6, 0, 1, 2, Qt::AlignCenter);
	mainLayout->addWidget(note1000L, 2, 2, 1, 2, Qt::AlignCenter);
	mainLayout->addWidget(note5000L, 4, 2, 1, 2, Qt::AlignCenter);
	mainLayout->addWidget(note50SB, 3, 0, 1, 2, Qt::AlignCenter);
	mainLayout->addWidget(note100SB, 5, 0, 1, 2, Qt::AlignCenter);
	mainLayout->addWidget(note500SB, 7, 0, 1, 2, Qt::AlignCenter);
	mainLayout->addWidget(note1000SB, 3, 2, 1, 2, Qt::AlignCenter);
	mainLayout->addWidget(note5000SB, 5, 2, 1, 2, Qt::AlignCenter);
	mainLayout->addWidget(nextButton, 8, 0, 2, 4, Qt::AlignCenter);
}

MoneyDepositionPage::~MoneyDepositionPage()
{
	delete note50SB;
	delete note100SB;
	delete note500SB;
	delete note1000SB;
	delete note5000SB;
	delete note50L;
	delete note100L;
	delete note500L;
	delete note1000L;
	delete note5000L;
	delete nextButton;
}

MoneyDepositionIsCanceledPage::MoneyDepositionIsCanceledPage(QWidget *parent)
{
	titleLabel->setText("Money deposition is not currently available");
	QFont titleFont("Helvetica", 11);
	titleLabel->setFont(titleFont);

	mainLayout->addWidget(titleLabel, 0, 0, 2, 4, Qt::AlignCenter);
}

MoneyDepositionIsCanceledPage::~MoneyDepositionIsCanceledPage()
{}


FinalPage::FinalPage(QWidget *parent)
{
	titleLabel->setText("Please, take your card");
	QFont titleFont("Helvetica", 11);
	titleLabel->setFont(titleFont);

	closeButton = new QPushButton("Ok");
	closeButton->setMinimumSize(95, 50);

	mainLayout->addWidget(titleLabel, 0, 0, 2, 4, Qt::AlignCenter);
	mainLayout->addWidget(closeButton, 2, 0, 2, 4, Qt::AlignCenter);
}

FinalPage::~FinalPage()
{
	delete closeButton;
}