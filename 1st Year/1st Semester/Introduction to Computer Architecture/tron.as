SP_INICIAL      EQU     FDFFh
IO_CURSOR       EQU     FFFCh
IO_WRITE        EQU     FFFEh
JANELA   		EQU     FFFFh
FIM_TEXTO       EQU     '@'
INICIAL			EQU		0B1fh
FIM				EQU		0B23h
FIM2			EQU		0C1Ah
EMPATE_CUR		EQU		0A25h           ;posicao onde se escreve o empate
INICIAL2		EQU		0C1bh
INT_MASK_ADDR   EQU     FFFAh
INT_MASK       	EQU     0000000000000010b
INT_MASK2       EQU     1000101010000001b
PORTCONTROL		EQU		FFF7h
LEDS			EQU		FFF8h
Contagem		EQU		FFF6h
binario1		EQU		1b
IO_DISPLAY      EQU     FFF0h
LCD				EQU		FFF5h
LCD_Cursor		EQU		FFF4h
Interruptores	EQU     FFF9h
				
                ORIG    8000h
mapa_str		TAB		1100
Contador        WORD    0000h
LCD_TEXTO		STR		'TEMPO MAX: 0000',FIM_TEXTO
LCD_JJ			STR		'J1: 00   J2: 00',FIM_TEXTO
VarTexto		STR		'Bem-Vindos ao Tron', FIM_TEXTO
VarTextoI		STR		'Pressione I1 para comecar', FIM_TEXTO
VarTexto1       STR     '+------------------------------------------------+',FIM_TEXTO
VarTexto2    	STR		'|                                                |', FIM_TEXTO
VarTexto3		STR		'                                                  ', FIM_TEXTO
VarTexto2_2		STR		'|                                |',FIM_TEXTO
VarTextoFim		STR		'Fim do jogo', FIM_TEXTO
VarTextoFim2	STR		'Pressione I1 para recomecar', FIM_TEXTO
VAREMPATE		STR		'EMPATE',FIM_TEXTO
JOGADOR1		STR		'#'
JOGADOR2		STR		'X'
POSJ1			WORD	0B17h
control_ESQ		WORD	1	;Variavel que se estiver a 0 influencia a posicao do cursor do JG1 conforme a sua posicao relativa	 
control_DIR		WORD	1	;Variavel que se estiver a 0 influencia a posicao do cursor do JG1 conforme a sua posicao relativa

control2_ESQ	WORD	1	;Variavel que se estiver a 0 influencia a posicao do cursor do JG2 conforme a sua posicao relativa
control2_DIR	WORD	1	;Variavel que se estiver a 0 influencia a posicao do cursor do JG2 conforme a sua posicao relativa
POSJ2			WORD	0B37h
POS_RELJ1		WORD	0001h
POS_RELJ2		WORD	0002h
PONTJ1			WORD	30h
PONTJ2			WORD	30h
TEMPO_MAX		WORD	0
Activo			WORD    1b
XY_INICIAL      WORD    010fh	;posicao inicial do cursor


;Tabela de interrupcoes

				ORIG	FE01h
INT01			WORD	Inicia

				ORIG	FE00h
INT0			WORD	MOVER1

				ORIG	FE0Bh
INT11			WORD	MOVER2

				ORIG	FE07h
INT07			WORD	MOVERJ2

				ORIG	FE09h
INT09			WORD	MOVER2J2

				ORIG	FE0Fh
INT15			WORD	TEMP

				ORIG    0000h
                JMP     inicio


MOVER1:			MOV	M[control_ESQ], R0
				RTI


MOVER2:			MOV	M[control_DIR], R0
				RTI


MOVERJ2:		MOV	M[control2_ESQ], R0
				RTI


MOVER2J2:		MOV	M[control2_DIR], R0
				RTI	


