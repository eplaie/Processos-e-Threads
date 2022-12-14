#include "gerenciador_mem.hpp"

int find_sc(vector<pair<int, int>> &elements, int current) {

    pair<int, int> aux;
    for(int i=0; i < elements.size(); i++) {
        // se encontrar a página na memória, atualiza o contador de referencias (bit R),
        if(elements[i].first == current) {
            aux = make_pair(elements[i].first, 2);
            elements.erase(elements.begin());
            elements.push_back(aux);
            return -1;
        }
        if(elements[i].second > 0){
            elements[i].second--;
            aux = elements[i];
            elements.erase(elements.begin());
            elements.push_back(aux);
        }
    }

    return 0;

}
int find_lru(vector<pair<int,int>> &elements, int current) {
    
    int min, min_pos = 0;
    if(elements.size() > 0) {
        min = elements[0].second;
    }

    for(int i=0; i<elements.size(); i++) {
        if(elements[i].first == current) {
            elements[i].second++;
            return -1;
        }
        if(elements[i].second < min) {
            min = elements[i].second;
            min_pos = i;
        }
    }
    
    return min_pos;
}

gerenciador_mem::gerenciador_mem(){}

gerenciador_mem::~gerenciador_mem(){}

estatisticas_paginacao gerenciador_mem::get_estatisticas(){
    return this->estatisticas;
}

void gerenciador_mem::set_estatisticas(estatisticas_paginacao estat){
    this->estatisticas = estat;
}

void gerenciador_mem::le_arquivo(string in_file) {
    
    string line;

    ifstream file(in_file);

    int count = 0;
    int cur_page = -1;
    while(getline(file, line)) {
        istringstream iss(line);

        if(count == 0) {
            iss >> qt_frames;
        }
        else { 
            iss >> cur_page;
            pages.push_back(cur_page);
        }

        count++;
    }
    file.close();
}

void gerenciador_mem::fifo() {

    deque<int> frames;
    int page_fault = 0;
    deque<int>::iterator it_verificador;
    estatisticas_paginacao estat;

    for(int i=0; i < pages.size(); i++) {
        int current_page = pages[i];

        it_verificador = find(frames.begin(), frames.end(), current_page);

        if(frames.size() == qt_frames){
            if(it_verificador == frames.end()) {
                frames.pop_front();
                page_fault++;
                frames.push_back(current_page);
            }
        }
        else {
            if(it_verificador == frames.end()) {
                page_fault++;
                frames.push_back(current_page);
            }
        }
    }

    estat = get_estatisticas();
    estat.fifo_pf = page_fault;
    set_estatisticas(estat);
}
void gerenciador_mem::sc() {

    int page_fault = 0;
    int found;
    vector<pair<int,int>> frames;
    estatisticas_paginacao estat;

    for(int i=0; i < pages.size(); i++) {
        int current_page = pages[i];

        found = find_sc(frames, current_page);
        if(frames.size() == qt_frames){
            if (found != -1) {
                page_fault++;
                frames.erase(frames.begin() + found);
                frames.push_back(make_pair(current_page, 0));
            }
        }
        else {
            if(found != -1) {
                page_fault++;
                frames.push_back(make_pair(current_page, 0));
            }
        }
    }
    estat = get_estatisticas();
    estat.sc_pf = page_fault;
    set_estatisticas(estat);
}
void gerenciador_mem::lru() {
    estatisticas_paginacao estat;
    int page_fault = 0;
    int current_page;
    int found;

    vector<pair<int,int>> frames;

    for(int i=0; i<pages.size(); i++) {
        current_page = pages[i];

        found = find_lru(frames, current_page);
        if(frames.size() < qt_frames) {
            if(found != -1) {
                page_fault++;
                frames.push_back(make_pair(current_page, 0));
            }
        }
        else {
            if(found != -1) {
                page_fault++;
                frames.erase(frames.begin() + found);
                frames.push_back(make_pair(current_page, 0));
            }
        }
    }

    estat = get_estatisticas();
    estat.lru_pf = page_fault;
    set_estatisticas(estat);
}

