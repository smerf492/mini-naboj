#include<iostream>
#include<cmath>
#include<fstream>
#include<ctime>
#include<windows.h>
#include "funkcje.h"
#include<conio.h>

using namespace std;

const int zad=50;//max zadan
const int zaw=50;//max zawodnikow
const int szer=300;//max rozmiary rysowanych ramek -> wartosci z rezerwa, bo nie ma wplywu na okno i nie zabiera duzo pamieci
const int wys=200;
bool ramki[wys+2][szer+2]={};
int il_zaw, il_zad, szer_nicosci;
int barwa=-1, barwa2, barwa3;
int poz_czas, czas_kon, dl_frozen, dl_nazw;
int ilnast, koniec=0, blad=0, czywid;
unsigned int szer_rys_tab;
string frozen;
string nazwy[zaw+1]={};//tablica na nazwy uczestnikow

struct tabela_danych //dane zadaniach
{	//dodana aby wprowadzic wzorzec projektowy, dlatego nie jest przewidziana w testach jednostkowych
	int wid[zaw][zad+1];//dane widoczne
	int akt[zaw][zad+1];//dane aktualne
	bool aktualne;
	int pamiatka;
	void zeruj()
	{
		for(int i=0;i<zaw;i++)for(int j=0;j<=zad;j++)akt[i][j]=0;
		for(int i=0;i<zaw;i++)for(int j=0;j<zad;j++)wid[i][j]=-1;
		for(int i=0;i<zaw;i++)wid[i][zad]=0;
		aktualne=1;
		pamiatka=0;
	}
	void akt_do_wid(int zaw_od0)
	{
		int do_pok=ilnast;
		for(int i=0;i<il_zad;i++)
		{
			if(akt[zaw_od0][i]==1)wid[zaw_od0][i]=1;
			else if(do_pok>0)
			{
				do_pok--;
				wid[zaw_od0][i]=0;
			}
			else wid[zaw_od0][i]=-1;
			wid[zaw_od0][zad]=akt[zaw_od0][zad];
		}
	}
	void pelna_akt(int zmiana_ilnast, bool pam=1)
	{
		ilnast+=zmiana_ilnast;
		for(int i=0;i<il_zaw;i++) akt_do_wid(i);
		if(pam==1)pamiatka=zmiana_ilnast-10;
	}
	void zmiana(int zawodnik, int zadanie, bool pam=1)
	{
		akt[zawodnik-1][zad] -= akt[zawodnik-1][zadanie-1]; //ta komorka pamieta ilosc zrobionych zadan
		akt[zawodnik-1][zadanie-1] = (akt[zawodnik-1][zadanie-1]+1)%2; //wpisanie drugi raz tych samych danych cofa zadanie
		akt[zawodnik-1][zad] += akt[zawodnik-1][zadanie-1];
		if(aktualne==1) akt_do_wid(zawodnik-1);
		//wzorzec pamiatka, struktura sama pamieta ostatnia akcje do ewentualnego cofniecia
		//ulatwia to logicznie cofniecie ostatniego wpisu
		//wzorzec jest uproszczony do wylacznie potrzebnych w tym programie rzeczy, stad zamyka sie w jednej zmiennej
		if(pam==1) pamiatka=(zawodnik<<8)+zadanie;
	}
	int back()
	{
		int tmp=pamiatka;
		if(tmp>0) zmiana(tmp>>8, tmp%256, 0);
		else if(tmp<0) pelna_akt(-(tmp+10));
		return pamiatka;
	}
};
tabela_danych dane;

