/*indica a posicao dos elementos*/
posicao(E,[E|_],1).
posicao(E,[_|R],P):- posicao(E,R,P1), P is P1 + 1 .

/*troca a posicao dos valores */
troca_posicao([],_,_,[]).
troca_posicao([E|R],E,D,[D|R1]) :- troca_posicao(R, E,D, R1).
troca_posicao([D|R],E,D,[E|R1]) :- troca_posicao(R, E,D, R1).
troca_posicao([E1|R],E,D,[E1|R1]) :- troca_posicao(R, E,D, R1).


pertence(L,[L|_]).
pertence(L,[_|R]):-
				pertence(L,R),!.


/*sao os predicados que escrevem o jogo*/

meu_escreve(0):-write(' '),!.
meu_escreve(P):-write(P).


write_quadro([]).
write_quadro([P,S,T|R]):-
						meu_escreve(P), meu_escreve(' '),
                        meu_escreve(S), meu_escreve(' '),
						meu_escreve(T), nl,
                        write_quadro(R).

write_setinha([A,B,C,D,E,F,G,H,I],[A1,B1,C1,D1,E1,F1,G1,H1,I1]):-
			    meu_escreve(A), meu_escreve(' '), meu_escreve(B), meu_escreve(' '), meu_escreve(C), write('      '), meu_escreve(A1), meu_escreve(' '),meu_escreve(B1), meu_escreve(' '), meu_escreve(C1), meu_escreve('      '),nl,
				meu_escreve(D), meu_escreve(' '), meu_escreve(E), meu_escreve(' '), meu_escreve(F), write('  ->  '), meu_escreve(D1), meu_escreve(' '), meu_escreve(E1), meu_escreve(' '), meu_escreve(F1), meu_escreve('      '),nl,
				meu_escreve(G), meu_escreve(' '), meu_escreve(H), meu_escreve(' '), meu_escreve(I), write('      '), meu_escreve(G1), meu_escreve(' '), meu_escreve(H1), meu_escreve(' '), meu_escreve(I1).


write_movimentos([]):-!.

write_movimentos([[E,M]|R]):-
					M = c,
					write('mova a peca '),write(E),write(' para cima'),
					nl, write_movimentos(R);
					M = b,
					write('mova a peca '),write(E),write(' para baixo'),
					nl, write_movimentos(R);
					M = d,
					write('mova a peca '),write(E),write(' para a direita'),
					nl, write_movimentos(R);
					M = e,
					write('mova a peca '),write(E),write(' para a esquerda'),
					nl, write_movimentos(R).

/*movimentos*/


move_cima(L1,E,L2):-
					posicao(E,L1,P),
					posicao(0,L1,P1),
					P =:= P1 + 3,
					P1 =\= 7,
					P1 =\= 8,
					P1 =\= 9,
					troca_posicao(L1,E,0,L2), !.

move_baixo(L1,E,L2):-
					posicao(E,L1,P),
					posicao(0,L1,P1),
					P =:= P1 - 3,
					P1 =\= 1,
					P1 =\= 2,
					P1 =\= 3,
					troca_posicao(L1,E,0,L2), !.

move_direita(L1,E,L2):-
					posicao(E,L1,P),
					posicao(0,L1,P1),
					P =:= P1 - 1,
					P1 =\= 1,
					P1 =\= 4,
					P1 =\= 7,
					troca_posicao(L1,E,0,L2), !.

move_esquerda(L1,E,L2):-
					posicao(E,L1,P),
					posicao(0,L1,P1),
					P =:= P1 + 1,
					P1 =\= 3,
					P1 =\= 6,
					P1 =\= 9,
					troca_posicao(L1,E,0,L2), !.

/* verifica se o movimento legal */

mov_legal(L1,M,E,L2):-
					M = c,
					move_cima(L1,E,L2);
					M = b,
					move_baixo(L1,E,L2);
					M = d,
					move_direita(L1,E,L2);
					M = e,
					move_esquerda(L1,E,L2).


/* faz o inicializacao do jogo --> escreve o que temos e o que queremos obter */

inicializacao(L1,L2):-
		write('Transformacao desejada:'),nl,
		write_setinha(L1,L2),nl.



/* ciclo do jogo */


jogo(L1,Lfinal,M):-
			mov_legal(L1,M,_,L3),
			write_quadro(L3),
			nl,
			pede_jogada(L3,Lfinal).

jogo(L1,Lfinal,_):-
			write('Movimento ilegal'),
			pede_jogada(L1,Lfinal).

pede_jogada(Lfinal,Lfinal):-
				/*mov_legal(Lfinal,_,_,Lfinal),*/
				write('Parabens!'),!.

pede_jogada(L1,Lfinal):-
				writeln('Qual o seu movimento?'), read(M),
				nl,
				jogo(L1,Lfinal,M),!.




resolve_manual(L1,L2):-
					inicializacao(L1,L2),
					pede_jogada(L1,L2).


/*----------------------------------------------- resolve_cego\2 ------------------------------------------------------*/

inverte(L, L1) :- inverte(L, [], L1).

inverte([], L1, L1).

inverte([P | R], Ac, L1) :- inverte(R, [P | Ac], L1).

guarda_mov(E,M, L ,[[E,M]|L]).

guarda_gerados(L1,Lgerados,[L1|Lgerados]).

jogo_cego(L1,Lfinal,E,M,Lmov,Lgerados):-
				mov_legal(L1,M,E,L2),
				guarda_mov(E,M,Lmov,Lmov2),
			    \+ pertence(L2,Lgerados),
				guarda_gerados(L2,Lgerados,Lgerados2),
				ciclo(L2,Lfinal,Lmov2,Lgerados2).


ciclo(Lfinal,Lfinal,Lmov,_):-
				inverte(Lmov,Lmov2),
				write_movimentos(Lmov2), !.


ciclo(L1,Lfinal,Lmov,Lgerados):-
				jogo_cego(L1,Lfinal,_,_,Lmov,Lgerados).

resolve_cego(L1,L2):-
				inicializacao(L1,L2),
				ciclo(L1,L2,[],[L1]), !.





/*-------------------------------resolve_informada----------------------------------*/
































