use strict;
use warnings; 

#use hash to avoid duplicate links ([link] => some)
my %links; 
my $hrefHandler = '\s*a.+?\bhref\s*';

while (<>) {
    #                        $1   $2    
    while (m{$hrefHandler=\s*('|")(.*?)\1.*?>}g) {
        my $rawLink = $2;
        #remove scheme and garbage (a.e query/port/fragment)
        $rawLink =~ s/((^.*?:\/\/)|([\/\\?#:].*$))//g;
        #check after remove and add in hash
        if ($rawLink !~ /(^\s*$)|(^\.)|(\.$)|(\.{2,})/) {
            $links{$rawLink} = 1; 
        }
    }
}

#sort and print link
foreach my $link (sort(keys %links)) {
    print $link . "\n";
}