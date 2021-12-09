#include <iostream>


using namespace std;

class User
{
    private:
    int id;
    string login, haslo;


public:
    int generowanieIDuzytkownika(vector <User>& uzytkownicy);
   void ladowanie(vector<User>&users);
   int logowanie (vector<User>&uzytkownicy);
   void rejestracja (vector<User>& uzytkownicy);
   void zapisanieUzytkownikow ( vector <User>& uzytkownicy);
   void zmianaHasla (vector<User>&uzytkownicy, int idZalogowanegoUzytkownika);
};
