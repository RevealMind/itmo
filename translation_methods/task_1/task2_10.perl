use strict;
use warnings; 

while(<>) {
    s/(a.*?a){3}/bad/g;
    print;
}