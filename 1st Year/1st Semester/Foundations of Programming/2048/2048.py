#81478 Joana Godinho
#81586 Diogo Freitas

#Este programa serve para jogar o jogo 2048.

from random import random

num_crd = (1, 2, 3, 4)
mov_cc = ('N', 'S', 'W', 'E')

def cria_coordenada (l, c):
    """cria_coordenada: int,int-tuple
    Esta funcao recebe dois numeros inteiros, o primeiro correspondente a uma 
    linha e o segundo correspondente a uma coluna. Caso os numero nao estejam 
    compreendidos entre 1 e 4, a funcao ira gerar um ValueError, caso contrario,
    ira devolver um tuplo correspondente a uma coordenada."""
    
    if l not in num_crd or c not in num_crd:
        raise ValueError('cria_coordenada: argumentos invalidos')
    return (l, c)

def coordenada_linha (crd):
    """coordenada_linha: tuple-int
    Esta funcao recebe um tuplo com uma coordenada e
    devolve um numero correspondente a uma linha."""
    
    return crd[0]

def coordenada_coluna (crd):
    """coordenada_coluna: tuple-int
    Esta funcao recebe um tuplo com uma coordenada e
    devolve um numero correspondente a uma coluna."""    

    return crd[1]

def e_coordenada (x):
    """e_coordenada: argument-bool
    Esta funcao pode receber um qualquer argumento e verifica se esse mesmo
    e uma coordenada ou nao. Caso afirmativo, retorna True, caso contrario,
    retorna False."""

    if isinstance(x, tuple) and len(x) == 2 and x[0] in num_crd and x[1] in num_crd:
        return True
    else:
        return False
    
def coordenadas_iguais (crd1, crd2):
    """coordenadas_iguais: tuple,tuple-bool
    Esta funcao recebe dois tuplos com coordenadas cada um e verifica se estas
    sao iguais. Caso afirmativo, retorna True, caso contario, retorna False."""

    return crd1 == crd2
    
def cria_tabuleiro ():
    """cria_tabuleiro: {}-dict
    Esta funcao nao recebe argumento e ao ser chamada cria um tabuleiro de jogo
    em que todas as entradas e a sua pontuacao correspondem a 0."""
    
    tab =[]
    for l in range(1,5):                                            #Corre todas as linhas
        tab= tab+[[[0,0],[0,0],[0,0],[0,0]]]                        #Coloca na lista uma linha que contem quatro listas com um valor e uma flag
    tab=tab+[0]                                                     #Atribui um valor(0) a pontuacao
    return tab

def tabuleiro_posicao (tab, crd):
    """tabuleiro_posicao: dict,tuple-int
    Esta funcao recebe um dicionario com um tabuleiro e tuplo com uma coordenada
    e devolve o numero que se encontra na respectiva coordenada no tabuleiro."""

    if e_coordenada(crd) == False:
        raise ValueError('tabuleiro_posicao: argumentos invalidos')
    else:
        return tab[coordenada_linha(crd)-1][coordenada_coluna(crd)-1][0]
    
def tabuleiro_flag (tab, crd):
    """tabuleiro_posicao: dict,tuple-int
    Esta funcao recebe um dicionario com um tabuleiro e tuplo com uma coordenada
    e devolve a flag que se encontra na respectiva coordenada no tabuleiro."""    
    
    if e_coordenada(crd) == False:
        raise ValueError('tabuleiro_flag: argumentos invalidos')
    else:
        return tab[coordenada_linha(crd)-1][coordenada_coluna(crd)-1][1]
    
def tabuleiro_pontuacao (tab):
    """tabuleiro_pontuacao: dict-int
    Esta funcao recebe um dicionario com um tabuleiro e retorna um inteiro
    correspondente a pontuacao."""

    return tab[4]
            
