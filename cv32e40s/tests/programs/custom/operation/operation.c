int main() {
    volatile int a = 5;   // Definindo a variável a
    volatile int b = 10;  // Definindo a variável b
    volatile int c = 20;  // Definindo a variável c
    
    // Realizando operações matemáticas e forçando o uso de memória
    volatile int sum = a + b;  // Soma
    volatile int diff = c - b; // Diferença
    volatile int prod = a * b; // Produto
    volatile int quot = c / a; // Quociente

    // Endereços de memória distintos para armazenar os resultados
    volatile int *sum_addr = (int *)0x1000;  // Endereço arbitrário para armazenar sum
    volatile int *diff_addr = (int *)0x1004; // Endereço arbitrário para armazenar diff
    volatile int *prod_addr = (int *)0x1008; // Endereço arbitrário para armazenar prod
    volatile int *quot_addr = (int *)0x100C; // Endereço arbitrário para armazenar quot

    // Armazenando os resultados na memória
    asm volatile ("sw %0, 0(%1)" : : "r"(sum), "r"(sum_addr));
    asm volatile ("sw %0, 0(%1)" : : "r"(diff), "r"(diff_addr));
    asm volatile ("sw %0, 0(%1)" : : "r"(prod), "r"(prod_addr));
    asm volatile ("sw %0, 0(%1)" : : "r"(quot), "r"(quot_addr));
    
    // Recuperando os valores da memória
    asm volatile ("lw %0, 0(%1)" : "=r"(sum) : "r"(sum_addr));
    asm volatile ("lw %0, 0(%1)" : "=r"(diff) : "r"(diff_addr));
    asm volatile ("lw %0, 0(%1)" : "=r"(prod) : "r"(prod_addr));
    asm volatile ("lw %0, 0(%1)" : "=r"(quot) : "r"(quot_addr));

    // Caminho de if-else para verificar o percurso
    if (sum > diff) {
        // Caminho 1: sum é maior que diff
        asm volatile ("li %0, 0xABC" : "=r"(c)); // Carrega 0xABC em c para indicar este caminho
    } else {
        if (prod > quot) {
            // Caminho 2: prod é maior que quot
            asm volatile ("li %0, 0x123" : "=r"(c)); // Carrega 0x123 em c para indicar este caminho
        } else {
            // Caminho 3: quot é maior ou igual a prod
            asm volatile ("li %0, 0x789" : "=r"(c)); // Carrega 0x789 em c para indicar este caminho
        }
    }
    
    return 0;
}