void pokaz_zapisane_dane()
{
	cout<<"ilosc zaw.: "<<il_zaw<<endl<<"ilosc zad.: "<<il_zad<<endl;
	cout<<"ilosc pocz. zad.: "<<ilnast<<endl<<"odl. od lewej kraw. okna: "<<szer_nicosci<<endl;
	cout<<"numery kolorow: "<<barwa<<" "<<barwa2<<" "<<barwa3<<endl;
	cout<<"czasy konkursu i zamrozenia: "<<czas_kon<<" "<<dl_frozen<<endl;
	cout<<"czy tabela jest aktualna po konkursie: "<<czywid<<endl;
	cout<<"zapisane napisy:\n-dla zamrozenia tabeli: "<<pl(frozen)<<endl;
	cout<<"-dla naglowka tabeli: "<<pl(nazwy[zaw])<<endl;
	
}

void __cdecl dwa(void*Args)//drugi watek aktywny
{
	int in1,in2, liczba1, liczba2;
	bool out=0;
	fstream dz;
	dz.open("zdarzenia.txt",ios::out);
	dz<<il_zaw<<" "<<il_zad<<endl;
	while(out==0)
	{
		in1=getch();
		while(in1==13)in1=getch();
		in1-=48;
		in2=getch()-48;
		if(in1==9)
		{
			if(in2==9)
			{
				dane.pelna_akt(1);
				dz<<99<<" "<<czas_kon-poz_czas<<endl;
			}
			else if(in2==8)
			{
				dane.pelna_akt(-1);
				dz<<98<<" "<<czas_kon-poz_czas<<endl;
			}
			else if(in2==7)//cofniecie ostatniej operacji, bazuje na pamiatce struktury tabela_danych
			{
				liczba1=dane.back();
				if(liczba1>0)
				{
					dz<<97<<" "<<czas_kon-poz_czas<<endl;
				}
				else
				{
					liczba1+=11;
					liczba1>>=1;//wynikiem powinno byc 1 lub 0
					if(liczba1==1 || liczba1==0)dz<<97<<" "<<czas_kon-poz_czas<<endl;
					else blad=4;
				}
			}
			else blad=2;
		}
		else
		{
			liczba1=in1*10+in2;
			if(poz_czas==0 && liczba1==0)out=1;
			else if(liczba1==0)blad=1;
			else if(liczba1>il_zaw || liczba1<0)blad=3;
			else
			{
				in1=getch()-48;
				in2=getch()-48;
				liczba2=in1*10+in2;
				while(getch()!=13);//czekanie na ENTER
				if(liczba2==0)blad=1;
				else if(liczba2>il_zad || liczba2<0)blad=3;
				else
				{
					dane.zmiana(liczba1,liczba2);
					dz<<liczba1<<" "<<liczba2<<" "<<czas_kon-poz_czas<<endl;
				}
			}
		}
		
	}
	blad=-1;
	dz<<0<<endl;
	dz.close();
	_endthread();
}

void pok_ram()
{
	int i,j;
	ekran("",barwa);
	for(i=1;i<wys+1;i++)for(j=1;j<szer+1;j++)if(ramki[i][j]==1)
	{
		to_xy(j,i);
		if(ramki[i+1][j]==1 and ramki[i][j+1]==1 and ramki[i][j-1]==1 and ramki[i-1][j]==1)cout<<(char)206;
		else if(ramki[i+1][j]==1 and ramki[i][j+1]==1 and ramki[i][j-1]==1)cout<<(char)203;
		else if(ramki[i+1][j]==1 and ramki[i][j+1]==1 and ramki[i-1][j]==1)cout<<(char)204;
		else if(ramki[i][j+1]==1 and ramki[i][j-1]==1 and ramki[i-1][j]==1)cout<<(char)202;
		else if(ramki[i+1][j]==1 and ramki[i][j-1]==1 and ramki[i-1][j]==1)cout<<(char)185;
		else if(ramki[i+1][j]==1 and ramki[i][j-1]==1)cout<<(char)187;
		else if(ramki[i+1][j]==1 and ramki[i][j+1]==1)cout<<(char)201;
		else if(ramki[i][j+1]==1 and ramki[i-1][j]==1)cout<<(char)200;
		else if(ramki[i][j-1]==1 and ramki[i-1][j]==1)cout<<(char)188;
		else if(ramki[i+1][j]==1 and ramki[i-1][j]==1)cout<<(char)186;
		else if(ramki[i][j+1]==1 and ramki[i][j-1]==1)cout<<(char)205;
		else if(ramki[i+1][j]==1)cout<<(char)220;
		else if(ramki[i-1][j]==1)cout<<(char)223;
		else cout<<(char)254;
	}
}

