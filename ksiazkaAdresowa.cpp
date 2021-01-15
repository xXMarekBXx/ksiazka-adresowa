#include <iostream>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <conio.h>
#include <sstream>

using namespace std;

struct Znajomy {
	int id;

	string imie;
	string nazwisko;
	string numerTelefonu;
	string email;
	string adres;	
};

vector<Znajomy> odczytZnajomychZPliku(vector<Znajomy> wektorZnajomych) {
	string linia;
	int numerLinii = 1;
	fstream plik;
	Znajomy nowyZnajomy;

	plik.open("ksiazka_adresowa.txt", ios::in);

	if (plik.is_open()) {
		while (getline(plik, linia)) {
			string Znajomy[6];
			int dlugoscLinii = linia.length();			
			int beginOfWord = 0;
			int lengthOfWord = 0;
			int numerZnajomego = 0;

			for (int i = 0; i < dlugoscLinii; i++) {

				if ((int)linia[i] == 124) {
					lengthOfWord = i - beginOfWord;
					Znajomy[numerZnajomego] = linia.substr(beginOfWord, lengthOfWord);
					beginOfWord = i + 1;
					numerZnajomego++;
				}
			}
			nowyZnajomy.id = atoi(Znajomy[0].c_str());
			nowyZnajomy.imie = Znajomy[1];
			nowyZnajomy.nazwisko = Znajomy[2];
			nowyZnajomy.numerTelefonu = Znajomy[3];
			nowyZnajomy.email = Znajomy[4];
			nowyZnajomy.adres = Znajomy[5];

			wektorZnajomych.push_back(nowyZnajomy);

		}
		plik.close();

		return wektorZnajomych;
	}else{
		plik.close();
		return wektorZnajomych;
	}
} 

vector<Znajomy> dodajZnajomegoDoListyKontaktow(vector<Znajomy> wektorZnajomych) {

	system("cls");

	fstream plik;
	string imie, nazwisko, numerTelefonu, adres, email;
	Znajomy nowyZnajomy;

	plik.open("ksiazka_adresowa.txt");
	if (plik.good()) {
		plik.close();
	}else{
		plik.open("ksiazka_adresowa.txt", ios::out);
		plik.close();
	}

	int iloscZnajomych = wektorZnajomych.size();
	int idOstatniegoZnajomego;
	if (wektorZnajomych.empty()) {
		idOstatniegoZnajomego = 0;
	}else{
		idOstatniegoZnajomego = wektorZnajomych[iloscZnajomych - 1].id;
	}
		
	cout << "Podaj imie znajomego: ";
	cin >> imie;
	cout << "Podaj nazwisko znajomego: ";
	cin >> nazwisko;
	cin.ignore();
	cout << "Podaj email znajomego: ";
	getline(cin, email);
	cout << "Podaj adres znajomego: ";
	getline(cin, adres);
	cout << "Podaj numer telefonu znajomego: ";
	getline(cin, numerTelefonu);

	nowyZnajomy = { idOstatniegoZnajomego + 1, imie, nazwisko, numerTelefonu, email, adres };

	wektorZnajomych.push_back(nowyZnajomy);
		
	plik.open("ksiazka_adresowa.txt", ios::out | ios::app);
	if (plik.good()) {
		plik << wektorZnajomych[iloscZnajomych].id << "|";
		plik << wektorZnajomych[iloscZnajomych].imie << "|";
		plik << wektorZnajomych[iloscZnajomych].nazwisko << "|";
		plik << wektorZnajomych[iloscZnajomych].numerTelefonu << "|";
		plik << wektorZnajomych[iloscZnajomych].email << "|";
		plik << wektorZnajomych[iloscZnajomych].adres << "|" << endl;
		cout << endl;
		cout << "Dodano nowego znajomego do listy kontaktow!" << endl;
		cout << endl;
		plik.close();
		Sleep(1000);
		return wektorZnajomych;
	}else{
		cout << "Nie udalo sie otworzyc pliku" << endl;
		system("Pause");			
	}
}

