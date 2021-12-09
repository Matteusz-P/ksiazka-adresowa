#include <iostream>
#include <fstream>
#include<windows.h>
#include<algorithm>
#include<string>
#include<vector>
#include<sstream>
#include "uzytkownik.h"

using namespace std;

struct daneOsobowe
{
    int id;
    string imie;
    string nazwisko;
    string email;
    string numer_telefonu;
    string adres;
};
struct Uzytkownik
{
    int id;
    string login, haslo;
};

void podmianaPlikow ()
{
    remove("KsiazkaAdresowa.txt");
    rename ("KsiazkaAdresowa2.txt", "KsiazkaAdresowa.txt");
}

void zapisanieNowychKontaktowDoPliku (vector <daneOsobowe>& ksiazkaAdresowa, int IdZalogowanegoUzytkownika)
{
    fstream plikKontaktow;
    int ilosc = ksiazkaAdresowa.size();

    plikKontaktow.open("KsiazkaAdresowa.txt",ios::out | ios::app);

    plikKontaktow<<ksiazkaAdresowa[ilosc-1].id<<"|";
    plikKontaktow<<IdZalogowanegoUzytkownika<<"|";
    plikKontaktow<<ksiazkaAdresowa[ilosc-1].imie<<"|";
    plikKontaktow<<ksiazkaAdresowa[ilosc-1].nazwisko<<"|";
    plikKontaktow<<ksiazkaAdresowa[ilosc-1].email<<"|";
    plikKontaktow<<ksiazkaAdresowa[ilosc-1].numer_telefonu<<"|";
    plikKontaktow<<ksiazkaAdresowa[ilosc-1].adres<<"|"<<endl;
    plikKontaktow.close();
}

void przepisaniePlikuPoUsuwaniu (daneOsobowe daneZnajomego, fstream &nowyPlikKontaktow, int idZPliku, int usunieteID)
{

    if(usunieteID!=daneZnajomego.id)
    {
        nowyPlikKontaktow<<daneZnajomego.id<<"|";
        nowyPlikKontaktow<<idZPliku<<"|";
        nowyPlikKontaktow<<daneZnajomego.imie<<"|";
        nowyPlikKontaktow<<daneZnajomego.nazwisko<<"|";
        nowyPlikKontaktow<<daneZnajomego.email<<"|";
        nowyPlikKontaktow<<daneZnajomego.numer_telefonu<<"|";
        nowyPlikKontaktow<<daneZnajomego.adres<<"|"<<endl;
    }
}
void przepisanieZmianDoPliku(vector <daneOsobowe>& ksiazkaAdresowa, daneOsobowe daneZnajomego, int idZPliku,fstream& nowyPlikKontaktow )
{
    vector<daneOsobowe>::iterator zapisywanyKontakt;
    for (zapisywanyKontakt =ksiazkaAdresowa.begin(); zapisywanyKontakt<=ksiazkaAdresowa.end(); zapisywanyKontakt++)
    {
        if(zapisywanyKontakt->id==daneZnajomego.id)
        {
            nowyPlikKontaktow<<zapisywanyKontakt->id<<"|";
            nowyPlikKontaktow<<idZPliku<<"|";
            nowyPlikKontaktow<<zapisywanyKontakt->imie<<"|";
            nowyPlikKontaktow<<zapisywanyKontakt->nazwisko<<"|";
            nowyPlikKontaktow<<zapisywanyKontakt->email<<"|";
            nowyPlikKontaktow<<zapisywanyKontakt->numer_telefonu<<"|";
            nowyPlikKontaktow<<zapisywanyKontakt->adres<<"|"<<endl;
            break;
        }
        else if (zapisywanyKontakt==ksiazkaAdresowa.end())
        {
            nowyPlikKontaktow<<daneZnajomego.id<<"|";
            nowyPlikKontaktow<<idZPliku<<"|";
            nowyPlikKontaktow<<daneZnajomego.imie<<"|";
            nowyPlikKontaktow<<daneZnajomego.nazwisko<<"|";
            nowyPlikKontaktow<<daneZnajomego.email<<"|";
            nowyPlikKontaktow<<daneZnajomego.numer_telefonu<<"|";
            nowyPlikKontaktow<<daneZnajomego.adres<<"|"<<endl;
        }
    }
}

