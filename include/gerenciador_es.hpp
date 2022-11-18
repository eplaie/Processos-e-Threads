#ifndef gerenciador_es_hpp
#define gerenciador_es_hpp

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class GerenciadorES {
    
    private:
    int tamanhoDisco;
    std::string nome_arq;
    public:
    GerenciadorES(); 
    ~GerenciadorES(); 
    void imprimeDistanciaPercorrida(std::string);
    void set_nome_arquivo(std::string);
    std::string get_nome_arquivo(void);
};

int calculaDistanciaPercorrida(std::vector<int>);

void ordenaSSTF(std::vector<int>&, std::vector<int>);

void ordenaSCAN(std::vector<int>&, std::vector<int>);
#endif