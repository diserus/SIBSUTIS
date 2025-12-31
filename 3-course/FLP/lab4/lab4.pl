sort_words_in_lines(InputFile, OutputFile) :-
    open(InputFile, read, InStream),
    open(OutputFile, write, OutStream),
    process_lines_sort(InStream, OutStream),
    close(InStream),
    close(OutStream).

process_lines_sort(InStream, OutStream) :-
    read_line_to_string(InStream, Line),
    (   Line \= end_of_file
    ->  split_string(Line, " \t", " \t", Words),
        sort(Words, SortedWords),
        atomic_list_concat(SortedWords, ' ', SortedLine),
        writeln(OutStream, SortedLine),
        process_lines_sort(InStream, OutStream)
    ;   true
    ).
remove_max_length_words(InputFile, OutputFile) :-
    read_all_lines(InputFile, Lines),
    find_all_words(Lines, AllWords),
    find_max_word_length(AllWords, MaxLength),
    open(OutputFile, write, OutStream),
    process_lines_remove(Lines, MaxLength, OutStream),
    close(OutStream).

read_all_lines(InputFile, Lines) :-
    open(InputFile, read, InStream),
    read_lines_list(InStream, Lines),
    close(InStream).

read_lines_list(InStream, [Line|Rest]) :-
    read_line_to_string(InStream, Line),
    Line \= end_of_file,
    !,
    read_lines_list(InStream, Rest).
read_lines_list(_, []).

find_all_words([], []).
find_all_words([Line|RestLines], AllWords) :-
    split_string(Line, " \t", " \t", Words),
    find_all_words(RestLines, RestWords),
    append(Words, RestWords, AllWords).

find_max_word_length([], 0).
find_max_word_length([Word|Rest], MaxLength) :-
    string_length(Word, Len),
    find_max_word_length(Rest, RestMax),
    MaxLength is max(Len, RestMax).

process_lines_remove([], _, _).
process_lines_remove([Line|Rest], MaxLength, OutStream) :-
    split_string(Line, " \t", " \t", Words),
    filter_words_by_length(Words, MaxLength, FilteredWords),
    (   FilteredWords \= []
    ->  atomic_list_concat(FilteredWords, ' ', NewLine),
        writeln(OutStream, NewLine)
    ;   writeln(OutStream, '')
    ),
    process_lines_remove(Rest, MaxLength, OutStream).

filter_words_by_length([], _, []).
filter_words_by_length([Word|Rest], MaxLength, Filtered) :-
    string_length(Word, Len),
    filter_words_by_length(Rest, MaxLength, RestFiltered),
    (   Len < MaxLength
    ->  Filtered = [Word|RestFiltered]
    ;   Filtered = RestFiltered
    ).
