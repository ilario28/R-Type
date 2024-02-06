if [ -d "./build" ]
then
    cd build && cmake .. -G Ninja && ninja
else
    mkdir build && cd build && cmake .. -G Ninja && ninja
fi