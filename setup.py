from setuptools import setup, Extension
import os

qctSource = [os.path.join("isomerNum","ln_quickCount.cpp"),
             os.path.join("isomerNum","quickCount.cpp")]
lsaSource = [os.path.join("isomerNum","ln_listAll.cpp"),
             os.path.join("isomerNum","listAll.cpp")]

setup(
    name = "isomerNum",
    ext_modules = [
        Extension("isomerNum.quickCount", sources=qctSource, language="c++"),
        Extension("isomerNum.listAll", sources=lsaSource, language="c++")
    ],
    version = "0.0.1",
    license = "MIT Licence",
    description = "Calculate the number of organic isomers of the specified formula. "
                  "List all possible structural formulas in SMILES languages.",
    keywords = ["isomer", "calculation", "SMILES language"],
    author = "Bohan Cao & Jiang Rou"
)
