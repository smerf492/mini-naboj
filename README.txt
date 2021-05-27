1.plik "conig.txt" nale¿y ustawiæ zgodnie z zapotrzebowaniem, wedle informacji w nim.
Kodowanie ANSI!!!, UTF zgubi polskie znaki (dwa "przypadkowe" znaki).
2.Je¿eli po w³¹czeniu program wyœwietli b³¹d macie prze... i nic tu na to nie poradze ...
3.W przeciwnym wypadku nale¿y wcisn¹æ cokolwiek, powinna sie pojawiæ tabela, a pod ni¹ napis sugeruj¹cy rozpoczêcie.
4.W wybranym momencie nale¿y ropocz¹æ.
5.Wpisywanie danych:
a) Wejœcie standardowe to cztery cyfry, dwie pierwsze to numer zawodnika (np. 04), a dwie nastêpne to numer zadania (np. 05),
nastêpnie nale¿y potwierdziæ zakoñczenie wejœcia wciskaj¹c "ENTER".
   Ten zestaw cyfr ZMIENIA STAN zadania, ze zrobionego na nie zrobione oraz z niezrobionego na zrobione.
b) Wejœcie "funkcyjne" to zestaw dwóch cyfr: 99, 98, 97.
   Ka¿dy z tych kodów to inna akcja:
	- 99 dodaje jeden do iloœci zadañ na stole,
	- 98 odejmuje jeden od iloœci zadañ na stole,
	- 97 cofa ostatni¹ akcjê (np. cofniêcie akcji).
	Po kodach nie potrzeba potwierdzenia (ewentualny "ENTER" zostanie pominiêty).
   Nadu¿ywasz tych komend na w³asne ryzyko, powinny dzia³aæ poprawnie, ale nie musz¹.
c) wejœcie koñcz¹ce wejscia do programu "00".
Tu równierz nie potrzeba potwierdzenia zakoñczenia wejœcia.
Mog¹ tu wyst¹piæ b³êdy:
1 - podanie kodu 00 przed zakoñczeniem czasu,
2 - nie istniej¹ca komenda (np. 96),
3 - b³êdny kod czterocyfrowy,
4 - b³¹d wewnêtrzy przy wykonywaniu komendy "97" dla innej komendy.
Je¿eli nie jesteœ pewny czy wpisa³eœ dobry kod czterocyfrowy dopisz jeszcze pare znaków, program je zignoroje jeœli nie bêd¹ potrzebne.