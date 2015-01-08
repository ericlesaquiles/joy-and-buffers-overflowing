apt-get --assume-yes install vim gcc gdb
# Disable ASLR
echo 0 > /proc/sys/kernel/randomize_va_space
