Skill Level: Beginner

##Value
When learning about [fuzzing](https://en.wikipedia.org/wiki/Fuzz_testing) and security, it’s not enough to understand how to point and click with metasploit, which is what most tutorials out there cover. The goal of these exercises is to introduce players to the art of buffer overflow attacks. No meterpreter or metasploit. *Just the basics.* Players will walk away understanding memory addressing and how it is exploited with simple overflow techniques. The hope is that they will be able to follow conversations about “EIP Integrity” and take these basics to other languages and implementations.

There are two buffer overflow exercises in this repo. The first exercise only uses authentication.c. The second uses the notetaker.c and notesearch.c code. I recommend following the exercises in that order.

##Requirements
* Latest vagrant and virtualbox installation

##Authentiflow: Basic Buffer Overflow
1. Run `vagrant up` and after provisioning, run `vagrant ssh` to enter the virtual machine.
2. Ensure that the base configure script worked.

    * `which gcc` and `which gdb` should locate each application properly. If not, please apt-get install both.

    * `cat /proc/sys/kernel/randomize_va_space` should return 0. If not, please modify this value to be 0. This will disable [ASLR](https://en.wikipedia.org/wiki/Address_space_layout_randomization) in your virtual machine.

3. Compile authentication.c without canaries with the command:
> `gcc -g -o authentication authentication.c -fno-stack-protector`

    * -g will add debugging hooks to the compiled program

    * -o specifies the output program name as authentication

    * -fno-stack-protector disables the creation of [stack canaries](https://en.wikipedia.org/wiki/Stack_buffer_overflow#Stack_canaries)

4. Run the program compiled in step 3 with some test values and then try to force “Access Granted” to be printed on your screen using a buffer overflow.
5. Change the code in the program to be resistant to the overflow attack.
6. Recompile your resistant code without canaries and ensure buffer overflows don’t work: 
> `gcc -g -o authentication authentication.c -fno-stack-protector`
7. Watch [this video]() on understanding function stack frames and basic gdb address examination.
8. Identify the memory address location of the “print Access Granted” functionality using gdb.
9. Use this address location to force your authentication program to print Access Granted.

    * Hint: “this_program” is a command line program that enjoys eating 0xdeadbeef.

   > `$ echo -e “\xef\xbe\xad\xde” | ./this_program`

##Effectiflow: Effective user ids (euid), Environment Variables, and NOP Sleds
1. Follow the first two steps in the Basic Buffer Overflow exercise above.

What did you learn?

How would you code differently to prevent buffer overflow attacks, given no canaries or ASLR?

##So you think you’ve got it?
###Intermediate
Use the notetaker file to write a new root user to /etc/passwd.
These exercises were inspired by exercises from the book Hacking the Art of Exploitation by Jon Erickson. I highly recommend buying and reading it.

###Advanced
Frolic in [narnia](https://overthewire.org/wargames/narnia).
