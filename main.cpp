#include <iostream>
#include <fstream>
#include<windows.h>
#include<algorithm>
#include<string>
#include<vector>
#include<sstream>

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
int generowanieID (vector <daneOsobowe>& ksiazkaAdresowa)
{
    int ilosc = ksiazkaAdresowa.size();
    int wygenerowaneID;

    if(ilosc>0)
    {
        wygenerowaneID=ksiazkaAdresowa[ilosc-1].id;
        wygenerowaneID++;
        return wygenerowaneID;
    }
    else if (ilosc==0)
    {
        wygenerowaneID=1;
        return wygenerowaneID;
    }
}

void pobieranieDanychkontaktu (vector <daneOsobowe>& ksiazkaAdresowa, char wybor)
{

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
        daneZnajomego.id=generowanieID(ksiazkaAdresowa);
        system("cls");
        ksiazkaAdresowa.push_back(daneZnajomego);
        cout<<"Kontakt zostal zapisany"<<endl;
        cout<<"Czy chcesz zapisac kolejny kontakt?"<<endl;
        cout<<"1 .TAK"<<endl;
        cout<<"2. NIE"<<endl;
        cin>>wybor;
    }
}


void otwieraniePlikuZapisanychDanych (fstream &plik, vector <daneOsobowe>& ksiazkaAdresowa)
{
    string linia;
    int nr_linii=0;
    daneOsobowe daneZnajomego;
    plik.open("wizytowka.txt", ios::in);

    if (plik.good()==false)
    {
        cout<<"Nie udalo sie otworzyc pliku!";
        Sleep(1000);

    }

    while(getline(plik,linia))
    {
        stringstream pobranaLinia(linia);
        string danaOsobowa;
        vector<string> pobraneDane;

        while(getline(pobranaLinia,danaOsobowa, '|'))
        {
            pobraneDane.push_back(danaOsobowa);
        }
        for(int i =0; i<6; i++)
        {
            switch(i)
            {
            case 0:
                daneZnajomego.id = atoi(pobraneDane[i].c_str());
                break;
            case 1:
                daneZnajomego.imie=pobraneDane[i];
                break;
            case 2:
                daneZnajomego.nazwisko=pobraneDane[i];
                break;
            case 3:
                daneZnajomego.email = pobraneDane[i];
                break;
            case 4:
                daneZnajomego.numer_telefonu = pobraneDane[i];
                break;
            case 5:
                daneZnajomego.adres = pobraneDane[i];
                break;
            }
        }

        ksiazkaAdresowa.push_back(daneZnajomego);
        nr_linii++;
    }
    plik.close();

}

void zapisanieDanychDoPliku (fstream &plik, vector <daneOsobowe>& ksiazkaAdresowa)
{
    int ilosc = ksiazkaAdresowa.size();

    plik.open("wizytowka.txt",ios::out);
    for (int i=0; i<ilosc; i++)
    {
        plik<<ksiazkaAdresowa[i].id<<"|";
        plik<<ksiazkaAdresowa[i].imie<<"|";
        plik<<ksiazkaAdresowa[i].nazwisko<<"|";
        plik<<ksiazkaAdresowa[i].email<<"|";
        plik<<ksiazkaAdresowa[i].numer_telefonu<<"|";
        plik<<ksiazkaAdresowa[i].adres<<"|"<<endl;
    }
    plik.close();
    cout<<"Ksiazka adresowa zostala zapisana";
    Sleep(1000);
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

int main()
{
    vector <daneOsobowe> ksiazkaAdresowa;
    char wybor='0';
    int ostatnieID;

    fstream plikZapisanychDanych;
    otwieraniePlikuZapisanychDanych(plikZapisanychDanych, ksiazkaAdresowa);


    while (1)
    {
        system("cls");
        cout<<"---MENU GLOWNE---"<<endl;
        cout<<"1. Zapisz nowy kontakt"<<endl;
        cout<<"2. Szukaj kontaktu"<<endl;
        cout<<"3. Wyswietl wszystkie kontakty"<<endl;
        cout<<"4. Usun kontakt"<<endl;
        cout<<"5. Zmien dane kontaktu"<<endl;
        cout<<"9. Zakoncz program"<<endl;
        cin>>wybor;

        if (wybor == '1')
        {
            pobieranieDanychkontaktu(ksiazkaAdresowa, wybor);
            zapisanieDanychDoPliku(plikZapisanychDanych,ksiazkaAdresowa);

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
            zapisanieDanychDoPliku(plikZapisanychDanych,ksiazkaAdresowa);
        }
        else if(wybor == '5')
        {
            szukaniePoIDKontaktu(ksiazkaAdresowa,wybor);
            zapisanieDanychDoPliku(plikZapisanychDanych,ksiazkaAdresowa);
        }
        else if (wybor == '9')
        {
            system("cls");
            exit(0);
        }

    }
    return 0;
}
