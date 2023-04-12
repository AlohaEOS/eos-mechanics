set -e

mkdir -p build
cd build
cmake ..
make -j

echo "WASM hash: $(sha256sum eosmechanics/eosmechanics.wasm)"

cd ..