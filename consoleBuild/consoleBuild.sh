#sh

mkdir build
cd ..

# builds all project which have CMakeLists.txt 
for dir in */; do
    if [ -f "$dir/CMakeLists.txt" ]; then
        mkdir ./consoleBuild/build/$dir
        cd ./consoleBuild/build/$dir
        cmake ../../../$dir
        make
        cd ../../../
    fi
done

cd ./consoleBuild/build

# runs executables and reports the result
for dir in */; do
    cd $dir 
    ./"${dir%/}"
    if [ $? -eq 0 ]; then
        echo "${dir%/} works"
    else
        echo "${dir%/} doesnt work"
    fi
    cd ..
done

# deletes generated files
rm -rf ../build