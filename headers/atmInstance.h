#ifndef ATM_INSTANCE_H
#define ATM_INSTANCE_H
#include <iostream>

using uint16 = unsigned __int16;

struct Notes
{
	uint16 note50;
	uint16 note100;
	uint16 note500;
	uint16 note1000;
	uint16 note5000;
};

class ATM_Instance
{
private:
	Notes notes;

	uint16 currentOverallNoteNumber;
	const uint16 noteLimit = 100;
	void recalculateLimit();

public:
	//ATM_Instance();
	ATM_Instance(uint16, uint16, uint16, uint16, uint16);
	~ATM_Instance();
	ATM_Instance(const ATM_Instance&) = delete;
	ATM_Instance& operator=(const ATM_Instance&) = delete;
	friend std::ostream& operator<<(std::ostream& os, const ATM_Instance& m);

	const uint16 getLimit() const;
	uint16 getCurrentNoteNumber();
	uint16 getNote50Number() const;
	uint16 getNote100Number() const;
	uint16 getNote500Number() const;
	uint16 getNote1000Number() const;
	uint16 getNote5000Number() const;

	void setNote50(uint16);
	void setNote100(uint16);
	void setNote500(uint16);
	void setNote1000(uint16);
	void setNote5000(uint16);
};


#endif