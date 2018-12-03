\"cat tblExample.ms | groff -t -ms -T pdf > tblexample.pdf
\"cat tblExample.ms | groff -t -ms -T utf8 | zathura

.TS
allbox;
lbw13 lbw12 lbw14 lbw18
l l l l.
Interface	Pool	T{
Blocking
\%behavior
T}	T{
Behavior when pool is not yet ready
T}
T{
.I /dev/random
T}	T{
Blocking pool
T}	T{
If entropy too low, blocks until there is enough entropy again
T}	T{
Blocks until enough entropy gathered
T}
T{
.I /dev/urandom
T}	T{
CSPRNG output
T}	T{
Never blocks
T}	T{
Returns output from uninitialized CSPRNG (may be low entropy and unsuitable for cryptography)
T}
T{
.BR getrandom ()
T}	T{
Same as
.I /dev/urandom
T}	T{
Does not block once is pool ready
T}	T{
Blocks until pool ready
T}
T{
.BR getrandom ()
.B GRND_RANDOM
T}	T{
Same as
.I /dev/random
T}	T{
If entropy too low, blocks until there is enough entropy again
T}	T{
Blocks until pool ready
T}
T{
.BR getrandom ()
.B GRND_NONBLOCK
T}	T{
Same as
.I /dev/urandom
T}	T{
Does not block once is pool ready
T}	T{
.B EAGAIN
T}
T{
.BR getrandom ()
.B GRND_RANDOM
+
.B GRND_NONBLOCK
T}	T{
Same as
.I /dev/random
T}	T{
.B EAGAIN
if not enough entropy available
T}	T{
.B EAGAIN
T}
.TE

