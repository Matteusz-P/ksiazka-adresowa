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
    int generowanieIDuzytkownika();
   void ladowanie();
   int logowanie ();
   void rejestracja ();
   void zapisanieUzytkownikow ( );
   void zmianaHasla (int idZalogowanegoUzytkownika);
};