;Rotina do temporizador que incrementa o contador e reinicializa o relogio
TEMP:         	INC 	M[Contador]
				MOV     R7,1
				MOV 	M[Contagem],R7
	        	MOV		M[PORTCONTROL],R7
				RTI

;Rotina que verifica se o Interruptor 7 esta para cima ou nao, e se estiver entao o jogo e pausado e desativa o temporizador 

PAUSA:			MOV		R1,M[Interruptores]
				AND		R1,80h
				CMP		R1,R0
				BR.NZ	PAUSA1
FIM_PAUS: 		RET
		
PAUSA1:			COM		M[Activo]			;M[Activo] = !M[Activo]
				MOV		R1, M[Activo]
				MOV		M[PORTCONTROL], R1		
CICLO_PAUSA: 	MOV		R1,M[Interruptores]
				AND		R1,80h
				CMP		R1,R0
				BR.NZ	CICLO_PAUSA
				COM		M[Activo]			;M[Activo] = !M[Activo]
				MOV		R1, M[Activo]
				MOV		M[PORTCONTROL], R1		
				MOV		R1,1
				MOV		M[control2_DIR],R1
				MOV		M[control2_ESQ],R1
				MOV		M[control_DIR],R1
				MOV		M[control_ESQ],R1
				BR      FIM_PAUS


;Rotina que escreve as colunas na Janela de Texto		
colunas:		MOV		R1, M[XY_INICIAL]
            	PUSH    VarTexto1          
				PUSH    R1                 
            	CALL    EscString
				RET

;Rotina que escreve as linhas na janela de texto dependendo se o interruptor 2 esta para cima ou nao
		
Linha:			MOV		R1,M[Interruptores]
				AND		R1,2h
				CMP		R1,R0
				BR.NZ	Linha2
				CALL	copia_matriz
				MOV     R6,0014h			
CICLO_ESCREV:   MOV     R4,0100h
				ADD		M[XY_INICIAL],R4
				MOV		R1,M[XY_INICIAL]
				PUSH	VarTexto2
				PUSH	R1
				CALL	EscString
				DEC		R6
				BR.NZ	CICLO_ESCREV
LINHA_FIM:		RET
		
Linha2:			CALL    copia_matriz_1
				MOV     R6,000Eh
CICLO_ESCREV2:  MOV     R4,0100h
				ADD		M[XY_INICIAL],R4
				MOV		R1,M[XY_INICIAL]
				PUSH	VarTexto2
				PUSH	R1
				CALL	EscString
				DEC		R6
				BR.NZ	CICLO_ESCREV2
				JMP		LINHA_FIM		
		
Inicia:			MOV		R2,1
				RTI

;Rotina que verifica o nivel de jogo

VER_NIVEL:		PUSH	R1
				PUSH	R2
				MOV		R1,M[Contador]	
				CMP		R1,0258h	
				JMP.NN	NIVEL5
				CMP		R1,0190h
				JMP.NN	NIVEL4
				CMP		R1,00c8h
				JMP.NN	NIVEL3
				CMP		R1,0064h
				JMP.NN	NIVEL2
				JMP		NIVEL1
FIM_NIVEL:		POP		R2
				POP		R1
				RET

;Rotina correspondente ao nivel5
NIVEL5:			MOV		R1,FFFFH
				MOV		M[LEDS],R1
				MOV		R1,M[Contador]
				MOV		R2,1
				DIV		R1,R2
				CMP		R2,R0
				JMP.Z	VERIFICA_POS
				JMP		FIM_NIVEL

;Rotina correspondente ao nivel4
NIVEL4:			MOV		R1,0FFFH
				MOV		M[LEDS],R1
				MOV		R1,M[Contador]
				MOV		R2,2
				DIV		R1,R2
				CMP		R2,R0
				JMP.Z	VERIFICA_POS
				JMP		FIM_NIVEL

