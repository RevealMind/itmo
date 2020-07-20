use strict;
use warnings; 


my $isFindFirstNotEmpty = 0;
my $counterOfEmptyString = 0;

while(<>) {
   # first for the  first non-empty line
    if ($isFindFirstNotEmpty == 0) {
        if (!/^\s*$/) {
            $isFindFirstNotEmpty = 1;
        }
    } 
    if ($isFindFirstNotEmpty == 1) {
        #handler of empty line
        if (/^\s*$/) {
            $counterOfEmptyString++;
        } else {
            if ($counterOfEmptyString > 0) {
                print "\n"; 
            }
            s/(^\s+)|(\s+$)//g;
            s/\s+/ /g;
            print $_ . "\n";
            $counterOfEmptyString = 0;
        }
    }
}