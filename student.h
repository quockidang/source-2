#ifndef _STUDENT_H
#define _STUDENT_H
#include"Subject.h"

struct student{
	char idStudent[12];
	char idClass[15];
	char fistName[10], lastName[20];
	int sex = 1; // 1 male, 2 female
	char phoneNUmber[13];
	int yearAdmission; // nam nhap hoc
};
typedef struct student STUDENT;
typedef STUDENT* PTR_STUDENT;
struct NodeStudent{
	STUDENT _student;
	struct NodeStudent *pNext;
};
typedef struct NodeStudent NODE_STUDENT;

struct ListStudent{
	int n = 0;
	NODE_STUDENT *pHead, *pTail;
};
typedef struct ListStudent LIST_STUDENT;

STUDENT** arrStudent = new STUDENT*[MAX_STUDENT];


// get node student -- lay dia chi cua mot sinh vie
NODE_STUDENT* GetNodeStudent(STUDENT DATA)
{
	NODE_STUDENT *p = new NodeStudent; //init pointer
	if (p == NULL)
		return NULL;
	p->_student = DATA; // export data to node;
	p->pNext = NULL; //init link list
	return p;
}

// init List student -- khoi tao danh sach sinh vien
void InitListStudent(LIST_STUDENT &l)
{
	l.pHead = l.pTail = NULL;
	
}


// Them vao dau danh sach -- add head list student

void AddHeadListStudent(LIST_STUDENT &l, STUDENT data)
{
	NODE_STUDENT* p = GetNodeStudent(data);
	
	p->pNext = l.pHead;
	l.pHead = p;
	++l.n;
}

bool ListStudentIsEmty(LIST_STUDENT l)
{
	if(l.n == 0) return true;
	return false;
	
}
// add tail list student
void AddTailListStudent(LIST_STUDENT &l, STUDENT data)
{
	NODE_STUDENT* p = GetNodeStudent(data);
	if(l.pHead == NULL)
	{
		l.pHead = l.pTail = p;
	}
	else
	{
		l.pTail->pNext = p;
		l.pTail = p;
	}
	
	++l.n;
}



// tim kiem voi maSV
NODE_STUDENT* FindStudent(LIST_STUDENT l, char* id)
{
	if(l.pHead == NULL) return NULL;
	for(NODE_STUDENT* p = l.pHead; p != NULL; p = p->pNext)
	{
		if (_strcmpi(p->_student.idStudent, id) == 0)
			return p;
	}
	return NULL;
}


// tim index cua sinh vien
int FindIndexStudent(LIST_STUDENT l, char *id)
{
	int index = -1;
	if(l.pHead == NULL) return -1;
	for(NODE_STUDENT *p = l.pHead; p != NULL; p = p->pNext)
	{
		++index;
		if(_strcmpi(p->_student.idStudent, id) == 0);
			return index;
	}
	return 0;
}


NODE_STUDENT* FindStudentByOrdinal(LIST_STUDENT l, int ordinal)
{
	if (l.pHead == NULL) return NULL;
	if (l.n -1 < ordinal) return NULL;
	if (l.n - 1 == ordinal) return l.pTail;
	if (ordinal == 0) return l.pHead;
	
	NODE_STUDENT* p = l.pHead;
	int count = 0;
	while(count != ordinal)
	{
		p = p->pNext;
		count++;
	}
	
	return p;
}



// insert apter - them vao sau
void InsertAfter(NODE_STUDENT* p, STUDENT &data)
{
	if(p == NULL) return;
	NODE_STUDENT* q = new NODE_STUDENT;
	
	q->_student = data;
	q->pNext = p->pNext;
	p->pNext = q;
}

// xoa dau - delete head
bool IsDeletedHead(LIST_STUDENT &l)
{
	if(ListStudentIsEmty(l)) return false;
	NODE_STUDENT *p =l.pHead; 
	
	l.pHead = p->pNext;
	delete p;
	--l.n;
	return true;
}


// delete tail -- xoa cuoi
bool IsDeletedTail(LIST_STUDENT &l)
{
	if(ListStudentIsEmty(l)) return false;
	
	NODE_STUDENT *beforeP = NULL;
	for (NODE_STUDENT *p = l.pHead; p != NULL; p = p->pNext)
	{
		if (p == l.pTail)
		{
			l.pTail = beforeP;
			beforeP->pNext = NULL;
			delete p;
			--l.n;
			return true;
		}
		beforeP = p;
	}
}

// delete after node p
bool IsDeletedAfter(LIST_STUDENT &l, NODE_STUDENT*p)
{
	if (p == NULL || p->pNext == NULL) return false;
	NODE_STUDENT* nodeDeleted = p->pNext;
	p->pNext = nodeDeleted->pNext;
	delete nodeDeleted;
	--l.n;
	return true;
}

