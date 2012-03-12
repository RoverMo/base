#!/bin/sh

ROOTFSDIR=/maxwit/rootfs
SRC_DIR=/work/source
CUR_DIR=`pwd`

show_menu()
{
	local i=1
	local count=1
	local choice

	echo ${1}
	echo
	shift

	count="$#"

	echo "	$i. make directory"
	((i++))

	echo "	$i. copy lib"
	((i++))

	echo "	$i. build sysvinit"
	((i++))

	echo "	$i. build bash"
	((i++))

	echo "	$i. build coreutils"
	((i++))

	echo "	$i. build util-linux-ng"
	((i++))

	echo "	x). Exit"
	echo 

	echo -n "Your choice[1-6]? "
	read choice
	
	if [ $choice = 1 ]
	then
		echo "build directory tree"
		cd ${ROOTFSDIR}
		mkdir dev etc sys proc root lib sbin var usr tmp mnt bin lib64
		cd ${CUR_DIR}
		((count++))

	elif [ $choice = 2 ]
	then
		echo "copying lib"
		cp -av /lib/*.so* ${ROOTFSDIR}/lib
		cp -av /lib64/*.so* ${ROOTFSDIR}/lib64
		((count++))

	elif [ $choice = 3 ]
	then
		tar xvf ${SRC_DIR}/sysvinit-2.86.tar.gz
		cp -v ${SRC_DIR}/sysvinit-2.86-fixes-1.patch .
		cd sysvinit-2.86
		patch -p1 < ../sysvinit-2.86-fixes-1.patch
		cd src
		make -j4
		echo "compiled"
		sudo make ROOT=${ROOTFSDIR} install
		echo "installed"
		((count++))

	elif [ $choice = 4 ]
	then
		tar xvf ${SRC_DIR}/bash-4.1.tar.gz
		cd bash-4.1
		./configure --prefix=/
		make -j4
		sudo make DESTDIR=${ROOTFSDIR} install
		ln -sv /bin/bash ${ROOTFSDIR}/bin/sh
		((count++))

	elif [ $choice = 5 ]
	then
		tar xvf ${SRC_DIR}/coreutils-8.8.tar.gz
		cd coreutils-8.8
		./configure --prefix=/
		make -j4
		sudo make DESTDIR=${ROOTFSDIR} install
		((count++))

	elif [ $choice = 6 ]
	then
		tar xvf ${SRC_DIR}/util-linux-ng-2.18.tar.bz2
		cd util-linux-ng-2.18
		./configure --prefix=/ --enable-login-utils --without-pam
		make -j4
		sudo make DESTDIR=${ROOTFSDIR} install
		((count++))

	else [ "${choice}" = "x" -o "${choice}" = "X"  -o "${choice}" = "q" -o "${choice}" = "Q" ]
		echo "Exit"
		return 0
	fi

	return 1
}

show_menu
while [ $? = 1 ]
do
	show_menu
done
