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

\<configuration-file\> ::= \<object\> | \<settings-list\>?

\<object\> ::= '{' \<settings-list\>? '}'

\<settings-list\> ::= \<setting\>? (\<item-separators\> \<setting\>?)*

\<setting\> ::= \<setting-name\> '=' \<setting-value\>

 \<setting-value\> ::=  \<value\> | \<object\> |  \<array\>

\<array\> ::= '[' \<values-list\>? ']'

\<values-list\> ::= \<value\>? (\<item-separators\> \<value\>?)*

\<item-separators\> ::= ',' | ';'

\<value\> ::= \<decimal-integer\> | 

​                    \<hexadecimal-integer\> |

​                    \<binary-integer\> |

​                    \<boolean\> |

​                    \<string\>