// delete with id Student
bool IsDeletedStudentWithId(LIST_STUDENT &l, STUDENT data)
{
	NODE_STUDENT* nodeDeleted = FindStudent(l, data.idStudent);
	if (nodeDeleted == NULL) return false;
	if (nodeDeleted == l.pHead) return IsDeletedHead(l);
	if (nodeDeleted == l.pTail) return IsDeletedTail(l);
	else
	{
		NODE_STUDENT* temp = l.pHead;
		while (temp->pNext != nodeDeleted)
			temp = temp->pNext;
		return IsDeletedAfter(l,temp);
	}
}

// xoa danh sach Sinh vien
bool ClearListStudent(LIST_STUDENT &l)
{
	if (l.pHead) return false;
	NODE_STUDENT* temp;
	while (l.pHead != NULL)
	{
		temp = l.pHead;
		l.pHead = l.pHead->pNext;
		delete temp;
	}
	return true;
}

void OutputStudent(STUDENT st, int locate)
{
	DeleteOldData(sizeof(keyDisplayStudent) / sizeof(string), locate);
	Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 3 + locate); cout << st.idStudent;
	Gotoxy(xKeyDisplay[1] + 1, Y_DISPLAY + 3 + locate); cout << st.idClass;
	Gotoxy(xKeyDisplay[2] + 1, Y_DISPLAY + 3 + locate); cout << st.fistName;
	Gotoxy(xKeyDisplay[3] + 1, Y_DISPLAY + 3 + locate); cout << st.lastName;
	Gotoxy(xKeyDisplay[4] + 1, Y_DISPLAY + 3 + locate);
	if(st.sex == 1)cout << "Nam";
	else cout << "Nu";
	Gotoxy(xKeyDisplay[5] + 1, Y_DISPLAY + 3 + locate); cout << st.phoneNUmber;
	Gotoxy(xKeyDisplay[6] + 1, Y_DISPLAY + 3 + locate); cout << st.yearAdmission;
}

void OutputListStudent(LIST_STUDENT l)
{
	if(l.pHead == NULL && l.pTail == NULL) return;
	int count = -1;
	
	for(NODE_STUDENT* q = l.pHead; q != NULL; q=q->pNext)
	{
		count++;
		OutputStudent(q->_student, count);
	}
}
	
void OutputListStudentPerPage(LIST_STUDENT l, int indexBegin)
{
	if (l.pHead == NULL && l.pTail == NULL) return;
	int count = -1;
	
	for(NODE_STUDENT* q = l.pHead; q != NULL; q=q->pNext)
	{
		count++;
		if(count == indexBegin)
		{
			int i = -1;			
			while (q != NULL && i < QUANTITY_PER_PAGE - 1)
			{
				OutputStudent(q->_student, (++i) * 2);
				q = q->pNext;
			}
			break;
		}
	}
	
	Gotoxy(X_PAGE, Y_PAGE);
	cout << "Trang " << pageNowStudent << "/" << totalPageStudent;
	return;
}

bool DataStudentIsEmty(STUDENT st)
{
	if(strlen(st.idClass) == 0)return true;
	if(strlen(st.idStudent) == 0) return true;
	
	return false;
}