void zapisanieDoNowegoPliku ( vector <daneOsobowe>& ksiazkaAdresowa,int szukaneId)
{
    string linia;
    fstream plikKontaktow;
    fstream nowyPlikKontaktow;
    vector<daneOsobowe>::iterator zapisywanyKontakt;
    int idZPliku;
    daneOsobowe daneZnajomego;
    plikKontaktow.open("KsiazkaAdresowa.txt", ios::in);
    nowyPlikKontaktow.open("KsiazkaAdresowa2.txt", ios::out);

    if (plikKontaktow.good()==false)
    {
        cout<<"Nie udalo sie otworzyc pliku!";
        Sleep(1000);
    }

    while(getline(plikKontaktow,linia))
    {
        stringstream pobranaLinia(linia);
        string danaOsobowa;
        vector<string> pobraneDane;

        while(getline(pobranaLinia,danaOsobowa, '|'))
        {
            pobraneDane.push_back(danaOsobowa);
        }
        for(int i =0; i<7; i++)
        {
            switch(i)
            {
            case 0:
                daneZnajomego.id = atoi(pobraneDane[i].c_str());
                break;
            case 1:
                idZPliku=atoi(pobraneDane[i].c_str());
                break;
            case 2:
                daneZnajomego.imie=pobraneDane[i];
                break;
            case 3:
                daneZnajomego.nazwisko=pobraneDane[i];
                break;
            case 4:
                daneZnajomego.email = pobraneDane[i];
                break;
            case 5:
                daneZnajomego.numer_telefonu = pobraneDane[i];
                break;
            case 6:
                daneZnajomego.adres = pobraneDane[i];
                break;
            }
        }
        if (szukaneId==0)
        {
            przepisanieZmianDoPliku(ksiazkaAdresowa,daneZnajomego,idZPliku,nowyPlikKontaktow);
        }
        else
        {
            przepisaniePlikuPoUsuwaniu(daneZnajomego,nowyPlikKontaktow,idZPliku,szukaneId);
        }

    }
    nowyPlikKontaktow.close();
    plikKontaktow.close();
    podmianaPlikow();
}


string pobieranieAdresuEmail (vector <daneOsobowe>& ksiazkaAdresowa)
{
    char wybor;
    string email;
    int ilosc=ksiazkaAdresowa.size();
    do
    {
        wybor = '1';
        system("cls");
        cout<<"Podaj adres email: ";
        cin>>email;
        for (int i = 0; i<ilosc; i++)
        {
            if (email==ksiazkaAdresowa[i].email)
            {

                cout<<"Podany adres email jest juz przypisany do innego kontaktu. Czy adres jest prawidlowy?"<<endl;
                cout<<"1 .TAK"<<endl;
                cout<<"2. NIE"<<endl;
                cin>>wybor;
                break;
            }
        }

    }
    while (wybor=='2');

    return email;
}

string pobieranieNumeruTelefonu ()
{
    int dlugosc_numeru;
    string numer_telefonu;
    char wybor;
    do
    {
        wybor = '1';
        system("cls");
        cout<<"Podaj numer telefonu: ";
        cin>>numer_telefonu;
        dlugosc_numeru=numer_telefonu.length();
        if (dlugosc_numeru!=9)
        {
            cout<<"Numer telefonu ma dlugosc inna niz 9 cyfr. Czy numer telefonu jest poprawny?"<<endl;
            cout<<"1 .TAK"<<endl;
            cout<<"2. NIE"<<endl;
            cin>>wybor;
        }
        else wybor='1';
    }
    while(wybor=='2');

    return numer_telefonu;
}
/*int generowanieIDuzytkownika (vector <Uzytkownik>& uzytkownicy)
{
    int ilosc = uzytkownicy.size();
    int wygenerowaneID;

    if(ilosc>0)
    {
        wygenerowaneID=uzytkownicy[ilosc-1].id;
        wygenerowaneID++;
        return wygenerowaneID;
    }
    else
    {
        wygenerowaneID=1;
        return wygenerowaneID;
    }
}*/

