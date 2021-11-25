-------------------------------------------------------------------------
Data File Maintenance
-------------------------------------------------------------------------

Each time you execute your program, the original accounts.txt and 
tickets.txt data files will be modified.

It is important you reset these files to their original state before each 
execution.

-------------------------------------------------------------------------
NOTE: DO NOT delete the files "accountsMaster.txt" or "ticketsMaster.txt"
-------------------------------------------------------------------------

To help you automate this, the master files are included along with a
script file to make resetting easier.  There are two variations of the
script file depending on which platform you are using.

-------------------------------------------------------------------------
Windows: "WinReset.bat"
-------------------------------------------------------------------------

On the Windows platform, all you have to do is double click the
"WinReset.bat" file from the file explorer and it will reset the 
accounts.txt and tickets.txt files.

-------------------------------------------------------------------------
Linux or Mac: "LinMacReset.sh"
-------------------------------------------------------------------------

On the Linux or Mac platforms, you will need to open a terminal window 
and "cd" to the directory you have placed your project files.

The first time you download the project files, you will need to modify 
the permissions of the script file:

chmod 500 LinMacReset.sh

After this is done, all you have to do is type "./LinMacReset.sh" and 
it will reset the accounts.txt and tickets.txt files.

