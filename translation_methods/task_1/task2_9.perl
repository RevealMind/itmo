use strict;
use warnings; 

while(<>) {
    s/\(.*?\)/()/g;
    print;
}