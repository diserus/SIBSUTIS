% --- смежность в неориентированном графе ---
adj(X,Y) :- edge(X,Y).
adj(X,Y) :- edge(Y,X).

% --- собрать список вершин из списка ребер ---
vertices(Vs) :-
    findall(X, (edge(X,_); edge(_,X)), V0),
    sort(V0, Vs).

% --- выбрать элемент из списка (рекурсивно) ---
select1(X, [X|T], T).
select1(X, [H|T], [H|R]) :-
    select1(X, T, R).

% --- перестановка (рекурсивно) ---
perm([], []).
perm(L, [X|P]) :-
    select1(X, L, Rest),
    perm(Rest, P).

% --- проверить, что список вершин идет по ребрам подряд ---
path_ok([_]).
path_ok([A,B|T]) :-
    adj(A,B),
    path_ok([B|T]).

% --- гамильтонов цикл: Cycle = [Start, ..., Start] ---
hamiltonian_cycle(Cycle) :-
    vertices(Vs),
    Vs = [Start|Rest],
    perm(Rest, Perm),
    Path = [Start|Perm],
    path_ok(Path),
    last(Path, Last),
    adj(Last, Start),
    append(Path, [Start], Cycle).


edge(a,b).
edge(b,c).
edge(c,d).
edge(d,a).
edge(a,c).