;Rotina correspondente ao nivel3
NIVEL3:			MOV		R1,00FFH
				MOV		M[LEDS],R1
				MOV		R1,M[Contador]
				MOV		R2,3
				DIV		R1,R2
				CMP		R2,R0
				JMP.Z	VERIFICA_POS
				JMP		FIM_NIVEL

;Rotina correspondente ao nivel2
NIVEL2:			MOV		R1,000FH
				MOV		M[LEDS],R1
				MOV		R1,M[Contador]
				MOV		R2,5
				DIV		R1,R2
				CMP		R2,R0
				JMP.Z	VERIFICA_POS
				JMP		FIM_NIVEL

;Rotina correspondente ao nivel1
NIVEL1:			MOV		R2,7
				DIV		R1,R2
				CMP		R2,R0
				JMP.Z	VERIFICA_POS
				JMP		FIM_NIVEL

;Rotina que verifica a posicao relativa do jogador1
VERIFICA_POS:	MOV		R1,M[POS_RELJ1]
				CMP		R1,0001h
				JMP.Z	CIMA
				CMP		R1,0002h
				JMP.Z	BAIXO
				CMP		R1,0003h
				JMP.Z	ESQUERDA
				CMP		R1,0004h
				JMP.Z	DIREITA

;Rotina que verifica a posicao relativa do jogador2
VERIFICA_POS2:	MOV		R1,M[POS_RELJ2]
				CMP		R1,0001h
				JMP.Z	CIMAJ2
				CMP		R1,0002h
				JMP.Z	BAIXOJ2
				CMP		R1,0003h
				JMP.Z	ESQUERDAJ2
				CMP		R1,0004h
				JMP.Z	DIREITAJ2

;================================================================================================================================================================================
;==============================================	Rotinas que escolhem a posicao do cursor do JG2 dependendo da sua posicao relativa e das interrupcoes ativas=====================
;================================================================================================================================================================================
CIMAJ2:			CMP		M[control2_ESQ],R0
				JMP.Z	MOV_ESQJ2
				CMP		M[control2_DIR],R0
				JMP.Z	MOV_DIRJ2
				JMP		MOV_CIMAJ2

BAIXOJ2:		CMP		M[control2_ESQ],R0
				JMP.Z	MOV_DIRJ2
				CMP		M[control2_DIR],R0
				JMP.Z	MOV_ESQJ2
				JMP		MOV_BAIXOJ2

ESQUERDAJ2:		CMP		M[control2_ESQ],R0
				JMP.Z	MOV_BAIXOJ2
				CMP		M[control2_DIR],R0
				JMP.Z	MOV_CIMAJ2
				JMP		MOV_ESQJ2

DIREITAJ2:		CMP		M[control2_ESQ],R0
				JMP.Z	MOV_CIMAJ2
				CMP		M[control2_DIR],R0
				JMP.Z	MOV_BAIXOJ2
				JMP		MOV_DIRJ2
		
MOV_CIMAJ2:		MOV		R1,0100h
				SUB		M[POSJ2],R1
				MOV		R1,0001h
				MOV		M[POS_RELJ2],R1
				JMP		MOVER

MOV_ESQJ2:		DEC		M[POSJ2]
				MOV		R1,0003h
				MOV		M[POS_RELJ2],R1
				JMP		MOVER

MOV_DIRJ2:		INC		M[POSJ2]
				MOV		R1,0004h
				MOV		M[POS_RELJ2],R1
				JMP		MOVER

MOV_BAIXOJ2:	MOV		R1,0100h
				ADD		M[POSJ2],R1
				MOV		R1,0002h
				MOV		M[POS_RELJ2],R1
				JMP		MOVER

;==========================================================================================================================================================================
;==============================================	Rotinas que escolhem a posicao do cursor do JG1 dependendo da sua posicao relativa e das interrupcoes ativas===============
;==========================================================================================================================================================================
	

CIMA:			CMP		M[control_ESQ],R0
				JMP.Z	MOV_ESQ
				CMP		M[control_DIR],R0
				JMP.Z	MOV_DIR
				JMP		MOV_CIMA

