#include "escalonador.hpp"
escalonador::escalonador() {
}
escalonador::~escalonador() {
}

vector<pair<int, int>> escalonador::get_lista_processos()
{
    return lista_processos;
}

estatisticas_processos escalonador::get_est_fifo()
{
    return est_fifo;
}

estatisticas_processos escalonador::get_est_sjf()
{
    return est_sjf;
}

estatisticas_processos escalonador::get_est_rr()
{
    return est_rr;
}

arquivo_saida escalonador::get_arquivo_saida()
{
    return texto_saida;
}

void escalonador::set_lista_processos(vector<pair<int, int>> lista)
{
    lista_processos = lista;
    return;
}

void escalonador::set_est_fifo(estatisticas_processos est)
{
    est_fifo = est;
}

void escalonador::set_est_sjf(estatisticas_processos est)
{
    est_sjf = est;
}

void escalonador::set_est_rr(estatisticas_processos est)
{
    est_rr = est;
}

void escalonador::set_arquivo_saida(arquivo_saida arq)
{
    texto_saida = arq;
}

void escalonador::le_arquivo_entrada(string arquivo)
{
    string linha;
    int a, b;
    pair<int, int> par_temp;
    vector<pair<int, int>> lista_temp;
    ifstream MyFile(arquivo);
    // le o arquivo de entrada
    while(getline(MyFile, linha)) {
        istringstream iss(linha);
        iss >> a >> b;
        par_temp = make_pair(a, b);
        lista_temp.push_back(par_temp);

    }
    set_lista_processos(lista_temp);
    MyFile.close();
}

void escalonador::fifo()
{
    int temp_execucao = 0;
    vector<processo> processos_finalizados;
    processo p_temp;
    estatisticas_processos st_fifo;
    string linha_temp;
    vector<string> arq_temp;
    arquivo_saida saida;
    priority_queue<processo, vector<processo>, compare_fifo> pq;
    processo topo_fila;
    for(int i=0; i<lista_processos.size(); i++) {
        p_temp.chegada = lista_processos[i].first;
        p_temp.duracao = lista_processos[i].second;
        p_temp.inicio_execucao = 0;
        p_temp.final_execucao = 0;
        p_temp.id = i;
        pq.push(p_temp);
    }

    while( !(pq.empty()) ) {
        topo_fila = pq.top();
        if( topo_fila.chegada > temp_execucao)
            temp_execucao = topo_fila.chegada;
        topo_fila.inicio_execucao = temp_execucao;
        temp_execucao += topo_fila.duracao;
        topo_fila.final_execucao = temp_execucao;
        pq.pop();
        processos_finalizados.push_back(topo_fila);
    }
    st_fifo.turnaround = 0;
    double soma = 0;
    for(int i=0; i<processos_finalizados.size(); i++) {
        soma += (processos_finalizados[i].inicio_execucao - processos_finalizados[i].chegada);
        st_fifo.turnaround += (processos_finalizados[i].final_execucao - processos_finalizados[i].chegada);
        linha_temp = "Rodou processo[" + to_string(processos_finalizados[i].id) + "] de [" + to_string(processos_finalizados[i].inicio_execucao) +"] ate [" + to_string(processos_finalizados[i].final_execucao) +"]" ;

        arq_temp.push_back(linha_temp);
    }
    st_fifo.turnaround = st_fifo.turnaround/processos_finalizados.size();
    soma = soma/processos_finalizados.size();

    st_fifo.tempo_medio_resposta = soma;
    st_fifo.tempo_medio_espera = soma;

    set_est_fifo(st_fifo);

    saida = get_arquivo_saida();
    saida.saida_fifo = arq_temp;

    set_arquivo_saida(saida);

}


void escalonador::sjf(void)
{
    int tempo_execucao = 0;
    processo p_temp, topo_fila;
    double soma, espera, duracao, resposta = 0;
    vector<processo> processos_finalizados;
    estatisticas_processos st_sjf;
    priority_queue<processo, vector<processo>, compare_fifo> pq;
    priority_queue<processo, vector<processo>, compare_sjf> fila_sjf;
    string linha_temp;
    vector<string> arq_temp;
    arquivo_saida saida;

    for(int i=0; i<lista_processos.size(); i++) {
        p_temp.chegada = lista_processos[i].first;
        p_temp.duracao = lista_processos[i].second;
        p_temp.restante = lista_processos[i].second;
        p_temp.inicio_execucao = -1;
        p_temp.final_execucao = 0;
        p_temp.id = i;
        pq.push(p_temp);
    }


    int proxima_chegada;
    while(1) {
        while( !(pq.empty()) ) {
            topo_fila = pq.top();
            if( topo_fila.chegada <= tempo_execucao ) {
                fila_sjf.push(topo_fila);
                pq.pop();
            }
            else {
                proxima_chegada = topo_fila.chegada;
                break;
            }
        }
        if(fila_sjf.empty() and !(pq.empty())) {
            topo_fila = pq.top();
            tempo_execucao = topo_fila.chegada;
            fila_sjf.push(topo_fila);
            pq.pop();
        }
        if(fila_sjf.empty())
            break;

        p_temp = fila_sjf.top();

        if(p_temp.inicio_execucao == -1) {
            p_temp.inicio_execucao = tempo_execucao;
        }
        fila_sjf.pop();
        tempo_execucao += p_temp.duracao;
        p_temp.final_execucao = tempo_execucao;
        processos_finalizados.push_back(p_temp);  

    }
    duracao = 0;
    espera = 0;
    for(int i=0; i<processos_finalizados.size(); i++) {
        espera += (processos_finalizados[i].final_execucao - processos_finalizados[i].chegada - processos_finalizados[i].duracao);
        duracao += processos_finalizados[i].final_execucao - processos_finalizados[i].chegada;
        resposta += (processos_finalizados[i].inicio_execucao - processos_finalizados[i].chegada);
        linha_temp = "Rodou processo[" + to_string(processos_finalizados[i].id) + "] de [" + to_string(processos_finalizados[i].inicio_execucao) +"] ate [" + to_string(processos_finalizados[i].final_execucao) +"]" ;
        arq_temp.push_back(linha_temp);
    }
  
    espera = espera/processos_finalizados.size();
    duracao = duracao/processos_finalizados.size();
    resposta = resposta/processos_finalizados.size();
    st_sjf.tempo_medio_espera = espera;
    st_sjf.turnaround = duracao;
    st_sjf.tempo_medio_resposta = resposta;
    set_est_sjf(st_sjf);
 
    // escreve o historico e o tempo de execucao dos processos
    saida = get_arquivo_saida();
    saida.saida_sjf = arq_temp;
    set_arquivo_saida(saida);
    
}

