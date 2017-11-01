#include"QUEUE.h"
#include<stdio.h>
#include<iostream>

using namespace std;

QUEUE::QUEUE(int m):m_sS1(m),m_sS2(m) {		//	������������ģ����е�ջ
	if ((true == m_sS1.m_bError_exist) || (true == m_sS2.m_bError_exist)) {
		cout << "can not make a new queue" << endl;
		m_bWrong = true;
		return;
	}
	m_bWrong = false;
}

QUEUE::QUEUE(const QUEUE& s) : m_sS1(s.m_sS1), m_sS2(s.m_sS2) {		//�������캯��
	if ((true == m_sS1.m_bError_exist) || (true == m_sS2.m_bError_exist)) {
		cout << "can not copy a new queue" << endl;
		m_bWrong = true;
		return;
	}
	m_bWrong = false;
}

QUEUE::operator int()const {		//����ĿǰԪ�صĸ���
	int pos_queue;
	pos_queue = m_sS1.operator int() + m_sS2.operator int();
	return pos_queue;
}

int QUEUE::full()const {
	if ((m_sS1.size() == m_sS1.operator int()) && (m_sS2.operator int())) {
		return true;
	}
	return false;
}

int QUEUE::operator[](int x)const {			//	ȡ�±�Ϊx��Ԫ����ֵ,δ�ж��±��������
	if (x <= (m_sS2.operator int() - 1)) {		//	Ԫ����s2��
		return m_sS2.m_iElems[m_sS2.operator int()-x-1];
	}
	else if ((x >= m_sS2.operator int()) && (x < (m_sS1.operator int()+m_sS2.operator int()))) {		//	Ԫ����s1��
		return m_sS1.m_iElems[x - m_sS2.operator int()];
	}
	/*else if (x >= (m_sS1.m_iPos + m_sS2.m_iPos)) {
	}*/
}

QUEUE& QUEUE::operator<<(int e) {			//	����У����ش˶���
	if (true == QUEUE::full()) {
		m_bWrong = true;
		return *this;
	}
	if ((m_sS1.size() == m_sS1.operator int())&&(0==m_sS2.operator int())) {		//	��s1����s2Ϊ��ʱ����s1�е�Ԫ���㵹��s2��
		m_sS2.setpos(m_sS1.operator int());
		/*int num_elems = m_sS1.operator int();
		int get_elems = NULL;
		for (; num_elems >= 0; num_elems--) {
			m_sS1.operator >> (get_elems);
			m_sS2.operator<<(get_elems);
		}*/

		int cnt_tran = 0;
		for (; cnt_tran < m_sS1.operator int(); cnt_tran++) {
			m_sS2.m_iElems[cnt_tran] = m_sS1.m_iElems[m_sS1.operator int() - cnt_tran - 1];
		}
		m_sS1.setpos(0);
	}
	m_sS1.operator<<(e);
	m_bWrong = false;
	return *this;
}

QUEUE& QUEUE::operator >> (int &e) {		//�����У����ش˶���
	if (0 == m_sS2.operator int()) {
		if (0 == m_sS1.operator int()) {		//	����Ϊ��ʱ�����ش�����Ϣ
			m_bWrong = true;
			return *this;
		}
		else {			//	s2Ϊ�գ���s1��Ϊ��ʱ����s1�е�Ԫ���㵹��s2��
			m_sS2.setpos(m_sS1.operator int());
			/*int num_elems = m_sS1.operator int();
			int get_elems = NULL;
			for (; num_elems >= 0; num_elems--) {
				m_sS1.operator >> (get_elems);
				m_sS2.operator<<(get_elems);
			}*/

			int cnt_tran = 0;
			for (; cnt_tran < m_sS1.operator int(); cnt_tran++) {
				m_sS2.m_iElems[cnt_tran] = m_sS1.m_iElems[m_sS1.operator int() - cnt_tran - 1];
			}
			m_sS1.setpos(0);
			m_sS2.operator >> (e);
			m_bWrong = false;
			return *this;
		}
	}
	else {		//	s2��Ϊ�գ�ֱ�ӳ�ջ
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
	const int p = m_sS2.operator int();
	const int *q = m_sS2.m_iElems;
	for (int cnt_pri = p-1; cnt_pri>=0; cnt_pri--) {
		fprintf(fp, "%d  ", q[cnt_pri]);
	}
	m_sS1.print(fp);
}

QUEUE::~QUEUE() {
}