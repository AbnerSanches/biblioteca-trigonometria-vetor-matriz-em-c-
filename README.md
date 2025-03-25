#  Biblioteca de Trigonometria, Vetores e Matrizes em C++

Este repositório contém uma biblioteca desenvolvida em C++ para manipulação de matrizes, vetores e cálculos trigonométricos.  

## Formato das Entradas e Testes  

### Matrizes  
- A entrada deve conter os elementos da matriz em **linha única**, separados por **espaço**.  
- O número total de elementos deve ser compatível com as dimensões esperadas (exemplo: 3x3 → 9 números).  

####  **Exemplo de entrada para uma matriz 3x3:** 1 2 3 4 5 6 7 8 9

####  **Testes possíveis:**  
✅ **Entrada válida:** `"1 2 3 4 5 6 7 8 9"`  
❌ **Entrada inválida:** `"1 2 3 4 5"` (faltam elementos)  
❌ **Caracteres não numéricos:** `"1 2 a 4 5 6 7 8 9"` (deve rejeitar)  

---

### Vetores  
- O formato é o mesmo das matrizes, mas com **uma única dimensão**.  
- Números decimais devem usar **"."** como separador decimal.  

####  **Exemplo de entrada para um vetor de 5 elementos:** 1.5 2.0 3.75 4.25 5.6


#### **Testes possíveis:**  
✅ **Entrada válida:** `"1.5 2.0 3.75 4.25 5.6"`  
❌ **Entrada inválida:** `"1,5 2,0 3,75"` (vírgula no lugar de ponto)  
❌ **Caracteres inválidos:** `"1.5 2.0 a 3.0"`  

---

### Funções Trigonométricas  
- As funções aceitam valores do tipo **int** ou **double**.  
- Suporte para entradas tanto em **graus** quanto em **radianos**.  

#### **Exemplo de conversão:**  
- **Entrada:** `45 graus` → **Saída:** `0.7854 radianos`  

#### **Testes possíveis:**  
✅ **Entrada válida:** `45` graus → convertido para `0.7854` radianos  
✅ **Entrada válida:** `45.0` graus → convertido para `0.7854` radianos  
❌ **Entrada inválida:** `"abc"` (deve rejeitar)  
✅ **Números negativos:** `-30` graus → `-0.5236` radianos
