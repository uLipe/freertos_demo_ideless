/********************************************************/
   Hi, my name is Felipe Neves, thank you to review
   my solution of homework1

/********************************************************/

Since I not have (and pretend to not have) a original copy
of Microsoft windows, I was unable to build the demo Provided
by the professor, so I was to run the demo using a ordinary
microcontroller board, more specifically a NXP K64 freedom boards
(only was because thats is the easiest on hand).

I was built a complete project with custom printf support, and
a simple build system in order you can build (and use it) without
a IDE (yes Im providing the toolchain too.)

The solution of this homework itself you will encounter in:

Hw_Nxp/main.c

And the results are discussed in the report attached plus
a screenshot in root directory:

screenshot
report

See the number of executions of task1 and task, task1 execute
5 times task 2 for a hyperperiod (251/51)

You can evaluate and judge by the code, but if you have a freedom or
other microcontroller board you can use the build instructions:

1 - Enter in Hw_Nxp/ directory
2 - Check if makefile is present;
3 - open a terminal
4 - type: $make all (you need gnu make installed in your machine)
5 - Its will output a .elf file that you can use with jlink to Debug

If you encounter some trouble, feel free to contact me at:
ryukokki.felipe@gmail.com

Oh, yes, you are free to use for your purpose.

Felipe.
