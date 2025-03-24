#include "matrizes.hpp"
#include "vetores.hpp"
#include "trigonometria.hpp"
#include <iostream>
#include <cstdio>  // Necessário para printf()

using namespace std;

int main() {
    cout << "=== Teste da Classe Matriz ===" << endl;
    Matriz A(2, 2), B(2, 2);
    A.lerDados();
    B.lerDados();

    cout << "\nMatriz A:" << endl;
    A.escreverDados();
    cout << "\nMatriz B:" << endl;
    B.escreverDados();

    Matriz C = A + B;
    cout << "\nA + B:" << endl;
    C.escreverDados();

    Matriz D = A * B;
    cout << "\nA * B:" << endl;
    D.escreverDados();

    cout << "\nDeterminante de A: " << A.determinante() << endl;
    cout << "Transposta de A:" << endl;
    A.transposta().escreverDados();

    cout << "\n=== Teste da Classe Vetor ===" << endl;
    int tamanho;
    cout << "Digite o tamanho dos vetores: ";
    cin >> tamanho;
    Vetor v1(tamanho), v2(tamanho);
    v1.carregarValores();
    v2.carregarValores();

    cout << "Vetor 1: ";
    v1.exibir();
    cout << "Vetor 2: ";
    v2.exibir();

    Vetor vSoma = v1 + v2;
    cout << "Soma dos vetores: ";
    vSoma.exibir();

    cout << "Produto interno (v1 * v2): " << (v1 * v2) << endl;
    cout << "Distância entre os vetores: " << v1.distancia(v2) << endl;
    cout << "São linearmente dependentes? " << (v1.saoLinearmenteDependentes(v2) ? "Sim" : "Não") << endl;

    if (tamanho == 3) {
        Vetor vCross = v1.produtoExterno(v2);
        cout << "Produto vetorial (v1 x v2): ";
        vCross.exibir();
    }

    cout << "\n=== Teste da Classe Trigonometria ===" << endl;
    Trigonometria trig;
    double angulo;
    cout << "Digite um ângulo em graus: ";
    cin >> angulo;
    trig.definirAngulo(angulo);

    // Saída formatada para duas casas decimais
    printf("Seno: %.2f\n", trig.seno(angulo * 3.14159265358979323846 / 180.0));
    printf("Cosseno: %.2f\n", trig.cosseno(angulo * 3.14159265358979323846 / 180.0));
    printf("Tangente: %.2f\n", trig.tangente());
    printf("Secante: %.2f\n", trig.secante());
    printf("Cossecante: %.2f\n", trig.cossecante());
    printf("Cotangente: %.2f\n", trig.cotangente());

    double angulo2;
    cout << "Digite outro ângulo em graus para soma trigonométrica: ";
    cin >> angulo2;
    printf("Seno(A + B): %.2f\n", trig(angulo, angulo2));
    printf("Cosseno(A + B): %.2f\n", trig + angulo2);
    printf("Cosseno(A - B): %.2f\n", trig - angulo2);

    return 0;
}
