# Patterns for Lexical Analyzer

| Token      | **Lexeme**                 | Pattern                  | Pattern names for BNF       | Description         |
| ---------- | -------------------------- | ------------------------ | --------------------------- | ------------------- |
| separator  | ,                          | ,                        |                             |                     |
| separator  | ;                          | ;                        |                             |                     |
| separator  | {                          | {                        |                             |                     |
| separator  | }                          | }                        |                             |                     |
| separator  | [                          | [                        |                             |                     |
| separator  | ]                          | ]                        |                             |                     |
| operator   | =                          | =                        |                             |                     |
| literal    | 120                        | [0-9]+                   | decimal-integer-pattern     | decimal integer     |
| literal    | 0x1A2B                     | 0[xX]\[0-9a-fA-F]+       | hexadecimal-integer-pattern | hexadecimal integer |
| literal    | 0b1010                     | 0[bB]\[0-1]+             | binary-integer-pattern      | binary integer      |
| literal    | true                       | [tT]\[rR]\[uU]\[eE]      | boolean-pattern             | boolean             |
| literal    | False                      | [fF]\[aA]\[lL]\[sS]\[eE] | boolean-pattern             | boolean             |
| literal    | "string /* { # [ // }] **" | "\[^"\]*"                | string-pattern              | string              |
| identifier | Set-Tst_1                  | [a-zA-Z0-9_-]+           | identifier-pattern          | setting name        |
| comment    | /* text */                 | /\*[^]\*?\*/             |                             | multiline comment   |
| comment    | // text                    | //.*$                    |                             | line comment        |
| comment    | # text                     | #.*$                     |                             | line comment        |