void czas()
{
	to_xy(szer_nicosci+szer_rys_tab-13,1+3+il_zaw*2+3);
	if(poz_czas>0)
	{
		ekran("czas: ",barwa);
		if(poz_czas/3600<10)cout<<"0";
		cout<<poz_czas/3600<<":";
		if((poz_czas/60)%60<10)cout<<"0";
		cout<<(poz_czas/60)%60<<":";
		if(poz_czas%60<10)cout<<"0";
		cout<<poz_czas%60;
	}
	else ekran("  KONIEC CZASU",barwa);
}

void gen_ram()//funkcja oznacza w tablicy pozycje ramek
{
	int i,j,x;
	x=10+dl_nazw+il_zad*3;
	for(i=0;i<x;i++)ramki[1+1][i+1+szer_nicosci]=1;
	ramki[2+1][1+szer_nicosci]=1;
	ramki[2+1][x+szer_nicosci]=1;
	for(i=0;i<x;i++)ramki[3+1][i+1+szer_nicosci]=1;
	ramki[4+1][1+szer_nicosci]=1;
	for(i=0;i<il_zad+1;i++)ramki[4+1][dl_nazw+5+3*i+szer_nicosci]=1;
	ramki[4+1][x+szer_nicosci]=1;
	for(i=0;i<x;i++)ramki[5+1][i+1+szer_nicosci]=1;
	for(i=0;i<il_zaw;i++)
	{
		ramki[6+1+i*2][1+szer_nicosci]=1;
		ramki[6+1+i*2][4+szer_nicosci]=1;
		for(j=0;j<il_zad+1;j++)ramki[6+1+i*2][dl_nazw+5+j*3+szer_nicosci]=1;
		ramki[6+1+i*2][x+szer_nicosci]=1;
		for(j=0;j<x;j++)ramki[7+1+i*2][j+1+szer_nicosci]=1;
	}
}

void wyp_ram()//wypelnia komorki opisowe tabeli
{
	int i,j;
	to_xy(szer_nicosci+1+(szer_rys_tab-nazwy[zaw].size())/2,1+2);
	ekran(nazwy[zaw],barwa);
	to_xy(szer_nicosci+2+(dl_nazw-13)/2,1+4);
	ekran("zawodnik\\zadanie",barwa);
	for(i=0;i<il_zad;i++)
	{
		if(i<9)j=1;
		else j=0;
		to_xy(szer_nicosci+6+j+dl_nazw+3*i,1+4);
		cout<<i+1;
	}
	to_xy(szer_nicosci+szer_rys_tab-4,1+4);
	cout<<"SUMA";
	for(i=0;i<il_zaw;i++)
	{
		if(i<9)j=1;
		else j=0;
		to_xy(szer_nicosci+2+j,1+6+i*2);
		cout<<i+1;
		to_xy(szer_nicosci+2+3,1+6+i*2);
		ekran(nazwy[i],barwa);
	}
}

int obraz()
{
	int i,j,suma;
	for(i=0;i<il_zaw;i++)
	{
		suma=dane.wid[i][zad];
		for(j=0;j<il_zad;j++)
		{
			to_xy(szer_nicosci+dl_nazw+2+4+3*j,7+2*i);
			if(dane.wid[i][j]>0)ekran("  ",barwa3);
			else if(dane.wid[i][j]==0)ekran("  ",barwa2);
			else if(dane.wid[i][j]==-1)ekran("  ",barwa);
		}
		to_xy(szer_nicosci+dl_nazw+2+4+3*il_zad,7+2*i);
		ekran("",barwa);
		if(suma<1000)cout<<" ";
		if(suma<100)cout<<" ";
		if(suma<10)cout<<" ";
		cout<<suma;
	}
	ekran("",barwa);
	return 0;
}

