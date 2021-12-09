#include <iostream>
#include <fstream>
#include<windows.h>
#include<algorithm>
#include<string>
#include<vector>
#include<sstream>
#include "uzytkownik.h"

using namespace std;


void User::ladowanie (vector<User>&users)
{
    string linia;
    fstream plikUzytkowinkow;
// vector<User>users;
    User daneLogowania;
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
        users.push_back(daneLogowania);
    }
    plikUzytkowinkow.close();
}

int User::logowanie (vector<User>&uzytkownicy)
{
    string nazwaUzytkownika, haslo;
    vector<User>::iterator istniejacyUzytkownik=uzytkownicy.begin();

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
}

void User::rejestracja (vector<User>& uzytkownicy)
{
    vector<User>::iterator istniejacyUzytkownik=uzytkownicy.begin();
    User nowyUzytkownik;
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
}

int User::generowanieIDuzytkownika (vector <User>& uzytkownicy)
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
}

void User::zapisanieUzytkownikow ( vector <User>& uzytkownicy)
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

void User::zmianaHasla (vector<User>&uzytkownicy, int idZalogowanegoUzytkownika)
{
    vector<User>::iterator istniejacyUzytkownik;
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