bool wyswietlWszystkichZnajomychZWektora(vector<Znajomy> wektorZnajomych) {
	
	if (wektorZnajomych.empty()) {
		system("cls");
		cout << "Brak znajomych na liscie kontaktow :(" << endl;
		Sleep(1000);
		return true;
	}else{
		system("cls");
		for (int i = 0; i < wektorZnajomych.size(); i++) {
			cout << wektorZnajomych[i].imie << endl;
			cout << wektorZnajomych[i].nazwisko << endl;
			cout << wektorZnajomych[i].numerTelefonu << endl;
			cout << wektorZnajomych[i].email << endl;
			cout << wektorZnajomych[i].adres << endl;			
			cout << endl;
		}
		cout << endl;
		system("pause");
		return true;
	}
	return true;
}

bool szukanieKonkretnegoImieniaWWektorze(vector<Znajomy> wektorZnajomych, string imieDoWyszukania) {

	for (int i = 0; i < wektorZnajomych.size(); i++) {
		if (wektorZnajomych[i].imie == imieDoWyszukania) {
			return true;
		}
	}
	return false;
}

void wyszukiwanieZnajomegoPoImieniu(vector<Znajomy> wektorZnajomych) {

	string imieDoWyszukania;
	system("cls");
	cout << "Podaj imie: ";
	cin >> imieDoWyszukania;

	bool czyToImieJestWWektorze = false;

	czyToImieJestWWektorze = szukanieKonkretnegoImieniaWWektorze(wektorZnajomych, imieDoWyszukania);

	if (czyToImieJestWWektorze) {

		for (int i = 0; i < wektorZnajomych.size(); i++){

			if (imieDoWyszukania == wektorZnajomych[i].imie) {
				cout << endl;
				cout << wektorZnajomych[i].imie << endl;
				cout << wektorZnajomych[i].nazwisko << endl;
				cout << wektorZnajomych[i].numerTelefonu << endl;
				cout << wektorZnajomych[i].email << endl;
				cout << wektorZnajomych[i].adres << endl;
				cout << endl;
				system("pause");
			}			
		}
	}else{
	system("cls");
	cout << "Nie znaleziono znajomego o takim imieniu." << endl;
	cout << endl;
	system("pause");
	}
}

bool szukanieKonkretnegoNazwiskaWWektorze(vector<Znajomy> wektorZnajomych, string nazwiskoDoWyszukania) {

	for (int i = 0; i < wektorZnajomych.size(); i++) {
		if (wektorZnajomych[i].nazwisko == nazwiskoDoWyszukania) {
			return true;
		}
	}
	return false;
}

void wyszukiwanieZnajomegoPoNazwisku(vector<Znajomy> wektorZnajomych) {

	string nazwiskoDoWyszukania;
	system("cls");
	cout << "Podaj nazwisko: ";
	cin >> nazwiskoDoWyszukania;

	bool czyToNazwiskoJestWWektorze = false;

	czyToNazwiskoJestWWektorze = szukanieKonkretnegoNazwiskaWWektorze(wektorZnajomych, nazwiskoDoWyszukania);
	
	if (czyToNazwiskoJestWWektorze) {

		for (int i = 0; i < wektorZnajomych.size(); i++)
		{
			if (nazwiskoDoWyszukania == wektorZnajomych[i].nazwisko) {
				cout << endl;
				cout << wektorZnajomych[i].imie << endl;
				cout << wektorZnajomych[i].nazwisko << endl;
				cout << wektorZnajomych[i].numerTelefonu << endl;
				cout << wektorZnajomych[i].email << endl;
				cout << wektorZnajomych[i].adres << endl;
				cout << endl;
				system("pause");
			}
		}
	}else{
		system("cls");
		cout << "Nie znaleziono znajomego o takim nazwisku." << endl;
		cout << endl;
		system("pause");
	}
}

