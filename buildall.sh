cd gnu-efi
make all
make bootloader
cd ..
cd kernel
make kernel
make buildimg
