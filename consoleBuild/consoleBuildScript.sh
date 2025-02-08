#sh

mkdir build
root=$(dirname "$PWD")
cd $root

# builds all projects which have CMakeLists.txt 
for dir in */; do
    if [ -f "$dir/CMakeLists.txt" ]; then
        mkdir consoleBuild/build/$dir
        cd consoleBuild/build/$dir
        cmake "$root/$dir"
        make
        cd $root
    fi
done

cd consoleBuild/build
echo "result:"
# runs executables and reports test result
for dir in */; do
    cd $dir
    name=$(basename "$dir")
    ./"$name"
    if [ $? -eq 0 ]; then
        echo "$name works"
    else
        echo "$name doesnt work"
    fi
    cd ..
done

# deletes generated files
rm -rf ../build