def tabuleiro_posicoes_vazias (tab):
    """tabuleiro_posicoes_vazias: dict-list
    Esta funcao recebe um dicionario com um tabuleiro e verifica quais as posicoes
    correspondentes a coordenadas que estao vazias, ou seja, correspondentes a zero
    e retorna essas coordenadas numa lista."""
    
    lst = []
    for l in range(len(tab)-1):                                     #Corre todas as linhas
        for c in range(len(tab[l])):                                #Corre todas as colunas
            if tab[l][c][0]==0:                                     
                lst = lst + [cria_coordenada(l+1,c+1)]              #Adiciona a coordenada a lista caso o valor seja 0
    return lst

def tabuleiro_preenche_posicao (tab, crd, num):
    """tabuleiro_preenche_posicao: dict,tuple,int-dict
    Esta funcao recebe um dicionario com um tabuleiro, um tuplo com uma coordenada
    e um inteiro. O que a funcao faz e pegar nesse inteiro e coloca-lo no numero
    da coordenada dada do tabuleiro dado e retornar esse tabuleiro actualizado."""
    
    if e_coordenada(crd) == False or not isinstance(num, int):
        raise ValueError('tabuleiro_preenche_posicao: argumentos invalidos')
    else:
        tab[coordenada_linha(crd)-1][coordenada_coluna(crd)-1][0]=num
    return tab

def tabuleiro_preenche_flag (tab, crd, flag):
    """tabuleiro_preenche_posicao: dict,tuple,int-dict
    Esta funcao recebe um dicionario com um tabuleiro, um tuplo com uma coordenada
    e um inteiro. O que a funcao faz e pegar nesse inteiro e coloca-lo na flag da 
    coordenada dada do tabuleiro dado e retornar esse tabuleiro actualizado."""    
    if e_coordenada(crd) and (flag == 0 or flag == 1):
        tab[coordenada_linha(crd)-1][coordenada_coluna(crd)-1][1]=flag
    else:
        raise ValueError('tabuleiro_preenche_flag: argumentos invalidos')
    return tab    

def tabuleiro_actualiza_pontuacao (tab, pts):
    """tabuleiro_actualiza_pontuacao: dict,int-dict
    Esta funcao recebe um dicionario com um tabuleiro e um inteiro correspondente 
    ao valor de pontos a adicionar a pontuacao.O que a funcao faz e somar esse 
    valor a pontucao e retornar o tabuleiro actualizado."""
    
    if pts >= 0 and pts % 4 == 0:
        tab[4] = tabuleiro_pontuacao(tab) + pts
    else:
        raise ValueError('tabuleiro_actualiza_pontuacao: argumentos invalidos')
    return tab

