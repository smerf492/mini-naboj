#include<iostream>
#include<windows.h>

using namespace std;

string pl(string tekst)
{
	for(unsigned int i=0;i<tekst.length();i++)
	switch(tekst[i])
	{
		case '�' : tekst[i]=(char)165;break;
		case '�' : tekst[i]=(char)134;break;
		case '�' : tekst[i]=(char)169;break;
		case '�' : tekst[i]=(char)136;break;
		case '�' : tekst[i]=(char)228;break;
		case '�' : tekst[i]=(char)162;break;
		case '�' : tekst[i]=(char)152;break;
		case '�' : tekst[i]=(char)171;break;
		case '�' : tekst[i]=(char)190;break;
		case '�' : tekst[i]=(char)164;break;
		case '�' : tekst[i]=(char)143;break;
		case '�' : tekst[i]=(char)168;break;
		case '�' : tekst[i]=(char)157;break;
		case '�' : tekst[i]=(char)227;break;
		case '�' : tekst[i]=(char)224;break;
		case '�' : tekst[i]=(char)151;break;
		case '�' : tekst[i]=(char)141;break;
		case '�' : tekst[i]=(char)189;break;
	}
	return tekst;
}

int ekran(string tekst, int kolor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),kolor);
	cout<<pl(tekst);
	return 0;
}
int to_xy(int szer, int wys)
{
	COORD a;
	a.X=szer-1;
	a.Y=wys-1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),a);
	return 0;
}
void Ukryjkursor()
{
	HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(a,&cci);
	cci.bVisible=FALSE;
	SetConsoleCursorInfo(a,&cci);
}
