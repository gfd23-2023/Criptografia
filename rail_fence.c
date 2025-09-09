/*IMPLEMENTAÇÃO CA CIFRA RAIL FENCE
 *Pontos importantes:
 * - O texto vai ficar inteiro em uma única matriz. Se a quantidade de caracteres
 * dividida por 5 (número de colunas) for maior do que 500.000, deve-se aumentar o número de colunas em 2.
 * - Para cifrar uma linha, deve-se fixar uma coluna e percorrer todas as linhas da matriz.
 * - Para decifrar uma linha é preciso saber a quantidade de linhas da matriz e pular esse mesmo número
 * de caracteres para encontrar a pŕoxima letra do texto cifrado.*/