int pobieranieDanychkontaktu (vector <daneOsobowe>& ksiazkaAdresowa,int ostatniId, int idZalogowanegoUzytkownika)
{
    char wybor = '1';
    daneOsobowe daneZnajomego;

    while(wybor=='1')
    {
        system("cls");
        cout<<"Podaj imie: ";
        cin>>daneZnajomego.imie;
        system("cls");
        cout<<"Podaj nazwisko: ";
        cin>>daneZnajomego.nazwisko;
        daneZnajomego.email = pobieranieAdresuEmail(ksiazkaAdresowa);
        daneZnajomego.numer_telefonu = pobieranieNumeruTelefonu();
        cin.sync();
        system("cls");
        cout<<"Podaj adres: ";
        getline(cin,daneZnajomego.adres );
        cin.sync();
        daneZnajomego.id=ostatniId+1;
        system("cls");
        ksiazkaAdresowa.push_back(daneZnajomego);
        ostatniId++;
        zapisanieNowychKontaktowDoPliku(ksiazkaAdresowa,idZalogowanegoUzytkownika);
        cout<<"Kontakt zostal zapisany"<<endl;
        cout<<"Czy chcesz zapisac kolejny kontakt?"<<endl;
        cout<<"1 .TAK"<<endl;
        cout<<"2. NIE"<<endl;
        cin>>wybor;
    }
    return daneZnajomego.id;
}


int otwieraniePlikuZapisanychDanych ( vector <daneOsobowe>& ksiazkaAdresowa, int IDuzytkownika)
{
    string linia;
    int idZPliku;
    fstream plikKontaktow;
    daneOsobowe daneZnajomego;
    plikKontaktow.open("KsiazkaAdresowa.txt", ios::in);

    if (plikKontaktow.good()==false)
    {
        cout<<"Nie udalo sie otworzyc pliku!";
        Sleep(1000);
        return 0;

    }

    while(getline(plikKontaktow,linia))
    {
        stringstream pobranaLinia(linia);
        string danaOsobowa;
        vector<string> pobraneDane;

        while(getline(pobranaLinia,danaOsobowa, '|'))
        {
            pobraneDane.push_back(danaOsobowa);
        }
        for(int i =0; i<7; i++)
        {
            switch(i)
            {
            case 0:
                daneZnajomego.id = atoi(pobraneDane[i].c_str());
                break;
            case 1:
                idZPliku=atoi(pobraneDane[i].c_str());
                break;
            case 2:
                daneZnajomego.imie=pobraneDane[i];
                break;
            case 3:
                daneZnajomego.nazwisko=pobraneDane[i];
                break;
            case 4:
                daneZnajomego.email = pobraneDane[i];
                break;
            case 5:
                daneZnajomego.numer_telefonu = pobraneDane[i];
                break;
            case 6:
                daneZnajomego.adres = pobraneDane[i];
                break;
            }
        }
        if(idZPliku==IDuzytkownika)
        {
            ksiazkaAdresowa.push_back(daneZnajomego);
        }
    }
    plikKontaktow.close();

    return daneZnajomego.id;
}

void zapisanieDanychDoPliku ( vector <daneOsobowe>& ksiazkaAdresowa, int IdZalogowanegoUzytkownika)
{
    fstream plikKontaktow;
    int ilosc = ksiazkaAdresowa.size();

    plikKontaktow.open("wizytowka.txt",ios::out);
    for (int i=0; i<ilosc; i++)
    {
        plikKontaktow<<ksiazkaAdresowa[i].id<<"|";
        plikKontaktow<<IdZalogowanegoUzytkownika<<"|";
        plikKontaktow<<ksiazkaAdresowa[i].imie<<"|";
        plikKontaktow<<ksiazkaAdresowa[i].nazwisko<<"|";
        plikKontaktow<<ksiazkaAdresowa[i].email<<"|";
        plikKontaktow<<ksiazkaAdresowa[i].numer_telefonu<<"|";
        plikKontaktow<<ksiazkaAdresowa[i].adres<<"|"<<endl;
    }
    plikKontaktow.close();
}

