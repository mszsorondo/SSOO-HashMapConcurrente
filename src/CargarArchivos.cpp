#ifndef CHM_CPP
#define CHM_CPP

#include <vector>
#include <iostream>
#include <fstream>
#include <pthread.h>    //lib de threads

#include "CargarArchivos.hpp"

int cargarArchivo(HashMapConcurrente &hashMap, std::string filePath) {
    std::fstream file;
    int cant = 0;
    std::string palabraActual;

    // Abro el archivo.
    file.open(filePath, file.in);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo '" << filePath << "'" << std::endl;
        return -1;
    }
    while (file >> palabraActual) {
        // Completar (Ejercicio 4)
        hashMap.incrementar(palabraActual);
        cant++;
    }
    // Cierro el archivo.
    if (!file.eof()) {
        std::cerr << "Error al leer el archivo" << std::endl;
        file.close();
        return -1;
    }
    file.close();
    return cant;
}

struct arg_struct {
    HashMapConcurrente *hashMap;
    std::vector<std::string> *filePaths;
    atomic<int> *file_index;
}args;

void *stmf(void *varg){ // single thread multiple files

    struct arg_struct *data;
    data = (struct arg_struct*) varg;
    
    int path_index = data->file_index->fetch_add(1); // actualizamos index
    while((long unsigned int) path_index < (*data->filePaths).size()){
        // si estamos aca es que podemos acceder al archivo dentro de filePaths en la posicion path_index
        cargarArchivo(*data->hashMap, (*data->filePaths)[path_index]);

        // actualizamos index
        path_index = data->file_index->fetch_add(1);
    }
    free(varg);
    pthread_exit(NULL); // terminar thread
}

void cargarMultiplesArchivos(HashMapConcurrente &hashMap, unsigned int cantThreads, std::vector<std::string> filePaths) {
    // Completar (Ejercicio 4)
    std::vector<pthread_t> ts (cantThreads);
    atomic<int> count(0); 
    for(long unsigned int i = 0; i < cantThreads; ++i){
        std::cout << "q onda" << "q onda" << endl;
        struct arg_struct *varg = (struct arg_struct *)malloc(sizeof(struct arg_struct));
        varg->hashMap = &hashMap;
        varg->filePaths = &filePaths;
        varg->file_index = &count;
        pthread_create(&ts[i], NULL, &stmf, (void *) varg);
    }

    for(unsigned int i = 0; i < cantThreads ; ++i) // joineamos threads
        pthread_join(ts[i], NULL);
    
}

#endif
