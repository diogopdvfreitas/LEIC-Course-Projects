#81586 Diogo Freitas

#Este programa serve para verificar ou gerar numeros
#de cartoes de credito validos e identificar qual foi
#a entendidade emissora do dito cartao.

from random import random

Redes = (('American Express', 'AE', ('34', '37'), (15,)),
         ('Diners Club International', 'DCI', ('309', '36', '38', '39'), (14,)),
         ('Discover Card', 'DC', ('65',), (16,)),
         ('Maestro', 'M', ('5018', '5020', '5038'), (13, 19)),
         ('Master Card', 'MC', ('50', '51', '52', '53', '54', '19'), (16,)),
         ('Visa Electron', 'VE', ('4026', '426', '4405', '4508'), (16,)),
         ('Visa', 'V', ('4024', '4532', '4556'), (13, 16)))
Categorias = ('Companhias aereas',
              'Companhias aereas e outras tarefas futuras da industria',
              'Viagens e entretenimento e bancario / financeiro',
              'Servicos bancarios e financeiros', 'Servicos bancarios e financeiros',
              'Merchandising e bancario / financeiro',
              'Petroleo e outras atribuicoes futuras da industria',
              'Saude, telecomunicacoes e outras atribuicoes futuras da industria',
              'Atribuicao nacional')
Nome = 0
Abv = 1
IIN = 2
Len = 3
        
def calc_soma (x):
    """calc_soma: string-int
    Esta funcao recebe e inverte uma cadeia de caracteres correspondente ao numero de 
    cartao de credito sem o digito de verificacao, multiplica os digitos em 
    posicoes impares por 2 subtraindo 9 aos superiores a 9 e soma todos os 
    digitos, retornando essa mesma soma."""
    
    count = 1
    i = len(x) - 1
    soma = 0       
    while i >= 0:               #Inversao do numero e multiplicacao do numero por 2.
        if count % 2 != 0:
            dig = eval(x[i]) * 2
            if dig > 9:
                dig = dig - 9
        else:
            dig = eval(x[i])
        soma = soma + dig       #Soma dos digitos, ja com os em posicoes impares multiplicados por 2.
        i = i - 1
        count += 1
    return soma

def luhn_verifica (x):
    """luhn_verifica: string-bool
    Esta funcao recebe uma cadeia de caracteres correspondente ao numero de 
    cartao de credito e soma o resultado da funcao calc_soma (x) ao digito de
    verificacao, verifica se o resultado e divisivel por 10 e ,caso seja, 
    retorna True, caso nao seja, retorna False."""

    y = eval(x)
    num_ver = y % 10
    if (calc_soma (str(y // 10)) + num_ver) % 10 == 0:
        return True
    else:
        return False
    
def comeca_por (cad1, cad2):
    """comeca_por: string,string-bool
    Esta funcao recebe duas cadeias de caracteres, uma delas correspondente 
    ao numero de cartao de credito e outra correspondente a um numero com o qual
    o numero de cartao de credito podera comecar. Caso o numero de cartao de 
    credito comece com o segundo numero a funcao retorna True, caso isso nao 
    aconteca retorna False."""
    
    control = 0
    if len(cad2) > len(cad1):
        return False
    else:
        count = 0
        while count < len(cad2):    #Condicao que verifica os digitos iniciais da string cad1 por digitos da cad2.
            if cad2[count] == cad1[count]:
                control = control + 1
            count += 1
        if control == len(cad2):
            return True
        else:
            return False
            
def comeca_por_um (cad, t_cads):
    """comeca_por_um: string,tuple-bool
    Esta funcao recebe uma cadeia de caracteres correspondente ao numero de 
    cartao de credito e um tuplo com as cadeias de caracteres dos possiveis 
    numeros iniciais do cartao de credito. Caso o numero de cartao de credito 
    comece com o um dos numeros no tuplo, a funcao retorna True, caso isso nao 
    aconteca, retorna False."""
    
    control = 0
    for y in range(len(t_cads)):    #Condicao que verifica todos digitos inciais de cad por digitos dentro do tuplo t_cads.
        if comeca_por(cad, t_cads[y]):
            control = 1
    if control == 1:
        return True
    else:
        return False

def valida_iin (x):
    """valida_iin: string-string
    Esta funcao recebe uma cadeia de caracteres correspondente ao numero de 
    cartao de credito e utilizando comeca_por_um (cad, t_cads), verifica os 
    digitos iniciais do cartao e o seu tamanho. Se encontrar, a funcao retorna
    uma cadeia de caracteres correspondente a rede emissora do cartao, caso 
    contrario retorna uma cadeia de caracteres vazia."""

    for i in range(len(Redes)):
        if comeca_por_um(x, Redes[i][IIN]) and len(x) in Redes[i][Len]:
            return Redes[i][Nome]
    return ''
    
def categoria (x):
    """categoria: string-string
    Esta funcao recebe uma cadeia de caracteres correspondente ao numero de 
    cartao de credito e utilizando comeca_por (cad1, cad2), vai retornar a 
    cadeia de caracteres correspondente a categoria emissora do cartao."""    

    for i in range(len(Categorias)):
        if comeca_por (x, str(i + 1)):
            return Categorias[i]
    
def verifica_cc (x):
    """verifica_-cc: int-string or tuple
    Esta funcao recebe o numero de cartao de credito e utilizando as funcoes
    luhn_verifica (x), categoria (x) e valida_iin (x) retorna cartao
    invalido caso o numero nao seja valido, caso contrario retorna a categoria
    e a rede emissora do cartao."""

    if luhn_verifica (str(x)) == False or valida_iin (str(x)) == '':
        return 'cartao invalido'
    else:
        return (categoria (str(x)), valida_iin (str(x)))

def digito_verificacao (x):
    """digito_verificacao: string-string
    Esta funcao recebe uma string com um numero de cartao de credito aleatorio
    sem o digito de verificacao e calcula esse mesmo digito."""
    
    if calc_soma(x) % 10 == 0:      #Assume que o digito de verificacao e 10, caso calc_soma(x) seja multiplo de 10.
        num_ver = 0
    else:                           #Calcula o digito de verificacao, caso calc_soma(x) nao seja multiplo de 10.
        num_ver = (((calc_soma(x) // 10) + 1) * 10) - calc_soma(x)        
    return str(num_ver)

def gera_num_cc (x):
    """gera_num_cc: string-int
    Esta funcao recebe uma cadeia de caracteres correspondente rede emissora,
    gera aleatoriamente um numero sem o digito de verificacao e utilizando a 
    funcao calc_soma (x) gera o digito de verificacao que torna o numero de 
    cartao valido segundo o algoritmo de luhn."""

    num = 0
    for i in range(len(Redes)):
        if x == Redes[i][Abv]:
            num = eval(Redes[i][IIN][int(random() * (len(Redes[i][IIN]) - 1))])   #Adiciona o IIN
            if len(Redes[i][Len]) == 2:                                 #Se houverem dois tamanhos de numeros para escolher
                y = round(random())                                     #y e a variavel que escolhe um dos tamanhos aleatoriamente
                while len(str(num)) < Redes[i][Len][y] - 1:             #Adiciona numeros ate so faltar o digito de verificacao
                    num = num * 10 + int(random() * 10)
            else:
                while len(str(num)) < Redes[i][Len][0] - 1:
                    num = num * 10 + int(random() * 10)        
            num = num * 10 + eval(digito_verificacao(str(num)))         #Adiciona o digito de verificacao ao numero de cartao de credito.
            return num
    return 'Rede Emissora Invalida'