void InputStudent(LIST_STUDENT &l, STUDENT &st, bool isEdited = false)
{
	ShowCur(true);
	int ordinal = 0;
	bool isMoveUp = false;
	bool isSave = false;
	bool idIsExist = false;
	
	string idClass, idStudent, firstName, lastName, phoneNumber;
	int yearAdmission = 0, sex = 0;
	
	
	if(isEdited)
	{
		// binding data
		idClass = st.idClass;
		idStudent = st.idStudent;
		firstName = st.fistName;
		lastName = st.lastName;
		phoneNumber = st.phoneNUmber;
		yearAdmission = st.yearAdmission;
		sex = st.sex;
		
		
		Gotoxy(X_ADD  + 20, 0 * 3 + Y_ADD);
		cout << idStudent;
		Gotoxy(X_ADD + 21, 1 * 3 + Y_ADD);
		cout << idClass;
		Gotoxy(X_ADD + 17, 2 * 3 + Y_ADD);
		cout << firstName;
		Gotoxy(X_ADD + 18, 3 * 3 + Y_ADD);
		cout << lastName;		
		Gotoxy(X_ADD + 19, 4 * 3 + Y_ADD);
		cout << sex;
		Gotoxy(X_ADD + 20, 5 * 3 + Y_ADD);
		cout << phoneNumber;
		Gotoxy(X_ADD + 21, 6 * 3 + Y_ADD);
		cout << yearAdmission;		
	}
	
	while(true)
	{
		switch(ordinal)
		{
			case 0:
				CheckMoveAndValidateID(idStudent, isMoveUp, ordinal, isSave, 20, 12);
				if(isEdited && _stricmp(idStudent.c_str(), st.idStudent) == 0) break;
				if(FindStudent(l, (char *)idStudent.c_str()) == NULL)
				{
					idIsExist = false;
					break;
				}
				idIsExist = true;
				break;
			case 1:
				CheckMoveAndValidateID(idClass, isMoveUp, ordinal, isSave, 21, 15);
				break;
			case 2:
				CheckMoveAndValidateNameSubject(firstName, isMoveUp, ordinal, isSave, 17);
				break;
			case 3:
				CheckMoveAndValidateNameSubject(lastName, isMoveUp, ordinal, isSave, 18);
				break;
			case 4:
				CheckMoveAndValidateNumber(sex, isMoveUp, ordinal, isSave, 19, 2);
				break;
			case 5:
				CheckMoveAndValidateID(phoneNumber, isMoveUp, ordinal, isSave, 20, 11);
				break;
			case 6:
				CheckMoveAndValidateNumber(yearAdmission, isMoveUp, ordinal, isSave, 21, 2019);
				break;	
		}
		
		if (isMoveUp)
		{
			if (ordinal == 0)
				isMoveUp = false;
			ordinal--;

		}
		else
		{
			if (ordinal == 6)
				isMoveUp = true;
			ordinal++;
		}
		
		
		if(isSave)
		{
			// binding data
			strcpy(st.idStudent, idStudent.c_str());
			strcpy(st.idClass, idClass.c_str());
			strcpy(st.fistName, firstName.c_str());
			strcpy(st.lastName, lastName.c_str());
			strcpy(st.phoneNUmber, phoneNumber.c_str());
			st.sex = sex;
			st.yearAdmission = yearAdmission;
			
			
			Gotoxy(X_NOTIFY, Y_NOTIFY);
			cout << setw(50) << setfill(' ') << " ";
			if(idStudent.empty() || idClass.empty() || sex == 0 || firstName.empty() || lastName.empty() || yearAdmission == 0 )
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "Cac truong du lieu khong dc de trong";
			}
			else if(idIsExist)
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "Ma sinh vien khong duoc trung";
			}
			else
			{
				if(isEdited)
				{
					NODE_STUDENT* p = FindStudent(l, st.idStudent);
					p->_student = st;
				}else
				{
					AddTailListStudent(l, st);				
				}
				totalPageStudent =((l.n - 1) / QUANTITY_PER_PAGE) + 1;
				DeleteMenuAdd();
				return;		
			}
			isSave = false;
		}
		else
		{
			isSave = false;
		}
	}
	ShowCur(false);
}

void SetDefaultChooseStudent(STUDENT st, int ordinal)
{
	SetBGColor(GREEN);
	OutputStudent(st, (ordinal % QUANTITY_PER_PAGE) * 2);
	SetBGColor(PURPLE);
}

void EffectiveMenuStudent(int ordinal, STUDENT stnew, STUDENT stold)
{
	int current = ordinal;
	SetDefaultChooseStudent(stnew, current);
	OutputStudent(stold, (currposPrecStudent % QUANTITY_PER_PAGE) * 2);
	currposPrecStudent = current;
}

void ChangePageChooseStudent(LIST_STUDENT l)
{
	clrscr();
	Display(keyDisplayStudent, sizeof(keyDisplayStudent) / sizeof(string));
	currposStudent = (pageNowStudent - 1) * QUANTITY_PER_PAGE;
	currposPrecStudent = (pageNowStudent - 1) * QUANTITY_PER_PAGE;
}

