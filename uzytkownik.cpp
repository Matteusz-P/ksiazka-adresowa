#include <iostream>
#include <fstream>
#include<windows.h>
#include<algorithm>
#include<string>
#include<vector>
#include<sstream>
#include "uzytkownik.h"

using namespace std;


void User::ladowanie ()
{
    string linia;
    fstream plikUzytkowinkow;
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

int User::logowanie ()
{
    string nazwaUzytkownika, haslo;
    vector<User>::iterator istniejacyUzytkownik=users.begin();

    system("cls");
    cout<<"Podaj login: ";
    cin>>nazwaUzytkownika;
    while (istniejacyUzytkownik<users.end())
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

void User::rejestracja ()
{
    vector<User>::iterator istniejacyUzytkownik=users.begin();
    User nowyUzytkownik;
    string nazwaUzytkownika, haslo;

    system("cls");
    cout<<"Podaj nazwe uzytkownika: ";
    cin>>nazwaUzytkownika;

    while (istniejacyUzytkownik<users.end())
    {
        if (istniejacyUzytkownik->login==nazwaUzytkownika)
        {
            system("cls");
            cout<<"Nazwa uzytkownika jest zajeta. Podaj inna nazwe uzytkownika: ";
            cin>>nazwaUzytkownika;
            istniejacyUzytkownik =users.begin();
        }
        else istniejacyUzytkownik++;
    }
    system("cls");
    cout<<"Podaj haslo: ";
    cin>>haslo;
    nowyUzytkownik.login=nazwaUzytkownika;
    nowyUzytkownik.haslo=haslo;
    nowyUzytkownik.id=generowanieIDuzytkownika();
    users.push_back(nowyUzytkownik);
    system("cls");
    cout<<"Konto zostalo zalozone";
    Sleep(1000);
}

int User::generowanieIDuzytkownika ()
{
    int ilosc = users.size();
    int wygenerowaneID;

    if(ilosc>0)
    {
        wygenerowaneID=users[ilosc-1].id;
        wygenerowaneID++;
        return wygenerowaneID;
    }
    else
    {
        wygenerowaneID=1;
        return wygenerowaneID;
    }
}

void User::zapisanieUzytkownikow ( )
{
    fstream plikUzytkowinkow;
    int ilosc = users.size();

    plikUzytkowinkow.open("Uzytkownicy.txt",ios::out);
    for (int i=0; i<ilosc; i++)
    {
        plikUzytkowinkow<<users[i].id<<"|";
        plikUzytkowinkow<<users[i].login<<"|";
        plikUzytkowinkow<<users[i].haslo<<"|"<<endl;
    }
    plikUzytkowinkow.close();
}

void User::zmianaHasla (int idZalogowanegoUzytkownika)
{
    vector<User>::iterator istniejacyUzytkownik;
    string noweHaslo;


    system("cls");
    cout<<"Podaj nowe haslo: ";
    cin>>noweHaslo;

    for (istniejacyUzytkownik=users.begin(); istniejacyUzytkownik<=users.end(); istniejacyUzytkownik++)
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