void wyszukiwaniePoImieniu (vector <daneOsobowe>& ksiazkaAdresowa)
{
    string imie;
    string imieDuzymi;
    int liczbaWynikow=0;
    int ilosc = ksiazkaAdresowa.size();

    system("cls");
    cout<<"Podaj imie znajomego: ";
    cin>>imie;
    transform(imie.begin(), imie.end(), imie.begin(), ::toupper);
    system("cls");
    for (int i=0; i<ilosc; i++)
    {
        imieDuzymi=ksiazkaAdresowa[i].imie;
        transform(imieDuzymi.begin(), imieDuzymi.end(), imieDuzymi.begin(), ::toupper);
        if(imieDuzymi==imie)
        {
            cout<<ksiazkaAdresowa[i].id<<endl;
            cout<<ksiazkaAdresowa[i].imie<<endl;
            cout<<ksiazkaAdresowa[i].nazwisko<<endl;
            cout<<ksiazkaAdresowa[i].email<<endl;
            cout<<ksiazkaAdresowa[i].numer_telefonu<<endl;
            cout<<ksiazkaAdresowa[i].adres<<endl;
            cout<<"-------------"<<endl;
            liczbaWynikow++;
        }
    }
    if(liczbaWynikow==0)cout<<"Nie znaleziono kontaktow o podanym imieniu"<<endl;
    cout<<"-------------"<<endl;
    cout<<"Nacisnij 'Enter', aby przejsc do nowego wyszukiwania"<<endl;
    Sleep(1000);
    getchar();
    getchar();
}
void wyszukiwaniePoNaziwsku (vector <daneOsobowe>& ksiazkaAdresowa)
{
    int liczbaWynikow=0;
    string nazwisko;
    string nazwiskoDuzymi;
    int ilosc = ksiazkaAdresowa.size();

    system("cls");
    cout<<"Podaj imie znajomego: ";
    cin>>nazwisko;
    transform(nazwisko.begin(), nazwisko.end(), nazwisko.begin(), ::toupper);
    system("cls");
    for (int i=0; i<ilosc; i++)
    {
        nazwiskoDuzymi=ksiazkaAdresowa[i].nazwisko;
        transform(nazwiskoDuzymi.begin(), nazwiskoDuzymi.end(), nazwiskoDuzymi.begin(), ::toupper);
        if(nazwiskoDuzymi==nazwisko)
        {
            cout<<ksiazkaAdresowa[i].id<<endl;
            cout<<ksiazkaAdresowa[i].imie<<endl;
            cout<<ksiazkaAdresowa[i].nazwisko<<endl;
            cout<<ksiazkaAdresowa[i].email<<endl;
            cout<<ksiazkaAdresowa[i].numer_telefonu<<endl;
            cout<<ksiazkaAdresowa[i].adres<<endl;
            cout<<"-------------"<<endl;
            liczbaWynikow++;
        }
    }
    if(liczbaWynikow==0)cout<<"Nie znaleziono kontaktow o podanym nazwisku"<<endl;
    cout<<"-------------"<<endl;
    cout<<"Nacisnij 'Enter', aby przejsc do nowego wyszukiwania"<<endl;
    Sleep(1000);
    getchar();
    getchar();
}
void wyswietlanieWszystkichKontaktow (vector <daneOsobowe>& ksiazkaAdresowa)
{
    int ilosc = ksiazkaAdresowa.size();

    system("cls");

    if (ksiazkaAdresowa.empty()==FALSE)
    {
        for (int i=0; i<ilosc; i++)
        {
            cout<<ksiazkaAdresowa[i].id<<endl;
            cout<<ksiazkaAdresowa[i].imie<<endl;
            cout<<ksiazkaAdresowa[i].nazwisko<<endl;
            cout<<ksiazkaAdresowa[i].email<<endl;
            cout<<ksiazkaAdresowa[i].numer_telefonu<<endl;
            cout<<ksiazkaAdresowa[i].adres<<endl;
            cout<<"-------------"<<endl;
        }
        cout<<"Nacisnij 'Enter', aby wrocic do menu"<<endl;
        Sleep(1000);
        getchar();
        getchar();
    }
    else
    {
        cout<<"Nie masz jeszcze kontaktow.";
        Sleep(2000);
    }

}
void zmianaDanych ( vector<daneOsobowe>::iterator zmienianyKontakt, char wybranaOpcja)
{
    switch (wybranaOpcja)
    {
    case '1':
    {
        string imie;
        system("cls");
        cout<<"Prosze podac nowe imie: ";
        cin>>imie;
        zmienianyKontakt->imie=imie;
        cout<<"Imie zostalo zmienione.";
        Sleep(1000);
        break;
    }
    case '2':
    {
        string nazwisko;
        system("cls");
        cout<<"Prosze podac nowe nazwisko: ";
        cin>>nazwisko;
        zmienianyKontakt->nazwisko=nazwisko;
        cout<<"Nazwisko zostalo zmienione.";
        Sleep(1000);
        break;
    }
    case '3':
    {
        string email;
        system("cls");
        cout<<"Prosze podac nowy email: ";
        cin>>email;
        zmienianyKontakt->email=email;
        cout<<"Email zostal zmieniony.";
        Sleep(1000);
        break;
    }
    case '4':
    {
        string numerTelefonu;
        system("cls");
        cout<<"Prosze podac nowy numer telefonu: ";
        cin>>numerTelefonu;
        zmienianyKontakt->numer_telefonu=numerTelefonu;
        cout<<"Numer telefonu zostal zmieniony.";
        Sleep(1000);
        break;
    }
    case '5':
    {
        system("cls");
        string adres;
        system("cls");
        cout<<"Prosze podac nowy adres: ";
        cin>>adres;
        zmienianyKontakt->adres=adres;
        cout<<"Adres zostal zmieniony.";
        Sleep(1000);
        break;
    }
    case '6':
    {
        system("cls");
        break;
    }
    }

}