BAIXO:			CMP		M[control_ESQ],R0
				JMP.Z	MOV_DIR
				CMP		M[control_DIR],R0
				JMP.Z	MOV_ESQ
				JMP		MOV_BAIXO

ESQUERDA:		CMP		M[control_ESQ],R0
				JMP.Z	MOV_BAIXO
				CMP		M[control_DIR],R0
				JMP.Z	MOV_CIMA
				JMP		MOV_ESQ

DIREITA:		CMP		M[control_ESQ],R0
				JMP.Z	MOV_CIMA
				CMP		M[control_DIR],R0
				JMP.Z	MOV_BAIXO
				JMP		MOV_DIR
		
MOV_CIMA:		MOV		R1,0100h
				SUB		M[POSJ1],R1
				MOV		R1,0001h
				MOV		M[POS_RELJ1],R1
				JMP		VERIFICA_POS2

MOV_ESQ:		DEC		M[POSJ1]
				MOV		R1,0003h
				MOV		M[POS_RELJ1],R1
				JMP		VERIFICA_POS2

MOV_DIR:		INC		M[POSJ1]
				MOV		R1,0004h
				MOV		M[POS_RELJ1],R1
				JMP		VERIFICA_POS2

MOV_BAIXO:		MOV		R1,0100h
				ADD		M[POSJ1],R1
				MOV		R1,0002h
				MOV		M[POS_RELJ1],R1
				JMP		VERIFICA_POS2


;Rotina que chama a rotina de verificacao(se a posicao esta preenchida ou nao) e caso nao esteje escreve na janela de texto o caracter do jogador na posicao selecionada
MOVER:			MOV		R1,M[POSJ1]
				CMP		R1,M[POSJ2]
				JMP.Z	EMPATE
				CALL	COOR_COLIS
				CALL	COOR_COLISJ2
				MOV		R1,M[POSJ1]
				PUSH	JOGADOR1
				PUSH	R1
				CALL	Ambiente1
				INC		M[control_ESQ]
				INC		M[control_DIR]
				MOV		R1,M[POSJ2]
				PUSH	JOGADOR2
				PUSH	R1
				CALL 	Ambiente2
				INC		M[control2_ESQ]
				INC		M[control2_DIR]
				MOV		R1,M[Contador]
CICLO2:			CMP		R1,M[Contador] 
				BR.Z	CICLO2
				JMP		FIM_NIVEL

;Rotina que verifica se a posicao do jogador 1 se encontra preenchida e caso esteja, ele perde o jogo, caso isso nao aconteca, coloca-se 1 nessa posicao de memoria 
COOR_COLIS:		PUSH	R1
				PUSH	R2
				PUSH	R3
				PUSH	R4
				PUSH	R5
				MOV		R1,R0
				MOV		R4,R0
				MOV		R1,M[POSJ1]
				SUB		R1,010Fh
				MOV		R2,100h
				DIV		R1,R2
COOR_CICL:		CMP		R1,R0
				BR.Z	COOR_CICL2
				ADD		R4,0032h
				DEC		R1
				BR		COOR_CICL
COOR_CICL2:		ADD		R4,R2
				MOV		R5,8000h
				ADD		R5,R4
				CMP		M[R5],R0
				JMP.NZ	COOR_COLISJ2EMP
				MOV		R1,1
				MOV		M[R5],R1
				POP		R5
				POP		R4
				POP		R3
				POP		R2
				POP		R1
				RET

;Rotina que atualiza a pontuacao do jogador 2
PONTUACAO:		POP		R5
				POP		R4
				POP		R3
				POP		R2
				POP		R1
				INC		M[PONTJ2]
				MOV		R3,M[PONTJ2]
				MOV		R1,10h
				DIV		R3,R1
				MOV		R2,10
				DIV		R1,R2
				MOV		R3,1000000000011110b
				MOV		M[LCD_Cursor],R3
				ADD		R1,030h
				MOV		M[LCD],R1
				MOV		R3,1000000000011111b
				MOV		M[LCD_Cursor],R3
				ADD		R2,030h
				MOV		M[LCD],R2
				JMP		TEMPOMAX

