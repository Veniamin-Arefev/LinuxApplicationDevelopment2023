dir_to_install=${1:-/tmp/guessr}
mkdir $dir_to_install
autoreconf -fisv
./configure --prefix $dir_to_install
make -C ./po update-po
make all install
