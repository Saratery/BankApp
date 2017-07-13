#ifndef ATM_H
#define ATM_H

#include <QWidget>
#include <QDialog>
#include <QMessageBox>
#include <QtWidgets/QMainWindow>
#include <QDesktopWidget>
//#include "ui_atm.h"
#include "pages.h"

class ATM : public QDialog
{
	Q_OBJECT

public:
	ATM();
	~ATM();
	AbstractPage *page;

public slots:
	void setAnotherPage(AbstractPage *);
	void setWithdrawalSumPage();
	void setWithdrawalChoicePage();
	void setDepositionPage(int);
	void setDepositionIsCanceledPage();
	void setFinalPage();
	void setWithdrawalExchangePage();
	void checkIfWithdrawalSumIsCorrect();
	void withdrawalSumIsNotCorrect(const char *);
	void checkIfDepositionSumIsCorrect();
	void checkIfWithdrawalFinalSumIsCorrect();
	void checkIfMachineSpaceIsAvailable();
	void finishService();
	void showCurrentMachineState(const char *);
	void requestCurrentMachineState();
	void sendNewValueNote50(int);
	void sendNewValueNote100(int);
	void sendNewValueNote500(int);
	void sendNewValueNote1000(int);
	void sendNewValueNote5000(int);
	void showNote50IsNotAvailable();
	void showNote100IsNotAvailable();
	void showNote500IsNotAvailable();
	void showNote1000IsNotAvailable();
	void showNote5000IsNotAvailable();
	void performLargeDenomWithdrawalExchange();

signals:
	void signalGoToNextPage(AbstractPage *);
	void checkIfWithDrawalSumIsAvailabale(int);
	void checkAvailableSpaceInMachine();
	void sendNew50NotesToMachine(int);
	void sendNew100NotesToMachine(int);
	void sendNew500NotesToMachine(int);
	void sendNew1000NotesToMachine(int);
	void sendNew5000NotesToMachine(int);
	void signalToPerformOperation();
	void signalRequestCurrentMachineState();

private:
	void setSettings(AbstractPage *);
	QGridLayout *layout;
	QStackedWidget *stack;
	AbstractPage *startPage;
	int availableDepositionNotesNumber;
	int userMoney;
	void showWarning(const char *);
	void showInformation(const char *);
};

#endif // ATM_H
