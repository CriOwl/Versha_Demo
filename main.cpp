#include <iostream>
#include <string>
#include <windows.h>
#include <cctype>
#include <cstdlib>
#include <limits>
#include "funciones.cpp"
#include <cstdlib>
#include <fstream>

using namespace std;

struct player {
    string nombre_jugador;
    int score = 0;
    int id_player = 0;
    int vidas = 2;
    int comodines[3] = {1, 2, 3};
};

struct questions {
    string preguntas;
    string opciones[4];
    char opcion_correcta = 'a';
};

const int cantidad_pre = 15;
player *jugadores = new player[25];
questions *preguntas_juego = new questions[cantidad_pre];

//variables
int opcion_random;
int tabla[25];
int id_global = 0;

//funciones
void insercion_datos(int casos, int id);

char string_char(const string &opcion);

void menu();

void Registro_datos(int id);

void partida(int id);

void MostarPuntaje(int id);

int comodines(int tipo, int pregunta, int id);

char string_char(const string &opcion) {
    return opcion[0];
}

void puntajes(int id);

void insercion_datos(int casos, int id) {
    switch (casos) {
        case 1: {
            ifstream preguntas("banco.txt");
            for (int i = 0; i < cantidad_pre; i++) {
                getline(preguntas, preguntas_juego[i].preguntas);
                for (int j = 0; j < 4; j++) {
                    getline(preguntas, preguntas_juego[i].opciones[j]);
                }
            }
            preguntas.close();
            string opcion_correcta;
            ifstream opcionc("opciones.txt");
            for (int i = 0; i < cantidad_pre; i++) {
                getline(opcionc, opcion_correcta);
                preguntas_juego[i].opcion_correcta = string_char(opcion_correcta);
            }
            opcionc.close();
            break;
        }
        case 2: {
            ofstream puntuaciones_G("tabla_Pos.txt");
            for (int i = 0; i < id + 1; i++) {
                tabla[i] = jugadores[i].score;
            }
            for (int j = 0; j < id + 1; j++) {
                int aux;
                for (int i = 0; i < id; i++) {
                    //ordenamiento burbuja
                    if (tabla[i] < tabla[i + 1]) {
                        aux = tabla[i + 1];
                        tabla[i + 1] = tabla[i];
                        tabla[i] = aux;
                    }
                }
            }
            for (int i = 0; i < id + 1; i++) {
                for (int j = 0; j < id + 1; j++) {
                    if (jugadores[j].score == tabla[i]) {
                        //busqueda e insercion de datos
                        puntuaciones_G << "\nJugador: " << jugadores[j].nombre_jugador << "  Puntuacion: " << jugadores[
                                j].score;
                    }
                }
            }
        }
    }
}


void menu() {
    int option;
    //poner acento a la palabra
    char wordo = 162;
    char worde = 130;
    char worda = 160;
    //char wordu = 163;
    do {
        system("cls");
        LogoMenu();
        cout << "\t\t\t------------------------------------------------------------------ " << endl;
        cout << "\t\t\t|               1.- Nueva partida                                | " << endl;
        cout << "\t\t\t|               2.- Cr" << worde << "ditos                                     | " << endl;
        cout << "\t\t\t|               3.- Puntajes                                     | " << endl;
        cout << "\t\t\t|               4.- Salir                                        | " << endl;
        cout << "\t\t\t------------------------------------------------------------------ " << endl;
        cout << "\t\t\t------------------------------------------------------------------ " << endl;
        cout << "\t\t\t Ingrese opci" << wordo << "n: ";;
        cin >> option;
        if (cin.fail()) {
            //validad de entrada
            cin.clear();
            cin.ignore();
            option = 5;
            cout << "\t\t Ingrese un numero, por favor " << endl;
            system("pause");
        } else {
            switch (option) {
                case 1: {
                    InicarJuego();
                    Registro_datos(id_global);
                    partida(id_global);
                    id_global = id_global + 1;
                    break;
                }
                case 2: {
                    system("cls");
                    MostrarCreditos();
                    break;
                }
                case 3: {
                    system("cls");
                    //puntajes(id);
                    MostrarPuntaje(id_global);
                    break;
                }
                case 4: {
                    system("cls");
                    SalirJuego();
                    break;
                }
                default: {
                    cout << "\n";

                    cout << "\t\t\t Opci" << wordo << "n no v" << worda << "lida..." << endl;

                    cout << " " << endl;
                    system("pause");
                    break;
                }
            }
        }
    } while (option != 4);
}

void Registro_datos(int id) {
    cout << "\t\t\t Ingrese el apodo del jugador " << id + 1 << ": ";
    cin >> jugadores[id].nombre_jugador;
    jugadores[id].id_player = id;
}


