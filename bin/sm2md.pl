#!/usr/bin/env perl
use warnings;
use strict;

opendir(D, "/var/www/htdocs/git/wwwsrc") || die "Can't open directory: $!\n";
while (my $f = readdir(D)) {

	next if $f !~ /.*\.sm/;

	my $input = "/var/www/htdocs/git/wwwsrc/$f";
	open my $fh, '<', "$input" or die "Can't read file: $!\n";
	my $file_content = do { local $/; <$fh> };
	$file_content =~ s/\[\[(.*)\]\]/\[$1\](\L$1)/g;
	close $fh;

	$f =~ s/sm$/md/;
	my $output = "/var/www/htdocs/md/$f";
	open(FH, '>', $output) or die "Can't write file: $!\n";
	print FH $file_content;
	close(FH);
}
closedir(D);
