#ifndef TRIGONOMETRIA_HPP
#define TRIGONOMETRIA_HPP

#include <iostream>

#define PI 3.14159265358979323846  // Valor de PI

class Trigonometria {
private:
    double anguloGraus;    
    double anguloRadianos; 

    double grausParaRadianos(double graus) {
        return (graus * PI) / 180.0;
    }

    double fatorial(int n) {
        double resultado = 1;
        for (int i = 1; i <= n; ++i) resultado *= i;
        return resultado;
    }

    double potencia(double base, int exp) {
        double resultado = 1;
        for (int i = 1; i <= exp; ++i) resultado *= base;
        return resultado;
    }

    // Função auxiliar para calcular o valor absoluto
    double valorAbsoluto(double valor) {
        return (valor < 0) ? -valor : valor;
    }

    // Limita para 2 casas decimais sem usar cmath
    double limitar2Casas(double valor) {
        int inteiro = static_cast<int>(valor * 100);
        return inteiro / 100.0;
    }

public:
    Trigonometria() : anguloGraus(0), anguloRadianos(0) {}

    void definirAngulo(double angulo, bool emGraus = true) {
        if (emGraus) {
            anguloGraus = angulo;
            anguloRadianos = grausParaRadianos(anguloGraus);
        } else {
            anguloRadianos = angulo;
            anguloGraus = angulo * 180.0 / PI;
        }
    }

    double seno(double anguloRad) {
        double resultado = 0;
        for (int i = 0; i < 10; ++i) {
            int termo = (2 * i + 1);
            double fator = (i % 2 == 0 ? 1 : -1);
            resultado += fator * potencia(anguloRad, termo) / fatorial(termo);
        }
        return limitar2Casas(resultado);
    }

    double cosseno(double anguloRad) {
        double resultado = 0;
        for (int i = 0; i < 10; ++i) {
            int termo = 2 * i;
            double fator = (i % 2 == 0 ? 1 : -1);
            resultado += fator * potencia(anguloRad, termo) / fatorial(termo);
        }
        return limitar2Casas(resultado);
    }

    double tangente() {
        double coseno = cosseno(anguloRadianos);
        double seno_val = seno(anguloRadianos);
        double epsilon = 0.000001;

        if (valorAbsoluto(coseno) < epsilon) {
            std::cout << "Tangente indefinida para " << anguloGraus << " graus.\n";
            return 0;
        }
        return limitar2Casas(seno_val / coseno);
    }

    double cotangente() {
        double seno_val = seno(anguloRadianos);
        double epsilon = 0.000001;

        if (valorAbsoluto(seno_val) < epsilon) {
            std::cout << "Cotangente indefinida para " << anguloGraus << " graus.\n";
            return 0;
        }
        return limitar2Casas(cosseno(anguloRadianos) / seno_val);
    }

    double secante() {
        double coseno_val = cosseno(anguloRadianos);
        double epsilon = 0.000001;
        if (valorAbsoluto(coseno_val) < epsilon) {
            std::cout << "Secante indefinida para " << anguloGraus << " graus.\n";
            return 0;
        }
        return limitar2Casas(1.0 / coseno_val);
    }

    double cossecante() {
        double seno_val = seno(anguloRadianos);
        double epsilon = 0.000001;
        if (valorAbsoluto(seno_val) < epsilon) {
            std::cout << "Cossecante indefinida para " << anguloGraus << " graus.\n";
            return 0;
        }
        return limitar2Casas(1.0 / seno_val);
    }

    // Seno da soma de dois ângulos
    double operator()(double angulo1, double angulo2) {
        double rad1 = grausParaRadianos(angulo1);
        double rad2 = grausParaRadianos(angulo2);
        return limitar2Casas(seno(rad1) * cosseno(rad2) + cosseno(rad1) * seno(rad2));
    }

    // Seno da diferença de dois ângulos
    double operatorSenoDiferenca(Trigonometria& t) {
        double rad1 = grausParaRadianos(this->anguloGraus);
        double rad2 = grausParaRadianos(t.anguloGraus);
        return limitar2Casas(seno(rad1) * cosseno(rad2) - cosseno(rad1) * seno(rad2));
    }

    // Cosseno da soma de dois ângulos
    double operator+(double angulo2) {
        double rad1 = grausParaRadianos(this->anguloGraus);
        double rad2 = grausParaRadianos(angulo2);
        return limitar2Casas(cosseno(rad1) * cosseno(rad2) - seno(rad1) * seno(rad2));
    }

    // Cosseno da diferença de dois ângulos
    double operator-(double angulo2) {
        double rad1 = grausParaRadianos(this->anguloGraus);
        double rad2 = grausParaRadianos(angulo2);
        return limitar2Casas(cosseno(rad1) * cosseno(rad2) + seno(rad1) * seno(rad2));
    }

    // Subtração simples de ângulos em graus
    double operator-(Trigonometria& t) {
        return this->anguloGraus - t.anguloGraus;
    }
};

#endif
