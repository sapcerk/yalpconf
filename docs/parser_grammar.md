# Parser grammar

The EBNF notation is used to write the grammar.



## Lexical Elements

Lexical elements and patters described in file lexical_analyzer_patterns.md.

\<decimal-integer\> ::=  decimal-integer-pattern

\<hexadecimal-integer\> ::=  hexadecimal-integer-pattern

\<binary-integer\> ::= binary-integer-pattern

\<boolean\> ::= boolean-pattern

\<string\> ::= string-pattern

\<setting-name\> ::= identifier-pattern



## Configuration Structure

\<configuration-file\> ::=  '{' \<settings-list\> '}' | \<settings-list\>

\<settings-list\> ::= \<setting\> ((',' | ';')? \<setting\>)*

\<setting\> ::= \<setting-name\> '=' \<setting-value\>

 \<setting-value\> ::=  \<value\> | '{' \<settings-list\> '}' |  '[' \<value-list\> ']'

\<value-list\> ::= \<value\> ((',' | ';')? \<value\>)*

\<value\> ::= \<decimal-integer\> | 

​                    \<hexadecimal-integer\> |

​                    \<binary-integer\> |

​                    \<boolean\> |

​                    \<string\>

