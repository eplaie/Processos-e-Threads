#ifndef escalonador_hpp
#define escalonador_hpp

#include <bits/stdc++.h>

using namespace std;

struct processo {
    int chegada;
    int duracao;
    int inicio_execucao;
    int final_execucao;
    int id;
    int restante;
};

struct estatisticas_processos {
    double turnaround;
    double tempo_medio_resposta;
    double tempo_medio_espera;
};

struct arquivo_saida {
    vector<string> saida_fifo;
    vector<string> saida_sjf;
    vector<string> saida_rr;
};

class escalonador {
    private:
        vector<pair<int, int>> lista_processos;
        estatisticas_processos est_fifo;
        estatisticas_processos est_sjf;
        estatisticas_processos est_rr;
        arquivo_saida texto_saida;
    public:
        escalonador(); // construtor
        ~escalonador(); 
        vector<pair<int, int>> get_lista_processos(void);
        estatisticas_processos get_est_fifo();
        estatisticas_processos get_est_sjf();
        estatisticas_processos get_est_rr();
        arquivo_saida get_arquivo_saida();

        void set_lista_processos(vector<pair<int, int>>);
        void set_est_fifo(estatisticas_processos);
        void set_est_sjf(estatisticas_processos);
        void set_est_rr(estatisticas_processos);
        void set_arquivo_saida(arquivo_saida);
        void fifo();
        void le_arquivo_entrada(string);
        void sjf(void);
        void sjf_preemptivo(void);
        void roundrobin(int);
        void escreve_historico_processos();
        void mostra_estatisticas();
};

struct compare_fifo {
    bool operator()(processo const& p1, processo const& p2)
    {
        if(p1.chegada == p2.chegada)
            return p1.id > p2.id;
        return p1.chegada > p2.chegada;
    }
};

struct compare_sjf {
    bool operator()(processo const& p1, processo const& p2)
    {
        return p1.duracao > p2.duracao;
    }
};
#endif