;Rotina que verifica se a posicao do jogador 2 se encontra preenchida e caso esteja e empate e se nao tiver entao e vitoria para o jogador 2	
COOR_COLISJ2EMP:PUSH	R1
				PUSH	R2
				PUSH	R3
				PUSH	R4
				PUSH	R5
				MOV		R1,R0
				MOV		R4,R0
				MOV		R1,M[POSJ2]
				SUB		R1,010Fh
				MOV		R2,100h
				DIV		R1,R2
COOR_CICLJ2EMP:	CMP		R1,R0
				BR.Z	COOR_CICL2J2EMP
				ADD		R4,0032h
				DEC		R1
				BR		COOR_CICLJ2EMP
COOR_CICL2J2EMP:ADD		R4,R2
				MOV		R5,8000h
				ADD		R5,R4
				CMP		M[R5],R0
				JMP.Z	PONTUACAO
				POP		R5
				POP		R4
				POP		R3
				POP		R2
				POP		R1
				JMP		EMPATE
			
;Rotina que verifica se a posicao do jogador 2 se encontra preenchida e caso esteja, ele perde o jogo, caso isso nao aconteca ele coloca 1 nessa posicao de memoria			
COOR_COLISJ2:	PUSH	R1
				PUSH	R2
				PUSH	R3
				PUSH	R4
				PUSH	R5
				MOV		R1,R0
				MOV		R4,R0
				MOV		R1,M[POSJ2]
				SUB		R1,010Fh
				MOV		R2,100h
				DIV		R1,R2
COOR_CICLJ2:	CMP		R1,R0
				BR.Z	COOR_CICL2J2
				ADD		R4,0032h
				DEC		R1
				BR		COOR_CICLJ2
COOR_CICL2J2:	ADD		R4,R2
				MOV		R5,8000h
				ADD		R5,R4
				CMP		M[R5],R0
				JMP.NZ	PONTUACAO2
				MOV		R1,1
				MOV		M[R5],R1
				POP		R5
				POP		R4
				POP		R3
				POP		R2
				POP		R1
				RET

;Rotina que atualiza a pontuacao do jogador 1
PONTUACAO2:		INC		M[PONTJ1]
				MOV		R3,M[PONTJ1]
				MOV		R1,10h
				DIV		R3,R1
				MOV		R2,10
				DIV		R1,R2
				MOV		R3,1000000000010101b
				MOV		M[LCD_Cursor],R3
				ADD		R1,030h
				MOV		M[LCD],R1
				MOV		R3,1000000000010110b
				MOV		M[LCD_Cursor],R3
				ADD		R2,030h
				MOV		M[LCD],R2
				JMP		TEMPOMAX
					
;Rotina responsavel pela escrita do caracter do jogador 1 na posicao pretendida
Ambiente1:		PUSH    R1
                PUSH    R2
				PUSH    R3
                MOV     R2, M[SP+6]   ; Apontador para inicio da "string"
                MOV     R3, M[SP+5]   ; Localizacao do primeiro carater
	        	MOV     M[IO_CURSOR], R3
                MOV     R1, M[R2]
				CALL	EscCar
				POP     R3
                POP     R2
                POP     R1
                RETN    2  

;Rotina responsavel pela escrita do caracter do jogador 1 na posicao pretendida              
Ambiente2:		PUSH    R1
                PUSH    R2
				PUSH    R3
                MOV     R2, M[SP+6]   ; Apontador para inicio da "string"
                MOV     R3, M[SP+5]   ; Localizacao do primeiro carater
	        	MOV     M[IO_CURSOR], R3
                MOV     R1, M[R2]
				CALL	EscCar
				POP     R3
                POP     R2
                POP     R1
                RETN    2  
    
