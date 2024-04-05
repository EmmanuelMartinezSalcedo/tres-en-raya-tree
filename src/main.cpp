#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
class Arista;
class Nodo {
public:
  vector<Arista*> aristas;
  int id;

  vector<string> tablero;
  int utilidad;
  bool minMax;
  Nodo(int id, bool minMax, vector<string> tablero) {
    this->id = id;
    this->minMax = minMax;
    this->tablero = tablero;
  }
  Nodo(int id) {
    this->id = id;
  }
  ~Nodo() {
    //...
  }
};

class Arista {
public:
	Nodo* nodos[2];
	Arista(Nodo* a, Nodo* b) {
		nodos[0] = a; //Origen
		nodos[1] = b; //Destino
		a->aristas.push_back(this);
		b->aristas.push_back(this);
	}
	~Arista() {
		//...
	}
};

class Grafo
{
public:
	vector<Nodo*> nodos;
  vector<Arista*> aristas;
  
	Grafo(int profundidad, char respuesta) {
    vector<string> tablero = {"   ", "   ", "   "};
    bool minMax; //min = false, max = true
		if (respuesta == 'X') {
      minMax = true;
      insertarNodo(0, minMax, tablero);
    }
    else {
      minMax = false;
      insertarNodo(0, minMax, tablero);
    }
    
    int index = 1;
    for (int i = profundidad - 1; i > 0; i--) {
      !minMax;
      for (int j = 0; j < i; j++) {
        vector<vector<string>> tableros = generarTableros(tablero, minMax);
        insertarNodo(index, minMax, tablero);
      }
    }
	}
	~Grafo() {
		//...
	}

private:
  Nodo* encontrarNodo(int d) {
    for (Nodo* nodo : nodos) {
      if (nodo->id == d) {
        return nodo;
      }
    }
    return NULL;
  }

  vector<vector<string>> generarTableros(vector<string> tablero, bool minMax) {
    vector<string> copy = tablero;
    vector<vector<string>> tableros;
    for (int i = 0; i < copy.size(); i++) {
      for (int j = 0; j < copy.size(); j++) {
        if (copy[i][j] != ' ') {
          copy[i][j] = minMax;
        }
        tableros.push_back(copy);
        copy = tablero;
      }
    }
  }

public:
	void insertarNodo(int id, bool minMax, vector<string> tablero) {
		nodos.push_back(new Nodo(id, minMax, tablero));
	}

	void insertarArista(int idOrigen, int idDestino) {
    Nodo* origen = encontrarNodo(idOrigen);
    Nodo* destino = encontrarNodo(idDestino);

    if (!origen || !destino) {
      return;
    }

		Arista* x = new Arista(origen, destino);
    aristas.push_back(x);
	}

  void borrarNodo(int id) {
    Nodo* nodoEliminar = encontrarNodo(id);

    if (!nodoEliminar)
      return;

    for (Arista* arista : nodoEliminar->aristas) {
        auto& vecinoAristas = arista->nodos[1] == nodoEliminar ? arista->nodos[0]->aristas : arista->nodos[1]->aristas;
        vecinoAristas.erase(remove(vecinoAristas.begin(), vecinoAristas.end(), arista), vecinoAristas.end());
        aristas.erase(remove(aristas.begin(), aristas.end(), arista), aristas.end());
        delete arista;
    }

    nodos.erase(remove(nodos.begin(), nodos.end(), nodoEliminar), nodos.end());
    delete nodoEliminar;
  }

  
};

int main() {
  char respuesta;
  int profundidad;

  cout << "Quien inicia (X,o): ";
  cin >> respuesta;
  respuesta = toupper(respuesta);

  if (respuesta == 'O') {
    cout << "Inicia IA" << endl;
  } else {
    respuesta = 'X';
    cout << "Inicia Jugador" << endl;
  }

  cout << "Dificultad (0 - 10): ";
  cin >> profundidad;

  if (profundidad > 10) {
    profundidad = 10;
  }
  else if (profundidad < 0) {
    profundidad = 0;
  }

  //Grafo arbol(profundidad, respuesta);
}
