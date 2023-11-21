READ.ME

TRABALHO 1 DE ALGORITMOS E ESTRUTURA DE DADOS 3
DATA: 09/10/2023

EQUIPE: MAISA CAROLINA MORENO GIRARDI (GRR20204081) E RAPHAEL AUGUSTO SURMACZ (GRR20213405)


    Esse trabalho foi feito para resolver os casos de inserção, busca e remoção de valores em uma árvore AVL, todo trabalho foi feito em conjunto pelos dois alunos Raphael e Maisa. 

    Usamos como base os pseudo-códigos vistos em sala de aula com o Professor Andre.

    A partir de agora falaremos sobre os códigos usados para resolver o problema ofertado. 
    Usamos a mesma declaração que foi passada em aula para a struct do nó da árvore e, dessa mesma forma, foi usado a struct "createNode" para criar um novo nó. 

    Para inserir na árvore usamos a função "insert()".
    A função "insert()" (struct node *insert(struct node *root, int x){...}) verifica se a árvore é nula, caso não seja, cria um novo nó e irá balancear, com o novo valor inserido, respeitando as propriedades da árvore binária. Caso já existir o valor na árvore, essa função não deixará esse elemento ser adicionado. Para balancear a árvore, usamos as funções "returnHeighest()" (int returnHeighest(int a, int b){...}) e "nodeHeight()" (int nodeHeight(struct node *no){...}). Essas duas funções retornam a maior altura da sub-árvore e a altura do nó, respectivamente. 
    Para finalizar a função "insert()", chamamos outra função "treeBalancer()", caso o fator de balanceamento (que será calculado ná próxima função chamada) seja maior do que 1 ou menor do que -1, ocorrerá o balanceamento da árvore AVL. Essa função irá chamar a função "balanceFactor()", que tem como objetivo balancear a árvore para que mantenha a propriedade da árvore balanceada, ou seja, a altura do lado esquerdo da árvore não difere mais de +- 1 do lado direto. Resumindo, |altura(esq) - altura(dir)|  <= 1.

    Já para remover na árvore, temos a função "nodeRemove()".
    Para a função "nodeRemove()", usamos como parâmetros o nó e o valor chave a ser removido. Essa função é separada em três casos: 1- exclusão na folha; 2- exclusão de um nó com dois filhos e 3- exclusão de um nó com só um filho.
    O primeiro caso, exclusão na folha, é o mais simples de efetuar pois, não precisará de balanceamento da árvore. O segundo caso, exclusão de um nó com dois filhos, usamos um nó auxiliar e buscaremos o valor, para, por fim, fazermos uma troca, deixando o valor chave em uma folha para podermos remover como se fosse o caso 1. Já o terceiro caso, exclusão de um nó com só um filho, analisará qual filho falta, removerá o valor chave e balanceará a árvore.
    Para finalizar a função, ele faz o balanceamento, recalculando a altura.

    Como foi pedido no enunciado, usamos para a impressão da árvore a notação textual com parênteses. E usamos uma função para imprimir a árvore, denominada "printAVL()".

    Para a função de busca, utilizamos a função searchNode(), a qual, de maneira recursiva, imprime os chaves dos nodos visitados da árvore, a partir de uma busca em profundidade.

    Agradecemos desde já, pela compreensão e pelo tempo, Maisa e Raphael.
