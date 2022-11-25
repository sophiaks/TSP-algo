# Traveling Salesperson Problem (TSP)

## Introdução
O problema do caixeiro viajante é baseado na seguinte pergunta: dada uma lista de cidades e a distância entre cada uma delas, qual a menor distância de modo que o caixeiro viajante visite todas as cidades e volte à cidade de origem?

É um problema classificado como NP-hard, ou seja, classificado como NP (Não Determinístico Polinomial). Desse modo, pode se tornar complexa.

## Utilização

### Compilação

- Script: Makefile

Para compilar o script, rode o comando `make` dentro do diretório raiz `./TSP-algo`

### Testes

___

## Heurística da cidade mais próxima
Para mais detalhes observe o arquivo em C++ da [heurística da cidade mais próxima](heuristico/main.cpp).

```c++

```
___

## Busca local
Para mais detalhes observe o arquivo em C++ da [busca local](heuristico/main.cpp).

O algoritmo de busca local, um algoritmo de otimização faz pequenas alterações até achar uma solução ótima. Neste projeto, a abordagem consiste em trocar a ordem das cidades visitadas sucessivamente, até que a rota com menor distância seja encontrada.
```c++

```
___

## Busca exaustiva
Para mais detalhes observe o arquivo em C++ da [busca exaustiva](heuristico/main.cpp).

```c++

```
___

## Paralelismo multi-core
Para mais detalhes observe o arquivo em C++ do [paralelismo multi-core](heuristico/main.cpp).

```c++

```
___

## Paralelismo em GPU
Para mais detalhes observe o arquivo em C++ do [paralelismo em GPU](heuristico/main.cpp).

```c++

```
___

## Comparações de desempenho
Muitos gráficos bem descritos :)
```c++

```

![](img/comp.png)

___

## Conclusão

<!-- 
$w(n) = \alpha - \beta\cos\frac{2\pi n}{N-1}$, where $\alpha=0.54$ and $\beta=0.46$ -->
