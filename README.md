Skill Level: Beginner

This workshop assumes no previous knowledge of C and the process of code execution.

##Value
When learning about [fuzzing](https://en.wikipedia.org/wiki/Fuzz_testing) and security, it’s not enough to understand how to point and click with metasploit, which is what most tutorials out there cover. The goal of these exercises is to introduce players to the art of buffer overflow attacks. No meterpreter or metasploit. *Just the basics.* Players will walk away understanding memory addressing and how it is exploited with simple overflow techniques. Once you complete this workshop, you will be able to understand conversations about “EIP Integrity” and take these basics to other languages and implementations.

##Requirements
* Latest vagrant and virtualbox installation

##Nice to haves
* Some C programming (If you are unfamiliar with C, don’t worry! The code example is very simple.)

##Authoriflow: Basic Buffer Overflow
1. Clone this repo, navigate inside, and run `vagrant up` and after provisioning. Next run `vagrant ssh` to enter the virtual machine.

2. Ensure that the base configure script worked.

    * `which gcc` and `which gdb` should locate each application properly. If not, please apt-get install both.

3. Compile authorization1.c without canaries with the command:
    ```
    $ gcc -g -o authorization1 authorization1.c -fno-stack-protector -m32
    ```

    * -g will add debugging hooks to the compiled program so that gdb can easily read it later

    * -o specifies the output program name as authorization1

    * -fno-stack-protector disables the creation of [stack canaries](https://en.wikipedia.org/wiki/Stack_buffer_overflow#Stack_canaries)

    * -m32 tells gcc to compile the code into a 32bit program which will make this tutorial easier

4. Run the program compiled in step 3 with some test values
    ```
    $ ./authorization1 testPassword
    ```

    Then try to force “Access Granted” to be printed on your screen using a buffer overflow.

5. That was simple. Now let’s get a little more complicated. Compile authorization2.c without canaries with the command:
    ```
    $ gcc -g -o authorization2 authorization2.c -fno-stack-protector -m32
    ```

    How is the authorization2 code different from authorization1?
    Can the method you used in step 4 be used with authorization2 to force “Access Granted” to be printed? If not, why?

6. Authorization2 is still vulnerable, and we can force the program to print “Access Granted” through different means. In order to do this, you will need to identify the memory address of the “print Access Granted” function and the memory address of the assembly instruction after call_authorization. Use [this video](http://youtu.be/WvdBr-Z1w-o) as a reference. Keep these addresses for step 8.

    Note: This is how you start the authorization2 program with gdb in order to get to the prompt in the video above:
    ```
    $ gdb -q authorization2
    ```

    * -q will start gdb quietly, meaning it won’t print out all the details about the version of gdb you’re using.

7. Next, you will need to understand how memory segmentation and stack frames work.
    1. Watch [this video](http://youtu.be/R2gqR-ToHDc) on memory segmentation. In step 6 above, you used gdb to look through the “Text” section which contains the code instructions for the program.
    2. Before watching [this video](http://youtu.be/A3cIpGgS0Kw) on stack frames, you will need to know these acronyms:

    * EIP - The instruction pointer. It will run whatever instruction it points to. Gaining control of the EIP pointer is crucial to exploiting code through memory corruption because then you can force execution of code that you control.
    * EBP - The base pointer of the current stack frame. This points at the bottom of the current function frame. This pointer and the ESP pointer make a sandwitch to contain the variable context of the function that is currently being executed by the EIP pointer.
    * ESP - The stack pointer. This points to the top of the current function frame. When a program starts executing a function, this pointer location is established after the system decides how much variable memory is needed for the execution of the function.
    * SFP - The save frame pointer. This pointer exists within a stack frame, and it points to the location of the old EBP. It will replace the current EBP when the function finishes.

    Pay particular attention to the different segments of the stack frame and which ones will give you control of the EIP pointer.

8. With gdb, navigate into the check_authorization function and use the location of the ESP register to locate the address of the next assembly instruction that EIP will use after check_authorization finishes. This is what you want to overwrite with the address to the “print Access Granted” function. You can use [this video](http://youtu.be/z3c-OmczCqc) as a reference to help you set breakpoints with gdb and analyze the variables within the check_authorization function.

Note: the code in the video is not the exact same code as in authorization2.c but the techniques for analyzing it will be the same.

    GDB Cheatsheet
    ----
    ```
    To examine 1 hexadecimal (x) word (w) at the variable x

    gdb>x/1xw &x

    Results look like...
    [address of variable]: [one word of hexadecimale numbers]
    ```

    ```
    To examine the variable x as a string (s)

    gdb>x/s &x

    Results look like...
    [address of variable]: [string representation of variable]
    ```

    ```
    To examine 16 hexadecimal (x) bits (b) from the EIP register

    gdb>x/16xb $eip

    Results look like...
    [starting address at EIP]: [four words of hexadecimale numbers]
    [starting address of this line]: [four words of hexadecimale numbers]
    [starting address of this line]: [four words of hexadecimale numbers]
    [starting address of this line]: [four words of hexadecimale numbers]
    ```

9. Based on the knowledge you gained in the previous steps, use the address location that you discovered in step 8 to force your authorization program to print “Access Granted”. If you are having a hard time, don’t give up. It’s supposed to be difficult. When you get “Access Granted” to print this way, buy yourself a drink. :)

    * Hint: Pretend that the authorization2 program enjoys eating 0xdeadbeef. How would you feed it?

    ```
    $ ./authorization2 $(perl -e ‘print “\xef\xbe\xad\xde”’)
    ```

    (*cough* Little Endian. *cough*)

##Reflection
Interestingly, when the code execution system was created, it allowed a user to compromise the program with a buffer overflow. Unless you are aware of the unsafe ways to use functions like strcpy, you could be compromised with the same attack. Today, we have implemented systems like stack canaries to protect unsuspecting developers a little better.

How would you code differently to prevent buffer overflow attacks (given no canaries)?

These exercises were inspired by lessons from the book Hacking the Art of Exploitation by Jon Erickson, and they are only the beginning when it comes to understanding memory exploitation. If you thought this session was interesting, I highly recommend buying and reading the book.

Thanks for trying this workshop! I’m open to any and all feedback and suggestions. The hope is that this will help make understanding security easier for everyone by making the root causes of systematic vulnerabilities widely known. That way more people will contribute to making the software environment secure at their core into the future instead of adding complexity through layers of patches.
