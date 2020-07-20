use strict;
use warnings; 

while(<>) {
    print if /\([^\(\)](\s*\w+)+[^\(\)]\)/;
}