void szukaniePoIDKontaktu (vector <daneOsobowe>& ksiazkaAdresowa, char wybor)
{
    vector<daneOsobowe>::iterator zmienianyKontakt;
    int szukaneID;
    char wybranaOpcja;

    system("cls");

    cout<<"Jakie dane chcesz zmienic?"<<endl;
    cout<<"1. Imie"<<endl;
    cout<<"2. Nazwisko"<<endl;
    cout<<"3. Email"<<endl;
    cout<<"4. Numer telefonu"<<endl;
    cout<<"5. Adres"<<endl;
    cout<<"6. Powrot do menu glownego"<<endl;
    cin>>wybranaOpcja;

    while(wybranaOpcja!='6'&&wybor!='2')
    {

        system("cls");
        cout<<"Prosze podac ID kontaktu: ";
        cin>>szukaneID;

        for (zmienianyKontakt =ksiazkaAdresowa.begin(); zmienianyKontakt<=ksiazkaAdresowa.end(); zmienianyKontakt++)
        {
            if(zmienianyKontakt->id==szukaneID)
            {
                system("cls");
                cout<<"Zaleziony kontakt to "<<zmienianyKontakt->imie<<" "<<zmienianyKontakt->nazwisko<<" "<<zmienianyKontakt->adres<<endl;
                cout<<"Czy chcesz wyszukac inny kontakt?"<<endl;
                cout<<"1. TAK"<<endl;
                cout<<"2. NIE"<<endl;
                cin>>wybor;
                if (wybor=='2')
                {
                    zmianaDanych(zmienianyKontakt,wybranaOpcja);
                }
                break;
            }
            else if (zmienianyKontakt==ksiazkaAdresowa.end())
            {
                system("cls");
                cout<<"Nie znaleziono kontaktu"<<endl;
                cout<<"Czy chcesz wyszukac inny kontakt?"<<endl;
                cout<<"1. TAK"<<endl;
                cout<<"2. NIE"<<endl;
                cin>>wybor;

            }
        }
    }

}

void usuwanieKontaktu     (vector <daneOsobowe>& ksiazkaAdresowa, char wybor)
{
    vector<daneOsobowe>::iterator zmienianyKontakt;
    int szukaneID;
    char wybranaOpcja;
    do
    {
        system("cls");
        cout<<"Prosze podac ID kontaktu: ";
        cin>>szukaneID;


        for (zmienianyKontakt =ksiazkaAdresowa.begin(); zmienianyKontakt<=ksiazkaAdresowa.end(); zmienianyKontakt++)
        {
            if(zmienianyKontakt->id==szukaneID)
            {
                system("cls");
                cout<<"Twoj kontakt to "<<zmienianyKontakt->imie<<" "<<zmienianyKontakt->nazwisko<<" "<<zmienianyKontakt->adres<<endl;
                cout<<"Czy chcesz usunac ten kontakt?"<<endl;
                cout<<"1. TAK"<<endl;
                cout<<"2. NIE"<<endl;
                cin>>wybranaOpcja;
                switch (wybranaOpcja)
                {
                case '1':
                {
                    system("cls");
                    ksiazkaAdresowa.erase(zmienianyKontakt);
                    cout<<"Kontakt zostal usuniety";
                    Sleep(1000);
                    zapisanieDoNowegoPliku(ksiazkaAdresowa,szukaneID);


                }
                case '2':
                {
                    system("cls");
                    cout<<"Czy chcesz wyszukac inny kontakt?"<<endl;
                    cout<<"1. TAK"<<endl;
                    cout<<"2. NIE"<<endl;
                    cin>>wybor;

                }
                }
                break;
            }
            else if (zmienianyKontakt==ksiazkaAdresowa.end())
            {
                system("cls");
                cout<<"Nie znaleziono kontaktu"<<endl;
                cout<<"Czy chcesz wyszukac inny kontakt?"<<endl;
                cout<<"1. TAK"<<endl;
                cout<<"2. NIE"<<endl;
                cin>>wybor;

            }
        }
    }
    while(wybor=='1');
}

