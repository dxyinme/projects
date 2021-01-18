<h1>DXYINME - c++ projects</h1>


build in [blade build](https://github.com/chen3feng/blade-build).

## env

    g++ 6.3.0
    c++ 11

## lib or project introduction template

[template](template.md)


## lib and project

- util
    - [dlogger](/util/dlogger/README.md)
    - [progress_show](/util/progress_show/README.md)


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
cp -r boost/ /usr/include/
```