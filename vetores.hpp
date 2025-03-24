#ifndef VETORES_HPP
#define VETORES_HPP

#include <iostream>

class Vetor {
private:
    double* vetor;  // Ponteiro para armazenar os elementos do vetor
    int tamanho;    // Tamanho do vetor

public:
    // Construtor que recebe o tamanho do vetor
    Vetor(int t) : tamanho(t) {
        vetor = new double[tamanho];  // Aloca memória para o vetor
        for (int i = 0; i < tamanho; ++i) {
            vetor[i] = 0.0;  // Inicializa todos os elementos com 0
        }
    }

    // Método para carregar os valores do vetor
    void carregarValores() {
        std::cout << "Digite os " << tamanho << " valores do vetor: ";
        for (int i = 0; i < tamanho; ++i) {
            std::cin >> vetor[i];  // Lê os valores do vetor
        }
    }

    // Método para exibir o vetor
    void exibir() const {
        std::cout << "[ ";
        for (int i = 0; i < tamanho; ++i) {
            std::cout << vetor[i] << " ";
        }
        std::cout << "]" << std::endl;
    }

    // Método para somar dois vetores
    Vetor operator+(const Vetor& outro) const {
        if (tamanho != outro.tamanho) {
            std::cerr << "Erro: Vetores de tamanhos diferentes!" << std::endl;
            exit(1);  // Se os tamanhos não coincidirem, sai do programa
        }
        Vetor resultado(tamanho);  // Cria um novo vetor para armazenar o resultado
        for (int i = 0; i < tamanho; ++i) {
            resultado.vetor[i] = vetor[i] + outro.vetor[i];  // Soma componente a componente
        }
        return resultado;
    }

    // Método para subtrair dois vetores
    Vetor operator-(const Vetor& outro) const {
        if (tamanho != outro.tamanho) {
            std::cerr << "Erro: Vetores de tamanhos diferentes!" << std::endl;
            exit(1);  // Se os tamanhos não coincidirem, sai do programa
        }
        Vetor resultado(tamanho);  // Cria um novo vetor para armazenar o resultado
        for (int i = 0; i < tamanho; ++i) {
            resultado.vetor[i] = vetor[i] - outro.vetor[i];  // Subtrai componente a componente
        }
        return resultado;
    }

    // Método para calcular o produto interno entre dois vetores
    double operator*(const Vetor& outro) const {
        if (tamanho != outro.tamanho) {
            std::cerr << "Erro: Vetores de tamanhos diferentes!" << std::endl;
            exit(1);  // Se os tamanhos não coincidirem, sai do programa
        }
        double produto = 0;
        for (int i = 0; i < tamanho; ++i) {
            produto += vetor[i] * outro.vetor[i];  // Produto interno (soma dos produtos dos componentes)
        }
        return produto;
    }

    // Método para calcular a norma do vetor (sem usar sqrt)
    double norma() const {
        double somaQuadrados = 0;
        for (int i = 0; i < tamanho; ++i) {
            somaQuadrados += vetor[i] * vetor[i];  // Soma dos quadrados dos componentes
        }
        return raizQuadrada(somaQuadrados);  // Norma é a raiz quadrada da soma dos quadrados
    }

    // Método auxiliar para calcular a raiz quadrada (Método de Newton)
    double raizQuadrada(double valor) const {
        if (valor == 0) return 0;  // Se o valor for 0, a raiz quadrada é 0
        double estimativa = valor / 2;  // Chute inicial para a raiz quadrada
        double precisao = 1e-10;  // Precisão desejada

        while (valorAbsoluto(estimativa - valor / estimativa) > precisao) {
            estimativa = 0.5 * (estimativa + valor / estimativa);  // Fórmula de Newton
        }

        return estimativa;
    }

    // Método auxiliar para calcular o valor absoluto
    double valorAbsoluto(double valor) const {
        return (valor < 0) ? -valor : valor;
    }

    // Método para calcular a distância entre dois vetores
    double distancia(const Vetor& outro) const {
        Vetor diferenca = *this - outro;  // Diferença entre os vetores
        return diferenca.norma();  // Distância é a norma da diferença
    }

    // Verifica se os vetores são linearmente dependentes
    bool saoLinearmenteDependentes(const Vetor& outro) const {
        if (tamanho != outro.tamanho) {
            std::cerr << "Erro: Vetores de tamanhos diferentes!" << std::endl;
            return false;
        }

        // Para vetores 2D
        if (tamanho == 2) {
            if (vetor[0] == 0 && outro.vetor[0] == 0) return true;  // Ambos os vetores estão na linha y
            if (vetor[1] == 0 && outro.vetor[1] == 0) return true;  // Ambos os vetores estão na linha x

            // Verifica se as razões entre os componentes são as mesmas (multiplicação escalar)
            return (vetor[0] / outro.vetor[0]) == (vetor[1] / outro.vetor[1]);
        }

        // Para vetores 3D
        if (tamanho == 3) {
            Vetor produtoExterno = this->produtoExterno(outro);  // Calcula o produto vetorial

            // Se o produto vetorial for (0, 0, 0), os vetores são linearmente dependentes
            if (produtoExterno.vetor[0] == 0 && produtoExterno.vetor[1] == 0 && produtoExterno.vetor[2] == 0) {
                return true;
            }
            return false;  // Caso contrário, são linearmente independentes
        }

        return false;     
    }

    // Verifica se os vetores são linearmente independentes
    bool saoLinearmenteIndependentes(const Vetor& outro) const {
        return !saoLinearmenteDependentes(outro);  // Se não forem dependentes, são independentes
    }

    // Produto vetorial (produto externo) para vetores 3D
    Vetor produtoExterno(const Vetor& outro) const {
        if (tamanho != 3 || outro.tamanho != 3) {
            std::cerr << "Erro: Produto externo só é definido para vetores 3D!" << std::endl;
            exit(1);  // Se não for 3D, sai do programa
        }

        Vetor resultado(3);  // Produto externo resulta em um vetor 3D
        resultado.vetor[0] = vetor[1] * outro.vetor[2] - vetor[2] * outro.vetor[1];
        resultado.vetor[1] = vetor[2] * outro.vetor[0] - vetor[0] * outro.vetor[2];
        resultado.vetor[2] = vetor[0] * outro.vetor[1] - vetor[1] * outro.vetor[0];

        return resultado;
    }

    // Destruidor para liberar a memória alocada
    ~Vetor() {
        delete[] vetor;  // Libera a memória alocada para o vetor
    }
};

#endif
