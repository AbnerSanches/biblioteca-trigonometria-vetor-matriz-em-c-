#ifndef MATRIZES_HPP
#define MATRIZES_HPP

#include <iostream>    // Para entrada/saída

class Matriz {
private:
    double* dados;  // Matriz como um array unidimensional
    size_t linhas;
    size_t colunas;

    // Função auxiliar para calcular o índice da matriz unidimensional
    size_t indice(size_t i, size_t j) const {
        return (i - 1) * colunas + (j - 1);  // Ajuste da indexação (1 para 0)
    }

public:
    // Construtor
    Matriz(size_t linhas, size_t colunas) : linhas(linhas), colunas(colunas) {
        dados = new double[linhas * colunas]();  // Inicializa com 0.0
    }

    // Destruidor
    ~Matriz() {
        delete[] dados;
    }

    // Acesso aos elementos da matriz (modificável)
    double& acessar(size_t i, size_t j) {
        if (i < 1 || j < 1 || i > linhas || j > colunas) {
            throw std::out_of_range("Índice fora dos limites da matriz.");
        }
        return dados[indice(i, j)];
    }

    // Acesso aos elementos da matriz (somente leitura)
    double acessar(size_t i, size_t j) const {
        if (i < 1 || j < 1 || i > linhas || j > colunas) {
            throw std::out_of_range("Índice fora dos limites da matriz.");
        }
        return dados[indice(i, j)];
    }

    // Obtém o número de linhas e colunas
    size_t obterLinhas() const { return linhas; }
    size_t obterColunas() const { return colunas; }

    // Entrada de dados na matriz (stream I/O)
    void lerDados() {
        std::cout << "Digite os dados para a matriz de " << linhas << " linhas e " << colunas << " colunas:" << std::endl;
        for (size_t i = 1; i <= linhas; ++i) {
            for (size_t j = 1; j <= colunas; ++j) {
                while (!(std::cin >> acessar(i, j))) {
                    std::cout << "Entrada inválida! Digite um número." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                }
            }
        }
    }

    // Saída dos dados da matriz (stream I/O)
    void escreverDados() const {
        std::cout << "Dados da matriz:" << std::endl;
        for (size_t i = 1; i <= linhas; ++i) {
            for (size_t j = 1; j <= colunas; ++j) {
                std::cout << acessar(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }

    // Operadores de soma, subtração e multiplicação de matrizes
    Matriz operator+(const Matriz& outra) const {
        if (linhas != outra.linhas || colunas != outra.colunas) {
            throw std::invalid_argument("Matrizes de dimensões incompatíveis para soma.");
        }
        Matriz resultado(linhas, colunas);
        for (size_t i = 1; i <= linhas; ++i) {
            for (size_t j = 1; j <= colunas; ++j) {
                resultado.acessar(i, j) = acessar(i, j) + outra.acessar(i, j);
            }
        }
        return resultado;
    }

    Matriz operator-(const Matriz& outra) const {
        if (linhas != outra.linhas || colunas != outra.colunas) {
            throw std::invalid_argument("Matrizes de dimensões incompatíveis para subtração.");
        }
        Matriz resultado(linhas, colunas);
        for (size_t i = 1; i <= linhas; ++i) {
            for (size_t j = 1; j <= colunas; ++j) {
                resultado.acessar(i, j) = acessar(i, j) - outra.acessar(i, j);
            }
        }
        return resultado;
    }

    Matriz operator*(const Matriz& outra) const {
        if (colunas != outra.linhas) {
            throw std::invalid_argument("Matrizes de dimensões incompatíveis para multiplicação.");
        }
        Matriz resultado(linhas, outra.colunas);
        for (size_t i = 1; i <= linhas; ++i) {
            for (size_t j = 1; j <= outra.colunas; ++j) {
                for (size_t k = 1; k <= colunas; ++k) {
                    resultado.acessar(i, j) += acessar(i, k) * outra.acessar(k, j);
                }
            }
        }
        return resultado;
    }

    // Função para calcular a transposta da matriz
    Matriz transposta() const {
        Matriz resultado(colunas, linhas);
        for (size_t i = 1; i <= linhas; ++i) {
            for (size_t j = 1; j <= colunas; ++j) {
                resultado.acessar(j, i) = acessar(i, j);
            }
        }
        return resultado;
    }

    // Função para calcular o determinante de uma matriz quadrada
    double determinante() const {
        if (linhas != colunas) {
            throw std::invalid_argument("O determinante só pode ser calculado para matrizes quadradas.");
        }
        return calcularDeterminante(dados, linhas);
    }

private:
    // Função auxiliar para calcular o determinante recursivamente
    double calcularDeterminante(double* matriz, size_t n) const {
        if (n == 1) {
            return matriz[0];  // Base: determinante de uma matriz 1x1
        }

        double det = 0;
        double* submatriz = new double[(n - 1) * (n - 1)];

        for (size_t c = 0; c < n; ++c) {
            size_t subi = 0;
            for (size_t i = 1; i < n; ++i) {
                size_t subj = 0;
                for (size_t j = 0; j < n; ++j) {
                    if (j == c) continue;
                    submatriz[subi * (n - 1) + subj] = matriz[i * n + j];
                    ++subj;
                }
                ++subi;
            }
            double subdet = calcularDeterminante(submatriz, n - 1);
            det += (c % 2 == 0 ? 1 : -1) * matriz[c] * subdet;
        }

        delete[] submatriz;
        return det;
    }
};

#endif
