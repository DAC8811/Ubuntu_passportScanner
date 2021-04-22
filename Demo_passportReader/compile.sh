#g++ test.cpp -o test -ldl  #动态加载动态库
g++ test_static.cpp libgetData.a -o test_static #加载静态库