NODE_STUDENT* ChooseStudent(LIST_STUDENT l)
{
	int keyboard_read = 0;
	ShowCur(false);
	pageNowStudent = 1;
	currposStudent = (pageNowStudent - 1) * QUANTITY_PER_PAGE;
	currposPrecStudent = (pageNowStudent - 1) * QUANTITY_PER_PAGE;
	totalPageStudent = ((l.n-1) / QUANTITY_PER_PAGE) + 1;
	
	NODE_STUDENT* newNodeStudent = FindStudentByOrdinal(l, currposStudent);
	NODE_STUDENT* oldNodeStudent = NULL;
	
	OutputListStudentPerPage(l, (pageNowStudent - 1) * QUANTITY_PER_PAGE);
	SetDefaultChooseStudent(newNodeStudent->_student, currposStudent);
	
	while(true)
	{
		keyboard_read = _getch();
		if (keyboard_read == 0)
			keyboard_read = _getch();
		switch (keyboard_read)
		{
			case KEY_UP:
				if(currposStudent % QUANTITY_PER_PAGE > 0)
				{
					currposStudent = currposStudent - 1;
					oldNodeStudent = newNodeStudent;
					for( newNodeStudent = l.pHead; newNodeStudent->pNext != oldNodeStudent; newNodeStudent = newNodeStudent->pNext);
					EffectiveMenuStudent(currposStudent, newNodeStudent->_student, oldNodeStudent->_student);				
				}
				break;
			case KEY_DOWN:
				if(currposStudent % QUANTITY_PER_PAGE < QUANTITY_PER_PAGE - 1 && newNodeStudent->pNext != NULL)
				{
					currposStudent = currposStudent + 1;
					oldNodeStudent = newNodeStudent;;
					newNodeStudent = newNodeStudent->pNext;
					EffectiveMenuStudent(currposStudent, newNodeStudent->_student, oldNodeStudent->_student);
				}
				break;
			case PAGE_DOWN:
				if(pageNowStudent < totalPageStudent)
				{
					pageNowStudent++;
					ChangePageChooseStudent(l);
					OutputListStudentPerPage(l, (pageNowStudent - 1) * QUANTITY_PER_PAGE);
					
					newNodeStudent = FindStudentByOrdinal(l, currposStudent);
					SetDefaultChooseStudent(newNodeStudent->_student, currposStudent);
				
				}
				break;
			case PAGE_UP:
				if(pageNowStudent > 1)
				{
					pageNowStudent--;
					ChangePageChooseStudent(l);
					OutputListStudentPerPage(l, (pageNowStudent - 1) * QUANTITY_PER_PAGE);
					newNodeStudent = FindStudentByOrdinal(l, currposStudent);
					SetDefaultChooseStudent(newNodeStudent->_student, currposStudent);
				}
				break;
			case ENTER:  //enter
				ShowCur(true);
				return newNodeStudent;
				break;
			case 27: 
				return NULL; 
				break;	
		}
	}
	
}

void ChangePageManageStudent(LIST_STUDENT l)
{
	clrscr();
	Gotoxy(X_TITLE, Y_TITLE); cout << "QUAN LY CAC CHUYEN BAY";
	OutputListStudentPerPage(l, (pageNowStudent - 1) * QUANTITY_PER_PAGE);
	Display(keyDisplayStudent, sizeof(keyDisplayStudent) / sizeof(string));
}

void MenuManagerStudent(LIST_STUDENT &l)
{
backMenu:
	clrscr();
	pageNowStudent = 1;
	OutputListStudentPerPage(l, 0);
	
	Display(keyDisplayStudent, sizeof(keyDisplayStudent) / sizeof(string));
	Gotoxy(X_TITLE, Y_TITLE); cout << "QUAN LY SINH VIEN";
	int key;
	while(true)
	{
		while(_kbhit())
		{
			key = _getch();
			if (key == 0 || key == 224)
			{
				key = _getch();
				if(key == KEY_F2)
				{
					STUDENT st;
					DisplayEdit(keyDisplayStudent, sizeof(keyDisplayStudent) / sizeof(string), 35);
					InputStudent(l, st, false);
					
					totalPageStudent = ((l.n - 1) / QUANTITY_PER_PAGE) + 1;
					ChangePageManageStudent(l);
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Them thanh cong";
				}
				else if( key == KEY_F3)
				{
					NODE_STUDENT* k = ChooseStudent(l);
					if(k == NULL) goto backMenu;
					
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Ban co chac chan xoa? Enter dong y";
					key = _getch();
					if(key == ENTER)
					{
						if(IsDeletedStudentWithId(l, k->_student))
						{
							totalPageStudent = ((l.n - 1) / QUANTITY_PER_PAGE) + 1;
							if(l.n % QUANTITY_PER_PAGE == 0) pageNowStudent--;
							ChangePageManageStudent(l);
							Gotoxy(X_NOTIFY, Y_NOTIFY);
							cout << "Xoa thanh cong";
						}
					}else goto backMenu;
				}
				else if( key == KEY_F4)
				{
					NODE_STUDENT* k = ChooseStudent(l);
					if(k == NULL) goto backMenu;
					
					DisplayEdit(keyDisplayStudent, sizeof(keyDisplayStudent) / sizeof(string), 35);
					InputStudent(l, k->_student, true);
					clrscr();
					Display(keyDisplayStudent, sizeof(keyDisplayStudent) / sizeof(string));
					OutputListStudentPerPage(l, (pageNowStudent - 1) * QUANTITY_PER_PAGE);
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Sua thanh cong";
				}
				else if(key == PAGE_DOWN && pageNowStudent < totalPageStudent)
				{
					pageNowStudent++;
					ChangePageManageStudent(l);
				}
				else if(key == PAGE_UP && pageNowStudent > 1)
				{
					pageNowStudent--;
					ChangePageManageStudent(l);
				}
			}
			else if(key == ESC)
			{
				return;
			}
		}
		
	}
	
}

#endif

