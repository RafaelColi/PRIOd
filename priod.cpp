#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Processo {
public:
    string nome;
    int tempo_ingresso;
    int tempo_cpu;
    int prioridade;

    Processo(string n, int ingresso, int cpu, int prio) : nome(n), tempo_ingresso(ingresso), tempo_cpu(cpu), prioridade(prio) {}

    void executa(int quantum) {
        cout << "Executando " << nome << " por " << quantum << " unidades de tempo." << endl;
        tempo_cpu -= quantum;
    }

    void ajusta_prioridade(int incremento) {
        prioridade += incremento;
    }
};

bool comparePorTempoIngresso(const Processo& a, const Processo& b) {
    return a.tempo_ingresso < b.tempo_ingresso;
}

void dynamic_priority_scheduling(vector<Processo>& processos) {
    int tempo_total = 0;
    int quantum = 5;  // Tamanho do qt
    int tempo_espera_total = 0;

    // Ordena os processos pelo tempo
    sort(processos.begin(), processos.end(), comparePorTempoIngresso);

    while (any_of(processos.begin(), processos.end(), [](const Processo& p) { return p.tempo_cpu > 0; })) {
        for (auto& processo : processos) {
            if (processo.tempo_cpu > 0 && processo.tempo_ingresso <= tempo_total) {
                processo.executa(quantum);
                tempo_total += quantum;
                tempo_espera_total += tempo_total - processo.tempo_ingresso - quantum;
                processo.ajusta_prioridade(-1);  // Diminui a prioridade após execução

                // Ajusta a prioridade baseada no tempo de execução
                if (tempo_total%20 == 0) {
                    processo.ajusta_prioridade(1);
                }

                cout << "Tempo total: " << tempo_total << ", Prioridade de " << processo.nome << ": " << processo.prioridade << endl;
            }
        }
    }

    // Tempo médio de espera
    double tempo_medio_espera = static_cast<double>(tempo_espera_total) / processos.size();

    cout << "Todos os processos foram concluidos." << endl;
    cout << "Tempo medio de espera: " << tempo_medio_espera << endl;
}

int main() {
    vector<Processo> processos;
    int num_processos;

    cout << "Digite o numero de processos: ";
    cin >> num_processos;

    for (int i = 0; i < num_processos; ++i) {
        string nome;
        int ingresso, duracao, prioridade;

        cout << "Digite o nome do processo " << i + 1 << ": ";
        cin >> nome;
        cout << "Digite o tempo de ingresso para " << nome << ": ";
        cin >> ingresso;
        cout << "Digite a duracao para " << nome << ": ";
        cin >> duracao;
        cout << "Digite a prioridade para " << nome << ": ";
        cin >> prioridade;

        processos.emplace_back(nome, ingresso, duracao, prioridade);
    }
    dynamic_priority_scheduling(processos);

    return 0;
}