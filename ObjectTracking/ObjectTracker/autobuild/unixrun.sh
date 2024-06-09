CURRENT_DIR=$(basename $(pwd))
echo $CURRENT_DIR

if [$CURRENT_DIR == "autobuild"]; then
    cd ..
fi

echo "Running"
./build/Driver/Driver