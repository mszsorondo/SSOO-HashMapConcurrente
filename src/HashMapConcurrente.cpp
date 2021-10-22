#ifndef CHM_CPP
#define CHM_CPP

#include <thread>
// alternativamente #include <pthread.h>
#include <iostream>
#include <fstream>
#include "HashMapConcurrente.hpp"

using namespace std;

HashMapConcurrente::HashMapConcurrente() {
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        tabla[i] = new ListaAtomica<hashMapPair>();
    }
}

unsigned int HashMapConcurrente::hashIndex(std::string clave) {
    return (unsigned int)(clave[0] - 'a');
}

ListaAtomica<hashMapPair>::iterator HashMapConcurrente::itSearch(string clave){
    unsigned int index = hashIndex(clave);
    ListaAtomica<hashMapPair> *tabla = (this->tabla)[index];

    ListaAtomica<hashMapPair>::iterator it = (*tabla).begin();
    while(it != (*tabla).end() && (*it).first != clave)
        it++;

    return it;

}

std::mutex ms[26];
void HashMapConcurrente::incrementar(std::string clave) {
    unsigned int index = hashIndex(clave);
    ListaAtomica<hashMapPair> *lista = (this->tabla)[index];


    ms[index].lock();//---------

    ListaAtomica<hashMapPair>::iterator it = itSearch(clave);
    if(it == (*lista).end()){
        this->c.push_back(clave);
        lista->insertar(make_pair(clave, 0));
        it = (*lista).begin();
    }
    (*it).second++;

    ms[index].unlock();//-------
}

std::vector<std::string> HashMapConcurrente::claves() {
    return this->c;
}

unsigned int HashMapConcurrente::valor(std::string clave) {
    ListaAtomica<hashMapPair> *lista = (this->tabla)[hashIndex(clave)];

    ListaAtomica<hashMapPair>::iterator it = itSearch(clave);

    if(it == (*lista).end())
        return 0;
    
    return(*it).second;
}

hashMapPair HashMapConcurrente::maximo() {
    hashMapPair *max = new hashMapPair();
    max->second = 0;

    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        for (auto &p : *tabla[index]) {
            if (p.second > max->second) {
                max->first = p.first;
                max->second = p.second;
            }
        }
    }

    return *max;
}


hashMapPair HashMapConcurrente::maximoParalelo(unsigned int cant_threads) {
    // Completar (Ejercicio 3)
}

#endif
