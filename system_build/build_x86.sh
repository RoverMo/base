#!/bin/sh

ROOTFSDIR=/tmp/rootfs
SRC_DIR=/work/source
CUR_DIR=`pwd`

show_menu()
{
	local i=1
	local j=1
	local choice

	echo ${1}
	echo
	shift

	echo "	${i}. Configure build"
	((i++))

	echo "	${i}. make directory"
	((i++))

	echo "	${i}. copy lib"
	((i++))

	echo "	${i}. build sysvinit"
	((i++))

	echo "	${i}. build bash"
	((i++))

	echo "	${i}. build coreutils"
	((i++))

	echo "	${i}. build util-linux-ng"
	((i++))

	echo "	x). Exit"
	echo 

	((i--))
	echo -n "Your choice[1-$i]? "
	read choice
	
	case ${choice} in
	1)
		grep "${ROOTFSDIR}" /etc/exports || \
		{
			fexport="/tmp/exports"
			cp /etc/exports $fexport
			echo "${ROOTFSDIR} *(rw,sync,no_subtree_check,no_root_squash)" >> ${fexport}
			sudo cp $fexport /etc
			sudo service nfs-kernel-server restart
			echo
		}
		;;

	2)
		echo "build directory tree"
		mkdir -pv ${ROOTFSDIR}
		cd ${ROOTFSDIR}
		mkdir -pv dev etc sys proc root lib sbin var usr tmp mnt bin lib64
		mkdir -pv etc/init.d etc/init usr/bin usr/include
		for j in 1 2 3 4 5 6 7 8
		do
			mkdir -pv usr/share/man/man${j}
		done

		cd ${CUR_DIR}
		;;

	3)
		echo "copying lib"
		cp -av /lib/*.so* ${ROOTFSDIR}/lib
		cp -av /lib64/*.so* ${ROOTFSDIR}/lib64
		;;

	4)
		tar xvf ${SRC_DIR}/sysvinit-2.86.tar.gz
		cp -v ${SRC_DIR}/sysvinit-2.86-fixes-1.patch .
		cd sysvinit-2.86
		patch -p1 < ../sysvinit-2.86-fixes-1.patch
		cd src
		make -j4
		sudo make ROOT=${ROOTFSDIR} install
		echo "#!/bin/sh" > ${ROOTFSDIR}/etc/init.d/rcS
		echo "mount -t proc proc /proc" >> ${ROOTFSDIR}/etc/init.d/rcS
		echo "mount -t sysfs none /sys" >> ${ROOTFSDIR}/etc/init.d/rcS
		echo "id0:5:initdefault:" > ${ROOTFSDIR}/etc/inittab
		echo "id1:5:sysinit:/etc/init.d/rcS" >> ${ROOTFSDIR}/etc/inittab
		echo "id2:5:respawn:/sbin/agetty 115200 tty1" >> ${ROOTFSDIR}/etc/inittab
		echo "id3:5:restart:/sbin/init" >> ${ROOTFSDIR}/etc/inittab
		echo "id3:5:shutdown:/bin/umount -a -r" >> ${ROOTFSDIR}/etc/inittab
		;;

	5)
		tar xvf ${SRC_DIR}/bash-4.1.tar.gz
		cd bash-4.1
		./configure --prefix=/
		make -j4
		sudo make DESTDIR=${ROOTFSDIR} install
		ln -sv /bin/bash ${ROOTFSDIR}/bin/sh
		;;

	6)
		tar xvf ${SRC_DIR}/coreutils-8.8.tar.gz
		cd coreutils-8.8
		./configure --prefix=/
		make -j4
		sudo make DESTDIR=${ROOTFSDIR} install
		;;

	7)
		tar xvf ${SRC_DIR}/util-linux-ng-2.18.tar.bz2
		cd util-linux-ng-2.18
		./configure --prefix=/ --enable-login-utils --without-pam
		make -j4
		sudo make DESTDIR=${ROOTFSDIR} install
		echo "root::0:0:/root:/bin/bash" > ${ROOTFSDIR}/etc/passwd
		;;

	x | X | q | Q)
		echo "Exit"
		return 0
		;;
	*)
		echo "Wrong choice! Please try again."
		;;
	esac

	return 1
}

show_menu
while [ $? = 1 ]
do
	show_menu
done
