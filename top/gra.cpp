#include <iostream>
#include "biblioteka.h"
#include <chrono>
#include <future>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

bool timeout(int& a, int s);
void gra(int gracz);

// Funkcja do odczytu odpowiedzi z ograniczeniem czasowym.
bool timeout(int& a, int s)
{
    auto future = async(launch::async, [&] {
        int temp;
        cin >> temp;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            clear_screen();
        }
        return temp;
        });

    // Czekamy
    if (future.wait_for(chrono::seconds(s)) == future_status::ready)
    {
        // Jeœli w wyznaczonym czasie
        a = future.get();
        return true;
    }
    else
    {
        // Jeœli przekroczono limit czasu
        return false;
    }
}

void gra(int gracz)
{
    // Inicjalizator generatora liczb losowych z time
    srand(static_cast<unsigned int>(time(nullptr)));

    const int LICZBA_PYTAN = 10;
    int poprawneOdpowiedzi = 0;
    int lineNumber = (1 + (gracz - 1) * 3);
    
    levelup(gracz);
    for (int i = 0; i < LICZBA_PYTAN; i++)
    {
        int level = readline(przelicznik(gracz) + 1);

        int zakres;
        if (level == 1)
        {
            zakres = 10;
        }
        else if (level == 2)
        {
            zakres = 20;
        }
        else if (level == 3)
        {
            zakres = 50;
        }
        else if (level == 4)
        {
            zakres = 100;
        }
        else if (level == 5)
        {
            zakres = 1000;
        }
        else
        {
            // Poziom poza zakresem 1–5
            zakres = 10;
        }

        int a = rand() % zakres + 1;
        int b = rand() % zakres + 1;
        // Losujemy dwie liczby

        cout << "  Ile to jest " << a << " x " << b << "? (Masz 10 sekund na odpowiedz): ";

        int odpowiedz;
        if (timeout(odpowiedz, 10))
        {
            if (odpowiedz == a * b)
            {
                clear_screen();
                cout << "\033[1;32m  Dobrze!\033[0m\n";
                cout << "  \n";
                poprawneOdpowiedzi++;
            }
            else
            {
                clear_screen();
                cout << "\033[1;31m  Zle.\033[0m\n";
                cout << "  \n";
            }
        }
        else
        {
            clear_screen();
            cout << "\n  Przekroczono limit czasu! " << "  Prawidlowa odpowiedz to: " << (a * b) << "\n";
        }
    }

    // Obliczamy procent poprawnych odpowiedzi
    int procentPoprawnych = (static_cast<double>(poprawneOdpowiedzi)) * 10.0;
    loaddata(gracz, to_string(procentPoprawnych));
    clear_screen();
    cout << "\n  Poprawnych odpowiedzi: " << poprawneOdpowiedzi << "/" << LICZBA_PYTAN << endl;
    cout << "  Procent poprawnych odpowiedzi: " << procentPoprawnych << "%\n";
    cout << "  Komputer 2 " << "%\n";
    cout << "  " << endl;

}
