##Requirements
* Latest vagrant and virtualbox installation

##Begin...
1. Run `vagrant up`
2. Ensure that the base configure script worked.

    * `which gcc` and `which gdb` should locate each application properly. If not, please apt-get install both.

    * `cat /proc/sys/kernel/randomize_va_space` should return 0. If not, please modify this value to be 0. This will disable [ASLR](https://en.wikipedia.org/wiki/Address_space_layout_randomization) in your virtual machine.

3. Compile auth_overflow.c without canaries with the command:
> `gcc -g -o auth_overflow auth_overflow.c -fno-stack-protector`

    * -g will add debugging hooks to the compiled program

    * -o specifies the output program name as auth_overflow

    * -fno-stack-protector disables the creation of [stack canaries](https://en.wikipedia.org/wiki/Stack_buffer_overflow#Stack_canaries)

4. User buffer overflows on the program compiled in step 3 to force “Access Granted” to be printed on your screen.
5. Change the code in the program to be resistant to the overflow attack.
6. Recompile your resistant code without canaries and ensure buffer overflows don’t work: 
> `gcc -g -o auth_overflow auth_overflow.c -fno-stack-protector`

7. Identify the memory address location of the “print Access Granted” functionality using gdb.
8. Use this address location to force your auth_overflow program to print Access Granted.

What did you learn?
How would you code differently to prevent buffer overflow attacks, given no canaries or ASLR?

##So you think you’ve got it?
Frolic in [narnia](https://overthewire.org/wargames/narnia).
