//POPA IOANA-THEODORA
//315CD

		A GAME OF SCRABBLE

Task 0:
	Am initializat tabla de joc parcurgand fiecare linie si coloana si dandu-i 
fiecarui element valoarea '.'

Task 1:
	Am citit in data_input numarul de cuvinte ce va fi adaugat si cuvintele,
facand conversia lui N in numar intreg; liniile au fost citite litera cu litera,
care ulterior au fost impartite in coordonatele cuvantului(memorate intr-un vector,
prima pozitie reprezinta numarul liniei, a doua numarul coloanei, iar a treia daca 
cuvantul va fi pus pe orizontala, respectiv verticala) si cuvantul propriu-zis,ce a
fost adaugat in tabla de joc in functie de coordonatele extrase.

Task 2:
	Au fost citite datele ca mai sus, iar in functie de linia pe care se afla cuvantul in
data_input, am determinat daca apartine primului jucator sau celui de-al doilea(pozitie 
impara->primul; pozitie para-> al doilea). Am initializat un vector de punctaje, creat ca 
in cerinta, si pentru fiecare litera din cuvant am extras din vector punctajul corespunzator
si l-am adaugat la scorul final al player-ului respectiv.

Task 3:
	Am citit inainte substring-urile bonus care au fost puse intr-o matrice, si restul datelor
ca in task-urile anterioare. Procedand ca la task-ul 2, am calculat punctajele fiecarui
jucator, de data aceasta tinand cont si de taba de punctaj bonusuri, astfel incat
daca apare substring-ul de bonus 1 in cuvant si cuvantul se suprapune pe tabla de
punctaje bonus cu '1', punctajul cuvantului respectiv va fi dublat de cate ori
apare '1'. Analog se procedeaza si pt substring-ul asociat bonusului 2, insa 
se verifica daca substring-ul se afla la sfarsitul cuvantului si punctajul
se tripleaza.

Task 4:
	Intai cream tabla de joc si citim datele, utilizand task-ul 1. Cautam primul
cuvant care respecta cerinta, netinand cont de punctaj. Asadar, verificam daca
string-ul de la pozitia i din matricea predefinita de cuvinte daca se mai gaseste
pe tabla: daca se gaseste continuam verificarile, daca nu trecem la urmatorul cuvant.
Cautam prima litera a cuvantului pe tabla; daca o gasim, vedem daca cuvantul poate fi
plasat pe orizontala, verticala sau amandoua(intai incercam sa punem pe orizontala, 
iar ulterior, daca se intrepatrunde cu o litera pe tabla de joc, pe verticala).
Am cautat prima litera a cuvantului pe tabla de joc, parcurgand matricea pe linii
si coloane, astfel incat primul cuvant care respecta toate cerintele este cel de pe
linia cu numarul cel mai mic si coloana cu numarul cel mai mic.

Task 5:
	Se procedeaza analog ca la task-ul 4, insa cuvantul este pus pe tabla astfel incat
sa produca punctajul cel mai mare si nu pe linia cu numarul cel mai mic si coloana 
cea mai mica(verificam toate pozitiile de pe tabla si ramanem cu pozitia corespunzatoare
punctajului maxim). De asemenea, nu este ales primul cuvant gasit, ci cel care genereaza
punctajul cel mai mare, deci calculam punctajul pentru fiecare cuvant care poate sa
fie pus pe tabla si il introducem pe cel care are punctajul maxim.

Task 6:
	Cautam dupa fiecare introducere de catre player-ul 1 un cuvant optim pentru a fi introdus,
asemanator ca la task-ul 5.