def tabuleiro_reduz (tab, cc):
    """tabuleiro_reduz: dict,str-dict
    Esta funcao recebe um dicionario com um tabuleiro e uma string que nos indica
    a direccao do movimento que a funcao vai executar. Verifica se a jogada e 
    valida e caso seja, faz o movimento na direccao pretendida, caso contrario,
    cria um ValueError."""
    
    if cc not in mov_cc:
        raise ValueError('tabuleiro_reduz: argumentos invalidos')
    else:
        mov_ran = {'N': {'l': range(1, 5), 'c': range(1, 5)},
                   'S': {'l': range(4, 0, -1), 'c': range(1, 5)},
                   'W': {'l': range(1, 5), 'c': range(1, 5)},
                   'E': {'l': range(1, 5), 'c': range(4, 0, -1)}}       #Range define a ordem pela qual o tabuleiro vai ser percorrido
        for w in range(1,4):                                            #Repete o ciclo 3 vezes para que o movimento seja completo
            for l in mov_ran[cc]['l']:
                for c in mov_ran[cc]['c']:
                    mov_dir = {'N': {'l': l - 1, 'c': c}, 'S': {'l': l + 1, 'c': c},
                               'W': {'l': l, 'c': c - 1}, 'E': {'l': l, 'c': c + 1}}    #Define a direccao do movimento
                    actu = cria_coordenada(l, c)
                    if mov_dir[cc]['l'] in num_crd and mov_dir[cc]['c'] in num_crd:                             #Define limites ao tabuleiro(as coordenadas nao podem ser diferentes das do tabuleiro)
                        prox = cria_coordenada(mov_dir[cc]['l'], mov_dir[cc]['c'])
                        if tabuleiro_posicao(tab, actu) != 0 and tabuleiro_posicao(tab, prox) == 0:             #Verifica se o numero na coordenada analisada != 0 e se o proximo == 0 (MOVIMENTO)
                            tabuleiro_preenche_posicao(tab,prox,tabuleiro_posicao(tab, actu))
                            tabuleiro_preenche_flag(tab,prox,tabuleiro_flag(tab,actu))
                            tabuleiro_preenche_posicao(tab,actu,0)
                            tabuleiro_preenche_flag(tab,actu,0)
                        elif tabuleiro_posicao(tab, actu) == tabuleiro_posicao(tab, prox) and tabuleiro_flag(tab, actu) == 0 and tabuleiro_flag(tab, prox) == 0:        #Verifica se o numero na coordenada analisada e igual ao
                            tabuleiro_preenche_posicao(tab,prox,tabuleiro_posicao(tab, prox) + tabuleiro_posicao(tab, actu))                                            #proximo e se as flags de ambos estao a 0 (JUNCAO)
                            tabuleiro_actualiza_pontuacao(tab, tabuleiro_posicao(tab,prox))
                            tabuleiro_preenche_flag(tab,prox,1)
                            tabuleiro_preenche_posicao(tab,actu,0)
                            tabuleiro_preenche_flag(tab,actu,0)
        for l in range(len(tab)-1):
            for c in range(len(tab[l])):
                tabuleiro_preenche_flag(tab,cria_coordenada(l+1,c+1),0)                 #Limpa todas as flags no fim do movimento                                  
        return tab

def e_tabuleiro (x):
    """e_tabuleiro_ argument-bool
    Esta funcao recebe um qualquer argumento e verifica se este e um dicionario
    com as caracteristicas de tabuleiro. Caso afirmativo, devolve True, caso
    contrario devolve False."""
    
    if not isinstance(x, list) or len(x) != 5 or not isinstance(tabuleiro_pontuacao(x), int):
        return False
    for l in range(len(x)-1):
        for c in range(len(x[l])):
            if not isinstance(tabuleiro_posicao(x, cria_coordenada(l+1,c+1)), int):
                return False
    return True

def tabuleiro_terminado (tab):
    """tabuleiro_terminado: dict-bool
    Esta funcao recebe um dicionario com um tabuleiro e verifica se esxistem
    movimentos possiveis para esse tabuleiro. Caso nao hajam movimento possiveis,
    devolve True, caso contrario, devolve False."""
    
    tab1 = copia_tabuleiro(tab)
    for i in mov_cc:
        if tabuleiros_iguais(tabuleiro_reduz(tab1, i), tab) == False:   #Executa todos os movimentos possiveis e verifica se o tabuleiro
            return False                                                #antes do movimento e o tabuleiro depois do movimento sao iguais
    return True

def tabuleiros_iguais (tab1, tab2):
    """tabuleiros_iguais: dict,dict-bool
    Esta funcao recebe dois dicionarios, cada um com um tabuleiro, e verifica
    se os tabuleiros sao iguais. Caso afirmativo, devolve True, caso
    contrario devolve False."""
    
    return tab1 == tab2

def escreve_tabuleiro (tab):
    """escreve_tabuleiro: dict-{}
    Esta funcao recebe um dicionario e caso este nao seja um dicionario cria um
    ValueError, caso contrario, faz print desse tabuleiro."""
    
    if not e_tabuleiro(tab):
        raise ValueError('escreve_tabuleiro: argumentos invalidos')
    else:
        for i in range(1,5):
            print('[', tabuleiro_posicao(tab, cria_coordenada(i,1)), ']','[', tabuleiro_posicao(tab, cria_coordenada(i,2)), ']',
                  '[', tabuleiro_posicao(tab, cria_coordenada(i,3)), ']','[', tabuleiro_posicao(tab, cria_coordenada(i,4)), '] ')
        print('Pontuacao:', tabuleiro_pontuacao(tab))
        
