#include <iostream>


using namespace std;

class User
{
    private:
    int id;
    string login, haslo;
    public:
    vector<User> users;


public:
    int generowanieIDuzytkownika(vector <User>& users);
   void ladowanie(vector<User>&users);
   int logowanie (vector<User>&users);
   void rejestracja (vector<User>& users);
   void zapisanieUzytkownikow ( vector <User>& users);
   void zmianaHasla (vector<User>&users, int idZalogowanegoUzytkownika);
};
