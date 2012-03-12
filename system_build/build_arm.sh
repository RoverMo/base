#!/bin/sh

ROOTFS_PATH=/tmp/rootfs_arm
SRC_PATH=/work/source
BUILD_PATH=/home/`whoami`/build
TOOLCHAIN_PATH=/home/`whoami`/maxwit/toolchain
TARGET_ARCH=arm
KERNEL_VER=2.6.36
BUSYBOX_VER=1.18.2
TARGET_MECH=mw61
COMPILE_OPT="ARCH=arm CROSS_COMPILE=arm-linux-"

check_pkg()
{
	if [ -ne ${SRC_PATH}/$1.tar.* ]
	then 
		echo "$1.tar.bz2, $1.tar.gz or $1.tar.xz do not exist in ${SRC_PATH}"
		return 1
	fi

	if [ -e ${BUILD_PATH}/$1 ]
	then
		echo "$1 already exist, skip"
		return 2
	else
		return 0
	fi
}

configure_build()
{
	grep "${ROOTFS_PATH}" /etc/exports || \
	{
		fexport="/tmp/exports"
		cp /etc/exports $fexport
		echo "${ROOTFS_PATH} *(rw,sync,no_subtree_check,no_root_squash)" >> ${fexport}
		sudo cp $fexport /etc
		sudo service nfs-kernel-server restart
		echo
	}
	mkdir -pv ${BUILD_PATH}
}

build_rootfs()
{
	mkdir -pv ${ROOTFS_PATH}
	cd ${ROOTFS_PATH}
	mkdir -pv dev etc sys proc root lib sbin var usr tmp mnt bin lib64 boot
	mkdir -pv etc/init.d etc/init usr/bin usr/include
	for j in 1 2 3 4 5 6 7 8
	do
		mkdir -pv usr/share/man/man${j}
	done

	echo "root::0:0:root:/root:/bin/bash" > ${ROOTFS_PATH}/etc/passwd

	cd ${BUILD_PATH}
}

build_kernel()
{
	cd ${BUILD_PATH}
	check_pkg linux-${KERNEL_VER}
	case $? in
	0)
		tar xf ${SRC_PATH}/linux-${KERNEL_VER}.tar.*
		;;
	1)
		exit
		;;
	esac

	cd linux-${KERNEL_VER}
	make ${COMPILE_OPT} ${TARGET_MECH}_defconfig
	make ${COMPILE_OPT} -j4
	cp -v arch/arm/boot/zImage ${ROOTFS_PATH}/boot/zImage_${TARGET_MECH}
	cd ${BUILD_PATH}
}

copy_lib()
{
	cp -av ${TOOLCHAIN_PATH}/lib/*.so* ${ROOTFS_PATH}/lib
	cp -av ${TOOLCHAIN_PATH}/usr/lib/* ${ROOTFS_PATH}/usr/lib
}

build_busybox()
{
	cd ${BUILD_PATH}
	check_pkg busybox-${BUSYBOX_VER}
	case $? in
	0)
		tar xf ${SRC_PATH}/busybox-${BUSYBOX_VER}.tar.*
		;;
	1)
		exit
		;;
	esac

	cd busybox-${BUSYBOX_VER}
	cp -v ${SRC_PATH}/busybox_defconfig .config
	sed -i "s/\.\/_install/\/${ROOTFS_PATH}" .config
	make ${COMPILE_OPT} && make ${COMPILE_OPT} install
	cd ${BUILD_PATH}
	echo "#!/bin/sh" > ${ROOTFS_PATH}/etc/init.d/rcS
	echo "mount -t proc  proc /proc" >> ${ROOTFS_PATH}/etc/init.d/rcS
	echo "mount -t sysfs none /sys" >> ${ROOTFS_PATH}/etc/init.d/rcS
	echo "mount -t tmpfs none /tmp" >> ${ROOTFS_PATH}/etc/init.d/rcS
	echo "mdev -s" >> ${ROOTFS_PATH}/etc/init.d/rcS
	echo "/sbin/getty 115200 /dev/ttyAMA0" >> ${ROOTFS_PATH}/etc/init.d/rcS
}

run_qemu()
{
	local mechine=realview-pb-a8
	local server_ip=10.0.0.1
	local bcast=${server_ip}
	local host_ip=10.0.0.22
	local mask=255.255.255.0

	sudo qemu-system-arm -M ${mechine} -kernel ${ROOTFS_PATH}/boot/zImage_${TARGET_MECH} \
	-serial stdio -net nic -net tap -append "root=/dev/nfs rw nfsroot=${server_ip}:${ROOTFS_PATH} \
	ip=${host_ip}:${server_ip}:${bcast}:${mask}::eth0:off console=ttyAMA0 mem=128M"
}

show_menu()
{
	local i=1
	local choice

	echo ${1}
	shift

	echo "	${i}. Configure build"
	((i++))

	echo "	${i}. make directory"
	((i++))

	echo "	${i}. build kernel"
	((i++))

	echo "	${i}. copy lib"
	((i++))

	echo "	${i}. build busybox"
	((i++))

	echo "	${i}. run_qemu"

	echo "	x. Exit"
	echo 

	((i--))
	echo -n "Your choice[1-$i]? "
	read choice
	
	case ${choice} in
	1)
		configure_build
		;;

	2)
		build_rootfs
		;;

	3)
		build_kernel
		;;

	4)
		copy_lib
		;;

	5)
		build_busybox
		;;
	6)
		run_qemu
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

cd ${BUILD_PATH}
show_menu
while [ $? = 1 ]
do
	show_menu
done