#--------------------------------Funcoes Adicionais----------------------------#

def pede_jogada ():
    """pede_jogada: {}-str
    Esta funcao nao recebe nenhum argumento e devolve uma string do input criado
    pela funcao."""
    
    jogada = str(input('Introduza uma jogada (N, S, E, W): '))
    if jogada in mov_cc:                            #Verifica se a jogada e valida
        return jogada
    else:
        print('Jogada Invalida')
        return pede_jogada()                        #Pede jogada de novo caso a anterior seja invalida

def preenche_posicao_aleatoria (tab):
    """preenche_posicao_aleatoria: dict-dict
    Esta funcao recebe um dicionario com um tabuleiro e preenche uma posicao vazia
    aleatoria desse dicionario com o valor 2 ou 4 e devolve o dicionario actualizado."""
    
    num = 0
    prob = random()
    num_intro = (2, 4)    
    vazias = tabuleiro_posicoes_vazias(tab)
    if prob <= 0.8:
        num = 0
    else:
        num = 1
    tabuleiro_preenche_posicao(tab, vazias[round(random() * (len(vazias) - 1))], num_intro[num])
    return tab

def copia_tabuleiro (tab):
    """copia_tabuleiro: dict-dict
    Esta funcao recebe um dicionario com um tabuleiro e devolve um dicionario com
    o mesmo tabuleiro mas atribuido a uma outra variavel."""
    
    tab1 = cria_tabuleiro()                                                                 #Cria um tabuleiro novo
    for l in range(len(tab)-1):
        for c in range(len(tab[l])):
            crd = cria_coordenada(l+1,c+1)
            if tabuleiro_posicao(tab, crd) != 0 or tabuleiro_flag(tab, crd) != 0:           #Verifica todas as coordenadas por coordenadas com valor atribuido != 0
                tabuleiro_preenche_posicao(tab1, crd, tabuleiro_posicao(tab, crd))          #Copia o valor para a mesma coordenada no tab1
                tabuleiro_preenche_flag(tab1, crd, tabuleiro_flag(tab, crd))
    tabuleiro_actualiza_pontuacao(tab1, tabuleiro_pontuacao(tab))                           #Copia a pontuacao para o tab1
    return tab1 

def jogo_2048 ():
    """jogo_2048: {}-{}
    Esta funcao nao recebe nem devolve qualquer argumento, apenas recorre as outras
    funcoes do programa para jogar o jogo 2048."""
    
    tab1 = preenche_posicao_aleatoria(preenche_posicao_aleatoria(cria_tabuleiro()))         #Cria um tabuleiro inicial com apenas duas posicoes preenchida   
    def jogo_2048_aux (tab1):
        escreve_tabuleiro(tab1)
        if tabuleiro_terminado(tab1):                                                       #Verifica se o tabuleiro esta terminado
            return 'Jogo Terminado'
        tab2 = tabuleiro_reduz(copia_tabuleiro(tab1), pede_jogada())                        #Pede uma jogada para a qual executara o movimento
        while tabuleiros_iguais(tab2, tab1):                                                #Enquanto o tabuleiro apos a jogada for igual ao tabuleiro antes da jogada
            escreve_tabuleiro(tab1)                                                         #escrevera de novo o tabuleiro e pedira uma nova jogada para a qual executara o movimento
            tab2 = tabuleiro_reduz(copia_tabuleiro(tab1), pede_jogada())
        tab1 = preenche_posicao_aleatoria(tab2)                                             #Se a jogada estiver de acordo com as condicoes adicionara um valor numa posicao vazia aleatoria
        return jogo_2048_aux(tab1)
    return jogo_2048_aux(tab1)