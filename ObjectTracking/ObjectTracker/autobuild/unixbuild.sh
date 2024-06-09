CURRENT_DIR=$(basename $(pwd))
echo $CURRENT_DIR

if [$CURRENT_DIR == "autobuild"]; then
    cd ..
fi

if [ ! -d "./build" ]; then
  echo "Build directory does not exist. Creating it now..."
  mkdir "build"
fi

cd build
cmake ..
cmake --build .
