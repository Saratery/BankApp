#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include "atm.h"
#include "workerATM.h"
#include "pages.h"

class Controller : public QObject
{
public:
	Controller(ATM *, workerATM *, QObject *parent = 0);
	virtual ~Controller();

public slots:
	void goToWorkerCheckAvailableMoney(int);

signals:
	void toViewToSetNewPage(AbstractPage *);

private:
	ATM *view;
	workerATM *worker;
	AbstractPage *currentPage;
};

#endif