# This is obsolete and doesn't make any sense in this day and age. Keeping it here as a memoir.

I was young and naive but still managed to write a decent regexp compiler in "C with classes" ;)

---

RECOM - Regular Expression COMpiler v0.1
by Marcin Gasperowicz

RECOM is a tool that can create a compiled match function from a regular expression.

Why?
- For epic speed
- When classic tools fail on huge amounts of data

What it does currently:
- Implements only minimal subset of RE
- Produces .o file with compiled function that can be linked with C/C++ programs

What will it do:
- Recognize perl (or maybe 9re) regular expression language
- Generate functions for matching, pattern extraction and substitution
- Optimize RE and automata on every level of compilation
- Enable JIT compilation for direct use in various applications
- ...

Requirements:
- nasm (for static backend)
- asmjit (for jit backend, currently defunct)
- gcc
- dot (option, for viewing nice debug pics)  


Installation:

1. Download the source
2. Run

```
$ make CONF=Release
```

3. Enjoy:

```
$ ./dist/Release/<your-arch>/regej "regular expression" 
```

Will output assembler to the stdout. 