void wybierzSposobWyszukiwaniaZnajomego(vector <Znajomy> &wektorZnajomych)
{
	if (wektorZnajomych.size() == 0)
	{
		system("cls");
		cout << "Brak znajomych na liscie kontaktow :(" << endl;
		system("pause");
	}else{
		system("cls");
		cout << "Jak chcesz wyszukac znajomego?" << endl;
		cout << endl;
		cout << "1. Po imieniu" << endl;
		cout << "2. Po nazwisku" << endl;
		cout << endl;
		cout << "Twoj wyborUrzytkownika: ";
		char wyborUrzytkownika;
		cin >> wyborUrzytkownika;

		if (wyborUrzytkownika == '1') wyszukiwanieZnajomegoPoImieniu(wektorZnajomych);

		if (wyborUrzytkownika == '2') wyszukiwanieZnajomegoPoNazwisku(wektorZnajomych);
	}
}

bool szukanieKonkretnegoIdWWektorze(vector<Znajomy> wektorZnajomych, int szukaneId) {

	if (wektorZnajomych.empty()) {
		system("cls");
		cout << "Lista kontaktow jest pusta :(" << endl;
		system("Pause");
		return false;
	}

	for (int i = 0; i < wektorZnajomych.size(); i++) {

		if (wektorZnajomych[i].id == szukaneId) {
			return true;
		}
	}
}

vector<Znajomy> usuwanieZnajomegoZListyKontaktow(vector<Znajomy> wektorZnajomych) {

	system("cls");
	cout << "Podaj id kontaktu do usuniecia: ";
	int idZnajomegoDoUsuniecia;
	cin >> idZnajomegoDoUsuniecia;

	string wyborUrzytkownika;
	fstream plik;

	bool czyToIdJestWWektorze = false;

	czyToIdJestWWektorze = szukanieKonkretnegoIdWWektorze(wektorZnajomych, idZnajomegoDoUsuniecia);
	if (czyToIdJestWWektorze) {

		for (int i = 0; i < wektorZnajomych.size(); i++) {
			if (idZnajomegoDoUsuniecia == wektorZnajomych[i].id) {
				system("cls");
				cout << wektorZnajomych[i].imie << endl;
				cout << wektorZnajomych[i].nazwisko << endl;
				cout << wektorZnajomych[i].email << endl;
				cout << wektorZnajomych[i].adres << endl;
				cout << wektorZnajomych[i].numerTelefonu << endl;
				cout << endl;
			}
		}

		cout << endl;
		cout << "Czy chcesz usunac tego znajomego z listy kontaktow? [t/n]" << endl;
		cin >> wyborUrzytkownika;
		if (wyborUrzytkownika == "t" || wyborUrzytkownika == "y" || wyborUrzytkownika == "tak" || wyborUrzytkownika == "yes") {

			plik.open("temp.txt", ios::out);
			if (plik.good()) {

				for (int i = 0; i < wektorZnajomych.size(); i++) {
					if (idZnajomegoDoUsuniecia == wektorZnajomych[i].id) {
						continue;
					}else{
						plik << wektorZnajomych[i].id << "|";
						plik << wektorZnajomych[i].imie << "|";
						plik << wektorZnajomych[i].nazwisko << "|";
						plik << wektorZnajomych[i].numerTelefonu << "|";
						plik << wektorZnajomych[i].email << "|";
						plik << wektorZnajomych[i].adres << "|" << endl;
					}
				}

				plik.close();

				remove("ksiazka_adresowa.txt");
				rename("temp.txt", "ksiazka_adresowa.txt");

				int numerZnajomegoDoUsuniecia = 0;
				for (int i = 0; i < wektorZnajomych.size(); i++) {
					if (wektorZnajomych[i].id == idZnajomegoDoUsuniecia) {
						numerZnajomegoDoUsuniecia = i;
					}
				}
				wektorZnajomych.erase(wektorZnajomych.begin() + numerZnajomegoDoUsuniecia);

				cout << endl;
				cout << "Kontakt usuniety!" << endl;
				cout << endl;
				system("Pause");
				return wektorZnajomych;
			}else {
				plik.close();
				cout << "Blad odczytu pliku!" << endl;
				cout << endl;
				system("Pause");
				return wektorZnajomych;
			}
		}else{
			cout << endl;
			cout << "Nie usunieto kontaktu!" << endl;
			cout << endl;
			system("Pause");
			return wektorZnajomych;
		}
	}else {
		cout << endl;
		cout << "Kontakt o podanym id nie istnieje!" << endl;
		cout << endl;
		system("Pause");
		return wektorZnajomych;
	}
}

