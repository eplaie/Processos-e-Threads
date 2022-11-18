#ifndef kernel_hpp
#define kernel_hpp

#include <bits/stdc++.h>
#include "escalonador.hpp"
#include "gerenciador_es.hpp"
#include "gerenciador_mem.hpp"

using namespace std;

class kernel {
    private:
    int modo_operacao;
    escalonador esc;
    gerenciador_mem g_memoria;

    GerenciadorES gerenciadorES_;

    public:
    kernel(); 
    ~kernel();
    
    int get_modo_operacao();
    escalonador get_escalonador(void);
    GerenciadorES gerenciadorES(void);
    gerenciador_mem get_gerenciador_mem(void);

    void set_modo_operacao(int);
    void set_escalonador(escalonador);
    void setGerenciadorES(GerenciadorES);
    void set_gerenciador_mem(gerenciador_mem);

    void verifica_entrada(int , string);
    void verifica_modo_op(void);
    void gerencia_processos(void);
    void gerencia_memoria(void);
    void gerencia_es(void);
};
#endif