#
# spec file for package Parabola Biblioteca (Version 0.999)
#
# Copyright (c) 2009 Jonas M. Gastal.
# This file and all modifications and additions to the pristine
# package are under the same license as the package itself.
#
# Please submit bug fixes or comments via https://sourceforge.net/apps/trac/plivros/
#

BuildRequires: DataBaseWrapper-devel RatingWidgetPlugin-devel HoverPushButton-devel qt-devel gcc-c++ cmake
Requires: DataBaseWrapper-devel RatingWidgetPlugin-devel HoverPushButton-devel qt

Summary: Program to manage book collections.
Name: plivros
Version: 0.999
Release: 1
License: LGPL
Group: Productivity/Other
Source: plivros-0.999.tgz
BuildRoot: /var/tmp/%{name}-buildroot

%description
Parabola Biblioteca is the ideal program for bibliophiles to manage their collection.

%prep
%setup -q

%build
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="$RPM_BUILD_ROOT/%_prefix/" -DLIB_DIR="$RPM_BUILD_ROOT/%_libdir/" -DDEBUG=OFF ..
make
make ts
make imgs

%install
cd build
make install
cd ..
cp sql/User.db "$RPM_BUILD_ROOT/%_prefix/share/plivros/User.db"
mkdir -p "$RPM_BUILD_ROOT/%_prefix/share/applications/"
mv pkg/plivros-Fedora_11.desktop "$RPM_BUILD_ROOT/%_prefix/share/applications/plivros.desktop"

%post
for user_home in /home/*
do
	user=${user_home#/home/}
	user=${user%/}
	mkdir -m 755 -p /home/$user/.plivros/
	chown $user:$user /home/$user/.plivros/
	install -o $user -g $user -m 644 %_prefix/share/plivros/User.db /home/$user/.plivros/$user.db
done
rm %_prefix/share/plivros/User.db

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%dir %_prefix/share/plivros

%_prefix/bin/plivros
%_libdir/libdata.so
%_libdir/libgui.so
%_libdir/libcollection.so
%_prefix/share/applications/plivros.desktop
%_prefix/share/plivros/imgs.bqrc
%_prefix/share/plivros/plivros_pt_BR.qm
%_prefix/share/plivros/User.db

%changelog
* Wed Jul 25 2009 Jonas M. Gastal <jgastal@gmail.com> 
- First RPM package.
