number   : /-?[0-9]+/ ;
operator : '+' | '-' | '*' | '/';
expr     : <number> | '(' <operator> <expr>+ ')';
lispy    : /^/ <operator> <expr>+ /$/;