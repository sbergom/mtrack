# Movie List Tracker

Has someone ever recommended to you a movie that you really need to
see and you say, "Sure, someday."  But then you forget about it until
years later and can't quite remember the name.  Yeah, that's happened
to me, too.  So when I was learning Qt I decided to do something about
it to practice my new knowledge, and this was it.

The Movie List Tracker is an application to keep track of movies that
I want to, at some point watch and make comments about.  It may be
used for other things; books, perhaps.  Or maybe flavors of ice cream.
Whatever!  If you find this application useful then use it all you
want, and good luck!

And, yes, I know it needs some work.

## Compiling

Compiling this requires CMake and is a simple process (no funky
command line options needed).

```
cmake
make
make install
```

## Using

On first use go to `File->New` to create a new file (pick a directory
and fill in the filename).  Then start typing in entries in the entry
field.  As list entries get added they will appear in the filter box
on the left side.  The text entry field above "New Entry" will filter
the entries, which is really helpful when your list gets really big.

You can re-open the file later with `File->Open`.

Happy listing!

