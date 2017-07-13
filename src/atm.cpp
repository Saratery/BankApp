#include "atm.h"

ATM::ATM() : QDialog()
{

	stack = new QStackedWidget();
	page = new StartPage(stack);
	stack->addWidget(page);

	setSettings(page);

	layout = new QGridLayout(this);
	int nWidth = 300;
	int nHeight = 200;
	this->resize(nWidth, nHeight);

	QPushButton *cancelButton = new QPushButton(tr("Retrieve the card"));
	cancelButton->setMinimumSize(150, 20);
	cancelButton->setMaximumSize(150, 20);
	QPushButton *stateButton = new QPushButton(tr("Check the ATM state"));
	stateButton->setMaximumSize(150, 20);

	layout->addWidget(stack, 0, 0, 2, 3);
	layout->addWidget(cancelButton, 2, 1, 1, 1);
	layout->addWidget(stateButton, 3, 1, 1, 1);

	connect(cancelButton, &QPushButton::clicked, this, &ATM::finishService);
	connect(stateButton, &QPushButton::clicked, this, &ATM::requestCurrentMachineState);
	connect(this, &ATM::signalGoToNextPage, this, &ATM::setAnotherPage);
}

ATM::~ATM()
{
	delete stack;
}

void ATM::setAnotherPage(AbstractPage * newPage)
{
	stack->addWidget(newPage);
	stack->setCurrentIndex(stack->currentIndex() + 1);
	page = newPage;
	setSettings(page);
}

void ATM::setSettings(AbstractPage * page)
{
	if (dynamic_cast<StartPage*>(page)) {
		connect(page->withdrawalButton, &QPushButton::clicked, this, &ATM::setWithdrawalSumPage);
		connect(page->depositionButton, &QPushButton::clicked, this, &ATM::checkIfMachineSpaceIsAvailable);
	}

	if (dynamic_cast<MoneyWithdrawalSumPage*>(page)) {
		connect(page->nextButton, &QPushButton::clicked, this, &ATM::checkIfWithdrawalSumIsCorrect);
	}

	if (dynamic_cast<MoneyWithdrawalChoicePage*>(page)) {
		connect(page->largeDenomButton, &QPushButton::clicked, this, &ATM::performLargeDenomWithdrawalExchange);
		connect(page->largeDenomButton, &QPushButton::clicked, this, &ATM::setFinalPage);
		connect(page->detailedExchangeButton, &QPushButton::clicked, this, &ATM::setWithdrawalExchangePage);
	}

	if (dynamic_cast<MoneyDepositionPage*>(page)) {
		connect(page->nextButton, &QPushButton::clicked, this, &ATM::checkIfDepositionSumIsCorrect);
	}

	if (dynamic_cast<MoneyWithdrawalExchangePage*>(page)) {
		connect(page->note50SB, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ATM::sendNewValueNote50);
		connect(page->note100SB, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ATM::sendNewValueNote100);
		connect(page->note500SB, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ATM::sendNewValueNote500);
		connect(page->note1000SB, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ATM::sendNewValueNote1000);
		connect(page->note5000SB, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ATM::sendNewValueNote5000);
		connect(page->nextButton, &QPushButton::clicked, this, &ATM::checkIfWithdrawalFinalSumIsCorrect);
	}

	if (dynamic_cast<FinalPage*>(page)) {
		connect(page->closeButton, &QPushButton::clicked, this, &ATM::finishService);
	}
}

void ATM::checkIfMachineSpaceIsAvailable()
{
	emit checkAvailableSpaceInMachine();
}

void ATM::setDepositionIsCanceledPage()
{
	emit signalGoToNextPage(new MoneyDepositionIsCanceledPage(stack));
}

void ATM::setDepositionPage(int number)
{
	availableDepositionNotesNumber = number;
	emit signalGoToNextPage(new MoneyDepositionPage(availableDepositionNotesNumber, stack));
}

void ATM::checkIfDepositionSumIsCorrect()
{
	int userDepositionNotesNumber = page->note50SB->text().toInt() + 
		+ page->note100SB->text().toInt() +
		+ page->note500SB->text().toInt() + 
		+ page->note1000SB->text().toInt() + 
		+ page->note5000SB->text().toInt();
	
	if (userDepositionNotesNumber <= availableDepositionNotesNumber) {
		emit sendNew50NotesToMachine(page->note50SB->text().toInt());
		emit sendNew100NotesToMachine(page->note100SB->text().toInt());
		emit sendNew500NotesToMachine(page->note500SB->text().toInt());
		emit sendNew1000NotesToMachine(page->note1000SB->text().toInt());
		emit sendNew5000NotesToMachine(page->note5000SB->text().toInt());
		emit signalGoToNextPage(new FinalPage(stack));
		emit signalToPerformOperation();
	}
	else {
		showWarning("The number of notes is too big");
	}
}

