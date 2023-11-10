dir_to_install=${1:-/tmp/guessr}
autoreconf -fisv
./configure --prefix $dir_to_install
make -C $dir_to_install/po update-po
make all install
