#!/bin/sh

#=============================== meta info ===================================#

show_help () {
cat << EndOfMessage
This script is used to prepare everything for the building of the buildroot
image. Note that it changes environment variables and the current path and
should preferably be used in a subshell

Usage: source setup-build.sh -b <buildroot-tree> -e <external-tree> -d <buildirectory> <defconfig>

Arguments:
    buildroot-tree : defaults to /buildroot
    external-tree : defaults to $BREXT
    buildirectory : defaults to /v/build/buildroot
    defconfig : Required - which defconfig to use

Example usage:
    > . setup-build.sh     # or source setup-build.sh
    > $BRMAKE
    Or
    > . setup-build.sh
    > make menuconfig
    > make savedefconfig
EndOfMessage
exit 1
}

#=========================== declare variables ===============================#

buildroot_tree=/buildroot
external_tree=$BREXT
build_directory=/v/build

#======================== parse optional arguments ===========================#

OPTIND=1 # Don't delete, is a POSIX variable
while getopts "h?b:e:d:" opt; do
    case "$opt" in
    h|\?)
        show_help
        ;;
    b)  buildroot_tree=$OPTARG
        ;;
    e)  external_tree=$OPTARG
        ;;
    d)  build_directory=$OPTARG
        ;;
    esac
done
shift $((OPTIND-1))
[ "${1:-}" = "--" ] && shift

#======================= parse positional arguments ==========================#

if [ "$#" -ne 1 ]; then echo "1 argument required" && show_help; fi
defconfig="$1"

#=========================== program logic ===================================#

BRMAKE="$buildroot_tree/utils/brmake"

external_tree=$(realpath $external_tree)

setup_buildroot () {
    # Setup variables
    local brargs="BR2_EXTERNAL=$external_tree O=$build_directory"
    local brlog="$buildroot_tree/br.log"

    # Make build directory if it does not yet exist
    mkdir -p "$build_directory"

    # Setup buildroot
    make $brargs $defconfig
}

cd "$buildroot_tree"
setup_buildroot
cd "$build_directory"
