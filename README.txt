1.plik "conig.txt" nale�y ustawi� zgodnie z zapotrzebowaniem, wedle informacji w nim.
Kodowanie ANSI!!!, UTF zgubi polskie znaki (dwa "przypadkowe" znaki).
2.Je�eli po w��czeniu program wy�wietli b��d macie prze... i nic tu na to nie poradze ...
3.W przeciwnym wypadku nale�y wcisn�� cokolwiek, powinna sie pojawi� tabela, a pod ni� napis sugeruj�cy rozpocz�cie.
4.W wybranym momencie nale�y ropocz��.
5.Wpisywanie danych:
a) Wej�cie standardowe to cztery cyfry, dwie pierwsze to numer zawodnika (np. 04), a dwie nast�pne to numer zadania (np. 05),
nast�pnie nale�y potwierdzi� zako�czenie wej�cia wciskaj�c "ENTER".
   Ten zestaw cyfr ZMIENIA STAN zadania, ze zrobionego na nie zrobione oraz z niezrobionego na zrobione.
b) Wej�cie "funkcyjne" to zestaw dw�ch cyfr: 99, 98, 97.
   Ka�dy z tych kod�w to inna akcja:
	- 99 dodaje jeden do ilo�ci zada� na stole,
	- 98 odejmuje jeden od ilo�ci zada� na stole,
	- 97 cofa ostatni� akcj� (np. cofni�cie akcji).
	Po kodach nie potrzeba potwierdzenia (ewentualny "ENTER" zostanie pomini�ty).
   Nadu�ywasz tych komend na w�asne ryzyko, powinny dzia�a� poprawnie, ale nie musz�.
c) wej�cie ko�cz�ce wejscia do programu "00".
Tu r�wnierz nie potrzeba potwierdzenia zako�czenia wej�cia.
Mog� tu wyst�pi� b��dy:
1 - podanie kodu 00 przed zako�czeniem czasu,
2 - nie istniej�ca komenda (np. 96),
3 - b��dny kod czterocyfrowy,
4 - b��d wewn�trzy przy wykonywaniu komendy "97" dla innej komendy.
Je�eli nie jeste� pewny czy wpisa�e� dobry kod czterocyfrowy dopisz jeszcze pare znak�w, program je zignoroje je�li nie b�d� potrzebne.