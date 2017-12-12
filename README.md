# Connect4_nao

# Requires 

connect4_rule
connect4_cv
libnaoqi
opencv
with the aruco
c++11
qibuild 

only sucessfuly compiled on a arch linux-lts  kernel equal to 4.9.67-1
# build 

# Nao and Qibuild
Because of some reason nao api need to be compiled and link with qibuild.

you need to have connect4_nao on the same directory than connect4_rule and connect_cv.

You need to follow this site to configure and get qibuild ready to use:
http://doc.aldebaran.com/2-1/dev/cpp/install_guide.html

```bash
qibuild configure -c toolchain
qibuild make -c toolchain
```



# Run
```
# with naoqi sometime bug
qibuild run -c toolchain c4nao
# or linux way over dirrect call 
./build-toolchain/sdk/bin/c4nao

```
