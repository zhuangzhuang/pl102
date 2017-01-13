number   : /-?[0-9]+/ ;
symbol   : '+' | '-' | '*' | '/' 
		  | "list" | "head" | "tail" | "join" | "eval";
sexpr    : '(' <expr>* ')';
qexpr    : '{' <expr>* '}';
expr     : <number> | <symbol> | <sexpr> | <qexpr>;
lispy    : /^/ <expr>+ /$/;