;Rotina que ativa o cursor da janela de Texto
AtivarJanela:   PUSH 	R2
                MOV     R2, JANELA
				MOV     M[IO_CURSOR], R2
                POP 	R2
                RET

;Rotina que escreve no LCD o texto inicial
LCD1:			MOV		R2,1000000000000001b
				MOV		R3,LCD_TEXTO
				MOV		R4,040h
Ciclo_LCD:		MOV		M[LCD_Cursor],R2
				MOV		R1,M[R3]
				MOV		M[LCD],R1
				INC		R2
				INC		R3
				CMP		M[R3],R4
				BR.NZ	Ciclo_LCD
				MOV		R2,1000000000010001b
				MOV		R3,LCD_JJ
				MOV		R4,040h
Ciclo_LCD2:		MOV		M[LCD_Cursor],R2
				MOV		R1,M[R3]
				MOV		M[LCD],R1
				INC		R2
				INC		R3
				CMP		M[R3],R4
				BR.NZ	Ciclo_LCD2		
                RET  

;Rotina que escreve na Janela de Texto
EscCar:         MOV     M[IO_WRITE], R1
				RET

;Rotina responsavel pela colocacao do cursor da janela de texto na posicao pretendida e incrementar as strings ate encontrar o carater de FIM_TEXTO
EscString:      PUSH    R1
                PUSH    R2
				PUSH    R3
                MOV     R2, M[SP+6]   ; Apontador para inicio da string
                MOV     R3, M[SP+5]   ; Localizacao do primeiro carater
Ciclo:          MOV     M[IO_CURSOR], R3
                MOV     R1, M[R2]
                CMP     R1, FIM_TEXTO
                BR.Z    FimEsc
                CALL    EscCar
                INC     R2
                INC     R3
                BR      Ciclo
FimEsc:			POP		R3
                POP     R2
                POP     R1
                RETN    2

;Rotina que divide o valor da memoria do contador por 10 quatro vezes e coloca o resto da segunda divisao no primeiro IO DISPLAY, o resto da terceira divisao no segundo DISPLAY e assim sucesivamente
MOSTRARTEMPO:	PUSH	R1
				PUSH	R2
				PUSH 	R3
				PUSH	R4
				PUSH	R5
				PUSH	R6
				MOV		R1,M[Contador]
				MOV		R2,10
				MOV		R3,10
				MOV		R4,10	
				MOV		R5,10
				DIV		R1,R2
				DIV     R1,R3
				DIV     R1,R4
				DIV     R1,R5	
				MOV 	R6, IO_DISPLAY
				CALL	NUM		
				POP		R6
				POP		R5
				POP		R4
				POP		R3
				POP		R2
				POP		R1
				RET

NUM:			MOV 	M[R6],R3
				INC 	R6
				MOV		M[R6],R4 
				INC 	R6
				MOV		M[R6],R5
				INC		R6
				MOV		M[R6],R1
				RET


;Rotina que copia para a memoria o mapa maior
copia_matriz:	MOV 	R1,1
				MOV		R2,0
				MOV		R3,8000h
ciclo_matriz:	MOV		M[R3],R1
				INC		R3
				INC		R2
				CMP		R2,0032h
				BR.NZ	ciclo_matriz
				MOV		R4,0013h
ciclo_matriz3:	MOV		M[R3],R1
				MOV		R2,0030h
ciclo_matriz2:	INC		R3
				MOV		M[R3],R0
				DEC		R2
				BR.NZ	ciclo_matriz2
				INC		R3
				MOV		M[R3],R1
				INC		R3
				DEC 	R4
				BR.NZ	ciclo_matriz3
				MOV		R2,0
				MOV		R1,1
