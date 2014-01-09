dmoz
====

dmoz classifier

Steps to build a new version:

* cd into dmoz-0.1
* make
* cd ../
* edit the file "pkg-debian/DEBIAN/control" and change the version number
* Copy the dmozClassify and dmozClassifyServer binaries to `pkg-debian/usr/bin`
* Copy the Top.Bow and Top.BowPart binaries to `pkg-debian/usr/lib`
* `dpkg -b pkg-debian/ dmoz_VERSION-1_amd64.deb`
* Test it on a clean server you don't mind potentially destroying