int testdanych6()//napisy
{
	int bl=0;
	szer_rys_tab=1+3+dl_nazw+1+il_zad*3+5;
	if(frozen.size()>szer_rys_tab-15)bl=-100;
	if(nazwy[zaw].size()>szer_rys_tab-2)bl=-100;
	return bl;
}

int testdanych5()//widocznosc na koniec
{
	int bl=0;
	if(czywid<0)
	{
		czywid=0;
		bl++;
	}
	if(czywid>1)
	{
		czywid=1;
		bl++;
	}
	if(dl_frozen==0 && czywid==0)
	{
		czywid=1;
		bl++;
	}
	return testdanych6()+bl;
}

int testdanych4()//czasy
{
	int bl=0;
	if(czas_kon<1 || czas_kon>300)bl=10;
	if(dl_frozen<0)
	{
		dl_frozen=0;
		bl++;
	}
	if(dl_frozen>czas_kon)
	{
		dl_frozen=czas_kon;
		bl++;
	}
	if(bl>5)return -100;
	else return testdanych5()+bl;
}

int testdanych3()//kolory
{
	int bl=0;
	if(barwa<0 || barwa>255)bl++;
	if(barwa2<0 || barwa2>255)bl++;
	if(barwa3<0 || barwa3>255)bl++;
	if(bl>0)return -100;
	else return testdanych4();
}

int testdanych2()//odleglosc tabeli od krawedzi okna
{
	int bl=0;
	if(szer_nicosci<0)
	{
		szer_nicosci=4; //wartosc domyslna
		bl++;
	}
	if(szer_nicosci>szer/10)
	{
		szer_nicosci=szer/10; //druga wartosc domyslna
		bl++;
	}
	return testdanych3()+bl;
}

int testdanych1()//ilosci zawodnikow i zadan
{
	int bl=0;
	if(il_zaw<1 || il_zaw>zaw)bl+=10;
	if(il_zad<1 || il_zad>zad)bl+=10;
	if(ilnast<1)
	{
		ilnast=1; //wartosc domyslna
		bl++;
	}
	else if(ilnast>il_zad)
	{
		ilnast=il_zad; //druga wartosc domyslna
		bl++;
	}
	if(bl>9)return -100;
	else return testdanych2()+bl;
}

int data_in(char* config)
{
	string kosz,nick;
	int i,k=0;
	fstream p;
	p.open(config,ios::in);
	if(!p)ekran("\n\tBrak pliku konfiguracji!\n",12);
	else
	{
		k=1;
		p.seekg(0,ios::beg);
		getline(p,kosz);//pomijanie linii komentarzy z pliku konfiruracyjnego
		getline(p,kosz);
		getline(p,kosz);
		p>>il_zaw;
		p>>il_zad;
		p>>ilnast;
		p>>szer_nicosci;
		getline(p,kosz);
		getline(p,kosz);
		p>>barwa;
		p>>barwa2;
		p>>barwa3;
		getline(p,kosz);
		getline(p,kosz);
		p>>czas_kon;
		p>>dl_frozen;
		p>>czywid;
		getline(p,kosz);
		getline(p,kosz);
		getline(p,frozen);
		getline(p,nazwy[zaw]);
		getline(p,kosz);
		p>>dl_nazw;
		if(dl_nazw<13)dl_nazw=13;//sprawdzane od razu do dalszych wpisow
		if(dl_nazw>25)dl_nazw=25;
		getline(p,kosz);
		for(i=0;i<il_zaw;i++)
		{
			getline(p,nick);
			nazwy[i].insert(0,nick,0,dl_nazw);
		}
	}
	p.close();
	//a teraz ³ancuch zobowiazan sprawdzi te dane
	//ten wzorzec projektowy pozwala mi lepiej panowac nad poprawnoscia danych i ulatwia zrozumienie dzialania tych sprawdzen
	if(k==1)
	{
		k=testdanych1();
		if(k>0)ekran("\n\tDane zawiera³y b³êdy, niektóre wartoœci zosta³y automatycznie zmienione\n",12);
		if(k<0)ekran("\n\tUszkodzony plik konfiguracji lub zbyt d³ugie napisy\n\t(wymagana naprawa przed uruchomieniem)\n",12);
	}
	if(k>=0)return 1;
	else return 0;
}

