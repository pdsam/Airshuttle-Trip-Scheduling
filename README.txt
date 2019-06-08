Para compilar:
Criar um projeto de eclipse C++ com a pasta code como raiz e compilar.
Temos o GraphViewer como dependência, pelo que em Windows é necessário adicionar a biblioteca wsock32.

Instruções de utilização:
Correr sem argumentos para obter a explicação de como usar.
Correr o executável do projeto com os possiveis seguintes argumentos:
    - view : vizualizar o mapa de uma regiao(Aveiro, Braga, Coimbra, Ermesinde, Fafe, Gondomar, Lisboa, Maia, Porto, Portugal, Viseu)
    - preprocess : vizualizar o produto do preprocessamento do mapa d uma região tendo um vertice como raiz
    - astar : calcular o caminho mais curto entre dois vertices de uma regiao
    - reservations : procesar as reservas contidas num ficheiro para uma determinada zona, é melhor usar um dos seguintes comandos:
        - ./airshuttle reservations Coimbra tests reservations_100.txt 711049847
        - ./airshuttle reservations Coimbra tests reservations_500.txt 711049847
        - ./airshuttle reservations Coimbra tests reservations_1000.txt 711049847
        - ./airshuttle reservations Coimbra tests reservations_5000.txt 711049847
        - ./airshuttle reservations Coimbra tests reservations_10000.txt 711049847