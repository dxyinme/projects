<h1>DXYINME - c++ projects</h1>


build in [blade build](https://github.com/chen3feng/blade-build).

[install_blade](https://github.com/chen3feng/blade-build/blob/master/doc/zh_CN/install.md)

blade dependency:
 [ninja](https://github.com/ninja-build/ninja/releases/tag/v1.10.2)

## env

    g++ 6.3.0
    c++ 11

## lib or project introduction template

[template](template.md)


## lib and project

- util
    - [flags](/util/flags/README.md)
    - [progress_show](/util/progress_show/README.md)
    - [md5](/util/md5/README.md)
    - [string_utils](util/string_utils/README.md)


## required

- boost 1.62.0
    - [boost FAQ](#boost_FAQ)





## boost_FAQ

### Unix

[download](https://www.boost.org/users/history/version_1_62_0.html)

```bash
tar -xzvf file.tar.gz
cd boost_1_62_0
bash bootstrap.sh
./b2
cd stage/lib
sudo cp * /usr/lib
cd ../..
sudo cp -r boost/ /usr/include/
```