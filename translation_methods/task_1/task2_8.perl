use strict;
use warnings; 

while(<>) {
    s/0\b//g;
    print;
}