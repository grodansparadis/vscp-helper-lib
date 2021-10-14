# Internal test files

Non of the files in this folder is of interest to end users.
Yes! that is true.

Use demands that libvscphelper is installed

http://www.adp-gmbh.ch/cpp/gcc/create_lib.html
http://tldp.org/HOWTO/Program-Library-HOWTO/shared-libraries.html

nm -Ca ../libvscphelper15.so  - list method sin lib

cc example1.c -o example1 -L.. -lvscphelper