# TADs

### **tipo abstrato** Elemento

Um elemento é um objeto que guarda um id, um tipo e um objeto que está sendo guardado no elemento

**função** inicializa_elemento(e : Elemento)
- pós-condição: o Elemento e é modificado para que seus atributos sejam inicializados com valores padrão

### **tipo abstrato** ListaEstatica

Uma lista estática é uma coleção de elementos de tamanho limitado em sua criação.

**função** cria_lista_estatica(tamanho : inteiro) : ListaEstatica
- pré-condição: n >= 0
- pós-condição: retorna uma referencia a uma lista

**função** adiciona_lista_estatica(lista : Lista, id, posicao : inteiro, objeto : referencia a um objeto)
- pré-condição: 0 <= p <= tamanho da lista
- pós-condição: O objeto é armazenado na posição passada no argumento

**função** busca_id(l : ListaEstatica, n, buscado : inteiro): Elemento
- pré-condição: n >= 0
- pós-condição: retorna uma referencia a um elemento cujo id é igual ao buscado, ou nulo se não o encontrar

**função** limpa_lista(elementos: vetor de elementos, n : inteiro)
- pré-condição: n >= 0
- pós-condição: desaloca todas as referencias a objetos nos elementos do vetor elementos

### **tipo abstrato** Circ

Circ é uma forma geométrica 2D, que possui uma posição x, y no plano cartesiano, um raio e uma cor.

**função** new_circ(raio, x, y: real, cor : string) : Circ
- pós-condição: retorna um Circ com raio, x, y e cor atribuidos pelos valores passados nos argumentos

**função** circ_upmost(c : Circ) : real
- pós-condição: retorna a componente y do ponto mais superior do círculo

**função** circ_leftmost(c : Circ) : real
- pós-condição: retorna a componente x do ponto mais à esquerda do círculo

**função** circ_botmost(c : Circ) : real
- pós-condição: retorna a componente y do ponto mais inferior do círculo

**função** circ_rightmost(c : Circ) : real
- pós-condição: retorna a componente x do ponto mais à direita do círculo

**fim tipo** Circ

### **tipo abstrato** Rect

Um Rect é uma forma geométrica 2D de quatro lados, com seus ângulos de seus vértices sendo iguais a 90 graus. Um rect possui a posição x, y no plano cartesiano, altura, largura e cor.

**função** new_rect(x, y, altura, largura : real, cor : string) : Rect
- pós-condição: retorna um Rect x, y, altura, largura e cor atribuidos pelos valores passados nos argumentos

**fim tipo** Rect
