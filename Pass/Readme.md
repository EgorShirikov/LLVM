This is example of LLVM pass that collect statistics of IR instructions int runtime.

clang++ Pass_route.cpp -c -fPIC -I`llvm-config --includedir` -o Pass.o\  

clang++ Pass.o `llvm-config --cxxflags` `llvm-config --libs --ldflags` `llvm-config --system-libs` -fPIC -shared -o libPass.so  

clang++ -Xclang -load -Xclang ./libPass.so Conway-Game-Of-Life/life.cpp -O2 -c -o life.o  

clang++ life.o log.cpp Conway-Game-Of-Life/sim.cpp -lsfml-graphics -lsfml-system -lsfml-window -O2  

./a.out > input.txt  


