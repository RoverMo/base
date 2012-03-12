#!/bin/bash

CUR_PATH=`pwd`
ROOTFS_PATH=${CUR_PATH}/rootfs
SOURCE_PATH=${CUR_PATH}/source
CONFIG_PATH=${CUR_PATH}/config

KERNEL_VERSION=2.6.35
BUSYBOX_VERSION=1.19.4

export ROOTFS_PATH

install_grub()
{
	[[ -e ${ROOTFS_PATH}/boot/grub/grub.cfg ]] && echo "Grub had been installed, skip!"  && return
	echo "If you want to add a new partition at /dev/sdb, press <n> and <w>"
	echo -n "Are you sure erase /dev/sdb and add a new partition [y/n]"
	read chioce
	if [ "y" != ${chioce} ]; then
		return
	fi
	
	fdisk /dev/sdb
	mkfs.ext4 /dev/sdb1
	mkdir -p ${ROOTFS_PATH}
	mount /dev/sdb1 ${ROOTFS_PATH}
	grub-install --root-directory=${ROOTFS_PATH} /dev/sdb
	cp ${CONFIG_PATH}/grub.cfg ${ROOTFS_PATH}/boot/grub/
}

build_kernel()
{
	[[ -e ${ROOTFS_PATH}/boot/vmlinuz-${main_ver} ]] && echo "Linux kernel had beeb builded, ship!" && return
	tar xvf ${SOURCE_PATH}/linux-${KERNEL_VERSION}.tar.*
	cp ${CONFIG_PATH}/vbox_defconfig ${CUR_PATH}/linux-${KERNEL_VERSION}/arch/x86/configs
	make -C ${CUR_PATH}/linux-${KERNEL_VERSION} vbox_defconfig
	make -C ${CUR_PATH}/linux-${KERNEL_VERSION} -j2 bzImage
	cp ${CUR_PATH}/linux-${KERNEL_VERSION}/arch/x86/boot/bzImage ${ROOTFS_PATH}/boot/vmlinuz-${main_ver}
}

copy_libc()
{
	[[ -e ${ROOTFS_PATH}/lib ]] && echo "Libc had been installed, skip!"
	mkdir -p ${ROOTFS_PATH}/lib64 ${ROOTFS_PATH}/lib
	cp -av /lib/*.so* ${ROOTFS_PATH}/lib
	cp -av /lib64/*.so* ${ROOTFS_PATH}/lib64
}

build_app()
{
	[[ -e ${ROOTFS_PATH}/bin/busybox ]] && echo "App had been build, ship!"
	tar xvf ${SOURCE_PATH}/busybox-${BUSYBOX_VERSION}.tar.bz2
	cp ${CONFIG_PATH}/bb_vbox_defconfig ${CUR_PATH}/busybox-${BUSYBOX_VERSION}/.config
	make -C ${CUR_PATH}/busybox-${BUSYBOX_VERSION} -j4
	make -C ${CUR_PATH}/busybox-${BUSYBOX_VERSION} install
	cd ${ROOTFS_PATH}
	mkdir -pv dev etc sys proc root var tmp mnt
	mkdir -pv etc/init.d etc/init usr/include
	mkdir -pv usr/share/man/man${1,2,3,4,5,6,7,8}
	cd ${CUR_PATH}
	cp -r ${CONFIG_PATH}/etc/* ${ROOTFS_PATH}/etc
}

show_menu()
{
	local i=1
	local choice

	echo "   ${i}. Install grub"
	((i++))

	echo "   ${i}. Build linux kernel"
	((i++))

	echo "   ${i}. Copy libc"
	((i++))

	echo "   ${i}. Build applications"

	echo "   x. Exit"

	echo -n "Your choice[1-${i}]: "
	read choice

	case ${choice} in
	1)
		install_grub
		;;
	2)
		build_kernel
		;;
	3)
		copy_libc
		;;
	4)
		build_app
		;;
	x | X | q | Q)
		echo "Exit"
		return 0;
		;;
	*)
		echo "Wrong choice! Please try agian."
		;;
	esac

	return 1;
}

show_menu
while [ 1 = $? ]
do
	show_menu
done
