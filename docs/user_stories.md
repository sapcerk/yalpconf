# User stories

## Terms

**Library** is yalpconf library.

**App** is third-party program, that uses the library to manage configuration files.

**App Users** is people who change settings in a configuration file to customize an app.

**Library Users** is people who will use this library in their apps for reading the configuration file.

**Developer** is developer of library.



## User stories

| #    | As a \<type of user> | I want to \<some goal/objective>                             | So that <benefit/result/some reason>                         |
| ---- | -------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 1    | App Users            | change settings in a configuration file                      | affects how the application works                            |
| 2    | App Users            | be notified where I made a syntax error                      | help me to fix it                                            |
| 3    | App Users            | be notified if i specify a setting that does not exist       | help me to fix it                                            |
| 4    | App Users            | be notified if i specify a value of a different type         | help me to fix it                                            |
| 5    | App Users            | be notified if i specify a value that is out of range        | help me to fix it                                            |
| 6    | App Users            | (AFTER MVP!) separate one file to few smaller files, included to main configuration file | improve readability of configuration file and                |
| 7    | App Users            | (AFTER MVP!) ability to include directory with configuration files. | improves the structure of storing and including configuration files |
| 8    | Library Users        | get a value by setting name                                  |                                                              |
| 9    | Library Users        | cast value to base types (int, double, string, bool)         |                                                              |
| 10   | Library Users        | group settings together                                      | increase readability of configuration file and simplify access to the values of a single object |
| 11   | Library Users        | creates arrays of base types or settings groups              |                                                              |
| 12   | Library Users        | leave comments                                               | improve understanding of settings for App Userss             |
| 13   | Library Users        | support literals for integer types (0x, 0b)                  |                                                              |
| 14   | Library Users        | (AFTER MVP!) create variables                                | reduce duplicate values for settings                         |
| 15   | Library Users        | check settings value with regex pattern                      | it will help notify the App Users if he specifies a value that is out of range (relate to user story #5) |
| 16   | Library Users        | change input stream if necessary (from file stream to custom stream) |                                                              |
| 17   | Developer            | extend base types in the future                              |                                                              |
| 18   | Developer            | extend data structures in the future (group/object, array)   |                                                              |

