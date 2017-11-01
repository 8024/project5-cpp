#include"STACK.h"
#include<stdio.h>
class QUEUE {		//	���е�Ԫ�ظ���������s1.pos+s2.pos����
public:
	QUEUE(int m);
	QUEUE(const QUEUE& s);
	virtual operator int() const;
	virtual int full() const;
	virtual int operator[](int x)const;
	virtual QUEUE& operator<<(int e);
	virtual QUEUE& operator >> (int &e);
	virtual	QUEUE& operator =(const QUEUE& s);
	virtual void print(FILE *fp) const;
	virtual ~QUEUE();
	bool m_bWrong;
private:
	STACK m_sS1, m_sS2;
};
