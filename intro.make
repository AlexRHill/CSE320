

                                  INTRODUCTION
                              TO THE MAKE UTILITY

The utility program named "make" allows the selective compilation and linking
of the files which constitute a program.  It does this by comparing the time
stamp on source code and object code files:  a more recent time stamp on a
source code file indicates that a recompilation and relink of some of the
files is necessary.  All files which depend upon a modified file are also
recompiled and relinked.

The file dependencies and actions to be done are specified by a 'makefile'
(default name "Makefile").  A typical entry is of the form:

          target: list of target dependencies
          TAB  command1
          TAB  command2
              ......

where command1, command2, etc. are the command lines needed to produce the
target (most often they invoke the compiler).  The commands are invoked if any
item in the dependency list is newer than the target.  The TAB is just that,
not spaces!  Also, be certain that the last line of the 'makefile' ends with a
newline (by touching the return key).  Either the target or command lines may
be continued on the next line by a backslash (followed by a return).

Consider the following example.  A program named 'project' consists of:

  2  C++ source code files named "main.cpp" and "one.cpp".
  1  C++ interface file named "two.h" (used in "one.cpp").
  1  object code file named "/user/cse320/three.o".

Using "g++", a possible 'makefile' would be:

      project:   main.o one.o /user/cse320/three.o
      ^I         g++ -o project main.o one.o \
                     /user/cse320/three.o

      main.o:    main.cpp
      ^I         g++ -c main.cpp

      one.o:     one.cpp two.h
      ^I         g++ -c one.cpp

      # Comment lines.  Note that tabs ('^I') are explicitly indicated
      # in the example (in the editor you would touch the 'tab' key).
      # Note the use of "-o" and "-c" options for the compiler.

The "make" program may be invoked using:

       > make                 (if the 'makefile' is named "Makefile")
       > make -f filename     (if the 'makefile' has another name)

If the final target (in this case 'project') is not the first thing listed in
the makefile, then use the command:

       > make  'final-target-name' 

The "make" program supports a number of features (such as macros) which allow
the user to construct complex (and sometimes unreadable) makefiles.

