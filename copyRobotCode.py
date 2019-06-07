from shutil import copyfile


def main():
    shutil.copy2('/SwarmboTron/src/motorDriver.cpp', '/', follow_symlinks=True)
    shutil.copy2('/SwarmboTron/src/motorDriver.h', 'SwarmboTron', follow_symlinks=True)