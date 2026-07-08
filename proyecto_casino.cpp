#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

#ifdef _WIN32
    #define LIMPIAR_PANTALLA "cls"
#else
    #define LIMPIAR_PANTALLA "clear"
#endif

using namespace std;

int main() {
    srand(time(0));

    int n;

    while (true) {
        cout << "\n========================================\n";
        cout << "Numero de jugadores (2 a 4): ";
        cin >> n;

        if (n == 1) {
            cout << "\n****************************************\n";
            cout << "  No se puede jugar con 1 solo jugador.\n";
            cout << "  Se necesitan al menos 2 jugadores.\n";
            cout << "****************************************\n";
        } else if (n < 1 || n > 4) {
            cout << "\n****************************************\n";
            cout << "  Limite permitido: entre 2 y 4 jugadores.\n";
            cout << "****************************************\n";
        } else {
            break;
        }
    }

    string nombre[4];
    int dinero[4];

    for (int i = 0; i < n; i++) {
        cout << "Nombre: ";
        cin >> nombre[i];
        dinero[i] = 1000;
    }

    int opcion;

    while (true) {

        if (n <= 1) break;

        cout << "\n========================================\n";
        cout << "|              C A S I N O              |\n";
        cout << "========================================\n";
        cout << "1. Ruleta\n";
        cout << "2. Trivia\n";
        cout << "3. Impostor\n";
        cout << "4. Salir\n";
        cout << "========================================\n";
        cin >> opcion;

        if (opcion == 4) break;

        if (opcion == 1) {

            cout << "\n----------------------------------------\n";
            cout << "  RULETA\n";
            cout << "  Apuesta 200$ al rojo (r) o al negro (n).\n";
            cout << "  Si aciertas el color, ganas 200$.\n";
            cout << "  Si fallas, pierdes 200$.\n";
            cout << "----------------------------------------\n";

            string ganadores = "";
            string perdedores = "";

            for (int i = 0; i < n; i++) {

                if (dinero[i] < 200) continue;

                char color;
                cout << "\nTurno de " << nombre[i] << endl;
                cout << "Dinero: $" << dinero[i] << endl;

                cout << "Apuesta (r/n): ";
                cin >> color;

                int num = rand() % 100;
                string res = (num % 2 == 0) ? "rojo" : "negro";

                cout << "Salio: " << res << endl;

                if ((color == 'r' && res == "rojo") ||
                    (color == 'n' && res == "negro")) {

                    cout << "GANASTE +200\n";
                    dinero[i] += 200;
                    ganadores += " [+] " + nombre[i] + "\n";

                } else {
                    cout << "PERDISTE -200\n";
                    dinero[i] -= 200;
                    perdedores += " [-] " + nombre[i] + "\n";
                }
            }

            cout << "\n>>>>>>>>>> RESULTADO DE LA RULETA <<<<<<<<<<\n";
            cout << "-- Ganadores --\n";
            cout << (ganadores == "" ? " (ninguno)\n" : ganadores);
            cout << "-- Perdedores --\n";
            cout << (perdedores == "" ? " (ninguno)\n" : perdedores);
            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
        }

        else if (opcion == 2) {

            cout << "\n----------------------------------------\n";
            cout << "  TRIVIA\n";
            cout << "  Se eligen 3 preguntas al azar entre los\n";
            cout << "  jugadores. Responde correctamente para\n";
            cout << "  ganar 200$, o pierdes 200$ si fallas.\n";
            cout << "----------------------------------------\n";

            string preguntas[3] = {
                "Capital de Francia?",
                "5+3?",
                "Color del cielo?"
            };

            string respuestas[3] = {
                "paris", "8", "azul"
            };

            string ganadores = "";
            string perdedores = "";

            for (int i = 0; i < 3; i++) {

                int turno = rand() % n;

                if (dinero[turno] < 200) continue;

                cout << "\nTurno de " << nombre[turno] << endl;
                cout << preguntas[i] << endl;

                string r;
                cin >> r;

                if (r == respuestas[i]) {
                    cout << "Correcto +200\n";
                    dinero[turno] += 200;
                    ganadores += " [+] " + nombre[turno] + "\n";

                } else {
                    cout << "Incorrecto -200\n";
                    dinero[turno] -= 200;
                    perdedores += " [-] " + nombre[turno] + "\n";
                }
            }

            cout << "\n>>>>>>>>>> RESULTADO DE LA TRIVIA <<<<<<<<<<\n";
            cout << "-- Ganadores --\n";
            cout << (ganadores == "" ? " (ninguno)\n" : ganadores);
            cout << "-- Perdedores --\n";
            cout << (perdedores == "" ? " (ninguno)\n" : perdedores);
            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
        }

        else if (opcion == 3) {

            cout << "\n----------------------------------------\n";
            cout << "  IMPOSTOR\n";
            cout << "  Cada jugador vera en privado si es el\n";
            cout << "  impostor o la palabra secreta. Luego\n";
            cout << "  todos votan quien creen que es el\n";
            cout << "  impostor. Si aciertan, pierde 200$ el\n";
            cout << "  impostor y ese dinero se reparte entre\n";
            cout << "  los demas. Si fallan, el impostor gana\n";
            cout << "  200$ de cada uno de los demas jugadores.\n";
            cout << "----------------------------------------\n";

            string palabras[3] = {"pizza", "perro", "playa"};
            string palabra = palabras[rand() % 3];

            int impostor = rand() % n;

            cin.ignore();

            for (int i = 0; i < n; i++) {

                if (dinero[i] < 200) continue;

                cout << "\nJugador " << nombre[i] << ", presiona ENTER...";
                cin.get();

                if (i == impostor) {
                    cout << " Eres el IMPOSTOR\n";
                } else {
                    cout << " La palabra es: " << palabra << endl;
                }

                cout << "Presiona ENTER para continuar...";
                cin.get();

                system(LIMPIAR_PANTALLA);
            }

            int voto;
            cout << "\nQuien es el impostor (numero): ";

            while (!(cin >> voto)) {
                cout << "\n****************************************\n";
                cout << "  No se permiten letras, solo numeros.\n";
                cout << "****************************************\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Quien es el impostor (numero): ";
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            voto--;

            string ganadores = "";
            string perdedores = "";

            if (voto == impostor) {
                cout << "Correcto! pierde el impostor\n";

                int reparto = 200 / (n - 1);
                int sobra = 200 % (n - 1);

                dinero[impostor] -= 200;
                perdedores += " [-] " + nombre[impostor] + " (impostor)\n";

                for (int i = 0; i < n; i++) {
                    if (i == impostor) continue;

                    dinero[i] += reparto;
                    ganadores += " [+] " + nombre[i] + "\n";
                }

                dinero[(impostor + 1) % n] += sobra;

            } else {
                cout << "Fallaron! gana el impostor\n";

                int totalGanado = 0;

                for (int i = 0; i < n; i++) {
                    if (i == impostor) continue;

                    dinero[i] -= 200;
                    perdedores += " [-] " + nombre[i] + "\n";
                    totalGanado += 200;
                }

                dinero[impostor] += totalGanado;
                ganadores += " [+] " + nombre[impostor] + " (impostor)\n";
            }

            cout << "\n>>>>>>>>>> RESULTADO DEL IMPOSTOR <<<<<<<<<<\n";
            cout << "-- Ganadores --\n";
            cout << (ganadores == "" ? " (ninguno)\n" : ganadores);
            cout << "-- Perdedores --\n";
            cout << (perdedores == "" ? " (ninguno)\n" : perdedores);
            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
        }

        for (int i = 0; i < n; i++) {
            if (dinero[i] < 200) {

                cout << nombre[i] << " eliminado\n";

                for (int j = i; j < n - 1; j++) {
                    nombre[j] = nombre[j + 1];
                    dinero[j] = dinero[j + 1];
                }

                n--;
                i--;
            }
        }

        cout << "\n--- ESTADO ---\n";
        for (int i = 0; i < n; i++) {
            cout << nombre[i] << " $" << dinero[i] << endl;
        }
    }

    cout << "\n========================================\n";
    cout << "|          FIN DEL JUEGO                |\n";
    cout << "========================================\n";

    if (n == 1) {
        cout << " [!] GANADOR: " << nombre[0] << " [!]\n";
    } else {
        cout << " Juego terminado\n";
    }
    cout << "========================================\n";

    return 0;
}