vector<Znajomy> edytujZnajomego(vector<Znajomy> wektorZnajomych, int idZnajomegoDoEdycji, int wyborUrzytkownika, string ktoraDanaZmienic) {

	fstream plik;

	int zmPomDoEdycjiDanejZnajomego;

	for (int i = 0; i < wektorZnajomych.size(); i++) {
		if (wektorZnajomych[i].id == idZnajomegoDoEdycji) {
			zmPomDoEdycjiDanejZnajomego = i;
		}
	}

	switch (wyborUrzytkownika) {
	case 1:
		wektorZnajomych[zmPomDoEdycjiDanejZnajomego].imie = ktoraDanaZmienic;
		break;
	case 2:
		wektorZnajomych[zmPomDoEdycjiDanejZnajomego].nazwisko = ktoraDanaZmienic;
		break;
	case 3:
		wektorZnajomych[zmPomDoEdycjiDanejZnajomego].numerTelefonu = ktoraDanaZmienic;
		break;
	case 4:
		wektorZnajomych[zmPomDoEdycjiDanejZnajomego].email = ktoraDanaZmienic;
		break;
	case 5:
		wektorZnajomych[zmPomDoEdycjiDanejZnajomego].adres = ktoraDanaZmienic;
		break;
	}

	plik.open("ksiazka_adresowa.txt", ios::out);
	if (plik.good()) {
		if (idZnajomegoDoEdycji > 1) {
			for (int i = 0; i < zmPomDoEdycjiDanejZnajomego; i++) {
				plik << wektorZnajomych[i].id << "|";
				plik << wektorZnajomych[i].imie << "|";
				plik << wektorZnajomych[i].nazwisko << "|";
				plik << wektorZnajomych[i].numerTelefonu << "|";
				plik << wektorZnajomych[i].email << "|";
				plik << wektorZnajomych[i].adres << "|" << endl;
			}
		}

		plik << wektorZnajomych[zmPomDoEdycjiDanejZnajomego].id << "|";
		plik << wektorZnajomych[zmPomDoEdycjiDanejZnajomego].imie << "|";
		plik << wektorZnajomych[zmPomDoEdycjiDanejZnajomego].nazwisko << "|";
		plik << wektorZnajomych[zmPomDoEdycjiDanejZnajomego].numerTelefonu << "|";
		plik << wektorZnajomych[zmPomDoEdycjiDanejZnajomego].email << "|";
		plik << wektorZnajomych[zmPomDoEdycjiDanejZnajomego].adres << "|" << endl;

		if (zmPomDoEdycjiDanejZnajomego + 1 < wektorZnajomych.size()) {
			for (int i = idZnajomegoDoEdycji; i < wektorZnajomych.size(); i++) {
				plik << wektorZnajomych[i].id << "|";
				plik << wektorZnajomych[i].imie << "|";
				plik << wektorZnajomych[i].nazwisko << "|";
				plik << wektorZnajomych[i].numerTelefonu << "|";
				plik << wektorZnajomych[i].email << "|";
				plik << wektorZnajomych[i].adres << "|" << endl;
			}
		}
		plik.close();
		cout << endl;
		cout << "Kontakt zmieniony" << endl;
		cout << endl;
		system("Pause");
		return wektorZnajomych;
	}
	else {
		plik.close();
		cout << "Blad odczytu pliku!" << endl;
		system("Pause");
		return wektorZnajomych;
	}
}

