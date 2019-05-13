#ifndef _GRAPH_VIEWER_H_
#define _GRAPH_VIEWER_H_

#ifdef linux
	#include <unistd.h>
#else
	#include <winsock2.h>
	#include <Windows.h>
#endif

#include <stdlib.h>
#include <signal.h>
#include <string>

#include "edgetype.h"
#include "connection.h"

#define BLUE "BLUE"
#define RED "RED"
#define PINK "PINK"
#define BLACK "BLACK"
#define WHITE "WHITE"
#define ORANGE "ORANGE"
#define YELLOW "YELLOW"
#define GREEN "GREEN"
#define CYAN "CYAN"
#define GRAY "GRAY"
#define DARK_GRAY "DARK_GRAY"
#define LIGHT_GRAY "LIGHT_GRAY"
#define MAGENTA "MAGENTA"

/**
 * Classe que guarda o grafo e o representa. Todas as suas funções retornam um booleano a indicar
 * se a sua execução decorreu ou não com sucesso.
 */
class GraphViewer {
 public:
  /**
   * Variável que guarda a próxima porta que o programa vai usar. O valor inicial é 7772.
   */
  static short port;
  
  /**
   * Construtor que cria um novo grafo e atribui automaticamente a porta.
   * @param width Inteiro que representa a lagura da área do grafo.
   * @param height Inteiro que representa a altura da área do grafo.
   * @param dynamic Booleano que determina se a localização dos nós é automaticamente.
   * determinado pelo programa (true) ou se deve ser determinado pelo utilizador (false).
   */
  GraphViewer(int width, int height, bool port_n);
  
  /**
   * Construtor que cria um novo grafo, utilizando uma porta especificada pelo utilizador para a ligação.
   * @param width Inteiro que representa a lagura da área do grafo.
   * @param height Inteiro que representa a altura da área do grafo.
   * @param dynamic Booleano que determina se a localização dos nós é automaticamente.
   * determinado pelo programa (true) ou se deve ser determinado pelo utilizador (false).
   * @param port_n Inteiro que determina a porta a utilizar. Deve-se ter cuidado para não utilizar uma porta
   * já usada por outro programa ou pelo sistema.
   */
  GraphViewer(int width, int height, bool dynamic, int port_n);
  
  /**
   * Função que cria a janela para visualização.
   * @param width Largura da janela a criar.
   * @param height Altura da janela a criar.
   */
  bool createWindow(int width, int height);
  /**
   * Fecha a janela a ser utilizada para visualização.
   */
  bool closeWindow();

  /**
   * Acrescenta um nó à representação do grafo, numa posição específica, irrelevante se o grafo
   * for dinâmico.
   * @param id Identificador único do nó.
   * @param x Posição horizontal do nó.
   * @param y Posição vertical do nó.
   */
  bool addNode(int id, int x, int y);
  /**
   * Acrescenta um nó à representação do grafo, numa posição ao critério do programa.
   * @param id Identificador único do nó.
   */
  bool addNode(int id); 
  /**
   * Acrescenta uma aresta à representação do grafo.
   * @param id Identificador único da aresta.
   * @param v1 Identificador único do nó de origem da aresta.
   * @param v2 Identificador único do nó de destino da aresta.
   * @param edgeType EdgeType.DIRECTED caso a aresta seja unidirecional
   * ou EdgeType.UNDIRECTED caso a aresta seja bidirecional.
   */
  bool addEdge(int id, int v1, int v2, int edgeType);

  /**
   * Remove um nó da representação do grafo e todas as arestas ligadas a este.
   * @param id Identificador único do nó a a remover.
   */
  bool removeNode(int id);
  /**
   * Remove uma aresta da representação do grafo.
   * @param id Identificador único da aresta a remover.
   */
  bool removeEdge(int id); 

  /**
   * Função que define o texto de um nó.
   * @param id Identificador único do nó com o texto a alterar.
   * @param label Novo texto do nó.
   */
  bool setVertexLabel(int id, string label);

  /**
   * Função que define o texto de uma aresta.
   * @param id Identificador único da aresta com o texto a alterar.
   * @param label Novo texto da aresta.
   */
  bool setEdgeLabel(int id, string label);
  /**
   * Função que define a cor de uma aresta.
   * @param id Identificador único da aresta com a cor a alterar.
   * @param color Nova cor da aresta, utilizar as constantes definidas no graphviewer.h para conveniência.
   */
  bool setEdgeColor(int id, string color);

  /**
   * Função que define a cor de um nó.
   * @param id Identificador único do nó com a cor a alterar.
   * @param color Nova cor do nó, utilizar as constantes definidas no graphviewer.h para conveniência.
   */
  bool setVertexColor(int id, string color);

  /**
   * Função que define a cor global das arestas.
   * @param color Nova cor das arestas, utilizar as constantes definidas no graphviewer.h para conveniência.
   */
  bool defineEdgeColor(string color);
  /**
   * Função que define a cor global dos nós.
   * @param color Nova cor dos nós, utilizar as constantes definidas no graphviewer.h para conveniência.
   */
  bool defineVertexColor(string color);
  /**
   * Função que define a espessura de uma aresta.
   * @param id Identificador único da aresta com a espessura a alterar.
   * @param thickness Nova espessura da aresta, sendo que por base, as
   * arestas são criadas com a espessura de 1.
   */
  bool setEdgeThickness(int id, int thickness);
  
  /**
   * Função que altera a imagem de fundo do grafo.
   * @param path Caminho para o ficheiro com a imagem.
   */
  bool setBackground(string path);

  /**
   * Função que define o peso de uma aresta na representação do grafo, a ser visualizado
   * como w: valor_do_peso, seguido de qualquer outro texto associado à aresta.
   * @param id Identificador único da aresta a modificar.
   * @param weight Peso associado à aresta.
   */
  bool setEdgeWeight(int id, int weight);
  /**
   * Função que define o fluxo de uma aresta na representação do grafo, a ser visualizado
   * como f: valor_do_fluxo, precedido pelo peso e seguido por texto definido pelo utilizador.
   * @param id Identificador único da aresta a modificar.
   * @param flow Fluxo associado à aresta.
   */
  bool setEdgeFlow(int id, int flow);

  /**
   * Função que actualiza a visualização do grafo.
   */
  bool rearrange();

#ifdef linux
  static pid_t procId;
#endif

 private:
  int width, height;
  bool isDynamic;

  Connection *con;

  void initialize(int, int, bool, int);
};

#endif
