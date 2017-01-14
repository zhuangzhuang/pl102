number   : /-?[0-9]+/ ;
symbol   : /[a-zA-Z0-9_+\-*\/\\=<>!&]+/;
sexpr    : '(' <expr>* ')';
qexpr    : '{' <expr>* '}';
expr     : <number> | <symbol> | <sexpr> | <qexpr>;
lispy    : /^/ <expr>+ /$/;