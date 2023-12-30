grammar mylang;

SIM_DATA_ADR : 'SIM_DATA_ADR';
SIM_X_SIZE : 'SIM_X_SIZE';
SIM_Y_SIZE : 'SIM_Y_SIZE';
INTEGER : 'integer';
BEGIN : 'begin_simulation';
END : 'exit_simulation';
FOR : 'for';
WHILE : 'while';
IF : 'if';
ELSE : 'else';
ARRAY : 'array';
POINTER : 'pointer';
INITIATE : 'initiate_simulation';
CHECK : 'check_simulation_event';
SET : 'set_simulation_pixel';
FLUSH : 'flush_simulation';
COLON : ':';
SEMI_COLON : ';';
COMMA : ',';
EQUALS : '=';
PLUS : '+';
MINUS : '-';
ASTERISK : '*';
SLASH : '/';
LPAREN : '(';
RPAREN : ')';
LBRACE : '{';
RBRACE : '}';
LBRACK : '[';
RBRACK : ']';


program: beginSimulation;

beginSimulation: BEGIN LBRACE arrayDeclaration* pointerDeclaration initiateSimulation forLoop* RBRACE;

arrayDeclaration: ARRAY ID LBRACK ID RBRACK SEMI_COLON;

pointerDeclaration: POINTER ID EQUALS ID SEMI_COLON;

initiateSimulation: INITIATE LPAREN RPAREN SEMI_COLON;

forLoop: FOR LPAREN INTEGER ID EQUALS expression SEMI_COLON ID LESS_THAN expression SEMI_COLON ID PLUS_PLUS RPAREN statement;

whileLoop: WHILE LPAREN CHECK RPAREN statement;

ifStatement: IF LPAREN expression RPAREN statement (ELSE statement)?;

statement: (forLoop | whileLoop | ifStatement | assignment | setSimulationPixel | flushSimulation | exitSimulation) SEMI_COLON;

assignment: ID EQUALS expression;

setSimulationPixel: SET LPAREN expression COMMA expression RPAREN;

flushSimulation: FLUSH LPAREN RPAREN;

exitSimulation: END;

expression: term (PLUS term | MINUS term)*;

term: factor (ASTERISK factor | SLASH factor)*;

factor: INTEGER | ID | LPAREN expression RPAREN | functionCall;

functionCall: ID LPAREN (expression (COMMA expression)*)? RPAREN;

ID: [a-zA-Z_][a-zA-Z0-9_]*;

WS: [ \t\r\n]+ -> skip;