vector<Znajomy> wyswietlPodmenuEdycjiZnajomego(vector<Znajomy> wektorZnajomych)
{
	system("cls");
	cout << "Podaj id kontaktu do edycji: ";
	int idZnajomegoDoEdycji;
	cin >> idZnajomegoDoEdycji;

	bool czyIstniejeMozliwoscEdycji = false;

	czyIstniejeMozliwoscEdycji = szukanieKonkretnegoIdWWektorze(wektorZnajomych, idZnajomegoDoEdycji);

	while (czyIstniejeMozliwoscEdycji) {
		system("cls");
		cout << "Edytuj:" << endl;
		cout << "1. Imie" << endl;
		cout << "2. Nazwisko" << endl;
		cout << "3. Numer telefonu" << endl;
		cout << "4. Email" << endl;
		cout << "5. Adres" << endl;
		cout << "6. Powrot do menu glownego" << endl;
		cout << endl;
		cout << "Twoj wybor: ";
		int wyborUrzytkownika;
		cin >> wyborUrzytkownika;

		switch(wyborUrzytkownika){
		case 1: {
			system("cls");
			string noweImie;
			cout << "Podaj nowe imie: ";
			cin >> noweImie;
			wektorZnajomych = edytujZnajomego(wektorZnajomych, idZnajomegoDoEdycji, wyborUrzytkownika, noweImie);
			break;
		}
		case 2:	{
			system("cls");
			string noweNazwisko;
			cout << "Podaj nowe nazwisko: ";
			cin >> noweNazwisko;
			wektorZnajomych = edytujZnajomego(wektorZnajomych, idZnajomegoDoEdycji, wyborUrzytkownika, noweNazwisko);
			break;
			}
		case 3: {
			system("cls");
			string nowyNumerTelefonu;
			cout << "Podaj nowy numer telefonu: ";
			cin.ignore();
			getline(cin, nowyNumerTelefonu);
			wektorZnajomych = edytujZnajomego(wektorZnajomych, idZnajomegoDoEdycji, wyborUrzytkownika, nowyNumerTelefonu);
			break;
			}
		case 4: {
			system("cls");
			string nowyEmail;
			cout << "Podaj nowy email: ";
			cin >> nowyEmail;
			wektorZnajomych = edytujZnajomego(wektorZnajomych, idZnajomegoDoEdycji, wyborUrzytkownika, nowyEmail);
			break;
			}
		case 5: {
			system("cls");
			string nowyAdres;
			cout << "Podaj nowy adres: ";
			cin.ignore();
			getline(cin, nowyAdres);
			wektorZnajomych = edytujZnajomego(wektorZnajomych, idZnajomegoDoEdycji, wyborUrzytkownika, nowyAdres);
			break;
			}
		case 6: {
			wektorZnajomych = wektorZnajomych;						
			czyIstniejeMozliwoscEdycji = false;
			}
		}
	}	
	return wektorZnajomych;
}

void balladaNaDowidzenia()
{
	system("cls");
	cout << "Dziekujemy za skorzystanie z naszych uslug :)" << endl;
	cout << endl << endl << endl;
	Sleep(1000);
	exit(0);
}

int main() {

	vector<Znajomy> wektorZnajomych;

	wektorZnajomych = odczytZnajomychZPliku(wektorZnajomych);
	
	while (true) {
		
		system("cls");
		cout << "KSIAZKA ADRESOWA" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "MENU" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "1. Dodaj znajomego do kontaktow" << endl;
		cout << "2. Wyszukaj znajomego w ksiazce kontaktow" << endl;
		cout << "3. Wyswietl wszystkie kontakty" << endl;
		cout << "4. Usun kontakt" << endl;
		cout << "5. Edytuj kontakt" << endl;
		cout << "6. Zakoncz program" << endl;
		cout << endl;
		cout << "Twoj wybor: ";
		int wyborUrzytkownika;
		cin >> wyborUrzytkownika;

		switch (wyborUrzytkownika)
		{
		case 1:
			wektorZnajomych = dodajZnajomegoDoListyKontaktow(wektorZnajomych);
			break;
		case 2:
			wybierzSposobWyszukiwaniaZnajomego(wektorZnajomych);
			break;
		case 3:					
			wyswietlWszystkichZnajomychZWektora(wektorZnajomych);			
			break;
		case 4:				
			wektorZnajomych = usuwanieZnajomegoZListyKontaktow(wektorZnajomych);
			break;
		case 5:			
			wektorZnajomych = wyswietlPodmenuEdycjiZnajomego(wektorZnajomych);
			break;
		case 6:
			balladaNaDowidzenia();
		}				
	}
}