/*void ladowanieUzytkownikowZPliku (vector <Uzytkownik>& uzytkownicy)
{
    string linia;
    fstream plikUzytkowinkow;
    Uzytkownik daneLogowania;
    plikUzytkowinkow.open("Uzytkownicy.txt", ios::in);

    if (plikUzytkowinkow.good()==false)
    {
        cout<<"Nie udalo sie otworzyc pliku!";
        Sleep(1000);

    }

    while(getline(plikUzytkowinkow,linia))
    {
        stringstream pobranaLinia(linia);
        string danaUzytkownika;
        vector<string> pobraneDane;

        while(getline(pobranaLinia,danaUzytkownika, '|'))
        {
            pobraneDane.push_back(danaUzytkownika);
        }
        for(int i =0; i<3; i++)
        {
            switch(i)
            {
            case 0:
                daneLogowania.id = atoi(pobraneDane[i].c_str());
                break;
            case 1:
                daneLogowania.login=pobraneDane[i];
                break;
            case 2:
                daneLogowania.haslo=pobraneDane[i];
                break;
            }

        }
        uzytkownicy.push_back(daneLogowania);
    }
    plikUzytkowinkow.close();
}*/
/*void zapisanieUzytkownikow ( vector <Uzytkownik>& uzytkownicy)
{
    fstream plikUzytkowinkow;
    int ilosc = uzytkownicy.size();

    plikUzytkowinkow.open("Uzytkownicy.txt",ios::out);
    for (int i=0; i<ilosc; i++)
    {
        plikUzytkowinkow<<uzytkownicy[i].id<<"|";
        plikUzytkowinkow<<uzytkownicy[i].login<<"|";
        plikUzytkowinkow<<uzytkownicy[i].haslo<<"|"<<endl;
    }
    plikUzytkowinkow.close();
}
*/
/*void rejestracja (vector<Uzytkownik>& uzytkownicy)
{
    vector<Uzytkownik>::iterator istniejacyUzytkownik=uzytkownicy.begin();
    Uzytkownik nowyUzytkownik;
    string nazwaUzytkownika, haslo;

    system("cls");
    cout<<"Podaj nazwe uzytkownika: ";
    cin>>nazwaUzytkownika;

    while (istniejacyUzytkownik<uzytkownicy.end())
    {
        if (istniejacyUzytkownik->login==nazwaUzytkownika)
        {
            system("cls");
            cout<<"Nazwa uzytkownika jest zajeta. Podaj inna nazwe uzytkownika: ";
            cin>>nazwaUzytkownika;
            istniejacyUzytkownik =uzytkownicy.begin();
        }
        else istniejacyUzytkownik++;
    }
    system("cls");
    cout<<"Podaj haslo: ";
    cin>>haslo;
    nowyUzytkownik.login=nazwaUzytkownika;
    nowyUzytkownik.haslo=haslo;
    nowyUzytkownik.id=generowanieIDuzytkownika(uzytkownicy);
    uzytkownicy.push_back(nowyUzytkownik);
    system("cls");
    cout<<"Konto zostalo zalozone";
    Sleep(1000);
}*/