ciclo_matriz4:	MOV		M[R3],R1
				INC		R3
				INC		R2
				CMP		R2,0032h
				BR.NZ	ciclo_matriz4
				MOV     R1,1
				MOV     M[821Ch],R1
				MOV     M[81FCh],R1
				RET

;Rotina que copia para a memoria o mapa menor	
copia_matriz_1:	MOV 	R1,1
				MOV		R2,0
				MOV		R3,8000h
ciclo_matriz_1:	MOV		M[R3],R1
				INC		R3
				INC		R2
				CMP		R2,0032h
				BR.NZ	ciclo_matriz_1
				MOV		R4,000Dh
ciclo_matriz3_1: MOV	M[R3],R1
				MOV		R2,0030h
ciclo_matriz2_1: INC	R3
				MOV		M[R3],R0
				DEC		R2
				BR.NZ	ciclo_matriz2_1
				INC		R3
				MOV		M[R3],R1
				INC		R3
				DEC 	R4
				BR.NZ	ciclo_matriz3_1
				MOV		R2,0
				MOV		R1,1
ciclo_matriz4_1: MOV	M[R3],R1
				INC		R3
				INC		R2
				CMP		R2,0032h
				BR.NZ	ciclo_matriz4_1
				MOV     R1,1
				MOV     M[8186h],R1
				MOV     M[8166h],R1
				RET
						
;Rotina que escreve a mensagem de boas vindas e escreve o mapa de jogo e as posicoes dos jogadores caso o mapa seja o maior
		
inicio:         MOV     R1, SP_INICIAL
                MOV     SP, R1
	        	MOV     R7, INT_MASK
	        	MOV     M[INT_MASK_ADDR], R7
				CALL	AtivarJanela
				MOV		R1,INICIAL
				PUSH	VarTexto
				PUSH	R1
				CALL	EscString
				MOV		R1,INICIAL2
				PUSH	VarTextoI
				PUSH	R1
				CALL	EscString
				MOV		R2,R0
				ENI
ciclo:			CMP		R2,1
				BR.NZ	ciclo
				DSI
				CALL	LCD1
REINICIO:		CALL	colunas
				CALL	Linha
				CALL	colunas
				MOV		R1,M[Interruptores]
				AND		R1,2h
				CMP		R1,R0
				JMP.NZ	limpa		
posicaoJG:		MOV		R1,M[POSJ1]
				PUSH	JOGADOR1
				PUSH	R1
				CALL	Ambiente1
				MOV		R1,M[POSJ2]
				PUSH	JOGADOR2
				PUSH	R1
				CALL 	Ambiente2
CONTINUA:		MOV     R7, INT_MASK2
                MOV     M[INT_MASK_ADDR], R7
				MOV		M[control2_DIR],R1
				MOV		M[control2_ESQ],R1
				MOV		M[control_DIR],R1
				MOV		M[control_ESQ],R1
				ENI
				CALL	Clock	

CicloCont:		CALL 	MOSTRARTEMPO				
				CALL	VER_NIVEL			
				CALL	PAUSA				
				BR	CicloCont

;Rotina que limpa a janela de texto caso o mapa seja mais pequeno e escreve a posicao dos jogadores
limpa:			MOV     R6,0006h
CICLO_ESCREV3:  MOV     R4,0100h
				ADD		M[XY_INICIAL],R4
				MOV		R1,M[XY_INICIAL]
				PUSH	VarTexto3
				PUSH	R1
				CALL	EscString
				DEC		R6
				BR.NZ	CICLO_ESCREV3
				MOV		R1,300h
				SUB		M[POSJ1],R1
				MOV		R1,M[POSJ1]
				PUSH	JOGADOR1
				PUSH	R1
				CALL	Ambiente1
				MOV		R1,300h
				SUB		M[POSJ2],R1
				MOV		R1,M[POSJ2]
				PUSH	JOGADOR2
				PUSH	R1
				CALL 	Ambiente2
				JMP		CONTINUA

