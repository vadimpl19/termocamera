/*****************************************************************************
���������� ������ �������. 
��������� ����������� �������� �� 16 ������. 
������������ ������� - ���� �� ��� � 16 ������ �������� ������� �������� 
��������.
������������ ���������� ���������, ������������ ������������� �������� 
�������� ����� define maxtout.
������������ ������� - ������ 3 + �� 2*maxtout ���� ���
****************************************************************************/
#define maxtout 8
/*
  0 - ������� ���������
  1-4 - �������� ������� �� �� �����
  5 - ������� ��������;
*/
void initime(); // ��������� ������ �������
void settout(char num, int tout);//������� ���������� �������� 
                                 //num - ������������� �������� (������������ 
                                 //      ��� ����������� ��������
                                 // tout - �������� �������� � �������������

char gettout(char num);//������� �������� ��������.���������� �������� 
                                 //num - ������������� �������� (��������� 
                                 //      ��� ����������
                                 // ���������� 0, ���� ������� �����
extern int time;                                 