/*void zmianaHasla (vector<Uzytkownik>&uzytkownicy, int idZalogowanegoUzytkownika)
{
    vector<Uzytkownik>::iterator istniejacyUzytkownik;
    string noweHaslo;


    system("cls");
    cout<<"Podaj nowe haslo: ";
    cin>>noweHaslo;

    for (istniejacyUzytkownik=uzytkownicy.begin(); istniejacyUzytkownik<=uzytkownicy.end(); istniejacyUzytkownik++)
    {
        if (istniejacyUzytkownik->id==idZalogowanegoUzytkownika)
        {
            system("cls");
            istniejacyUzytkownik->haslo=noweHaslo;
            cout<<"Haslo zostalo zmienione.";
            Sleep(1000);
        }
    }
}
*/
/*int logowanie (vector<Uzytkownik>&uzytkownicy)
{
    string nazwaUzytkownika, haslo;
    vector<Uzytkownik>::iterator istniejacyUzytkownik=uzytkownicy.begin();

    system("cls");
    cout<<"Podaj login: ";
    cin>>nazwaUzytkownika;
    while (istniejacyUzytkownik<uzytkownicy.end())
    {
        if (istniejacyUzytkownik->login==nazwaUzytkownika)
        {
            for(int i=0; i<3; i++)
            {
                system("cls");
                cout<<"Podaj haslo. Pozostala ilosc prob "<<(3-i)<<". Haslo: ";
                cin>>haslo;
                if (istniejacyUzytkownik->haslo==haslo)
                {
                    system("cls");
                    cout<<"Zostales zalogowany.";
                    Sleep(1000);
                    return istniejacyUzytkownik->id;
                }
            }
            system("cls");
            cout<<"Podales blednie haslo 3 razy. Poczekaj na mozliwosc ponownej proby logowania";
            Sleep(3000);
            return 0;
        }
        else istniejacyUzytkownik++;
    }
    system("cls");
    cout<<"Nie odnaleziono loginu w systemie.";
    Sleep(1500);
    return 0;
}*/

int main()
{
    vector <daneOsobowe> ksiazkaAdresowa;
    char wybor='0';
    int idZalogowanegoUzytkownika=0;
    int kontaktID=0;
    User u(0,"brak","brak");
u.ladowanie();




    while (1)
    {
        if (idZalogowanegoUzytkownika==0)
        {

            system("cls");
            cout<<"---MENU GLOWNE---"<<endl;
            cout<<"1. Logowanie"<<endl;
            cout<<"2. Rejestracja"<<endl;
            cout<<"9. Zamknij program"<<endl;
            cin>>wybor;

            if (wybor == '1')
            {
                idZalogowanegoUzytkownika=u.logowanie();
                kontaktID=  otwieraniePlikuZapisanychDanych(ksiazkaAdresowa,idZalogowanegoUzytkownika);
            }
            else if(wybor == '2')
            {
                u.rejestracja ();
                u.zapisanieUzytkownikow();
            }
            else if (wybor == '9')
            {
                system("cls");
                cout<<"Program zostanie zamkniety";
                Sleep(1000);
                exit(0);
            }
        }


        else
        {
            system("cls");
            cout<<"---MENU GLOWNE---"<<endl;
            cout<<"1. Zapisz nowy kontakt"<<endl;
            cout<<"2. Szukaj kontaktu"<<endl;
            cout<<"3. Wyswietl wszystkie kontakty"<<endl;
            cout<<"4. Usun kontakt"<<endl;
            cout<<"5. Zmien dane kontaktu"<<endl;
            cout<<"6. Zmien haslo"<<endl;
            cout<<"9. Wyloguj sie"<<endl;
            cin>>wybor;

            if (wybor == '1')
            {
                kontaktID=pobieranieDanychkontaktu(ksiazkaAdresowa, kontaktID,idZalogowanegoUzytkownika);
            }
            else if(wybor == '2')
            {
                while(1)
                {
                    system("cls");
                    cout<<"1. Wyszukaj po imieniu"<<endl;
                    cout<<"2. Wyszukaj po nazwisku"<<endl;
                    cout<<"3. Wroc do menu glownego"<<endl;
                    cin>>wybor;
                    if (wybor == '1')
                    {
                        wyszukiwaniePoImieniu(ksiazkaAdresowa);
                    }
                    else if(wybor == '2')
                    {
                        wyszukiwaniePoNaziwsku(ksiazkaAdresowa);
                    }
                    else if(wybor == '3')
                    {
                        break;
                    }
                }
            }
            else if(wybor == '3')
            {
                wyswietlanieWszystkichKontaktow(ksiazkaAdresowa);
            }
            else if(wybor == '4')
            {
                usuwanieKontaktu(ksiazkaAdresowa,wybor);
            }
            else if(wybor == '5')
            {
                szukaniePoIDKontaktu(ksiazkaAdresowa,wybor);
                zapisanieDoNowegoPliku(ksiazkaAdresowa,0);
            }
            else if(wybor == '6')
            {
                u.zmianaHasla(idZalogowanegoUzytkownika);
                u.zapisanieUzytkownikow();
            }
            else if (wybor == '9')
            {
                idZalogowanegoUzytkownika=0;
                ksiazkaAdresowa.clear();
            }
        }
    }
    return 0;
}