void ATM::setWithdrawalSumPage()
{
	emit signalGoToNextPage(new MoneyWithdrawalSumPage(stack));
}

void ATM::setWithdrawalChoicePage()
{
	userMoney = page->moneyAmountLine->text().toInt();
	emit signalGoToNextPage(new MoneyWithdrawalChoicePage(stack));
}

void ATM::setWithdrawalExchangePage()
{
	emit signalGoToNextPage(new MoneyWithdrawalExchangePage(userMoney, stack));
}

void ATM::checkIfWithdrawalSumIsCorrect()
{
	if (page->moneyAmountLine->text().size() == 0 
		|| page->moneyAmountLine->text().toInt() < 0) {
		showWarning("The sum is invalid");
	}
	emit checkIfWithDrawalSumIsAvailabale(page->moneyAmountLine->text().toInt());
}

void ATM::withdrawalSumIsNotCorrect(const char *str)
{
	char actual_str[1000];
	strcpy(actual_str, "The sum is not available at this moment.\nAvailable denominations:\n");
	strcat(actual_str, str);
	showInformation(actual_str);
}

void ATM::performLargeDenomWithdrawalExchange()
{
	emit signalToPerformOperation();
}

void ATM::setFinalPage()
{
	emit signalGoToNextPage(new FinalPage(stack));
}

void ATM::finishService()
{
	this->reject();
}

void ATM::requestCurrentMachineState()
{
	emit signalRequestCurrentMachineState();
}

void ATM::showCurrentMachineState(const char * str)
{
	char actual_str[1000];
	strcpy(actual_str, "Current state: ");
	strcat(actual_str, str);
	showInformation(actual_str);
}

void ATM::sendNewValueNote50(int value)
{
	emit sendNew50NotesToMachine(value);
}

void ATM::sendNewValueNote100(int value)
{
	emit sendNew100NotesToMachine(value);
}

void ATM::sendNewValueNote500(int value)
{
	emit sendNew500NotesToMachine(value);
}

void ATM::sendNewValueNote1000(int value)
{
	emit sendNew1000NotesToMachine(value);
}

void ATM::sendNewValueNote5000(int value)
{
	emit sendNew5000NotesToMachine(value);
}

void ATM::showNote50IsNotAvailable()
{
	page->note50SB->setValue(0);
	showWarning("The requested number of 50 Ruble notes is not available");
}

void ATM::showNote100IsNotAvailable()
{
	page->note100SB->setValue(0);
	showWarning("The requested number of 100 Ruble notes is not available");
}

void ATM::showNote500IsNotAvailable()
{
	page->note500SB->setValue(0);
	showWarning("The requested number of 500 Ruble notes is not available");
}

void ATM::showNote1000IsNotAvailable()
{
	page->note1000SB->setValue(0);
	showWarning("The requested number of 1000 Ruble notes is not available");
}

void ATM::showNote5000IsNotAvailable()
{
	page->note5000SB->setValue(0);
	showWarning("The requested number of 5000 Ruble notes is not available");
}

void ATM::showWarning(const char * str)
{
	QMessageBox msgBox(QMessageBox::Warning,
		tr("Warning"),
		tr(str)
		);
	msgBox.exec();
}

void ATM::showInformation(const char * str)
{
	QMessageBox msgBox(QMessageBox::Information,
		tr("Information"),
		tr(str)
		);
	msgBox.exec();
}

void ATM::checkIfWithdrawalFinalSumIsCorrect()
{
	int userWithdrawalNotesNumber = page->note50SB->text().toInt() * 50 + 
		+ page->note100SB->text().toInt() * 100 + 
		+ page->note500SB->text().toInt() * 500 +
		+ page->note1000SB->text().toInt() * 1000 +
		+ page->note5000SB->text().toInt() * 5000;

	if (userWithdrawalNotesNumber == userMoney) {
		emit sendNew50NotesToMachine(-page->note50SB->text().toInt());
		emit sendNew100NotesToMachine(-page->note100SB->text().toInt());
		emit sendNew500NotesToMachine(-page->note500SB->text().toInt());
		emit sendNew1000NotesToMachine(-page->note1000SB->text().toInt());
		emit sendNew5000NotesToMachine(-page->note5000SB->text().toInt());
		emit signalToPerformOperation();
		emit signalGoToNextPage(new FinalPage(stack));
	}
	else {
		showWarning("The sum does not coincide with requested");
	}
}