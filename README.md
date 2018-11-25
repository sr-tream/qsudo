# qsudo
GUI for sudo<br/>
![qsudo -E gparted // hide password](https://dl.prime-hack.net/161031543108073.png)
![qsudo -E gparted // show password](https://dl.prime-hack.net/161501543108084.png)

## Feature

* You can use sudo options

  

## Build

#### Dependencies

* git
* qmake-qt5
* qt5-base

###### Debian, Ubuntu, Mint

```bash
apt update
apt install -y git qt5-default make g++
```

###### Arch, Antergos, Manjaro

```bash
pacman -Syu
pacman -S --noconfirm git make qt5-tools qt5-base gcc
```

#### Building

```bash
git clone https://github.com/sr-tream/qsudo.git
mkdir qsudo-build
cd qsudo-build
qmake ../qsudo
make -j$(nproc --all)
```

##### Possible problems with building

###### On Ubuntu

qmake-qt5 may not exist in PATH ([issue](https://github.com/sr-tream/qsudo/issues/3)), then instead of the command `qmake` use `/usr/lib/qt5/bin/qmake`



## Usage

`./qsudo [options] program`

#### Example
`./qsudo -E gparted`
