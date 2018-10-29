##cat playbackExample.cpp | perl test.pl

while(<>){
	$_=~s/ ?= ?/=/g;
	$_=~s/ ?< ?/</g;
	$_=~s/ ?> ?/>/g;
	$_=~s/ ?, ?/,/g;
	$_=~s/ ?; ?/;/g;
	$_=~s/ ?{ ?/{/g;
	$_=~s/if /if/g;
	$_=~s/include</include </g;
	print $_;
}
