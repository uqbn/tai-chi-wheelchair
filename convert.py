#!/usr/bin/env python
import os


def convrt(filename):
    try:
        with open(filename, "r", encoding="gbk") as f:
            data = f.read()
        if '.c' in filename or '.h' in filename:
            data = data.replace('\t', "    ")
            while " \n" in data:
                data = data.replace(" \n", '\n')
            with open(filename, "wb") as f:
                f.write(data.encode(encoding="utf-8"))
            print(filename)
    except Exception as e:
        return


def listdir(pwd="."):
    if pwd[-1] != '\\' or pwd[-1] != '/':
        pwd += '/'
    for name in os.listdir(pwd):
        if os.path.isdir(pwd + name):
            listdir(pwd + name)
        if os.path.isfile(pwd + name):
            convrt(pwd + name)


if __name__ == "__main__":
    listdir(".")
