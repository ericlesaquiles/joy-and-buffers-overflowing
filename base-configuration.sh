apt-get --assume-yes install vim gcc gdb libc6-dev-i386
# Disable ASLR
echo 0 > /proc/sys/kernel/randomize_va_space
