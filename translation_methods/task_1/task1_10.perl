use strict;
use warnings; 

while(<>) {
    print if /\b(\S+)(\g1)\b/;
}