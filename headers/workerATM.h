#ifndef WORKER_ATM_H
#define WORKER_ATM_H
#include <QObject>
#include "atmInstance.h"

class workerATM : public QObject
{
	Q_OBJECT
public:
	workerATM(uint16 n50 = 30, uint16 n100 = 30, uint16 n500 = 20, uint16 n1000 = 5, uint16 n5000 = 5);
	~workerATM();

public:
	uint16 getFreeAmountForNewNotes();
	uint16 getNote50Number() const;
	uint16 getNote100Number() const;
	uint16 getNote500Number() const;
	uint16 getNote1000Number() const;
	uint16 getNote5000Number() const;

public slots:
	void setNewValueOf50Notes(int);
	void setNewValueOf100Notes(int);
	void setNewValueOf500Notes(int);
	void setNewValueOf1000Notes(int);
	void setNewValueOf5000Notes(int);
	void checkFreeAmountForNewNotes();
	void checkAvailableMoney(int);
	void setNewValues();
	void checkCurrentMachineState();

signals:
	void enoughAmountForNewNotes(int);
	void notEnoughAmountForNewNotes();
	void enoughMoneyToWithdraw();
	void notEnoughMoneyToWithdraw(const char *);
	void sentNotesState(const char *);
	void requestedNote50NumberIsNotAvailable();
	void requestedNote100NumberIsNotAvailable();
	void requestedNote500NumberIsNotAvailable();
	void requestedNote1000NumberIsNotAvailable();
	void requestedNote5000NumberIsNotAvailable();

private:
	Notes tempNotes;
	uint16 tempLimit;
	const uint16 withdrawLimit = 20000;
	ATM_Instance * machine;
	void setRealNumbersOfNotes();
	void setNewNumbersOfNotes();
};
#endif