# Conda
This directory contains conda package description and recipies.

Conda: https://github.com/hutualive/conda

## Conda Installation

Install Miniconda with the default settings.

https://docs.conda.io/en/latest/miniconda.html

Uninstall via 'Add or remove programs' (Windows).

## Start
start > Anaconca prompt

getting started: https://conda.io/projects/conda/en/latest/user-guide/getting-started.html#starting-conda

Cheat-Sheet:
https://conda.io/projects/conda/en/latest/user-guide/cheatsheet.html

Check version:
```
conda --version
```
Update:
```
conda update conda
```
Or from a non-base environment:
```
conda update -n base -c defaults conda
```
## List environment
```
conda env list
```

getting started: https://conda.io/projects/conda/en/latest/user-guide/getting-started.html#starting-conda

## Create environment
```
conda create -n myenv
``` 

## Activate environment
```
conda activate myenv
``` 

## Delete environment
```
conda deactivate
conda env remove --name myenv
````

## Search package
```
conda search cmake
``` 

## List installed packages
```
conda list
``` 

## Install/uninstall packages
```
conda install cmake
conda install cmake=3.26.4
``` 
```
conda uninstall cmake
``` 

```
conda env update -f environment.yml
```
## Creating packages
Do it in a dedicated environment!
```
conda install conda-build 
```

Create directory with
- meta.yaml
- build.bat
- build.sh

SHA256 file checksum: https://emn178.github.io/online-tools/sha256_checksum.html

cd into directory:
```
conda config --set anaconda_upload no
conda-build .
```
Note: powershell: conda-build, normal shell: conda build

```
conda deactivate
conda create -n test
conda activate test
```
Install from build environment:
```
conda install -c C:\Users\erich\miniconda3\envs\build\conda-bld ninja gcc-arm* 
```
Or (if package is built in same environment):
```
conda install --use-local ninja
```

Directly install from package (file is in C:\Users\erich\miniconda3\envs\build\conda-bld\win-64):
```
conda install --no-deps .\ninja-1.11.11-0.tar.bz2
```
## Other
'where' in PowerShell:
```
(Get-Command ninja.exe).Path
```
## Links
- https://github.com/hutualive/conda/tree/master
- https://interrupt.memfault.com/blog/conda-developer-environments