void partida(int id) {
    int i = 0;
    string opcion_string;
    char opcion_char;
    while (jugadores[id].vidas > 0 || i == cantidad_pre) {
        cout << "\t\t Puntuacion: " << jugadores[id].score << "               " << "Vidas: " << jugadores[id].vidas <<
             endl;
        cout << preguntas_juego[i].preguntas << endl;
        for (int j = 0; j < 4; j++) {
            cout << preguntas_juego[i].opciones[j] << endl;
        }
        //comodines
        if (jugadores[id].comodines[0] != 0) {
            cout << "\t 1. Llamada a un experto";
        }
        if (jugadores[id].comodines[1] != 0) {
            cout << "\t 2. Llamada al publico";
        }
        if (jugadores[id].comodines[2] != 0) {
            cout << "\t 3. 50/50";
        }
        cout << "\n";
        cout << "\t\t Escoga la opcion correcta o un comodin: ", cin >> opcion_string;
        opcion_char = string_char(opcion_string);
        switch (opcion_char) {
            case '1': {
                i = comodines(1, i, id_global);
                break;
            }
            case '2': {
                i = comodines(2, i, id_global);
                break;
            }
            case '3': {
                i = comodines(3, i, id_global);
                break;
            }
            default: {
                if (opcion_char == preguntas_juego[i].opcion_correcta) {
                    jugadores[id].score = jugadores[id].score + 1000;
                    cout << "\t\t\t Felicitaciones Acertaste";
                } else {
                    jugadores[id].vidas = jugadores[id].vidas - 1;
                    cout << "\t\t Fallaste ";
                    cout << "\n";
                    cout << "\t\t La opcion correcta... ";
                    cout << preguntas_juego[i].opcion_correcta << endl;
                    cout << "\n";
                }
                i = i + 1;
            }
        }
    }
    insercion_datos(2, id_global);
    if (jugadores[id].vidas != 0) {
        cout<<"felicidades ganaste";
        Win();
    } else {
        cout<<"felicidades perdiste";
        GameOver();
    }
}

int comodines(int tipo, int pregunta, int id) {
    string opcion_string;
    char opcion_char;
    char opcion_co = preguntas_juego[pregunta].opcion_correcta;
    switch (tipo) {
        case 1: {
            //Llamada al publico
            if (jugadores[id].comodines[0] != 0) {
                cout << "\n";
                cout << "\t\t LLamando a un experto ..." << endl;
                cout << "\t\t Yo creo que es .. " << preguntas_juego[pregunta].opcion_correcta << endl;
                jugadores[id].comodines[0] = 0;
                cout << " " << endl;
            }
            return pregunta;
        }
        case 2: {
            //Graficos en ascii con casos
            if (jugadores[id].comodines[1] != 0) {
                switch (opcion_co) {
                    case 'a': {
                        MostrarOpcionA();
                        break;
                    }
                    case 'b': {
                        MostrarOpcionB();
                        break;
                    }
                    case 'c': {
                        MostrarOpcionC();
                        break;
                    }
                    case 'd': {
                        MostrarOpcionD();
                        break;
                    }
                }
            }
            jugadores[id].comodines[1] = 0;
            return pregunta;
        }
        case 3: {
            //50 50
            if (jugadores[id].comodines[2] != 0) {
                cout << preguntas_juego[pregunta].preguntas << endl;
                switch (preguntas_juego[pregunta].opcion_correcta) {
                    case 'a': {
                        cout << preguntas_juego[pregunta].opciones[0] << endl;
                        do { opcion_random = rand() % 4; } while (opcion_random == 0);
                        cout << preguntas_juego[pregunta].opciones[opcion_random] << endl;
                        break;
                    }
                    case 'b': {
                        do { opcion_random = rand() % 4; } while (opcion_random == 1);
                        cout << preguntas_juego[pregunta].opciones[1] << endl;
                        cout << preguntas_juego[pregunta].opciones[opcion_random] << endl;
                        break;
                    }
                    case 'c': {
                        do { opcion_random = rand() % 4; } while (opcion_random == 2);
                        cout << preguntas_juego[pregunta].opciones[2] << endl;
                        cout << preguntas_juego[pregunta].opciones[opcion_random] << endl;
                        break;
                    }
                    case 'd': {
                        do { opcion_random = rand() % 4; } while (opcion_random == 3);
                        cout << preguntas_juego[pregunta].opciones[opcion_random] << endl;
                        cout << preguntas_juego[pregunta].opciones[3] << endl;
                        break;
                    }
                }
                cout << "\n ";
                cout << "\t\t Escoga la opcion correcta: ", cin >> opcion_string;
                opcion_char = string_char(opcion_string);
                if (opcion_char == preguntas_juego[pregunta].opcion_correcta) {
                    jugadores[id].score = jugadores[id].score + 1000;
                    cout << "\t\t Felicitaciones Acertaste";
                } else {
                    jugadores[id].vidas = jugadores[id].vidas - 1;
                    cout << "\n";
                    cout << "\t\t Fallaste";
                    cout << "\n";
                    cout << "\t\t La opcion correcta...";
                    cout << preguntas_juego[pregunta].opcion_correcta << endl;
                }
                jugadores[id].comodines[2] = 0;
                return pregunta + 1;
            }
        }
    }
}

