:- module(catalog, [start/0, start/1]).

:- use_module(library(readutil)).
:- dynamic book/4.

start :-
    start('books_db.pl').

start(DbFile) :-
    load_db(DbFile),
    menu(DbFile).

load_db(DbFile) :-
    (   exists_file(DbFile)
    ->  consult(DbFile)
    ;   true
    ).

menu(DbFile) :-
    repeat,
    nl,
    writeln('--- Книжный каталог ---'),
    writeln('1. Просмотр базы'),
    writeln('2. Добавить запись(и)'),
    writeln('3. Удалить запись(и)'),
    writeln('4. Запрос (издательство + год)'),
    writeln('5. Выход (сохранить)'),
    write('Выберите пункт (1-5): '),
    read_int(Choice),
    handle_choice(Choice, DbFile),
    Choice =:= 5,
    !.

handle_choice(1, _) :-
    show_db.
handle_choice(2, _) :-
    add_many.
handle_choice(3, _) :-
    delete_many.
handle_choice(4, _) :-
    query_by_publisher_and_year.
handle_choice(5, DbFile) :-
    save_db(DbFile),
    writeln('Сохранено. Выход.').
handle_choice(_, _) :-
    writeln('Неверный пункт меню.').

% -------- IO-helpers --------

read_int(N) :-
    read_line_to_string(user_input, S),
    normalize_space(string(S2), S),
    (   S2 = ""
    ->  N = -1
    ;   number_string(N, S2)
    ).

read_str(Prompt, S) :-
    write(Prompt),
    read_line_to_string(user_input, Raw),
    normalize_space(string(S), Raw).

% -------- Просмотр --------

show_db :-
    (   book(_,_,_,_)
    ->  forall(book(A,T,P,Y),
               format('Автор: ~w | Книга: ~w | Изд-во: ~w | Год: ~d~n', [A,T,P,Y]))
    ;   writeln('База пустая.')
    ).

% -------- Добавление --------

add_many :-
    writeln('Добавление записей (пустой автор = стоп).'),
    repeat,
    read_str('Автор: ', A),
    (   A = ""
    ->  !
    ;   read_str('Название: ', T),
        read_str('Издательство: ', P),
        read_str('Год: ', YearS),
        (   number_string(Y, YearS)
        ->  assertz(book(A, T, P, Y)),
            writeln('Добавлено.'), fail
        ;   writeln('Год должен быть числом.'), fail
        )
    ).

delete_many :-
    writeln('Удаление записей (пустой автор = стоп).'),
    repeat,
    read_str('Автор: ', A),
    (   A = ""
    ->  !
    ;   read_str('Название: ', T),
        read_str('Издательство: ', P),
        read_str('Год: ', YearS),
        (   number_string(Y, YearS)
        ->  (   retract(book(A, T, P, Y))
            ->  writeln('Удалено.')
            ;   writeln('Не найдено совпадений.')
            ),
            fail
        ;   writeln('Год должен быть числом.'), fail
        )
    ).

% -------- Запрос --------

query_by_publisher_and_year :-
    read_str('Введите издательство: ', Pub),
    read_str('Введите год (книги позже этого года): ', YearS),
    (   number_string(Year, YearS)
    ->  findall(book(A,T,Pub,Y),
                ( book(A,T,Pub,Y), Y > Year ),
                Result),
        (   Result = []
        ->  writeln('Ничего не найдено.')
        ;   writeln('Найдено:'),
            forall(member(book(A,T,Pub,Y), Result),
                   format('Автор: ~w | Книга: ~w | Изд-во: ~w | Год: ~d~n', [A,T,Pub,Y]))
        )
    ;   writeln('Год должен быть числом.')
    ).

% -------- Сохранение --------

save_db(DbFile) :-
    open(DbFile, write, S),
    forall(book(A,T,P,Y),
           ( write_term(S, book(A,T,P,Y), [quoted(true)]),
             write(S, '.'),
             nl(S)
           )),
    close(S).