;Rotina que inicializa o relogio
Clock:			MOV     R7,1
				MOV 	M[Contagem],R7
	        	MOV		M[PORTCONTROL],R7	
				RET

;Rotina correspondente ao EMPATE 
EMPATE:			MOV		R1,M[Contador]
				MOV		R2,M[TEMPO_MAX]
				CMP		R2,R1
				JMP.NN	EMPATEC
				MOV		M[TEMPO_MAX],R1
				CALL	LCD_TEMPO
EMPATEC:		MOV		R1,FIM
				PUSH	VarTextoFim
				PUSH	R1
				CALL	EscString
				MOV		R1,FIM2
				PUSH	VarTextoFim2
				PUSH	R1
				CALL	EscString
				MOV		R1,EMPATE_CUR
				PUSH	VAREMPATE
				PUSH	R1
				CALL	EscString
				MOV     R7, INT_MASK
		        MOV     M[INT_MASK_ADDR], R7
				MOV	R2,R0
				JMP	Ciclo_int				
		
;Rotina que escreve a mensagem fim de jogo e coloca todas as variaveis conforme se encontravam inicialmente
FIM_JOGO:		MOV		R1,FIM
				PUSH	VarTextoFim
				PUSH	R1
				CALL	EscString
				MOV		R1,FIM2
				PUSH	VarTextoFim2
				PUSH	R1
				CALL	EscString
				MOV     R7, INT_MASK
                MOV     M[INT_MASK_ADDR], R7
				MOV		R2,R0
Ciclo_int:		CMP		R2,1
				BR.NZ	Ciclo_int
				MOV		M[Contador],R0
				MOV		R1,0B17h
				MOV		M[POSJ1],R1
				MOV		R1,0B37h
				MOV		M[POSJ2],R1
				MOV		R1,0001h
				MOV		M[POS_RELJ1],R1
				MOV		R1,0002h
				MOV		M[POS_RELJ2],R1
				MOV		M[LEDS],R0
				MOV		R1,1
				MOV     R1,010Fh
				MOV     M[XY_INICIAL],R1
				MOV		R1,8000h
ciclo_0:		MOV		M[R1],R0
				INC		R1
				CMP		R1,844Ch
				BR.NZ	ciclo_0
				JMP		REINICIO

;Rotina que atualiza o tempo maximo no LCD
TEMPOMAX:		MOV		R1,M[Contador]
				MOV		R2,M[TEMPO_MAX]
				CMP		R2,R1
				JMP.NN	FIM_JOGO
				MOV		M[TEMPO_MAX],R1
				CALL	LCD_TEMPO
				JMP		FIM_JOGO		
		
;Rotina responsavel pela escrita no LCD do tempo maximo
LCD_TEMPO:		PUSH	R1
				PUSH	R2
				PUSH 	R3
				PUSH	R4
				PUSH	R5
				PUSH	R6
				MOV		R1,M[Contador]
				MOV		R2,10
				MOV		R3,10
				MOV		R4,10	
				MOV		R5,10
				DIV		R1,R2
				DIV     R1,R3
				DIV     R1,R4
				DIV     R1,R5	
				MOV 	R6,1000000000001100b
				CALL	NUMERO		
				POP		R6
				POP		R5
				POP		R4
				POP		R3
				POP		R2
				POP		R1
				RET

NUMERO:			ADD		R1,030h
				MOV 	M[LCD_Cursor],R6
				MOV		M[LCD],R1
				INC 	R6
				ADD		R5,030h	
				MOV 	M[LCD_Cursor],R6
				MOV		M[LCD],R5
				INC 	R6
				ADD		R4,030h
				MOV 	M[LCD_Cursor],R6
				MOV		M[LCD],R4
				INC		R6
				ADD		R3,030h
				MOV 	M[LCD_Cursor],R6
				MOV		M[LCD],R3
				RET	