void puntajes(int id) {
    string puntajes[25];
    ifstream posiciones("tabla_Pos.txt");
    for (int i = 0; i < 5; i++) {
        getline(posiciones, puntajes[i]);
        cout << puntajes[i] << endl;
    }
}


int main() {
    LogoPrincipal();
    insercion_datos(1, id_global);
    menu();
    return 0;
}
/*
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;

struct player {
    string nombre_jugador;
    int score = 0;
    int id_player = 0;
    int vidas = 2;
    int comodines[3] = {1, 2, 3};
};

struct questions {
    string preguntas;
    string opciones[4];
    char opcion_correcta = 'a';
};

const int cantidad_pre = 15;
player *jugadores = new player[25];
questions *preguntas_juego = new questions[cantidad_pre];
//variables
int opcion_random;
int id = 0;
int tabla[25];

//funciones
void insercion_datos(int casos = 0);

char string_char(const string &opcion);

void menu();

void Registro_datos(int id);

void partida(int id);

int comodines(int tipo, int pregunta);

char string_char(const string &opcion) {
    return opcion[0];
}
void puntajes(int id);
void insercion_datos(int casos) {
    switch (casos) {
        case 1: {
            ifstream preguntas("banco.txt");
            for (int i = 0; i < cantidad_pre; i++) {
                getline(preguntas, preguntas_juego[i].preguntas);
                for (int j = 0; j < 4; j++) {
                    getline(preguntas, preguntas_juego[i].opciones[j]);
                }
            }
            preguntas.close();
            string opcion_correcta;
            ifstream opcionc("opciones.txt");
            for (int i = 0; i < cantidad_pre; i++) {
                getline(opcionc, opcion_correcta);
                preguntas_juego[i].opcion_correcta = string_char(opcion_correcta);
            }
            opcionc.close();
            break;
        }
        case 2: {
            ofstream puntuaciones_G("tabla_Pos.txt");
            for (int i = 0; i < id + 1; i++) {
                tabla[i] = jugadores[i].score;
            }
            for (int j = 0; j < id + 1; j++) {
                int aux;
                for (int i = 0; i < id; i++) {
                    //ordenamiento burbuja
                    if (tabla[i] < tabla[i + 1]) {
                        aux = tabla[i + 1];
                        tabla[i + 1] = tabla[i];
                        tabla[i] = aux;
                    }
                }
            }
            for (int i = 0; i < id + 1; i++) {
                for (int j = 0; j < id + 1; j++) {
                    if (jugadores[j].score == tabla[i]) {
                        //busqueda e insercion de datos
                        puntuaciones_G << "\nJugador: " << jugadores[j].nombre_jugador << "  Puntuacion: " << jugadores[
                            j].score;
                    }
                }
            }
        }
    }
}

void menu() {
    int option;
    do {
        cout << "1.Nueva Partida";
        cout << "\n2.Creditos";
        cout << "\n3.Puntajes";
        cout << "\n4.Salir";
        cout << "\nEscoga una opcion:";
        cin >> option;
        if (cin.fail()) {
            //validad de entrada
            cin.clear();
            cin.ignore();
            option = 5;
            cout << "\nIngrese un numero" << endl;
        } else {
            switch (option) {
                case 1: {
                    Registro_datos(id);
                    partida(id);
                    id = id + 1;
                    break;
                }
                case 2: {
                    break;
                }
                case 3: {
                    puntajes(id);
                    break;
                }
                case 4: {
                    break;
                }
                default: {
                    cout << "Ingrese un valor valido";
                }
            }
        }
    } while (option != 4);
}

void Registro_datos(int id) {
    cout << "Ingreso del apodo del jugador " << id + 1 << ": ";
    cin >> jugadores[id].nombre_jugador;
    jugadores[id].id_player = id;
}

void partida(int id) {
    int i = 0;
    string opcion_string;
    char opcion_char;
    while (jugadores[id].vidas > 0 || i == cantidad_pre) {
        cout << "Puntuacion: " << jugadores[id].score << "               " << "Vidas: " << jugadores[id].vidas <<
                endl;
        cout << preguntas_juego[i].preguntas << endl;
        for (int j = 0; j < 4; j++) {
            cout << preguntas_juego[i].opciones[j] << endl;
        }
        //comodines
        if (jugadores[id].comodines[0] != 0) {
            cout << "1. Llamada a un experto";
        }
        if (jugadores[id].comodines[1] != 0) {
            cout << "\t2. Llamada al publico";
        }
        if (jugadores[id].comodines[2] != 0) {
            cout << "\t3. 50/50";
        }
        cout << "\nEscoga la opcion correcta o un comodin:";
        cin >> opcion_string;
        opcion_char=string_char(opcion_string);
        switch (opcion_char) {
            case '1': {
                i = comodines(1, i);
                break;
            }
            case '2': {
                i = comodines(2, i);
                break;
            }
            case '3': {
                i = comodines(3, i);
                break;
            }
            default: {
                if (opcion_char == preguntas_juego[i].opcion_correcta) {
                    jugadores[id].score = jugadores[id].score + 1000;
                    cout << "Felicitaciones Acertaste";
                } else {
                    jugadores[id].vidas = jugadores[id].vidas - 1;
                    cout << "\nFallaste";
                    cout << "\nLa opcion correcta...";
                    cout << preguntas_juego[i].opcion_correcta << endl;
                }
                i = i + 1;
            }
        }
    }
    insercion_datos(2);
}

int comodines(int tipo, int pregunta) {
    string opcion_string;
    char opcion_char;
    char opcion_co = preguntas_juego[pregunta].opcion_correcta;
    switch (tipo) {
        case 1: {
            //Llamada al publico
            if (jugadores[id].comodines[0] != 0) {
                cout << "\nLLamando a un experto ..." << endl;
                cout << "Yo creo que es .." << preguntas_juego[pregunta].opcion_correcta << endl;
                jugadores[id].comodines[0] = 0;
            }
            return pregunta;
        }
        case 2: {
            //Graficos en ascii con casos
            if (jugadores[id].comodines[1] != 0) {
                switch (opcion_co) {
                    case 'a': {
                        break;
                    }
                    case 'b': {
                        break;
                    }
                    case 'c': {
                        break;
                    }
                    case 'd': {
                        break;
                    }
                }
            }
            jugadores[id].comodines[1] = 0;
            return pregunta;
        }
        case 3: {
            //50 50
            if (jugadores[id].comodines[2] != 0) {
                cout << preguntas_juego[pregunta].preguntas << endl;
                switch (preguntas_juego[pregunta].opcion_correcta) {
                    case 'a': {
                        cout << preguntas_juego[pregunta].opciones[0] << endl;
                        do { opcion_random = rand() % 4; } while (opcion_random == 0);
                        cout << preguntas_juego[pregunta].opciones[opcion_random] << endl;
                        break;
                    }
                    case 'b': {
                        do { opcion_random = rand() % 4; } while (opcion_random == 1);
                        cout << preguntas_juego[pregunta].opciones[1] << endl;
                        cout << preguntas_juego[pregunta].opciones[opcion_random] << endl;
                        break;
                    }
                    case 'c': {
                        do { opcion_random = rand() % 4; } while (opcion_random == 2);
                        cout << preguntas_juego[pregunta].opciones[2] << endl;
                        cout << preguntas_juego[pregunta].opciones[opcion_random] << endl;
                        break;
                    }
                    case 'd': {
                        do { opcion_random = rand() % 4; } while (opcion_random == 3);
                        cout << preguntas_juego[pregunta].opciones[opcion_random] << endl;
                        cout << preguntas_juego[pregunta].opciones[3] << endl;
                        break;
                    }
                }
                cout << "\nEscoga la opcion correcta:";
                cin >> opcion_string;
                opcion_char=string_char(opcion_string);
                if (opcion_char == preguntas_juego[pregunta].opcion_correcta) {
                    jugadores[id].score = jugadores[id].score + 1000;
                    cout << "Felicitaciones Acertaste";
                } else {
                    jugadores[id].vidas = jugadores[id].vidas - 1;
                    cout << "\nFallaste";
                    cout << "\nLa opcion correcta...";
                    cout << preguntas_juego[pregunta].opcion_correcta << endl;
                }
                jugadores[id].comodines[2] = 0;
                return pregunta + 1;
            }
        }
    }
}
void puntajes(int id) {
    string puntajes[25];
    ifstream posiciones("tabla_Pos.txt");
    for (int i=0;i<5;i++) {
        getline(posiciones,puntajes[i]);
        cout<<puntajes[i]<<endl;
    }
}

int main() {
    insercion_datos(1);
    menu();
    return 0;
}*/


