# Compilation-Order
This code solves a small subset of the problems that a modern compiler must solve when it is compiling code that is spread across multiple files. The compiler can compile only a single file at a time. Since some files may depend on others (via #include statements, for example), we can use a topological sort of a DAG (directed acyclic graph) to compile the files that nothing else depends on first, then to compile files that depend only on those files and so on until all files are compiled. 

This is my code completed for ECE 250 Project 4.
