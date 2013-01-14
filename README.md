Sqlite Extensions
=================

Sqlite is an amazing piece of kit, it does however lack a lot of functionality, luckily it allows [dynamic loading of custom extensions](http://www.sqlite.org/cvstrac/wiki?p=LoadableExtensions). 

Sqlite provide a [math extension](http://www.sqlite.org/contrib/download/extension-functions.c?get=25) which does a lot. What I found lacking were string based extensions, most notably concatenate. While sqlite provides a method to do so it is not portable, seemingly all database vendors have their own implementation of concatenate. 

These extensions will hopefully be of use to somebody else as they have been to me.

Usage
=====

The [Sqlite extensions](http://www.sqlite.org/cvstrac/wiki?p=LoadableExtensions) provides a more in depth guide of how to use dynamically loaded extensions but here is a brief guide:

	$ sqlite3
	sqlite> select load_extension('digest.so');
	sqlite> select sha1('password');
	5baa61e4c9b93f3f0682250b6cf8331b7ee68fd8

	$ sqlite3
	sqlite> .load 'digest.so';
	sqlite> select sha1('password');
	5baa61e4c9b93f3f0682250b6cf8331b7ee68fd8

I have had little success with the .load command but the documentation suggests that it should work.

The sqlite3 binary bundled with OS X (I currently know for sure on 10.6.x -> 10.8.2) is not compiled with --enable-load-extension. Which means you cannot load extensions at all, to get around this either compile sqlite with --enable-load-extension added to configure or use the brew (possibly ports) sqlite.

	brew install sqlite3

Compilation
===========

To compile run the following:

	gcc -bundle -fPIC -Isqlite3 -o digest.so digest.c

Then load the extensions as described above.

Notes
=====

I have only compiled these on OS X, I have attempted to take into account other systems but I have not tested them.

I am a complete C n00b, the extensions compile but they could almost definitely be improved.