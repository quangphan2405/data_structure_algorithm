Short explanation of test files:

Files named "...-in.txt" are input files containing commands for different tests.

Files named "...-out.txt" are output files containing expected output of the corresponding input.

You can either just run the input file with command read "...-in.txt" or compare your own output with the expected output with command testread "...-in.txt" "...-out.txt" (the graphical UI's file selector allows you to select both files at once by control-clicking with mouse).

Files named "perftest-....txt" are performance tests of various types of operations. They can be run with command read "perftest-....txt".

Correctness tests:
- simpletest-compulsory-in/out.txt: Really simple test to find most obvious bugs
- example-*-in/out.txt: The example in the assignment description, showing basic operation of all commands
- Tretest-*-in/out.txt: Somewhat bigger tests with real Tampere centre information

Performance tests:
- ...coming

More info on testing on the course web pages!
