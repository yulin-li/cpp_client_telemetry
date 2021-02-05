#!/usr/bin/env bash
ARCH="x86_64"
if [ "$1" == "arm64" ]; then
  ARCH="arm64"
fi

cd `dirname $0`
SQLITE_PATH=sqlite
pushd $SQLITE_PATH
set -evx
env | sort
rm -rf build
mkdir -p build || true
cd build
cmake -DCMAKE_CXX_FLAGS="-fPIC $CXX_FLAGS" \
      -DARCH=$ARCH \
      ..
make
make install
popd
