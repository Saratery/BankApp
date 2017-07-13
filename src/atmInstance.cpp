#include "atmInstance.h"

/*ATM_Instance::ATM_Instance() : 
note50(1000), note100(1000), note500(1000), note1000(500), note5000(500) 
{
	currentOverallNoteNumber = this->note50 + this->note100 
		+ this->note500 + this->note1000 + this->note5000;
}*/

ATM_Instance::ATM_Instance(uint16 n50, uint16 n100, uint16 n500, uint16 n1000, uint16 n5000)
{
	notes.note50 = n50;
	notes.note100 = n100;
	notes.note500 = n500;
	notes.note1000 = n1000;
	notes.note5000 = n5000;
	recalculateLimit();
}

ATM_Instance::~ATM_Instance()
{}

const uint16 ATM_Instance::getLimit() const
{
	return noteLimit;
}

uint16 ATM_Instance::getCurrentNoteNumber()
{
	return currentOverallNoteNumber;
}

uint16 ATM_Instance::getNote50Number() const 
{
	return notes.note50;
}

uint16 ATM_Instance::getNote100Number() const
{
	return notes.note100;
}

uint16 ATM_Instance::getNote500Number() const
{
	return notes.note500;
}

uint16 ATM_Instance::getNote1000Number() const
{
	return notes.note1000;
}

uint16 ATM_Instance::getNote5000Number() const
{
	return notes.note5000;
}

void ATM_Instance::setNote50(uint16 newNotes) 
{
	this->notes.note50 = newNotes;
	recalculateLimit();
}

void ATM_Instance::setNote100(uint16 newNotes) 
{
	this->notes.note100 = newNotes;
	recalculateLimit();
}

void ATM_Instance::setNote500(uint16 newNotes) 
{
	this->notes.note500 = newNotes;
	recalculateLimit();
}

void ATM_Instance::setNote1000(uint16 newNotes)
{
	this->notes.note1000 = newNotes;
	recalculateLimit();
}

void ATM_Instance::setNote5000(uint16 newNotes)
{
	this->notes.note5000 = newNotes;
	recalculateLimit();
}

void ATM_Instance::recalculateLimit()
{
	currentOverallNoteNumber = this->notes.note50 + this->notes.note100
		+ this->notes.note500 + this->notes.note1000 + this->notes.note5000;
}

std::ostream& operator<<(std::ostream& os, const ATM_Instance& m)
{
	os << m.getNote50Number() << ' ' << m.getNote100Number() << ' '
		<< m.getNote500Number() << ' ' << m.getNote1000Number() << ' ' 
		<< m.getNote5000Number() << '\n';
	return os;
}