int konkurs(char* plik_wej)
{
	Ukryjkursor();
	int i,j,k,rr,t2,wj=0;
	dane.zeruj();
	
	rr=data_in(plik_wej);
	
	if(rr==1)
	{
		ekran("",barwa);
		system("cls");
		ekran("Wciœnij dowolny klawisz",barwa);
		getch();
		
		czas_kon=60*czas_kon;
		dl_frozen=60*dl_frozen;
		poz_czas=czas_kon;
		
		system("cls");
		gen_ram();
		pok_ram();
		wyp_ram();
		czas();
		
		ekran("\n\tWciœnij dowolny klawisz aby rozpocz¹æ",barwa);
		getch();
		
		_beginthread(dwa,0,NULL);
		
		clock_t start=clock();
		dane.pelna_akt(0,0);
		
		obraz();
		czas();
		to_xy(1,1+3+il_zaw*2+4);
		for(i=0;i<50;i++)ekran(" ",barwa);
		while(wj!=1)
		{
			while(clock()-start<=1000*(czas_kon-poz_czas)+100 or poz_czas==0);
			
			if(clock()-start>1000*(czas_kon-poz_czas+1))
			{
				poz_czas-=1;
				czas();
				obraz();
				if(poz_czas%5==0)//to zabezpieczenie na wypadek zmiany rozmiaru okna w czasie pracy programu
				{
					system("cls");
					obraz();
					czas();
					pok_ram();
					wyp_ram();
				}
				if(poz_czas<=dl_frozen && poz_czas>0)
				{
					dane.aktualne=0;
					to_xy(szer_nicosci+1,1+3+il_zaw*2+3);
					ekran(frozen,barwa);
				}
				if(poz_czas==0 && czywid==0)
				{
					to_xy(szer_nicosci+1,1+3+il_zaw*2+3);
					ekran(frozen,barwa);
				}
				if(blad>0)
				{
					to_xy(1,1);
					string tmp;
					tmp=(char)(48+blad);
					ekran(tmp,barwa/16*16+12);
					blad=0;
				}
				else 
				{
					to_xy(1,1);
					ekran("X",barwa/16*17);//zmiana koloru tekstu na kolor tla
				}
			}
			
			for(i=0;i<il_zaw;i++)
			{
				k=0;
				for(j=0;j<il_zad;j++)if(dane.akt[i][j]==1)k++;
				if(k==il_zad)koniec=1;
			}
			
			if(koniec==1)
			{
				t2=poz_czas;
				poz_czas=0;
				to_xy(szer_nicosci+1,1+3+il_zaw*2+3);
				ekran("KONIEC ZADAÑ      ",barwa);
			}
			if(poz_czas==0)wj=1;
		}
		wj=0;
		while(wj!=1)
		{
			while(clock()-start<=1000*(czas_kon-t2)+100);
			t2-=1;
			if(czywid==1 && dane.aktualne==0)
			{
				dane.aktualne=1;
				dane.pelna_akt(0,0);
			}
			obraz();
			pok_ram();
			if(blad==-1)wj=1;
		}
	}
	cout<<"\n\t";
	if(barwa==-1)barwa=15;
	to_xy(szer_nicosci+1,1+3+il_zaw*2+4);
	ekran("Wciœnij dowolny klawisz aby zakoñczyæ",barwa);
	cout<<"\n";
	getch();
	return 0;
}