void escalonador::roundrobin(int quantum)
{
    int tempo_execucao = 0;
    processo p_temp, topo_fila;
    double soma=0, espera=0, duracao=0, resposta = 0;
    vector<processo> processos_finalizados;
    estatisticas_processos st_rr;
    priority_queue<processo, vector<processo>, compare_fifo> pq;
    queue<processo> fila_rr;
    string linha_temp;
    vector<string> arq_temp;
    arquivo_saida saida;
    for(int i=0; i<lista_processos.size(); i++) {
        p_temp.chegada = lista_processos[i].first;
        p_temp.duracao = lista_processos[i].second;
        p_temp.restante = lista_processos[i].second;
        p_temp.inicio_execucao = -1;
        p_temp.final_execucao = 0;
        p_temp.id = i;
        pq.push(p_temp);
    }
    p_temp.id = -1;
     while(1) {
        while( !(pq.empty()) ) {
            topo_fila = pq.top();
            if( topo_fila.chegada <= tempo_execucao ) {
                fila_rr.push(topo_fila);
                pq.pop();
            }
            else {
                break;
            }
        }
        if(p_temp.restante != 0 and p_temp.id != -1)
            fila_rr.push(p_temp);
        else {
            if(p_temp.id != -1) {
                p_temp.final_execucao = tempo_execucao;
                processos_finalizados.push_back(p_temp);
            }
        }
        if(fila_rr.empty() and !(pq.empty())) {
            topo_fila = pq.top();
            tempo_execucao = topo_fila.chegada;
            fila_rr.push(topo_fila);
            pq.pop();
        }
        if(fila_rr.empty())
            break;

        p_temp = fila_rr.front();
        if(p_temp.inicio_execucao == -1) {
            p_temp.inicio_execucao = tempo_execucao;
        }

        fila_rr.pop();
        // verifica se o processo vai executar pela duracao total do quantum
        if(p_temp.restante >= quantum) {
            linha_temp = "Rodou processo[" + to_string(p_temp.id) + "] de [" + to_string(tempo_execucao) +"] ate [" + to_string(tempo_execucao+quantum) +"]" ;
            p_temp.restante -= quantum;
            tempo_execucao += quantum;
        }
        else {
            linha_temp = "Rodou processo[" + to_string(p_temp.id) + "] de [" + to_string(tempo_execucao) +"] ate [" + to_string(tempo_execucao+p_temp.restante) +"]" ;
            tempo_execucao += p_temp.restante;
            p_temp.restante = 0;
        }
        arq_temp.push_back(linha_temp);
    }
    for(int i=0; i<processos_finalizados.size(); i++) {
        espera += (processos_finalizados[i].final_execucao - processos_finalizados[i].chegada - processos_finalizados[i].duracao);
        duracao += processos_finalizados[i].final_execucao - processos_finalizados[i].chegada;
        resposta += (processos_finalizados[i].inicio_execucao - processos_finalizados[i].chegada);
        
    }
    espera = espera/processos_finalizados.size();
    duracao = duracao/processos_finalizados.size();
    resposta = resposta/processos_finalizados.size();
    st_rr.tempo_medio_espera = espera;
    st_rr.turnaround = duracao;
    st_rr.tempo_medio_resposta = resposta;
    set_est_rr(st_rr);
    saida = get_arquivo_saida();
    saida.saida_rr = arq_temp;
    set_arquivo_saida(saida);
}

void escalonador::escreve_historico_processos()
{
    arquivo_saida historico;
    ofstream MyFile("historico_processos.txt");

    historico = get_arquivo_saida();
    MyFile << "FIFO:\n";
    for(int i=0; i<historico.saida_fifo.size(); i++)
        MyFile << historico.saida_fifo[i] << "\n";

    MyFile << "\nSJF:\n";
    for(int i=0; i<historico.saida_sjf.size(); i++)
        MyFile << historico.saida_sjf[i] << "\n";
    
    MyFile << "\nRound Robin:\n";
    for(int i=0; i<historico.saida_rr.size(); i++)
        MyFile << historico.saida_rr[i] << "\n";
    MyFile.close();
}

void escalonador::mostra_estatisticas()
{
    cout << "FIFO "<<est_fifo.turnaround << " " << est_fifo.tempo_medio_resposta << " " << est_fifo.tempo_medio_espera << endl;
    cout << "SJF "<<est_sjf.turnaround << " " << est_sjf.tempo_medio_resposta << " " << est_sjf.tempo_medio_espera << endl;
    cout << "ROUND ROBIN "<<est_rr.turnaround << " " << est_rr.tempo_medio_resposta << " " << est_rr.tempo_medio_espera << endl;
}