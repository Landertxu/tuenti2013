#!/usr/bin/env perl

use v5.14;
use warnings;

my $file = shift // 'image.pbm';

my @zbar = `zbarimg $file 2>/dev/null`;
die $? if $?;

foreach (@zbar) {
    print if s/\AQR-Code://;
}