tree_values(nil, []).
tree_values(t(X,L,R), Values) :-
    tree_values(L, LV),
    tree_values(R, RV),
    append(LV, [X|RV], Values).

build_balanced([], nil).
build_balanced(Sorted, t(Mid, Left, Right)) :-
    split_mid(Sorted, LeftList, Mid, RightList),
    build_balanced(LeftList, Left),
    build_balanced(RightList, Right).

split_mid(List, Left, Mid, Right) :-
    length(List, N),
    H is N // 2,
    length(Left, H),
    append(Left, [Mid|Right], List).

balance_to_bst(Tree, BalancedBST) :-
    tree_values(Tree, Values),
    sort(Values, SortedUnique),
    build_balanced(SortedUnique, BalancedBST).

print_tree(Tree) :-
    print_tree(Tree, 0).

print_tree(nil, _) :- !.
print_tree(t(X,L,R), Depth) :-
    D1 is Depth + 1,
    print_tree(R, D1),
    tab(Depth * 4), writeln(X),
    print_tree(L, D1).
