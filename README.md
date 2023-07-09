# Linux-Shell
Linux Shell implemented in C
# Description of the system: 
The system is a command-line interface for executing various commands provided by the user. It shows the output of the result on the terminal itself. It is essentially a shell program for linux based systems. This shell executes various
other programs according to the input provided by the user to the shell program. The various commands that shell can handle are as below: 
# Internal commands - 
* cd 

options available: 
a. -L: symlinks are not resolved 
b. ~: changes the directory to home directory 

errors handled: 
a. no such directory found 
b. format not valid 
c. invalid option 
d. no option/path provided 

* pwd 

optons: 
a. -L 
b. -P 

errors handled: 
a. invalid option 
b. invalid format 

* echo 

assumptions: 
it is required to pass an option with the command 

options available: 
a. -n: Doesn't output the trailing new line. 
b. -E: Doesn't interprets the backslash escapes 

errors handled: 
a. invalid format 
b. invalid option 

# External command: 
* ls 

assumption: 
it is required to pass an option with the command 

options available: 
a. -a,--all: Doesn't ignore the files starting with '.' 
b. -i,--inode: prints the files with their index number 

errors handled: 
a. option not valid 
b. option not provided as input in command 

* cat 

assumption: 
it is required to pass an option with the command 

options available: 
a. -n: numbers all output lines 
b. -b: ignores blank lines while numbering the lines 

errors handled: 
a. invalid option 
b. path provided doesn't point to a regular file 
c. option not provided 
d. path not provided 

* date 

assumptions: 
it is required to pass an option with the command 
options available 
a. -u,--universal,--utc: prints the Universal time(UTC) 
b. -r: prints the last modified time of any file/directory specified 

errors handled: 
a. invalid option provided 
b. if input doesn't math the required format, "invalid format" is printed 
* rm 

assumption: 
it is required to pass an option with the command 

options available: 
a. -i: asks for confirmation before every removal of a file 
b. -v: displays what is being done 

errors handled: 
a. Path provided doesn't point to a regular file for its deletion 
b. invalid option provided for confirmation regarding deletion of the file under the option '-i' 
c. invalid option 
d. option not provided 
e. path not provided 
* mkdir 

assumption: 
it is required to pass an option with the command 

options available: 
a. -v: displays what is being done 
b. -p,--parent: makes parent directories if not already existing 

errors handled: 
a. Directory already exists 
b. Not a valid path for a directory. For example a path that requires parent directories to be created first but the option chosen as input is not "-p" or "--parent" 
c. invalid option 
d. option not provided in the input 
e. path not provided in the input 

The shell itself runs by two seperate implementations: 
1. using system calls: fork(),execl() and wait() in order to handle external commands 
2. using API function calls: system() and POSIX Pthread family of functions i.e., pthread create() in order to handle 
external commands 
In order to run through the second type of implementation, the user is required to provide "&t" at the end of each comm
and, for example,"date -u" would be executed using the first type of implementation while "date&t -u" would be executed u
sing the second type of implementation. 

Assumption "test" folder should be present in the working directory in order to run the test case successfully. 

# TEST CASE: 
ls -a 
ls&t -i 
cat&t -b ./test/testfile 
cat -n ./test/testfile 
date -u 
date&t -r ./test 
rm -i ./test/testfile 
rm&t -v ./test/testfile 
mkdir -v ./fold1 
mkdir&t -p ./fold2/fold1 
cd ~ 
pwd -P 
cd -L .. 
pwd -L 
echo -n hello there 
echo -E hi there
