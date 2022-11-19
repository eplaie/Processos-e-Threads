# Processos-e-Threads
Sistemas Operacionais

# 1 - Sistema Multitarefa

![Linguagem C](https://img.shields.io/badge/Linguagem-C++-green.svg)

A etapa 5 e 6: consiste em modificar a politica de escalonamento, neste projeto foi adotado 3 politicas, sendo: Roudin Robin, Menor job primeiro e Maior job primeiro. Como algumas das chamadas dos metodos são bastantes semelhantes, a execução do Kernel foi modificada para trabalhar no modelo de template. 
Nesta etapa será utilizado os pacotes criados na etapa 5, com a diferença de que agora eles serão processados em threads. A execução das threads aumenta a complexidade, logo o tempo de execução também sofreu impacotos.

Implementação de umsistema multiprogramado, composto por um Gerenciador de Processos,
por um Gerenciador de Memória e por um Gerenciador de Entrada/Saída. O gerenciador de processos 
deve ser capaz de aplicar o algoritmo de escalonamento definido por meio de parâmetro pelo usuário. O gerenciador de 
entrada/saída deve ser responsável por administrar o algoritmo especificado para a busca em disco

# 1.1 - Módulo de Gerência de Processos

• FIFO: First-In, First-Out
<br>
• SJF: Shortest Job First
<br>
• RR: Round Robin (com quantum = 2)
<br>
<br>
O módulo de gerência de processos deverá ler da entrada padrão uma lista de processos com seus respectivos tempos de chegada e de duração, e deverá imprimir na saída padrão uma tabela contendo os  valores para as seguintes métricas:
<br> <br>
• Tempo médio de execução total do processo - turnaround;
<br>
• Tempo médio de resposta;
<br>
• Tempo médio de espera
<br> <br>
Tempo de execução total do processo é a quantidade de tempo necessária para executar totalmente um  processo, ou seja, é o tempo total entre a criação de um processo e seu término. Tempo de resposta é a  quantidade de tempo entre a requisição de execução de um programa (quando ele é colocado na fila de pronto) e o seu tempo de ir para a execução (sistema de compartilhamento de tempo), isso significa que é o tempo que o processo demora para produzir cada resposta a uma requisição (assim, vamos considerar que é o tempo decorrido entre uma ida e outra para a CPU. Essa métrica é importante para processos interativos).E tempo de espera é a quantidade total de tempo que um processo aguardou na fila de prontos esperandopara ser escalonado, ou seja, é o tempo que processo ficou esperando na fila de prontos.

# 2 - Estrutura do Programa
<br>
• Módulo Kernel – contém as chamadas para os demais módulos.
<br>
• Módulo de Processos – classes e estruturas de dados relativas ao processo. Basicamente, 
mantém informações específicas do processo.
<br>
• Módulo de Memória – provê uma interface de abstração de memória RAM.
<br>
• Módulo de Entrada/Saída – trata a alocação do braço do disco para realização de escrita/leitura 
nos blocos do disco para os processos
<br> <br>

# Compilação e Execução


| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |

Autor:[Ygor Vieira](https://github.com/eplaie).
