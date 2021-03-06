#include"QUEUE.h"
#include<stdio.h>
#include<iostream>

using namespace std;

QUEUE::QUEUE(int m):m_sS1(m),m_sS2(m) {		//	创建两个用于模拟队列的栈
	if ((true == m_sS1.m_bError_exist) || (true == m_sS2.m_bError_exist)) {
		cout << "can not make a new queue" << endl;
		m_bWrong = true;
		return;
	}
	m_bWrong = false;
}

QUEUE::QUEUE(const QUEUE& s) : m_sS1(s.m_sS1), m_sS2(s.m_sS2) {		//拷贝构造函数
	if ((true == m_sS1.m_bError_exist) || (true == m_sS2.m_bError_exist)) {
		cout << "can not copy a new queue" << endl;
		m_bWrong = true;
		return;
	}
	m_bWrong = false;
}

QUEUE::operator int()const {		//返回目前元素的个数
	int pos_queue;
	pos_queue = m_sS1.m_iPos + m_sS2.m_iPos;
	return pos_queue;
}

int QUEUE::full()const {
	if ((m_sS1.m_iMax == m_sS1.m_iPos) && (m_sS2.m_iPos)) {
		return true;
	}
	return false;
}

int QUEUE::operator[](int x)const {			//	取下标为x的元素数值,未判断下标符合条件
	if (x <= (m_sS2.m_iPos - 1)) {		//	元素在s2中
		return m_sS2.m_iElems[m_sS2.m_iPos-x-1];
	}
	else if ((x >= m_sS2.m_iPos) && (x < (m_sS1.m_iPos+m_sS2.m_iPos))) {		//	元素在s1中
		return m_sS1.m_iElems[x - m_sS2.m_iPos];
	}
	/*else if (x >= (m_sS1.m_iPos + m_sS2.m_iPos)) {
	}*/
}

QUEUE& QUEUE::operator<<(int e) {			//	入队列，返回此队列
	if (true == QUEUE::full()) {
		m_bWrong = true;
		return *this;
	}
	if ((m_sS1.m_iMax == m_sS1.m_iPos)&&(0==m_sS2.m_iPos)) {		//	当s1满且s2为空时，将s1中的元素倾倒到s2中
		m_sS2.m_iPos = m_sS1.m_iPos;
		int cnt_tran = 0;
		for (; cnt_tran < m_sS1.m_iPos; cnt_tran++) {
			m_sS2.m_iElems[cnt_tran] = m_sS1.m_iElems[m_sS1.m_iPos - cnt_tran - 1];
		}
		m_sS1.m_iPos = 0;
	}
	m_sS1.operator<<(e);
	m_bWrong = false;
	return *this;
}

QUEUE& QUEUE::operator >> (int &e) {		//出队列，返回此队列
	if (0 == m_sS2.m_iPos) {
		if (0 == m_sS1.m_iPos) {		//	对列为空时，返回错误信息
			m_bWrong = true;
			return *this;
		}
		else {			//	s2为空，且s1不为空时，将s1中的元素倾倒到s2中
			m_sS2.m_iPos = m_sS1.m_iPos;
			int cnt_tran = 0;
			for (; cnt_tran < m_sS1.m_iPos; cnt_tran++) {
				m_sS2.m_iElems[cnt_tran] = m_sS1.m_iElems[m_sS1.m_iPos - cnt_tran - 1];
			}
			m_sS1.m_iPos = 0;
			m_sS2.operator >> (e);
			m_bWrong = false;
			return *this;
		}
	}
	else {		//	s2不为空，直接出栈
		m_sS2.operator >> (e);
		m_bWrong = false;
		return *this;
	}
}

QUEUE& QUEUE::operator=(const QUEUE& s) {
	m_sS1.operator=(s.m_sS1);
	m_sS2.operator=(s.m_sS2);
	if ((true == m_sS1.m_bError_exist) || (true == m_sS2.m_bError_exist)) {
		cout << "errors" << endl;
		m_bWrong = true;
		return *this;
	}
	m_bWrong = false;
	return *this;
}

void QUEUE::print(FILE *fp) const {
	const int *p = &m_sS2.m_iPos;
	const int *q = m_sS2.m_iElems;
	for (int cnt_pri = *p-1; cnt_pri>=0; cnt_pri--) {
		fprintf(fp, "%d  ", q[cnt_pri]);
	}
	m_sS1.print(fp);
}

QUEUE::~QUEUE() {
}